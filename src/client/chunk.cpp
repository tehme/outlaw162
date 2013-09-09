#include "chunk.hpp"


// Coord utils

int WorldToColumnRel(int _worldCoord)
{
	int rel = _worldCoord % 16;
	if(rel < 0)
		rel += 15;
	return rel;
}

int WorldToColumnCoord(int _worldCoord)
{
	if(_worldCoord < 0)
		_worldCoord -= 1; // chunk 0: -16 .. -1
	return _worldCoord / 16;
}

int RoundWorldCoord(double _worldCoord)
{
	int crd = int(_worldCoord);
	if(_worldCoord < std::numeric_limits<double>::epsilon())
		crd -= 1;
	return crd;
}



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
				_dst.resize(stream.total_out);
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


// Chunk column Public

ChunkColumn::ChunkColumn(const ChunkColumn& _other)
//	:	m_columnDataRef(_other.m_columnDataRef)
{
	std::cout << "ChunkColumn copy ctr!" << std::endl;
	memcpy(m_columnData.data(), _other.m_columnData.data(), m_columnData.max_size());
}

size_t ChunkColumn::load(std::vector<uint8_t>& _src, size_t _offset, int _nNonAirChunks)
{
	int nNonAirSquares = _nNonAirChunks * 16;

	static bool dbgFirstLine = true;
	// Block types
	for(int y = 0; y < nNonAirSquares; ++y)
		for(int z = 0; z < 16; ++z)
			for(int x = 0; x < 16; ++x)
				getBlock(x, y, z).m_type = _src[_offset++];

	// Block metadata
	for(int y = 0; y < nNonAirSquares; ++y)
		for(int z = 0; z < 16; ++z)
			for(int x = 0; x < 16; x += 2)
			{
				// Even-indexed items are packed into the high bits, odd-indexed into the low bits. 
				getBlock(x, y, z).m_metadata = _src[_offset] >> 4;
				getBlock(x + 1, y, z).m_metadata = _src[_offset] & 0x0F;
				++_offset;
			}

	// Block light
	for(int y = 0; y < nNonAirSquares; ++y)
		for(int z = 0; z < 16; ++z)
			for(int x = 0; x < 16; x += 2)
			{
				// Even-indexed items are packed into the high bits, odd-indexed into the low bits. 
				getBlock(x, y, z).m_blockLight = _src[_offset] >> 4;
				getBlock(x + 1, y, z).m_blockLight = _src[_offset] & 0x0F;
				++_offset;
			}

	// Sky light
	for(int y = 0; y < nNonAirSquares; ++y)
		for(int z = 0; z < 16; ++z)
			for(int x = 0; x < 16; x += 2)
			{
				// Even-indexed items are packed into the high bits, odd-indexed into the low bits. 
				getBlock(x, y, z).m_skyLight = _src[_offset] >> 4;
				getBlock(x + 1, y, z).m_skyLight = _src[_offset] & 0x0F;
				++_offset;
			}

	// Add array - uses secondary bitmap (assumed 0)
	//for(int y = 0; y < nNonAirSquares; ++y)
	//	for(int z = 0; z < 16; ++z)
	//		for(int x = 0; x < 16; x += 2)
	//		{
	//			// Even-indexed items are packed into the high bits, odd-indexed into the low bits. 
	//			getBlockByRelCoords(x, y, z).m_add = _src[_offset] >> 4;
	//			getBlockByRelCoords(x + 1, y, z).m_add = _src[_offset] & 0x0F;
	//			++_offset;
	//		}

	// Skip biome array
	_offset += 256;

	// Fill rest with air	
	/*for(int y = nNonAirSquares; y < 256; ++y)
	for(int z = 0; z < 16; ++z)
	for(int x = 0; x < 16; ++x)
	memset(&getBlock(x, y, z), 0, sizeof(BlockData));*/

	// May be bad, but FAST
	//memset(&m_columnDataRef[nNonAirSquares][0][0], 0, sizeof(BlockData) * (256 - nNonAirSquares));
	memset(&getBlock(0, nNonAirSquares, 0), 0, sizeof(BlockData) * (256 - nNonAirSquares));
	
	
	return _offset;
}


// World Public

void World::loadColumns(protocol::msg::MapChunkBulk& _columnsMsg)
{
	std::vector<uint8_t> colData;
	Inflate(_columnsMsg.get_data(), colData);

	//ByteVecConstItr colDataItr = colData.begin();
	size_t srcOffset = 0;
	
	boost::timer t;

	t.restart();
	for(auto itr = _columnsMsg.get_metaInformation().begin(); itr != _columnsMsg.get_metaInformation().end(); ++itr)
	{
		
		int nChunks = 0;
		for(int i = 0; i < 16; ++i)
		{
			bool bit = (itr->m_primaryBitmap >> i) & 1;
			if(bit == 0) break;
			++nChunks;
		}

		ChunkColumnID curID(itr->m_chunkX, itr->m_chunkZ);

		(m_columnsMap[curID] = new ChunkColumn)->load(colData, srcOffset, nChunks);

		// Loading scheduled blocks
		if(m_scheduledBlocks.find(curID) != m_scheduledBlocks.end())
		{
			while(!m_scheduledBlocks.at(curID).empty())
			{
				ScheduledBlock sb = m_scheduledBlocks.at(curID).front();
				getBlock(sb.m_x, sb.m_y, sb.m_z) = sb.m_block;
				m_scheduledBlocks.at(curID).pop();

				std::cout << "DBG: block changed from queue!" << std::endl;
			}
		}

	}

	std::cout << "Loading columns took " << t.elapsed() << " s" << std::endl;
}

void World::scheduleBlockChange(int _blockX, int _blockY, int _blockZ, BlockData _newBlock)
{
	ChunkColumnID id(WorldToColumnCoord(_blockX), WorldToColumnCoord(_blockZ));
	ScheduledBlock sblock = {_blockX, _blockY, _blockZ, _newBlock};
	m_scheduledBlocks[id].push(sblock);
}

// World Private

// 255 * 256 + 0 * 16 + 15