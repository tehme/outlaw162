#ifndef _PROTOCOL_MARSHALLING_HPP_
#define _PROTOCOL_MARSHALLING_HPP_

#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdlib>

namespace protocol
{

typedef std::vector<uint8_t> SimpleBinaryBuffer;

class PartialMessageException {};

// Serialization

// Byte version
//template<>
size_t Serialize(SimpleBinaryBuffer& _dst, const int8_t& _val);
// Unsigned byte version
//template<>
size_t Serialize(SimpleBinaryBuffer& _dst, const uint8_t& _val);
// String version
//template<>
size_t Serialize(SimpleBinaryBuffer& _dst, const std::wstring& _val);

// Deserialization

// Byte version
//template<>
size_t Deserialize(const SimpleBinaryBuffer& _src, int8_t& _dst, size_t _offset);
// Unsigned byte version, bad copy-paste
//template<>
size_t Deserialize(const SimpleBinaryBuffer& _src, uint8_t& _dst, size_t _offset);
// String version
//template<>
size_t Deserialize(const SimpleBinaryBuffer& _src, std::wstring& _dst, size_t _offset);


// Used to reverse byteorder, replace later.
template<class T>
void DumbReverse(T& _arg)
{
	uint8_t *p = reinterpret_cast<uint8_t*>(&_arg);
	std::reverse(p, p + sizeof(T));
}

template<class T>
T DumbReverseCopy(const T& _arg)
{
	T res = _arg;
	DumbReverse(res);
	return res;
}

//------------------------------------------------------------------------------

// General version (float-types need this too)
template<class T>
size_t Serialize(SimpleBinaryBuffer& _dst, const T& _val)
{
	T val = DumbReverseCopy(_val);
	_dst.insert(_dst.end(), (uint8_t*) &val, ((uint8_t*) &val) + sizeof(T));
	return 0;
}

// Array version
template<class T>
size_t Serialize(SimpleBinaryBuffer& _dst, const std::vector<T>& _val)
{
	for(auto itr = _val.begin(); itr != _val.end(); ++itr)
		Serialize(_dst, *itr);

	return 0;
}

//------------------------------------------------------------------------------

// General version
template<class T>
size_t Deserialize(const SimpleBinaryBuffer& _src, T& _dst, size_t _offset)
{
	// This is TCP, baby. Message can arrive in parts.
	if(_offset + sizeof(T) > _src.size())
		throw PartialMessageException();

	_dst = *reinterpret_cast<const T*>(_src.data() + _offset); // may cause const const, fix later
	DumbReverse(_dst);


	return _offset + sizeof(T);
}

// Array version
template<class T>
size_t Deserialize(const SimpleBinaryBuffer& _src, std::vector<T>& _dst, size_t _offset, size_t _arrSize)
{
	if(_offset + sizeof(T) * _arrSize > _src.size())
		throw PartialMessageException();

	_dst.clear();
	_dst.resize(_arrSize);
	for(auto itr = _dst.begin(); itr != _dst.end(); ++itr)
		_offset = Deserialize(_src, *itr, _offset);

	return _offset;
}


} // namespace protocol

#endif // _PROTOCOL_MARSHALLING_HPP_