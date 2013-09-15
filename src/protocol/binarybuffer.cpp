#include "binarybuffer.hpp"


namespace protocol {


BinaryBuffer::BinaryBuffer(size_t _capacity)
	:	m_offset(0)
{
	m_data.reserve(_capacity);
}


void BinaryBuffer::addData(const std::vector<uint8_t>& _data)
{
	m_data.insert(m_data.end(), _data.begin(), _data.end());
}

void BinaryBuffer::removeDataUntil(size_t _offset)
{
	m_data.erase(m_data.begin(), m_data.begin() + _offset);
	m_offset = 0;
}

void BinaryBuffer::removeReadData()
{
	removeDataUntil(m_offset);
}

void BinaryBuffer::clear()
{
	m_data.clear();
	m_offset = 0;
}

void BinaryBuffer::reserve(size_t _newCapacity)
{
	m_data.reserve(_newCapacity);
}


uint8_t BinaryBuffer::at(size_t _offset) const
{
	return m_data.at(_offset);
}

uint8_t BinaryBuffer::atOffset() const
{
	return m_data.at(m_offset);
}

uint8_t BinaryBuffer::operator[](size_t _offset) const
{
	return m_data[_offset];
}


size_t BinaryBuffer::getOffset() const
{
	return m_offset;
}

size_t BinaryBuffer::getSize() const
{
	return m_data.size();
}

const std::vector<uint8_t>& BinaryBuffer::getData() const
{
	return m_data;
}

const uint8_t* BinaryBuffer::getFlatData() const
{
	return m_data.data();
}


void BinaryBuffer::setOffset(size_t _val)
{
	if(_val > m_data.size()) // user can set offset to end
		throw OffsetOutOfRangeException();

	m_offset = _val;
}


} // namespace protocol