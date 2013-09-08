#ifndef _DEBUG_HPP_
#define _DEBUG_HPP_


#include <iostream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <cstdint>
#include "chunk.hpp"


void DumpHex(const uint8_t* _buf, int _size, std::ostream& _out);
void DumpColumnBlockTypes(const ChunkColumn& _col, const ChunkColumnID& _colID, std::ostream& _ostr);
void DumpColumnHeightsMap(const ChunkColumn& _col, const ChunkColumnID& _colID);

#endif // _DEBUG_HPP_
