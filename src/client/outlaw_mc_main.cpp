#include <iostream>
#include <iomanip>
#include <map>

#include <sdl2/SDL.h>
#include <sdl2/SDL_net.h>
#include <sdl2/SDL_image.h>

#include <boost/thread.hpp>
#include <boost/timer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/lockfree/spsc_queue.hpp>

//#include "../protocol/protocol.hpp"
//#include "chunk.hpp"
#include "protocol/protocol.hpp"

using namespace protocol;
using namespace protocol::msg;

struct ClientInfo
{
	bool m_initialPosGot;
	PlayerPositionAndLook m_playerPosLook;
	TCPsocket m_socket;

	float m_hp;

	ClientInfo()
		:	m_initialPosGot(false)
		,	m_socket(nullptr)
		,	m_hp(0.0)
	{}
};



std::map<uint8_t, std::function<size_t(const BinaryBuffer&, size_t, ClientInfo&)>> g_callbacks;

ClientInfo g_clientInfo;


// CALLBACKS, move

size_t Handler_0x00_KeepAlive(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
{
	std::cout << "Keep alive!" << std::endl;
	return KeepAlive().deserialize(_src, _offset);
}

size_t Handler_0x03_Chat(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
{
	ChatMessage chatMsg;
	_offset = chatMsg.deserialize(_src, _offset);
	std::wcout << L"Chat message." << std::endl << chatMsg.get_jsonStr() << std::endl;
	return _offset;
}

size_t Handler_0x06_SpawnPosition(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
{
	SpawnPosition sp;
	_offset = sp.deserialize(_src, _offset);
	std::cout << "Spawn Position: " << sp.get_x() << " " << sp.get_y() << " " << sp.get_z() << std::endl;
	return _offset;
}

size_t Handler_0x08_UpdateHealth(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
{
	UpdateHealth tmp;
	_offset = tmp.deserialize(_src, _offset);
	std::cout << "Health updated! Health: " << tmp.get_health() << "; Food: " << tmp.get_food() << std::endl;
	_clientInfo.m_hp = tmp.get_health();

	return _offset;
}

size_t Handler_0x0D_PlayerPositionAndLook(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
{
	if(_clientInfo.m_initialPosGot == false)
		_clientInfo.m_initialPosGot = true;

	_offset = _clientInfo.m_playerPosLook.deserialize_stc(_src, _offset);

	std::cout	<< "Player position: " 
				<< _clientInfo.m_playerPosLook.get_x() << " "
				<< _clientInfo.m_playerPosLook.get_y() << " "
				<< _clientInfo.m_playerPosLook.get_z() << std::endl;

	return _offset;
}

size_t Handler_0x38_MapChunkBulk(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
{
	protocol::msg::MapChunkBulk tmp;
	_offset = tmp.deserialize(_src, _offset);

	std::cout << "-------- 0x38 --------\nColumns: " << tmp.get_chunkColumnCount() << std::endl;

	auto meta = tmp.get_metaInformation();
	for(auto itr = meta.begin(); itr != meta.end(); ++itr)
		std::cout << itr->m_chunkX << " " << itr->m_chunkZ << std::endl;
	std::cout << std::endl;

	return _offset;
}


size_t Handler_0xFF_DisconnectOrKick(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
{
	DisconnectOrKick dok;
	_offset = dok.deserialize(_src, _offset);
	std::cout << "Disconnected." << std::endl;

	return _offset;
}

//------------------------------------------------------------------------------

// packet is received block, message is real object
typedef boost::lockfree::spsc_queue<std::vector<uint8_t>> LockfreePacketQueue;

void Thread_RecvMessages(TCPsocket _socket, LockfreePacketQueue& _msgPartsQueue)
{
	uint8_t buf[20480];
	int size;

	while((size = SDLNet_TCP_Recv(_socket, buf, 20480)) > 0) // 0 is closed socket, -1 is error
	{
		_msgPartsQueue.push(std::vector<uint8_t>(buf, buf + size));

		SDL_Event msgEv;
		msgEv.type = SDL_USEREVENT;
		msgEv.user.code = 10; // MAGIC, replace with enum
		msgEv.user.data1 = &_msgPartsQueue;
		SDL_PushEvent(&msgEv);	
	}

	std::cout << "Exitting recv thread." << std::endl;
}


void ApplyTexture(SDL_Renderer* _ren, int _x, int _y, SDL_Texture* _tex, SDL_Rect* _clip = nullptr)
{
	SDL_Rect pos;
	pos.x = _x;
	pos.y = _y;
	
	if(_clip)
	{
		pos.w = _clip->w;
		pos.h = _clip->h;
	}
	else
		SDL_QueryTexture(_tex, NULL, NULL, &pos.w, &pos.h);

	SDL_RenderCopy(_ren, _tex, _clip, &pos);
}


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	IMG_Init(IMG_INIT_PNG);

	BinaryBuffer outputBuf, inputBuf;

	// Initial message
	Handshake(74, L"Tester3", L"localhost", 25565).serialize(outputBuf);
	ClientStatuses(0).serialize(outputBuf);

	// Network part
	IPaddress ip;
	SDLNet_ResolveHost(&ip, "192.168.1.11", 25565);
	g_clientInfo.m_socket = SDLNet_TCP_Open(&ip);
	if(!g_clientInfo.m_socket)
	{
		//std::cout << "Failed to connect." << std::endl;
		std::cout << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	std::cout << "Connected!" << std::endl;
	SDLNet_TCP_Send(g_clientInfo.m_socket, outputBuf.data(), outputBuf.size());


	// Graphics part

	SDL_Window *mainWindow = SDL_CreateWindow("Outlaw", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		800, 600, SDL_WINDOW_SHOWN);

	SDL_Renderer *ren = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Texture *healthCellFullTx	= IMG_LoadTexture(ren, "res/healthcell_full.png");
	SDL_Texture *healthCellEmptyTx	= IMG_LoadTexture(ren, "res/healthcell_empty.png");
	SDL_Texture *healthBarTx		= IMG_LoadTexture(ren, "res/healthbar.png");

	SDL_Texture *tx_healthLineFull	= IMG_LoadTexture(ren, "res/healthline_full.png");
	SDL_Texture *tx_healthLineEmpty	= IMG_LoadTexture(ren, "res/healthline_empty.png");

	// Callbacks part
	
	g_callbacks[0x00] = Handler_0x00_KeepAlive;
	g_callbacks[0x03] = Handler_0x03_Chat;
	g_callbacks[0x06] = Handler_0x06_SpawnPosition;
	g_callbacks[0x08] = Handler_0x08_UpdateHealth;
	g_callbacks[0x0D] = Handler_0x0D_PlayerPositionAndLook;
	g_callbacks[0x38] = Handler_0x38_MapChunkBulk;
	g_callbacks[0xFF] = Handler_0xFF_DisconnectOrKick;

	// Main loop part

	bool quit = false;
	SDL_Event ev;
	LockfreePacketQueue msgParts(1000); // number is random, tweak later

	std::vector<uint8_t> tmpVec;

	inputBuf.reserve(102480);

	boost::thread recvThread(boost::bind(&Thread_RecvMessages, g_clientInfo.m_socket, boost::ref(msgParts)));
	boost::timer timer_sendPos;

	bool freeze = false;

	// main loop
	while(!quit)
	{
		// ---- Event handling ----
		while(SDL_PollEvent(&ev))
		{
			if(ev.type == SDL_QUIT)
			{
				quit = true;
				break;
			}

			else if(ev.type == SDL_KEYDOWN)
			{
				if(ev.key.keysym.sym == SDLK_SPACE)
				{
					freeze = !freeze;
				}
			}

			else if(ev.type == SDL_USEREVENT)
			{			
				//msgParts.pop(tmpVec);
				static_cast<LockfreePacketQueue*>(ev.user.data1)->pop(tmpVec);
				inputBuf.insert(inputBuf.end(), tmpVec.begin(), tmpVec.end()); // COPIES COPIES
				
			}
		}

		// ---- Logic ----
		//HandleMessages(inputBuf);
		HandleMessages(inputBuf, g_callbacks, g_clientInfo);

		// Sending position
		if(g_clientInfo.m_initialPosGot && !freeze && timer_sendPos.elapsed() >= 0.05)
		{
			timer_sendPos.restart();
			outputBuf.clear();
			g_clientInfo.m_playerPosLook.serialize(outputBuf);
			SDLNet_TCP_Send(g_clientInfo.m_socket, outputBuf.data(), outputBuf.size());
		}

		// ---- Drawing ----
		SDL_RenderClear(ren);
		
		ApplyTexture(ren, 10, 10, healthBarTx);

		int hpInt = int(g_clientInfo.m_hp * 10); // 200 max
		int hpLineLen = hpInt ;
		SDL_Rect fullHpRect;
		fullHpRect.x = 0;
		fullHpRect.y = 0;
		fullHpRect.w = hpLineLen;
		fullHpRect.h = 20;

		ApplyTexture(ren, 10 + 2, 10 + 2, tx_healthLineEmpty);
		ApplyTexture(ren, 10 + 2, 10 + 2, tx_healthLineFull, &fullHpRect);


		SDL_RenderPresent(ren);

		// Capping
		//SDL_Delay(1);
	}


	SDLNet_TCP_Close(g_clientInfo.m_socket);
	recvThread.join();
	SDLNet_Quit();

	SDL_DestroyTexture(healthCellFullTx);
	SDL_DestroyTexture(healthCellEmptyTx);
	SDL_DestroyTexture(tx_healthLineFull);
	SDL_DestroyTexture(tx_healthLineEmpty);
	SDL_DestroyTexture(healthBarTx);
	IMG_Quit();

	SDL_Quit();
	std::cout << "FINISH" << std::endl;
	//system("pause");
	return 0;
}