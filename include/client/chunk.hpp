#ifndef _CHUNK_HPP_
#define _CHUNK_HPP_

#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include "messages.hpp"


//template<class T>
//bool GetBitFromBitmask(const T& _bitmask, size_t _bitIndex)
//{
//	return (_bitmask >> _bitIndex) & 1;
//}


struct BlockData
{
	uint8_t m_blockType;
	uint8_t m_blockMetadata;	// 4 bits when arrives
	uint8_t m_blockLight;		// 4 bits when arrives
	uint8_t m_skyLight;			// only if 'skylight' is true; 4 bits when arrives
};

// 16x16x16 block, part of column
class Chunk
{
public:
	boost::multi_array<BlockData, 3> m_blocksData;
	boost::multi_array<uint8_t, 2> m_biomeData; // each element is 1 block column
	

	Chunk()
		:	m_blocksData(boost::extents[16][16][16]) // YZX
		,	m_biomeData(boost::extents[16][16]) // ZX
	{}

private:
	

};


// 16x256x16 block, 16 chunks
class ChunkColumn
{
public:
	void read(const std::vector<uint8_t>& _columnData);

private:
	boost::array<Chunk, 16> m_chunks;

};



void ChunkColumn::read(protocol::msg::ChunkColumnData& _columnDataMsg)
{
	

	// Creating chunks
	for(int i = 0; i < 16; ++i)
	{
		


	}
}


#endif // _CHUNK_HPP_