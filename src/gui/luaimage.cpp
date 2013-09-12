#include "luaimage.hpp"


namespace gui {
namespace luaimage {


SDL_Renderer *g_renderer; // global renderer to use


// Utility functions

FontData CheckRenderFontData(lua_State* _state)
{
	FontData res;
	//res.m_font = static_cast<TTF_Font*>(luaL_checkudata(_state, 1, FONT_METATABLE_NAME));
	res.m_font = static_cast<TTF_Font*>(lua_touserdata(_state, 1));
	res.m_text = static_cast<const char*>(luaL_checkstring(_state, 2));
	res.m_color.r = luaL_checkint(_state, 3);
	res.m_color.g = luaL_checkint(_state, 4);
	res.m_color.b = luaL_checkint(_state, 5);
	// alpha
	if(lua_isnumber(_state, 6))
		res.m_color.a = luaL_checkint(_state, 6);

	return res;
}

void CreateAndFillObjectMetatable(lua_State* _state, const char* _metatableName, luaL_Reg* _methods)
{
	// Create metatable
	luaL_newmetatable(_state, _metatableName);
	// Write methods into metatable, bad
	luaL_setfuncs(_state, _methods, 0);

	// Metatable itself as index
	lua_pushvalue(_state, -1);
	lua_setfield(_state, -2, "__index");

	lua_pop(_state, 1);
}


// API functions

// Args: path: string
// Rets: object: image userdata
int LoadImage(lua_State* _state)
{
	const char *filename = luaL_checkstring(_state, 1);
	SDL_Texture *tx = IMG_LoadTexture(g_renderer, filename);
	if(!tx)
	{
		// Replace with lua error later
		std::cerr << __FUNCTION__ << ": failed to load image: " << filename << std::endl;
		return 0;
	}
	
	PushLightUserdata(_state, tx, IMAGE_METATABLE_NAME);

	return 1;
}

// Args: path: string; font size: int
// Rets: object: font userdata
int LoadFont(lua_State* _state)
{
	const char *filename = luaL_checkstring(_state, 1);
	int fontSize = luaL_checkint(_state, 2);
	TTF_Font *font = TTF_OpenFont(filename, fontSize);
	if(!font)
	{
		// Replace with lua error later
		std::cerr << __FUNCTION__ << ": failed to load font: " << filename << std::endl;
		return 0;
	}

	//PushLightUserdata(_state, font, FONT_METATABLE_NAME);
	lua_pushlightuserdata(_state, font);
	luaL_getmetatable(_state, FONT_METATABLE_NAME);
	lua_setmetatable(_state, -2);

	return 1;
}

// Args: font: font userdata; text: string; r, g, b: int
// Rets: object: image userdata
int RenderTextSolid(lua_State* _state)
{
	FontData fd = CheckRenderFontData(_state);
	SDL_Surface *sf = TTF_RenderText_Solid(fd.m_font, fd.m_text, fd.m_color);
	SDL_Texture *tx = SDL_CreateTextureFromSurface(g_renderer, sf);
	SDL_FreeSurface(sf);

	PushLightUserdata(_state, tx, IMAGE_METATABLE_NAME);
	return 1;
}

// Args: font: font userdata; text: string; r, g, b: int
// Rets: object: image userdata
int RenderTextBlended(lua_State* _state)
{
	FontData fd = CheckRenderFontData(_state);
	SDL_Surface *sf = TTF_RenderText_Solid(fd.m_font, fd.m_text, fd.m_color);
	SDL_Texture *tx = SDL_CreateTextureFromSurface(g_renderer, sf);
	SDL_FreeSurface(sf);

	PushLightUserdata(_state, tx, IMAGE_METATABLE_NAME);
	return 1;
}


// Image methods

// Args: object : image userdata
// Rets: none
int Image_free(lua_State* _state)
{
	SDL_Texture *tx = static_cast<SDL_Texture*>(luaL_checkudata(_state, 1, IMAGE_METATABLE_NAME));
	SDL_DestroyTexture(tx);

	std::cout << "DEBUG: " << __FUNCTION__ << " called." << std::endl;

	return 0;
}

// Args: object: image userdata; x, y: int; clip: table {x, y, w, h} (nil to draw whole image)
// Rets: none
int Image_draw(lua_State* _state)
{

	SDL_Texture *tx = static_cast<SDL_Texture*>(luaL_checkudata(_state,  1, IMAGE_METATABLE_NAME));

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

// Args: object: image userdata
// Rets: width, height: int
int Image_getDimensions(lua_State* _state)
{
	SDL_Texture *tx = static_cast<SDL_Texture*>(luaL_checkudata(_state,  1, IMAGE_METATABLE_NAME));

	int w, h;
	SDL_QueryTexture(tx, nullptr, nullptr, &w, &h);

	lua_pushinteger(_state, w);
	lua_pushinteger(_state, h);
	return 2;
}

// Args: object: image userdata
// Rets: width: int
int Image_getWidth(lua_State* _state)
{
	SDL_Texture *tx = static_cast<SDL_Texture*>(luaL_checkudata(_state,  1, IMAGE_METATABLE_NAME));

	int w;
	SDL_QueryTexture(tx, nullptr, nullptr, &w, nullptr);

	lua_pushinteger(_state, w);
	return 1;
}

// Args: object: image userdata
// Rets: height: int
int Image_getHeight(lua_State* _state)
{
	SDL_Texture *tx = static_cast<SDL_Texture*>(luaL_checkudata(_state,  1, IMAGE_METATABLE_NAME));

	int h;
	SDL_QueryTexture(tx, nullptr, nullptr, nullptr, &h);

	lua_pushinteger(_state, h);
	return 1;
}


// Font methods

// Args: object : image userdata
// Rets: none
int Font_free(lua_State* _state)
{
	TTF_Font *font = static_cast<TTF_Font*>(luaL_checkudata(_state, 1, FONT_METATABLE_NAME));
	TTF_CloseFont(font);

	return 0;
}


// Load lib function

luaL_Reg imageMethods[] =
{
	{"free",			Image_free},
	{"draw",			Image_draw},
	{"getDimensions",	Image_getDimensions},
	{"getWidth",		Image_getWidth},
	{"getHeight",		Image_getHeight},
	{"__gc",			Image_free},
	{NULL, NULL}
};

luaL_Reg fontMethods[] =
{
	{"free",	Font_free},
	{"__gc",	Font_free},
	{NULL, NULL}
};

luaL_Reg apiFuncs[] =
{
	{"LoadImage",		LoadImage},
	{"LoadFont",		LoadFont},
	{"RenderTextSolid",	RenderTextSolid},
	{NULL, NULL}
};

void LoadLib(lua_State* _state, SDL_Renderer* _ren)
{
	g_renderer = _ren;

	std::cout << __FUNCTION__ << ": stack size before: " << lua_gettop(_state) << std::endl;

	// Loading image-related api functions
	lua_getglobal(_state, "api");
	luaL_setfuncs(_state, apiFuncs, 0);
	lua_pop(_state, 1);

	CreateAndFillObjectMetatable(_state, IMAGE_METATABLE_NAME, imageMethods);
	CreateAndFillObjectMetatable(_state, FONT_METATABLE_NAME, fontMethods);

	std::cout << __FUNCTION__ << ": stack size after:  " << lua_gettop(_state) << std::endl;
}


} // namespace luaimage
} // namespace gui