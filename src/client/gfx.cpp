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


// Assumes that heights 2d array is 16x16 and filled with zeroes
void BuildColumnHeightsMap(const ChunkColumn& _col, boost::multi_array<int, 2>& _heights)
{
	int nFilled = 0;
	for(int y = 0; y < 256; ++y)
	{
		for(int z = 0; z < 16; ++z)
			for(int x = 0; x < 16; ++x)
				if(_heights[z][x] == 0 && _col.getBlock(x, y, z).m_type == 0)
				{
					_heights[z][x] = y;
					++nFilled;	
				}

		if(nFilled == 256)
			break;
	}
}

SDL_Texture* RenderColumnHeightsTexture(SDL_Renderer* _ren, int _blockSidePx, const ChunkColumn& _col)
{
	boost::multi_array<int, 2> heights(boost::extents[16][16]);
	BuildColumnHeightsMap(_col, heights);

	SDL_Surface *surf = SDL_CreateRGBSurface(0, _blockSidePx * 16, _blockSidePx * 16, 32, 0, 0, 0, 0);

	// notchian x points south, z points west; YZX // XY
	SDL_Rect rect;
	rect.w = rect.h = _blockSidePx;
	for(int y = 0; y < 16; ++y)
			for(int x = 0; x < 16; ++x)
			{
				rect.x = (16 - x - 1) * _blockSidePx;
				rect.y = y * _blockSidePx;

				SDL_FillRect(surf, &rect, SDL_MapRGBA(surf->format, 0, heights[x][y], 0, 255));
			}

	SDL_Texture *tx = SDL_CreateTextureFromSurface(_ren, surf);
	SDL_FreeSurface(surf);

	return tx;	
}


SDL_Texture* RenderHeightTexture(SDL_Renderer* _ren, const World& _world)
{
	SDL_Surface *surf = SDL_CreateRGBSurface(0, 640, 640, 32, 0, 0, 0, 0);

	SDL_Rect rect;
	rect.w = rect.h = 2;

	int minX = INT_MAX, minZ = INT_MAX;
	//_world.m_columnsMap
	for(auto itr = _world.m_columnsMap.begin(); itr != _world.m_columnsMap.end(); ++itr)
	{
		minX = std::min(minX, itr->first.m_columnX);
		minZ = std::min(minZ, itr->first.m_columnZ);
	}

	// Column coords to block coords
	minX *= 16; 
	minZ *= 16;

	// building height map (notchian coordinates)
	//boost::multi_array<int, 2> heights(boost::extents[320][320]);
	std::vector<int> heights(320 * 320, -1);

	//for(auto itr = _world.m_columnsMap.begin(); itr != _world.m_columnsMap.end(); ++itr)
	//{
		for(int y = 128; y >= 0; --y)
		{
			static int nGot = 0;
			std::cout << y << std::endl;
			for(int z = minZ; z < minZ + 320; ++z)
				for(int x = minX; x < minX + 320; ++x)
				{
					
					if(heights[(z - minZ) * 320 + (x - minX)] == -1 && _world.getBlock(x, y, z).m_type != 0)
					{
						heights[(z - minZ) * 320 + (x - minX)] = y;
						++nGot;
					}
				}
			if(nGot == 320 * 320)
				break;
		}
	//}
	

	// In notchian coords X points South, and Z points West
	// In normal flat coords X points East, and Y points South
	// So, notchian X = flat Y; notchian Z = flat -X

	/*for(int y = 0; y < 320; ++y)
		for(int x = 0; x < 320; ++x)
		{
			rect.x = (320 - x - 1) * 2;
			rect.y = y * 2;
			SDL_FillRect(surf, &rect, SDL_MapRGBA(surf->format, 0, heights[x * 320 + y], 0, 255));
		}*/

	for(int x = 0; x < 320; ++x)
		for(int y = 0; y < 320; ++y)
		{
			rect.x = (320 - x - 1) * 2;
			rect.y = y * 2;
			SDL_FillRect(surf, &rect, SDL_MapRGBA(surf->format, 0, heights[x * 320 + y], 0, 255));
		}

		SDL_Texture *tx = SDL_CreateTextureFromSurface(_ren, surf);
		SDL_FreeSurface(surf);

		return tx;		
}