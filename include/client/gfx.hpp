#ifndef _GFX_HPP_
#define _GFX_HPP_


#include <sdl2/SDL.h>
#include "chunk.hpp"


void ApplyTexture(SDL_Renderer* _ren, int _x, int _y, SDL_Texture* _tex, SDL_Rect* _clip = nullptr);

// Assumes that heights 2d array is 16x16 and filled with zeroes
void BuildColumnHeightsMap(const ChunkColumn& _col, boost::multi_array<int, 2>& _heights);
SDL_Texture* RenderColumnHeightsTexture(SDL_Renderer* _ren, int _blockSidePx, const ChunkColumn& _col);

SDL_Texture* RenderHeightTexture(SDL_Renderer* _ren, const World& _world);


#endif // _GFX_HPP_