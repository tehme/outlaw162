#ifndef _CHUNK_HPP_
#define _CHUNK_HPP_

#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include <cstdint>
#include <unordered_map>
#include "protocol/messages.hpp"

#include <boost/timer.hpp>

#include <zlib/zlib.h>


typedef std::vector<uint8_t>::const_iterator ByteVecConstItr;

void Inflate(const std::vector<uint8_t>& _src, std::vector<uint8_t>& _dst);


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
		uint32_t x = static_cast<uint32_t>(_subject.m_columnX);
		uint32_t z = static_cast<uint32_t>(_subject.m_columnZ);

		size_t retr = 23;
		retr *= 31 + x;
		retr *= 31 + z;

		return retr;
	}
};

} // namespace std




struct BlockData
{
	uint8_t m_blockType;
	uint8_t m_blockMetadata;	// 4 bits when arrives
	uint8_t m_blockLight;		// 4 bits when arrives
	uint8_t m_skyLight;			// only if 'skylight' is true; 4 bits when arrives
	uint8_t m_add;				// 4 bits when arrives; ??? wtf is this?
};

// 16x16x16 block, part of column
struct Chunk
{
	boost::multi_array<BlockData, 3> m_blocksData;
	boost::multi_array<uint8_t, 2> m_biomeData; // each element is 16x1x1 YZX
	

	Chunk()
		:	m_blocksData(boost::extents[16][16][16]) // YZX
		,	m_biomeData(boost::extents[16][16]) // ZX
	{}
};


// 16x256x16 block, 16 chunks
typedef boost::array<Chunk, 16> ChunkColumn;

// rename
class World
{
public:
	World(){}


	void loadColumns(protocol::msg::MapChunkBulk& _columns);

private:
	std::unordered_map<ChunkColumnID, ChunkColumn> m_columnsMap;

	void fillChunkWithAir(Chunk& _dst);
	size_t loadChunkBlockTypes(std::vector<uint8_t>& _src, size_t _offset, Chunk& _dst);
	ByteVecConstItr loadChunkBlockTypes(ByteVecConstItr _begin, Chunk& _dst);
	size_t loadColumn(std::vector<uint8_t>& _src, size_t _offset, ChunkColumn& _dst, int _nChunks);
	ByteVecConstItr loadColumn(ByteVecConstItr _begin, ChunkColumn& _dst, int _nChunks);

};

//------------------------------------------------------------------------------


#endif // _CHUNK_HPP_