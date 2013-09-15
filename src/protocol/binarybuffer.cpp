#include "binarybuffer.hpp"


namespace protocol {


void BinaryBuffer::removeDataUntil(size_t _offset)
{
	m_data.erase(m_data.begin(), m_data.begin() + _offset);
	m_offset = 0;
}

void BinaryBuffer::removeReadData()
{
	removeDataUntil(m_offset);
}


size_t BinaryBuffer::getOffset() const
{
	return m_offset;
}

void BinaryBuffer::setOffset(size_t _val)
{
	if(_val > m_data.size()) // user can set offset to end
		throw OffsetOutOfRangeException();

	m_offset = _val;
}


} // namespace protocol