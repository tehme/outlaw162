#ifndef _INTERFACE_LUAIMAGE_HPP_
#define _INTERFACE_LUAIMAGE_HPP_

#include <iostream>
#include <lua/lua.hpp>
#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>


namespace interface {
namespace luaimage {


void LoadLib(lua_State* _state, SDL_Renderer* _ren);


} // namespace luaimage
} // namespace interface


#endif // _INTERFACE_LUAIMAGE_HPP_


