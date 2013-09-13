#ifndef _GUI_LUAIMAGE_HPP_
#define _GUI_LUAIMAGE_HPP_

#include <iostream>
#include <lua/lua.hpp>
#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <sdl2/SDL_ttf.h>


namespace gui {
namespace luaimage {

const char IMAGE_METATABLE_NAME[]	= "gui_image";
const char FONT_METATABLE_NAME[]	= "gui_font";

struct FontData
{
	TTF_Font *m_font;
	const char *m_text;
	SDL_Color m_color;
};

struct Image
{
	SDL_Texture *m_pData;
};

struct Font
{
	TTF_Font *m_pData;
};


// Template utilities

// Pushes light userdata to stack and sets its metatable
template<class T>
void PushLightUserdata(lua_State* _state, T* _data, const char* _metatableName)
{
	lua_pushlightuserdata(_state, _data);
	luaL_getmetatable(_state, _metatableName);
	lua_setmetatable(_state, -2);
}

template<class ContainerT, class DataT>
void PushUserdata(lua_State* _state, DataT* _data, const char* _metatableName)
{
	ContainerT *udata = static_cast<ContainerT*>(lua_newuserdata(_state, sizeof(ContainerT)));
	udata->m_pData = _data;
	luaL_getmetatable(_state, _metatableName);
	lua_setmetatable(_state, -2);
}

template<class ContainerT>
ContainerT* CheckUserdata(lua_State* _state, int _index, const char* _metatableName)
{
	return static_cast<ContainerT*>(luaL_checkudata(_state, _index, _metatableName));
}


void LoadLib(lua_State* _state, SDL_Renderer* _ren);


} // namespace luaimage
} // namespace gui


#endif // _GUI_LUAIMAGE_HPP_


