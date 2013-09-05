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