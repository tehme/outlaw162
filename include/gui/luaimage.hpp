#ifndef _GUI_LUAIMAGE_HPP_
#define _GUI_LUAIMAGE_HPP_

#include <iostream>
#include <lua/lua.hpp>
#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>


namespace gui {
namespace luaimage {


void LoadLib(lua_State* _state, SDL_Renderer* _ren);


} // namespace luaimage
} // namespace gui


#endif // _GUI_LUAIMAGE_HPP_


