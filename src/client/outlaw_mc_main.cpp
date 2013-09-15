// TODO:
// - world rendering
// - encryption
// - chat
// - buffer that handles offset automatically

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

#include <sdl2/SDL.h>
#include <sdl2/SDL_net.h>
#include <sdl2/SDL_image.h>

#include <boost/thread.hpp>
#include <boost/timer.hpp>
//#include <boost/lexical_cast.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/spsc_queue.hpp>

#include "protocol/protocol.hpp"
#include "gui/api.hpp"
#include "gui/luaimage.hpp"
#include "gfx.hpp"
#include "chunk.hpp"
#include "debug.hpp"


struct ClientInfo; // forward hack

//typedef std::function<size_t(const protocol::BinaryBuffer&, size_t, ClientInfo&)> MessageHandlerCallback;
typedef std::function<void(const protocol::BinaryBuffer&, ClientInfo&)> MessageHandlerCallback;

struct ClientInfo
{
	bool m_initialPosGot;
	protocol::msg::PlayerPositionAndLook m_playerPosLook;
	World m_world;

	std::map<uint8_t, MessageHandlerCallback> m_callbacks;

	lua_State *m_lstate;

	float m_hp;

	// Application state related part
	bool m_quit;

	// Network
	TCPsocket m_socket;
	protocol::BinaryBuffer m_inBuf, m_outBuf;


	ClientInfo()
		:	m_initialPosGot(false)
		,	m_socket(nullptr)
		,	m_hp(0.0)
		,	m_lstate(nullptr)

		,	m_quit(false)
	{}
};


ClientInfo g_clientInfo;


enum UserEventCode
{
	USEREVENT_RECVMESSAGE,
	USEREVENT_MAPRECEIVED,

};

// CALLBACKS, move

void Handler_0x00_KeepAlive(const protocol::BinaryBuffer& _src, ClientInfo& _clientInfo)
{
	static int nKeeps = 0;
	++nKeeps;
	std::cout << "Keep alive! " << nKeeps << std::endl;
	return protocol::msg::KeepAlive().deserialize(_src);
}

void Handler_0x03_Chat(const protocol::BinaryBuffer& _src, ClientInfo& _clientInfo)
{
	protocol::msg::ChatMessage chatMsg;
	chatMsg.deserialize(_src);
	std::wcout << L"Chat message." << std::endl << chatMsg.get_jsonStr() << std::endl;
}

void Handler_0x06_SpawnPosition(const protocol::BinaryBuffer& _src, ClientInfo& _clientInfo)
{
	protocol::msg::SpawnPosition sp;
	sp.deserialize(_src);
	std::cout << "Spawn Position: " << sp.get_x() << " " << sp.get_y() << " " << sp.get_z() << std::endl;
}

void Handler_0x08_UpdateHealth(const protocol::BinaryBuffer& _src, ClientInfo& _clientInfo)
{
	protocol::msg::UpdateHealth tmp;
	tmp.deserialize(_src);
	std::cout << "Health updated! Health: " << tmp.get_health() << "; Food: " << tmp.get_food() << std::endl;
	_clientInfo.m_hp = tmp.get_health();

	// Sending event to gui
	lua_pushinteger(_clientInfo.m_lstate, int(tmp.get_health() * 2));
	lua_pushinteger(_clientInfo.m_lstate, int(tmp.get_food() * 2));
	gui::api::FireEvent(_clientInfo.m_lstate, "EV_HEALTH_CHANGED", 2);
}

void Handler_0x0D_PlayerPositionAndLook(const protocol::BinaryBuffer& _src, ClientInfo& _clientInfo)
{
	if(!_clientInfo.m_initialPosGot)
		_clientInfo.m_initialPosGot = true;

	_clientInfo.m_playerPosLook.deserialize(_src);

	std::cout	<< "0x0D!\nPlayer position: " 
				<< _clientInfo.m_playerPosLook.get_x() << " "
				<< _clientInfo.m_playerPosLook.get_y() << " "
				<< _clientInfo.m_playerPosLook.get_z() << std::endl;
}

void Handler_0x35_BlockChange(const protocol::BinaryBuffer& _src, ClientInfo& _clientInfo)
{
	protocol::msg::BlockChange tmp;
	tmp.deserialize(_src);

	int16_t prevBlock = _clientInfo.m_world.getBlock(tmp.get_x(), tmp.get_y(), tmp.get_z()).m_type;

	try
	{
		_clientInfo.m_world.getBlock(tmp.get_x(), tmp.get_y(), tmp.get_z()).m_type = tmp.get_blockType();
		_clientInfo.m_world.getBlock(tmp.get_x(), tmp.get_y(), tmp.get_z()).m_metadata = tmp.get_blockMetadata();
	}
	catch(ColumnDoesNotExistException&)
	{
		BlockData block = { tmp.get_blockType(), tmp.get_blockMetadata(), 0, 0 };

		_clientInfo.m_world.scheduleBlockChange(tmp.get_x(), tmp.get_y(), tmp.get_z(), block);
		std::cout << "Scheduled!" << std::endl;
		return;
	}	

	std::cout	<< "Block changed! "
				<< tmp.get_x() << ' '
				<< static_cast<int>(tmp.get_y()) << ' '
				<< tmp.get_z() 
				<< ": " << prevBlock << " to " << tmp.get_blockType();
	
	if(tmp.get_blockMetadata())
		std::cout << ':' << static_cast<int>(tmp.get_blockMetadata());

	std::cout << std::endl;
}

void Handler_0x38_MapChunkBulk(const protocol::BinaryBuffer& _src, ClientInfo& _clientInfo)
{
	protocol::msg::MapChunkBulk tmp;
	tmp.deserialize(_src);
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
}

void Handler_0x6A_ConfirmTransaction(const protocol::BinaryBuffer& _src, ClientInfo& _clientInfo)
{
	protocol::msg::ConfirmTransaction tmp;
	tmp.deserialize(_src);
	std::cout << "Confirm Transaction works!" << std::endl;
}

void Handler_0xFF_DisconnectOrKick(const protocol::BinaryBuffer& _src, ClientInfo& _clientInfo)
{
	protocol::msg::DisconnectOrKick dok;
	dok.deserialize(_src);
	std::cout << "Disconnected." << std::endl;
}


//------------------------------------------------------------------------------

void LoadGUI(lua_State* _state, SDL_Renderer* _renderer, const std::string& _pathToMainGuiFile)
{
	luaL_openlibs(_state);
	gui::api::LoadLib(_state);
	gui::luaimage::LoadLib(_state, _renderer);
	if(luaL_dofile(_state, _pathToMainGuiFile.c_str()))
	{
		std::cerr << __FUNCTION__ << ": " << lua_tostring(_state, -1) << std::endl;
		lua_pop(_state, 1);
	}
}

void SetMessageHandlers(std::map<uint8_t, MessageHandlerCallback>& _callbacksMap)
{
	_callbacksMap[0x00] = Handler_0x00_KeepAlive;
	_callbacksMap[0x03] = Handler_0x03_Chat;
	_callbacksMap[0x06] = Handler_0x06_SpawnPosition;
	_callbacksMap[0x08] = Handler_0x08_UpdateHealth;
	_callbacksMap[0x0D] = Handler_0x0D_PlayerPositionAndLook;
	//_callbacksMap[0x35] = Handler_0x35_BlockChange;
	//_callbacksMap[0x38] = Handler_0x38_MapChunkBulk;
	//_callbacksMap[0x38] = Handler_Log0x38;
	_callbacksMap[0xFF] = Handler_0xFF_DisconnectOrKick;
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


void AppInit()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLNet_Init();
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();
}

void AppQuit()
{
	SDLNet_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


// Main loop utilities

void HandleEvent(const SDL_Event& _ev, ClientInfo& _clientInfo)
{
	if(_ev.type == SDL_QUIT)
		_clientInfo.m_quit = true;

	else if(_ev.type == SDL_KEYDOWN)
	{
		if(_ev.key.keysym.sym == SDLK_z)
		{
			int x = RoundWorldCoord(g_clientInfo.m_playerPosLook.get_x());
			int y = RoundWorldCoord(g_clientInfo.m_playerPosLook.get_y()) - 1;
			int z = RoundWorldCoord(g_clientInfo.m_playerPosLook.get_z());

			const BlockData &block = g_clientInfo.m_world.getBlock(x, y, z);

			std::cout<< x << ' ' << y << ' '<< z << " Block type: " << block.m_type << std::endl;
		}
	}

	else if(_ev.type == SDL_USEREVENT)
	{
		if(_ev.user.code == USEREVENT_RECVMESSAGE)
		{
			static std::vector<uint8_t> msgBuf;
			static_cast<LockfreePacketQueue*>(_ev.user.data1)->pop(msgBuf);
			//_clientInfo.m_inBuf.insert(_clientInfo.m_inBuf.end(), msgBuf.begin(), msgBuf.end());
			_clientInfo.m_inBuf.addData(msgBuf);
		}

		else if(_ev.user.code == USEREVENT_MAPRECEIVED)
		{
		}


	}
}


void Logic_SendPosition(ClientInfo& _clientInfo)
{
	_clientInfo.m_outBuf.clear();
	_clientInfo.m_playerPosLook.serialize(_clientInfo.m_outBuf);
	SDLNet_TCP_Send(_clientInfo.m_socket, _clientInfo.m_outBuf.getFlatData(), _clientInfo.m_outBuf.getSize());
}



int main(int argc, char* argv[])
{
	AppInit();

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
		return 1;
	}
	std::cout << "Connected!" << std::endl;

	// Initial message
	protocol::msg::Handshake(74, std::wstring(username.begin(), username.end()), 
		std::wstring(host.begin(), host.end()), port).serialize(g_clientInfo.m_outBuf);
	protocol::msg::ClientStatuses(0).serialize(g_clientInfo.m_outBuf);
	SDLNet_TCP_Send(g_clientInfo.m_socket, g_clientInfo.m_outBuf.getFlatData(), g_clientInfo.m_outBuf.getSize());


	// Graphics part

	SDL_Window *mainWindow = SDL_CreateWindow("Outlaw", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		800, 600, SDL_WINDOW_SHOWN);

	SDL_Renderer *ren = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Callbacks part
	SetMessageHandlers(g_clientInfo.m_callbacks);

	// GUI part
	g_clientInfo.m_lstate = luaL_newstate();
	LoadGUI(g_clientInfo.m_lstate, ren, "healthbar.lua");

	// Main loop part

	SDL_Event ev;
	LockfreePacketQueue msgParts(1000); // number is random, tweak later

	std::vector<uint8_t> tmpVec;

	g_clientInfo.m_inBuf.reserve(102480);

	boost::thread recvThread(boost::bind(&Thread_RecvMessages, g_clientInfo.m_socket, boost::ref(msgParts)));
	boost::timer timer_sendPos;

	bool mapReceived = false;

	// main loop
	while(!g_clientInfo.m_quit)
	{
		// ---- Event handling ----
		while(SDL_PollEvent(&ev))
		{
			HandleEvent(ev, g_clientInfo);
		}

		// ---- Logic ----
		protocol::HandleMessages(g_clientInfo.m_inBuf, g_clientInfo.m_callbacks, g_clientInfo); // bad!

		// Sending position
		if(g_clientInfo.m_initialPosGot && timer_sendPos.elapsed() >= 0.05)
		{
			timer_sendPos.restart();
			Logic_SendPosition(g_clientInfo);
		}

		// ---- Drawing ----
		SDL_RenderClear(ren);
		gui::api::FireEvent(g_clientInfo.m_lstate, "EV_DRAW", 0);
		SDL_RenderPresent(ren);
	}

	lua_close(g_clientInfo.m_lstate); // destructor in g_clientInfo may be better
	recvThread.interrupt(); // bad, but better than trying to access closed socket
	SDLNet_TCP_Close(g_clientInfo.m_socket);

	AppQuit();

	return 0;
}