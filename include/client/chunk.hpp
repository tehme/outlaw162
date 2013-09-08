#ifndef _CHUNK_HPP_
#define _CHUNK_HPP_

#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include <cstdint>
#include <unordered_map>
#include <boost/timer.hpp>
#include <zlib/zlib.h>
#include "protocol/messages.hpp"
//#include "debug.hpp"


typedef std::vector<uint8_t>::const_iterator ByteVecConstItr;

void Inflate(const std::vector<uint8_t>& _src, std::vector<uint8_t>& _dst);


int WorldToColumnRel(int _worldCoord);
int WorldToColumnCoord(int _worldCoord);
int RoundWorldCoord(double _worldCoord);

/*int ColumnRelToWorld(int _relCoord, int _colCoord)
{
	return 
}*/


struct ChunkColumnID
{
	int32_t m_columnX;
	int32_t m_columnZ;

	ChunkColumnID(int32_t _columnX, int32_t _columnZ)
		:	m_columnX(_columnX)
		,	m_columnZ(_columnZ)
	{}

	bool operator==(const ChunkColumnID& _other) const
	{
		return _other.m_columnX == m_columnX && _other.m_columnZ == m_columnZ;
	}

};

namespace std {

template <>
struct hash<ChunkColumnID>
{
	size_t operator()(const ChunkColumnID& _subject) const
	{
		union {int32_t x; uint32_t ux;};
		x = _subject.m_columnX;
		union {int32_t z; uint32_t uz;};
		z = _subject.m_columnZ;

		size_t retr = 23;
		retr *= 31;
		retr += ux;
		retr *= 31;
		retr += uz;

		return retr;
	}
};

} // namespace std



struct BlockData
{
	uint16_t m_type;
	uint8_t m_metadata;		// 4 bits when arrives
	uint8_t m_blockLight;	// 4 bits when arrives
	uint8_t m_skyLight;		// only if 'skylight' is true; 4 bits when arrives
};


// 16x256x16 block, 16 chunks
class ChunkColumn
{
public:
	ChunkColumn()
		//:	m_columnData(boost::extents[256][16][16]) // YZX
	{ /*static int instances = 0; ++instances; std::cout << "Columns exist: " << instances << std::endl;*/ }

	// Copy ctr
	ChunkColumn(const ChunkColumn& _other);

	~ChunkColumn()
	{
		//std::cout << "COLUMN DESTRUCTED!" << std::endl;
		//system("pause");
	}

	size_t load(std::vector<uint8_t>& _src, size_t _offset, int _nNonAirChunks);

	inline BlockData& getBlockByRelCoords(int _relX, int _relY, int _relZ)
	{
		return m_columnData[_relY * 256 + _relZ * 16 + _relX];
	}

	inline const BlockData& getBlockByRelCoords(int _relX, int _relY, int _relZ) const
	{
		return m_columnData[_relY * 256 + _relZ * 16 + _relX];
	}

	//boost::multi_array<BlockData, 3> m_columnData;
	boost::array<BlockData, 256 * 16 * 16> m_columnData; // flat representation of 3d array
};



// rename
class World
{
public:
	World(){}

	~World()
	{
		for(auto itr = m_columnsMap.begin(); itr != m_columnsMap.end(); ++itr)
			delete itr->second;
	}

	std::unordered_map<ChunkColumnID, ChunkColumn*> m_columnsMap;

	void loadColumns(protocol::msg::MapChunkBulk& _columnsMsg);

	inline BlockData& getBlock(int _blockX, int _blockY, int _blockZ);
	inline const BlockData& getBlock(int _blockX, int _blockY, int _blockZ) const;

private:

};

//------------------------------------------------------------------------------

BlockData& World::getBlock(int _blockX, int _blockY, int _blockZ)
{
	return m_columnsMap.at(ChunkColumnID(WorldToColumnCoord(_blockX), WorldToColumnCoord(_blockZ)))
		->getBlockByRelCoords(WorldToColumnRel(_blockX), _blockY, WorldToColumnRel(_blockZ));
}

const BlockData& World::getBlock(int _blockX, int _blockY, int _blockZ) const
{
	return m_columnsMap.at(ChunkColumnID(WorldToColumnCoord(_blockX), WorldToColumnCoord(_blockZ)))
		->getBlockByRelCoords(WorldToColumnRel(_blockX), _blockY, WorldToColumnRel(_blockZ));
}

#endif // _CHUNK_HPP_