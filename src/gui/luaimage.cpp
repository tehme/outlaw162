#include "luaimage.hpp"


namespace gui {
namespace luaimage {


SDL_Renderer *g_renderer; // global renderer to use


// API functions

// Args: path: string
// Rets: object: image userdata
int Image_LoadImage(lua_State* _state)
{
	SDL_Texture *tx = IMG_LoadTexture(g_renderer, lua_tostring(_state, 1));
	if(!tx)
	{
		std::cout << "NO TEXTURE!" << std::endl;
		system("pause");
	}
	lua_pushlightuserdata(_state, tx);
	luaL_getmetatable(_state, "interface_image");
	lua_setmetatable(_state, -2);

	return 1;
}


// Image methods

// Args: object : image userdata
// Rets: none
int Image_free(lua_State* _state)
{
	SDL_Texture *tx = static_cast<SDL_Texture*>(luaL_checkudata(_state, 1, "interface_image"));
	SDL_DestroyTexture(tx);

	return 0;
}

// Args: object: image userdata; x, y: int; clip: table {x, y, w, h} (nil to draw whole image)
// Rets: none
int Image_draw(lua_State* _state)
{

	SDL_Texture *tx = static_cast<SDL_Texture*>(luaL_checkudata(_state,  1, "interface_image"));

	SDL_Rect srcRect, dstRect;

	dstRect.x = luaL_checkint(_state, 2);
	dstRect.y = luaL_checkint(_state, 3);

	bool clipGiven = lua_istable(_state, 4);
	if(clipGiven)
	{
		lua_getfield(_state, 4, "x");
		srcRect.x = luaL_checkint(_state, -1);
		lua_getfield(_state, 4, "y");
		srcRect.y = luaL_checkint(_state, -1);
		lua_getfield(_state, 4, "w");
		srcRect.w = luaL_checkint(_state, -1);
		lua_getfield(_state, 4, "h");
		srcRect.h = luaL_checkint(_state, -1);

		dstRect.w = srcRect.w;
		dstRect.h = srcRect.h;
	}
	else
		SDL_QueryTexture(tx, nullptr, nullptr, &dstRect.w, &dstRect.h);

	SDL_RenderCopy(g_renderer, tx, clipGiven ? &srcRect : nullptr, &dstRect);

	return 0;
}


luaL_Reg methods[] =
{
	{"free", Image_free},
	{"draw", Image_draw},
	{NULL, NULL}

};


void LoadLib(lua_State* _state, SDL_Renderer* _ren)
{
	g_renderer = _ren;

	// LoadImage to api table
	lua_getglobal(_state, "api");
	lua_pushcfunction(_state, Image_LoadImage);
	lua_setfield(_state, -2, "LoadImage");

	// metatable
	luaL_newmetatable(_state, "interface_image");

	// methods table
	luaL_newlib(_state, methods);

	// methods to metatable
	//lua_setfield(_state, -2, "methods");

	// methods as index
	lua_setfield(_state, -2, "__index");
}


} // namespace luaimage
} // namespace gui