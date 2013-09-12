#include "api.hpp"



namespace interface {
namespace api {


SDL_Surface *sf = NULL;

// ---- Utility subsection; not listed in header ----
namespace
{


}


// ---- Events subsection ----

// Args: object : table; event name : string
// Rets: none
// This function assumes subscribers table exists.
int Subscribe(lua_State* _state)
{
	//luaL_checktype(_state, 1, LUA_TTABLE); // raises error if arg is not a table

	lua_getglobal(_state, "api");
	lua_getfield(_state, -1, "subscribers");

	lua_pushvalue(_state, 2);
	lua_gettable(_state, -2);

	// Create list of subscribers as value to given string key, if it does not exist
	if(lua_isnil(_state, -1))
	{
		lua_pop(_state, 1); // throw out nil value
		lua_pushvalue(_state, 2);
		lua_newtable(_state);
		lua_rawset(_state, -3);

		// To make similar stack state after doing in both cases
		lua_pushvalue(_state, 2);
		lua_gettable(_state, -2);
	}

	lua_pushvalue(_state, 1); // subscriber is key
	lua_pushboolean(_state, true);
	lua_settable(_state, -3);

	return 0;
}


// Args: object : frame; event name : string
// Rets: none
// This function assumes subscribers table exists.
int Unsubscribe(lua_State* _state)
{
	lua_getglobal(_state, "api");
	lua_getfield(_state, -1, "subscribers");

	lua_pushvalue(_state, 2);
	lua_gettable(_state, -2); // event table is on top

	if(lua_isnil(_state, -1))
	{
		std::cout << "ZERO" << std::endl;
		return 0;
	}

	lua_pushvalue(_state, 1); // subscriber is key
	lua_pushnil(_state);
	lua_settable(_state, -3);

	return 0;
}


//--------

// Equivalent to:
// for k,v in pairs(api.subscribers[_eventName]) do k[_eventName](...) end
//void FireEvent(lua_State* _state, const std::string& _eventName, int _nArgs)
//{
//	// If there are 0 args, bot > top, hence push-up loop will not start.
//	int argsTop = lua_gettop(_state); // Args end here
//	int argsBot = argsTop - _nArgs + 1; // Args start here
//
//	lua_getglobal(_state, "api");
//	lua_getfield(_state, -1, "subscribers");
//	lua_getfield(_state, -1, _eventName.c_str());
//
//	// If table with event's name is not found, there are no subscribers.
//	if(lua_isnil(_state, -1))
//	{
//		lua_pop(_state, 3 + _nArgs);
//		return;
//	}
//
//	// Iterating through subscribers table
//	lua_pushnil(_state); // first key wtf
//	while(lua_next(_state, -2) != 0)
//	{
//		lua_pop(_state, 1); // we don't need value; subscriber table (key) is on top
//
//		lua_pushstring(_state, _eventName.c_str());
//		//lua_rawget(_state, -2); // or gettable; handler is on top
//		lua_gettable(_state, -2);
//		
//		// Pushing args up, rework later if possible
//
//		// Subscriber
//		lua_pushvalue(_state, -2);
//		// Args
//		for(int i = argsBot; i <= argsTop; ++i)
//			lua_pushvalue(_state, i);
//
//		// Call
//		lua_pcall(_state, _nArgs + 1, 0, 0);
//
//		if(lua_isstring(_state, -1))
//		{
//			std::cerr << __FUNCTION__ << ": " << lua_tostring(_state, -1) << std::endl;
//			lua_pop(_state, 1);
//		}
//	}
//
//	lua_pop(_state, 3 + _nArgs);
//}

// Equivalent to:
// for k,v in pairs(api.subscribers[_eventName]) do k[_eventName](...) end
void FireEvent(lua_State* _state, const std::string& _eventName, int _nArgs)
{
	// If there are 0 args, bot > top, hence push-up loop will not start.
	int argsTop = lua_gettop(_state); // Args end here
	int argsBot = argsTop - _nArgs + 1; // Args start here

	lua_getglobal(_state, "api");
	lua_getfield(_state, -1, "subscribers");
	lua_getfield(_state, -1, _eventName.c_str());

	// If table with event's name is not found, there are no subscribers.
	if(lua_isnil(_state, -1))
	{
		lua_pop(_state, 3 + _nArgs);
		return;
	}

	// Iterating through subscribers table
	lua_pushnil(_state); // first key wtf
	while(lua_next(_state, -2) != 0)
	{
		lua_pop(_state, 1); // we don't need value; subscriber table (key) is on top

		lua_getfield(_state, -1, "onEvent"); // handler is on top
		if(lua_isnil(_state, -1))
		{
			std::cout << "NO FUNCTION!!!" << std::endl;
			system("pause");
		}

		// Pushing args up, rework later if possible

		// Subscriber
		lua_pushvalue(_state, -2);
		// Event name
		lua_pushstring(_state, _eventName.c_str());
		// Args
		for(int i = argsBot; i <= argsTop; ++i)
			lua_pushvalue(_state, i);

		// Call
		lua_pcall(_state, _nArgs + 2, 0, 0);

		if(lua_isstring(_state, -1))
		{
			std::cerr << __FUNCTION__ << ": " << lua_tostring(_state, -1) << std::endl;
			lua_pop(_state, 1);
		}
	}

	lua_pop(_state, 3 + _nArgs);
}


// ---- Management subsection ----

namespace
{

bool loaded = false;

luaL_Reg apiFuncs[] =
{
	{"Subscribe",		Subscribe},
	{"Unsubscribe",		Unsubscribe},

	{NULL, NULL}
};

}


// Does not fit lua function prototype.
void LoadLib(lua_State* _state)
{
	if(loaded)
		return;
	loaded = true;

	luaL_newlib(_state, apiFuncs);

	// Creating table for subscribers
	lua_newtable(_state);
	lua_setfield(_state, -2, "subscribers");

	lua_setglobal(_state, "api");
}

} // namespace api
} // namespace interface