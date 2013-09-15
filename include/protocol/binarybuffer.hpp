#ifndef _PROTOCOL_BINARYBUFFER_HPP_
#define _PROTOCOL_BINARYBUFFER_HPP_


#include <vector>
#include <string>
#include <cstdint>
#include "endian_conversion.hpp"


namespace protocol {


class BinaryBuffer
{
public:
	BinaryBuffer();

	template<class T>	void serialize(const T& _src);
	template<class T>	void serialize(const std::vector<T>& _src);
	template<>			void serialize(const int8_t& _src);
	template<>			void serialize(const uint8_t& _src);
	template<>			void serialize(const float& _src);
	template<>			void serialize(const double& _src);
	template<>			void serialize(const std::wstring& _src);	

	template<class T>	void deserialize(T& _dst);
	template<class T>	void deserialize(std::vector<T>& _dst, size_t _nElems);
	template<>			void deserialize(int8_t& _dst);
	template<>			void deserialize(uint8_t& _dst);
	template<>			void deserialize(float& _dst);
	template<>			void deserialize(double& _dst);
	template<>			void deserialize(std::wstring& _dst);

	void	removeDataUntil(size_t _offset);
	void	removeReadData();

	size_t	getOffset() const;
	void	setOffset(size_t _val);
	
	class PartialMessageException	{};
	class OffsetOutOfRangeException	{};

private:
	std::vector<uint8_t> m_data;
	size_t m_offset;
};

//------------------------------------------------------------------------------

template<class T>
void BinaryBuffer::serialize(const T& _src)
{
	T val;
	boost::endian::native_to_big(_src, val);
	uint8_t *valAsArray = reinterpret_cast<uint8_t*>(&val);
	m_data.insert(m_data.end(), valAsArray, valAsArray + sizeof(T));
}

template<class T>
void BinaryBuffer::serialize(const std::vector<T>& _src)
{
	for(auto itr = _src.begin(); itr != _src.end(); ++itr)
		serialize(*itr);
}

template<>
inline void BinaryBuffer::serialize(const int8_t& _src)
{
	m_data.push_back(_src);
}

template<>
inline void BinaryBuffer::serialize(const uint8_t& _src)
{
	m_data.push_back(_src);
}

template<>
inline void BinaryBuffer::serialize(const float& _src)
{
	const uint32_t& asInt = reinterpret_cast<const uint32_t&>(_src);
	serialize(asInt);
}

template<>
inline void BinaryBuffer::serialize(const double& _src)
{
	const uint64_t& asInt = reinterpret_cast<const uint64_t&>(_src);
	serialize(asInt);
}

template<>
inline void BinaryBuffer::serialize(const std::wstring& _src)
{
	int16_t len = _src.size();
	serialize(len);

	for(auto itr = _src.begin(); itr != _src.end(); ++itr)
		serialize(reinterpret_cast<const uint16_t&>(*itr));
}

//--------------------------------

template<class T>
void BinaryBuffer::deserialize(T& _dst)
{
	// Message may arrive in parts.
	if(m_offset + sizeof(T) > m_data.size())
		throw PartialMessageException();

	_dst = *reinterpret_cast<T*>(m_data.data() + m_offset);
	boost::endian::big_to_native(_dst);

	m_offset += sizeof(T);
}

template<class T>
void BinaryBuffer::deserialize(std::vector<T>& _dst, size_t _nElems)
{
	if(m_offset + sizeof(T) * _nElems > m_data.size())
		throw PartialMessageException();

	_dst.clear();
	_dst.resize(_nElems);
	for(auto itr = _dst.begin(); itr != _dst.end(); ++itr)
		deserialize(*itr);
}

template<>
inline void BinaryBuffer::deserialize(int8_t& _dst)
{
	if(m_offset + 1 > m_data.size())
		throw PartialMessageException();

	_dst = m_data[m_offset];
	//memcpy(&_dst, m_data.data() + m_offset, 1); // to ensure data is not lost in conversion; review this
	m_offset += 1;
}

template<>
inline void BinaryBuffer::deserialize(uint8_t& _dst)
{
	if(m_offset + 1 > m_data.size())
		throw PartialMessageException();

	_dst = m_data[m_offset];
	m_offset += 1;
}

template<>
inline void BinaryBuffer::deserialize(float& _dst)
{
	uint32_t asInt;
	deserialize(asInt);
	_dst = reinterpret_cast<float&>(asInt);
}

template<>
inline void BinaryBuffer::deserialize(double& _dst)
{
	uint64_t asInt;
	deserialize(asInt);
	_dst = reinterpret_cast<double&>(asInt);
}

template<>
inline void BinaryBuffer::deserialize(std::wstring& _dst)
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


#endif // _PROTOCOL_BINARYBUFFER_HPP_