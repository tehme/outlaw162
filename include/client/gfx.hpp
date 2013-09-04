#ifndef _GFX_HPP_
#define _GFX_HPP_


#include <sdl2/SDL.h>


void ApplyTexture(SDL_Renderer* _ren, int _x, int _y, SDL_Texture* _tex, SDL_Rect* _clip = nullptr);


#endif // _GFX_HPP_