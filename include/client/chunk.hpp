#ifndef _CHUNK_HPP_
#define _CHUNK_HPP_

#include <unordered_map>
#include <queue>
#include <cstdint>
#include <boost/timer.hpp>
#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include <zlib/zlib.h>

#include "protocol/messages.hpp"


typedef std::vector<uint8_t>::const_iterator ByteVecConstItr;

void Inflate(const std::vector<uint8_t>& _src, std::vector<uint8_t>& _dst);

// Exceptions
class ColumnDoesNotExistException {};

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
	//	:	m_columnDataRef(m_columnData.c_array(), boost::extents[256][16][16]) // YZX
	{}
	ChunkColumn(const ChunkColumn& _other);
	~ChunkColumn(){}


	size_t load(std::vector<uint8_t>& _src, size_t _offset, int _nNonAirChunks);

	size_t load(std::vector<uint8_t>& _src, size_t _offset, uint16_t _PrimBitmask, uint16_t _addBitmask);
	ByteVecConstItr load(ByteVecConstItr _begin, uint16_t _PrimBitmask, uint16_t _addBitmask);

	inline BlockData& getBlock(int _relX, int _relY, int _relZ);
	inline const BlockData& getBlock(int _relX, int _relY, int _relZ) const;
	

private:
	boost::array<BlockData, 256 * 16 * 16> m_columnData; // flat representation of 3d array
	

};


BlockData& ChunkColumn::getBlock(int _relX, int _relY, int _relZ)
{
	return m_columnData[_relY * 256 + _relZ * 16 + _relX];
	//return m_columnDataRef[_relY][_relZ][_relX];
	// boost multi array ref is too slow
}

const BlockData& ChunkColumn::getBlock(int _relX, int _relY, int _relZ) const
{
	return m_columnData[_relY * 256 + _relZ * 16 + _relX];
	//return m_columnDataRef[_relY][_relZ][_relX];
}



//------------------------------------------------------------------------------

struct ScheduledBlock
{
	int m_x, m_y, m_z;
	BlockData m_block;
};


class World
{
public:
	World(){}

	~World()
	{
		for(auto itr = m_columnsMap.begin(); itr != m_columnsMap.end(); ++itr)
			delete itr->second;
	}

	void loadColumns(protocol::msg::MapChunkBulk& _columnsMsg);

	inline BlockData& getBlock(int _blockX, int _blockY, int _blockZ);
	inline const BlockData& getBlock(int _blockX, int _blockY, int _blockZ) const;

	// If column that block belongs to does not exist when change block message arrived,
	// this can be used to change block when column appears.
	// Will be called automatically when anyone tries to change block in non-existent column.
	// Move to private?
	void scheduleBlockChange(int _blockX, int _blockY, int _blockZ, BlockData _newBlock);

private:
	std::unordered_map<ChunkColumnID, ChunkColumn*> m_columnsMap;
	// Merge with columns?
	std::unordered_map<ChunkColumnID, std::queue<ScheduledBlock>> m_scheduledBlocks;

};

//------------------------------------------------------------------------------

BlockData& World::getBlock(int _blockX, int _blockY, int _blockZ)
{
	auto colItr = m_columnsMap.find(ChunkColumnID(WorldToColumnCoord(_blockX), WorldToColumnCoord(_blockZ)));
	if(colItr == m_columnsMap.end())
		throw ColumnDoesNotExistException();

	return colItr->second->getBlock(WorldToColumnRel(_blockX), _blockY, WorldToColumnRel(_blockZ));
}


const BlockData& World::getBlock(int _blockX, int _blockY, int _blockZ) const
{
	return const_cast<World*>(this)->getBlock(WorldToColumnRel(_blockX), _blockY, WorldToColumnRel(_blockZ));	
}



#endif // _CHUNK_HPP_