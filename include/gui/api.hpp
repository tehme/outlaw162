#ifndef _GUI_API_HPP_
#define _GUI_API_HPP_

#include <iostream>
#include <string>
#include <lua/lua.hpp>
#include <sdl2/SDL.h>



namespace gui {
namespace api {

// ---- Utility subsection ----

// Check if this works ok
template<class T>
T CheckSizedInt(lua_State* _state, int _stackPos)
{
	lua_Integer lint = luaL_checkinteger(_state, _stackPos);
	T res = lint;
	luaL_argcheck(_state, res == lint, _stackPos, "wrong integer size");

	return res;
}


//--------

// Equivalent to:
// for k,v in pairs(api.subscribers[_eventName]) do k[_eventName](...) end
void FireEvent(lua_State* _state, const std::string& _eventName, int _nArgs);


// ---- Management subsection ----

void LoadLib(lua_State* _state);


} // namespace api
} // namespace gui


#endif // _GUI_API_HPP_