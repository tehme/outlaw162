#ifndef _CHUNK_HPP_
#define _CHUNK_HPP_

#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include <cstdint>
#include <map>
#include "protocol/messages.hpp"

#include <zlib/zlib.h>


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
//public:
//	boost::multi_array<BlockData, 3> m_blocksData;
//	boost::multi_array<uint8_t, 2> m_biomeData; // each element is 1 block column
//	
//
//	Chunk()
//		:	m_blocksData(boost::extents[16][16][16]) // YZX
//		,	m_biomeData(boost::extents[16][16]) // ZX
//	{}
//
//private:
//	

};


// 16x256x16 block, 16 chunks
class ChunkColumn
{
public:
	void read(const std::vector<uint8_t>& _columnData);

private:
	boost::array<Chunk, 16> m_chunks;

};

// rename
class World
{
public:
	World(){}


	void loadColumns(protocol::msg::MapChunkBulk& _columns)
	{
		for(auto itr = _columns.get_metaInformation().begin(); itr != _columns.get_metaInformation().end(); ++itr)
		{
			m_columnsMap[itr->m_chunkZ][itr->m_chunkX];
			std::cout << "Storage prepared for " << itr->m_chunkX << " " << itr->m_chunkZ << std::endl;
		}

	}

private:
	std::map<int, std::map<int, ChunkColumn>> m_columnsMap; // ZX, in chunk coordinates

};

//------------------------------------------------------------------------------

//void ChunkColumn::read(protocol::msg::ChunkColumnData& _columnDataMsg)
//{
//	
//
//	// Creating chunks
//	for(int i = 0; i < 16; ++i)
//	{
//		
//
//
//	}
//}



// Dirty stolen inflate.
void Inflate (const std::vector<uint8_t>& _src, std::vector<uint8_t>& _dst)
{
	z_stream stream;

	try
	{
		// Initialize a stream	
		stream.zalloc = Z_NULL;
		stream.zfree = Z_NULL;
		stream.opaque = Z_NULL;

		if (inflateInit2(&stream, 32 + MAX_WBITS) != Z_OK)
			throw "wtf";
			//throw std::runtime_error(zlib_error);

		stream.avail_in = _src.size();
		stream.next_in = const_cast<uint8_t*>(_src.data());

		_dst.resize(500000);

		// Loop and decompress
		for (;;)
		{

			// Set out to _dst
			// Bad hack
			stream.next_out = _dst.data();
			stream.avail_out = _dst.size();

			// Inflate
			int result = inflate(&stream, Z_FINISH);

			// Did we decompress everything?
			// If so we're done.
			if (result == Z_STREAM_END)
			{
				_dst.resize(_dst.size() - stream.avail_out);
				break;
			}

			// Did something go wrong?
			if (result != Z_OK)
			{
				if(result == Z_BUF_ERROR)
					_dst.resize(_dst.size() * 2);
				else
					throw "wtf";
			}

			// LOOP
		}
	} 

	catch (...)
	{
		inflateEnd(&stream);
		std::cerr << "THROW IN INFLATE" << std::endl;
	}

}


#endif // _CHUNK_HPP_