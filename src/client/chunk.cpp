#include "chunk.hpp"


// Inflate

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


// World Public

void World::loadColumns(protocol::msg::MapChunkBulk& _columns)
{
	std::vector<uint8_t> colData;
	Inflate(_columns.get_data(), colData);

	//ByteVecConstItr colDataItr = colData.begin();
	size_t srcOffset = 0;
	
	boost::timer t;

	for(auto itr = _columns.get_metaInformation().begin(); itr != _columns.get_metaInformation().end(); ++itr)
	{
		t.restart();
		int nChunks = 0;
		for(int i = 0; i < 16; ++i)
		{
			bool bit = (itr->m_primaryBitmap >> i) & 1;
			if(bit == 0) break;
			++nChunks;
		}

		//colDataItr = loadColumn(colDataItr, m_columnsMap[itr->m_chunkZ][itr->m_chunkX], nChunks);
		srcOffset = loadColumn(colData, srcOffset, m_columnsMap[ChunkColumnID(itr->m_chunkX, itr->m_chunkZ)], nChunks);
		//srcOffset = loadColumn(colData, srcOffset, m_columnsMap[itr->m_chunkX, itr->m_chunkZ], nChunks);

		std::cout << "Loading a column took " << t.elapsed() << " s" << std::endl;
	}
}


// World Private

void World::fillChunkWithAir(Chunk& _dst)
{
	for(int y = 0; y < 16; ++y)
		for(int z = 0; z < 16; ++z)
			for(int x = 0; x < 16; ++x)
			{
				_dst.m_blocksData[y][z][x].m_blockType		= 0;
				_dst.m_blocksData[y][z][x].m_blockMetadata	= 0;
				_dst.m_blocksData[y][z][x].m_blockLight		= 0;
				_dst.m_blocksData[y][z][x].m_skyLight		= 0;
				_dst.m_blocksData[y][z][x].m_add			= 0;
			}
}


size_t World::loadChunkBlockTypes(std::vector<uint8_t>& _src, size_t _offset, Chunk& _dst)
{
	for(int y = 0; y < 16; ++y)
		for(int z = 0; z < 16; ++z)
			for(int x = 0; x < 16; ++x)
				_dst.m_blocksData[y][z][x].m_blockType = _src[_offset++];

	return _offset;
}

ByteVecConstItr World::loadChunkBlockTypes(std::vector<uint8_t>::const_iterator _begin, Chunk& _dst)
{
	for(int y = 0; y < 16; ++y)
		for(int z = 0; z < 16; ++z)
			for(int x = 0; x < 16; ++x)
				_dst.m_blocksData[y][z][x].m_blockType = *_begin++;

	return _begin;
}

size_t World::loadColumn(std::vector<uint8_t>& _src, size_t _offset, ChunkColumn& _dst, int _nChunks)
{
	for(int chunkY = 0; chunkY < _nChunks; ++chunkY)
		_offset = loadChunkBlockTypes(_src, _offset, _dst[chunkY]);

	// Filling not transmitted air chunks
	for(int chunkY = _nChunks; chunkY < 16; ++chunkY)
		fillChunkWithAir(_dst[chunkY]);

	return _offset;
}

ByteVecConstItr World::loadColumn(std::vector<uint8_t>::const_iterator _begin, ChunkColumn& _dst, int _nChunks)
{
	for(int chunkY = 0; chunkY < _nChunks; ++chunkY)
		_begin = loadChunkBlockTypes(_begin, _dst[chunkY]);

	// Filling not transmitted air chunks
	for(int chunkY = _nChunks; chunkY < 16; ++chunkY)
		fillChunkWithAir(_dst[chunkY]);

	return _begin;
}