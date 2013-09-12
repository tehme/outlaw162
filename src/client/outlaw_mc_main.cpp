#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

#include <sdl2/SDL.h>
#include <sdl2/SDL_net.h>
#include <sdl2/SDL_image.h>

#include <boost/thread.hpp>
#include <boost/timer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/spsc_queue.hpp>

#include "protocol/protocol.hpp"
#include "gui/api.hpp"
#include "gui/luaimage.hpp"
#include "gfx.hpp"
#include "chunk.hpp"
#include "debug.hpp"

using namespace protocol;
using namespace protocol::msg;


struct ClientInfo
{
	bool m_initialPosGot;
	PlayerPositionAndLook m_playerPosLook;
	TCPsocket m_socket;
	World m_world;
	bool m_locationLoaded; // temporary hack

	lua_State *m_lstate;

	float m_hp;

	ClientInfo()
		:	m_initialPosGot(false)
		,	m_socket(nullptr)
		,	m_hp(0.0)
		,	m_locationLoaded(false)
		,	m_lstate(nullptr)
	{}
};



std::map<uint8_t, std::function<size_t(const BinaryBuffer&, size_t, ClientInfo&)>> g_callbacks;

ClientInfo g_clientInfo;


enum UserEventCode
{
	USEREVENT_RECVMESSAGE,
	USEREVENT_MAPRECEIVED,

};

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

	// Sending event to gui
	lua_pushinteger(_clientInfo.m_lstate, int(tmp.get_health() * 2));
	gui::api::FireEvent(_clientInfo.m_lstate, "EV_HEALTH_CHANGED", 1);

	return _offset;
}

size_t Handler_0x0D_PlayerPositionAndLook(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
{
	if(_clientInfo.m_initialPosGot == false)
		_clientInfo.m_initialPosGot = true;

	_offset = _clientInfo.m_playerPosLook.deserialize(_src, _offset);

	std::cout	<< "0x0D!\nPlayer position: " 
				<< _clientInfo.m_playerPosLook.get_x() << " "
				<< _clientInfo.m_playerPosLook.get_y() << " "
				<< _clientInfo.m_playerPosLook.get_z() << std::endl;

	return _offset;
}

size_t Handler_0x35_BlockChange(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
{
	protocol::msg::BlockChange tmp;
	_offset = tmp.deserialize(_src, _offset);

	int16_t prevBlock = _clientInfo.m_world.getBlock(tmp.get_x(), tmp.get_y(), tmp.get_z()).m_type;

	try
	{
		_clientInfo.m_world.getBlock(tmp.get_x(), tmp.get_y(), tmp.get_z()).m_type = tmp.get_blockType();
		_clientInfo.m_world.getBlock(tmp.get_x(), tmp.get_y(), tmp.get_z()).m_metadata = tmp.get_blockMetadata();
	}
	catch(ColumnDoesNotExistException)
	{
		BlockData block = { tmp.get_blockType(), tmp.get_blockMetadata(), 0, 0 };

		_clientInfo.m_world.scheduleBlockChange(tmp.get_x(), tmp.get_y(), tmp.get_z(), block);
		std::cout << "Scheduled!" << std::endl;
		return _offset;
	}
	

	std::cout	<< "Block changed! " << tmp.get_x() << ' ' << int(tmp.get_y()) << ' ' << tmp.get_z() 
				<< ": " << prevBlock << " to " << tmp.get_blockType();
	
	if(tmp.get_blockMetadata())
		std::cout << ':' << int(tmp.get_blockMetadata());

	std::cout << std::endl;

	return _offset;
}

size_t Handler_0x38_MapChunkBulk(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
{
	protocol::msg::MapChunkBulk tmp;
	_offset = tmp.deserialize(_src, _offset);
	_clientInfo.m_world.loadColumns(tmp);

	static int nColumns = 0;
	nColumns += tmp.get_chunkColumnCount();
	if(nColumns == 400)
	{
		SDL_Event ev;
		ev.type = SDL_USEREVENT;
		ev.user.code = USEREVENT_MAPRECEIVED;
		SDL_PushEvent(&ev);
	}
	
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
		msgEv.user.code = USEREVENT_RECVMESSAGE;
		msgEv.user.data1 = &_msgPartsQueue;
		SDL_PushEvent(&msgEv);	
	}

	std::cout << "Exitting recv thread." << std::endl;
}


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	IMG_Init(IMG_INIT_PNG);

	BinaryBuffer outputBuf, inputBuf;

	std::string host, username;
	uint16_t port;

	std::cin >> host >> port >> username;

	// Network part
	IPaddress ip;
	SDLNet_ResolveHost(&ip, host.c_str(), port);
	g_clientInfo.m_socket = SDLNet_TCP_Open(&ip);
	if(!g_clientInfo.m_socket)
	{
		std::cout << SDL_GetError() << std::endl;
		system("pause");
		return 0;
	}

	// Initial message
	Handshake(74, std::wstring(username.begin(), username.end()), std::wstring(host.begin(), host.end()), port).serialize(outputBuf);
	ClientStatuses(0).serialize(outputBuf);

	std::cout << "Connected!" << std::endl;
	SDLNet_TCP_Send(g_clientInfo.m_socket, outputBuf.data(), outputBuf.size());


	// Graphics part

	SDL_Window *mainWindow = SDL_CreateWindow("Outlaw", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		800, 600, SDL_WINDOW_SHOWN);

	SDL_Renderer *ren = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Texture *tx_healthBar		= IMG_LoadTexture(ren, "res/healthbar.png");
	SDL_Texture *tx_healthLineFull	= IMG_LoadTexture(ren, "res/healthline_full.png");
	SDL_Texture *tx_healthLineEmpty	= IMG_LoadTexture(ren, "res/healthline_empty.png");
	SDL_Texture *tx_minimap			= nullptr;


	// Callbacks part
	
	g_callbacks[0x00] = Handler_0x00_KeepAlive;
	g_callbacks[0x03] = Handler_0x03_Chat;
	g_callbacks[0x06] = Handler_0x06_SpawnPosition;
	g_callbacks[0x08] = Handler_0x08_UpdateHealth;
	g_callbacks[0x0D] = Handler_0x0D_PlayerPositionAndLook;
	//g_callbacks[0x35] = Handler_0x35_BlockChange;
	//g_callbacks[0x38] = Handler_0x38_MapChunkBulk;
	//g_callbacks[0x38] = Handler_Log0x38;
	g_callbacks[0xFF] = Handler_0xFF_DisconnectOrKick;


	// Lua part
	g_clientInfo.m_lstate = luaL_newstate();
	luaL_openlibs(g_clientInfo.m_lstate);
	gui::api::LoadLib(g_clientInfo.m_lstate);
	gui::luaimage::LoadLib(g_clientInfo.m_lstate, ren);
	luaL_dofile(g_clientInfo.m_lstate, "interface.lua");



	// Main loop part

	bool quit = false;
	SDL_Event ev;
	LockfreePacketQueue msgParts(1000); // number is random, tweak later

	std::vector<uint8_t> tmpVec;

	inputBuf.reserve(102480);

	boost::thread recvThread(boost::bind(&Thread_RecvMessages, g_clientInfo.m_socket, boost::ref(msgParts)));
	boost::timer timer_sendPos;

	bool freeze = false;
	bool mapReceived = false;

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
				else if(ev.key.keysym.sym == SDLK_z)
				{
					int x = RoundWorldCoord(g_clientInfo.m_playerPosLook.get_x()),
						y = RoundWorldCoord(g_clientInfo.m_playerPosLook.get_y()) - 1,
						z = RoundWorldCoord(g_clientInfo.m_playerPosLook.get_z());

					const BlockData &block = g_clientInfo.m_world.getBlock(x, y, z);

					std::cout<< x << ' ' << y << ' '<< z << " Block type: " << block.m_type << std::endl;
				}
			}

			else if(ev.type == SDL_USEREVENT)
			{
				if(ev.user.code == USEREVENT_RECVMESSAGE)
				{
					static_cast<LockfreePacketQueue*>(ev.user.data1)->pop(tmpVec);
					inputBuf.insert(inputBuf.end(), tmpVec.begin(), tmpVec.end()); // COPIES COPIES
				}

				else if(ev.user.code == USEREVENT_MAPRECEIVED)
				{
					g_clientInfo.m_locationLoaded = true;
					//tx_minimap = RenderHeightTexture(ren, g_clientInfo.m_world);
					//mapReceived = true;

					int colX = WorldToColumnCoord(RoundWorldCoord(g_clientInfo.m_playerPosLook.get_x()));
					int colZ = WorldToColumnCoord(RoundWorldCoord(g_clientInfo.m_playerPosLook.get_z()));
					std::cout << colX << ' ' << colZ << std::endl;

					//tx_minimap = RenderColumnHeightsTexture(ren, 32, *g_clientInfo.m_world.m_columnsMap.at(ChunkColumnID(colX, colZ)));
					mapReceived = true;
				}
				
				
			}
		}

		// ---- Logic ----
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

		if(tx_minimap)
			ApplyTexture(ren, 0, 0, tx_minimap);

		gui::api::FireEvent(g_clientInfo.m_lstate, "EV_DRAW", 0);

		SDL_RenderPresent(ren);
	}


	SDLNet_TCP_Close(g_clientInfo.m_socket);
	//recvThread.join();
	SDLNet_Quit();

	SDL_DestroyTexture(tx_healthLineFull);
	SDL_DestroyTexture(tx_healthLineEmpty);
	SDL_DestroyTexture(tx_healthBar);
	IMG_Quit();

	SDL_Quit();

	lua_close(g_clientInfo.m_lstate); // destructor in g_clientInfo may be better

	return 0;
}