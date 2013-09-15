#include "marshalling.hpp"

namespace protocol
{

// Byte version
//template<>
size_t Serialize(SimpleBinaryBuffer& _dst, const int8_t& _val)
{
	_dst.push_back(_val);
	return 0;
}

// Unsigned byte version
//template<>
size_t Serialize(SimpleBinaryBuffer& _dst, const uint8_t& _val)
{
	_dst.push_back(_val);
	return 0;
}

// String version
//template<>
size_t Serialize(SimpleBinaryBuffer& _dst, const std::wstring& _val)
{
	int16_t len = _val.size();
	Serialize(_dst, len);

	// copy-paste, fix later
	for(auto itr = _val.begin(); itr != _val.end(); ++itr)
		Serialize(_dst, *itr);

	return 0;
}

//------------------------------------------------------------------------------

// Byte version
//template<>
size_t Deserialize(const SimpleBinaryBuffer& _src, int8_t& _dst, size_t _offset)
{
	if(_offset + 1 > _src.size())
		throw PartialMessageException();

	_dst = _src[_offset];
	return _offset + 1;
}

// Unsigned byte version, bad copy-paste
//template<>
size_t Deserialize(const SimpleBinaryBuffer& _src, uint8_t& _dst, size_t _offset)
{
	if(_offset + 1 > _src.size())
		throw PartialMessageException();

	_dst = _src[_offset];
	return _offset + 1;
}

// String version
//template<>
size_t Deserialize(const SimpleBinaryBuffer& _src, std::wstring& _dst, size_t _offset)
{
	if(_offset + sizeof(int16_t) + _dst.size() * sizeof(std::wstring::size_type) > _src.size())
		throw PartialMessageException();

	uint16_t size;
	_offset = Deserialize(_src, size, _offset);

	_dst.clear();
	_dst.resize(size);
	for(auto itr = _dst.begin(); itr != _dst.end(); ++itr)
		_offset = Deserialize(_src, *itr, _offset);

	return _offset;
}

} // namespace protocol