#include "gfx.hpp"


void ApplyTexture(SDL_Renderer* _ren, int _x, int _y, SDL_Texture* _tex, SDL_Rect* _clip)
{
	SDL_Rect pos;
	pos.x = _x;
	pos.y = _y;

	if(_clip)
	{
		pos.w = _clip->w;
		pos.h = _clip->h;
	}
	else
		SDL_QueryTexture(_tex, NULL, NULL, &pos.w, &pos.h);

	SDL_RenderCopy(_ren, _tex, _clip, &pos);
}