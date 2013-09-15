#include "binarybuffer.hpp"


namespace protocol {


template<>
void BinaryBuffer::serialize(const int8_t& _src)
{
	m_data.push_back(_src);
}

template<>
void BinaryBuffer::serialize(const uint8_t& _src)
{
	m_data.push_back(_src);
}

template<>
void BinaryBuffer::serialize(const float& _src)
{
	const uint32_t& asInt = reinterpret_cast<const uint32_t&>(_src);
	serialize(asInt);
}

template<>
void BinaryBuffer::serialize(const double& _src)
{
	const uint64_t& asInt = reinterpret_cast<const uint64_t&>(_src);
	serialize(asInt);
}

template<>
void BinaryBuffer::serialize(const std::wstring& _src)
{
	int16_t len = _src.size();
	serialize(len);

	for(auto itr = _src.begin(); itr != _src.end(); ++itr)
	{
		serialize(reinterpret_cast<const uint16_t&>(*itr));
	}
}


template<>
void BinaryBuffer::deserialize(int8_t& _dst)
{
	if(m_offset + 1 > m_data.size())
		throw PartialMessageException();

	//_dst = m_data[m_offset];
	memcpy(&_dst, m_data.data() + m_offset, 1); // to ensure data is not lost in conversion; review this
	m_offset += 1;
}

template<>
void BinaryBuffer::deserialize(uint8_t& _dst)
{
	if(m_offset + 1 > m_data.size())
		throw PartialMessageException();

	_dst = m_data[m_offset];
	m_offset += 1;
}

template<>
void BinaryBuffer::deserialize(float& _dst)
{
	uint32_t asInt;
	deserialize(asInt);
	_dst = reinterpret_cast<float&>(asInt);
}

template<>
void BinaryBuffer::deserialize(double& _dst)
{
	uint64_t asInt;
	deserialize(asInt);
	_dst = reinterpret_cast<double&>(asInt);
}

template<>
void BinaryBuffer::deserialize(std::wstring& _dst)
{
	uint16_t size;
	deserialize(size);

	if(m_offset + size * sizeof(int16_t) > m_data.size())
		throw PartialMessageException();

	_dst.clear();
	_dst.resize(size);
	for(auto itr = _dst.begin(); itr != _dst.end(); ++itr)
	{
		// endian_conversion can't convert wchar_t; bad
		deserialize(reinterpret_cast<uint16_t&>(*itr));
	}
}

} // namespace protocol