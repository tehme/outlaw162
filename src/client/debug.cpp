#include "debug.hpp"


namespace
{

	void OutHexLine(const uint8_t* _ptr, int _startingByteNum, int _len, char* _dst)
	{
		// First byte offset
		sprintf(_dst, "%04X  ", _startingByteNum);
		_dst += 6;

		// Hex
		for(int i = 0; i < _len; ++i)
		{
			sprintf(_dst, "%02X ", (unsigned int) _ptr[i]);
			_dst += 3;
		}

		// Alignment
		for(int i = 0; i < (16 - _len) * 3 + 1; ++i)
		{
			//printf(" ");
			sprintf(_dst, " ");
			++_dst;
		}

		// Chars
		for(int i = 0; i < _len; ++i)
		{
			sprintf(_dst, "%c", isprint(_ptr[i]) ? _ptr[i] : '.');
			++_dst;
		}

		sprintf(_dst, "\n");
	}

}


void DumpHex(const uint8_t* _buf, int _size, std::ostream& _out)
{
	char line[81];

	sprintf(line, "Size: %d\n", _size);
	_out << line;

	for(int i = 0; i < _size; i += 16)
	{
		OutHexLine(_buf + i, i, (_size - i >= 16) ? 16 : _size - i, line);
		_out << line;
	}

	_out << std::endl << std::endl;
	_out.flush();
}

void DumpColumnBlockTypes(const ChunkColumn& _col, const ChunkColumnID& _colID, std::ostream& _ostr)
{
	int colBeginX = _colID.m_columnX * 16;
	int colBeginZ = _colID.m_columnZ * 16;

	_ostr << "Column abs XZ: " << colBeginX << ' ' << colBeginZ << std::endl;
	for(int y = 0; y < 256; ++y)
		for(int z = 0; z < 16; ++z)
			for(int x = 0; x < 16; ++x)
				_ostr	<< "Block XYZ: " << x + colBeginX << ' ' << y << ' ' << z + colBeginZ
						<< ";\ttype: " << int(_col.getBlockByRelCoords(x, y, z).m_type) << "; addr: " << &_col.getBlockByRelCoords(x, y, z) << std::endl;
	_ostr << std::endl;
}

void DumpColumnHeightsMap(const ChunkColumn& _col, const ChunkColumnID& _colID)
{	
	std::vector<int> heights(16 * 16, -1);
	std::ofstream ofs("dump_heights.txt");

	for(int y = 255; y >= 0; --y)
		for(int z = 0; z < 16; ++z)
			for(int x = 0; x < 16; ++x)
				if(heights[z * 16 + x] == -1 && _col.getBlockByRelCoords(x, y, z).m_type != 0)
				{
					heights[z * 16 + x] = y;
					ofs	<< "Highest point in coords X: " << x + _colID.m_columnX * 16
						<< " ( chunk X: " << _colID.m_columnX 
						<< "); Z: " << z + _colID.m_columnZ * 16 << " (chunk Z: " << _colID.m_columnZ
						<< ") is: " << y << " with block " << int(_col.getBlockByRelCoords(x, y, z).m_type) << std::endl;
				}

	ofs.flush();
	ofs.close();
}