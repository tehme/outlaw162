#ifndef _PROTOCOL_BASE_MESSAGE_HPP_
#define _PROTOCOL_BASE_MESSAGE_HPP_

#include <iostream>
#include "marshalling.hpp"

namespace protocol {
namespace msg {

class SlotData
{
public:
	void serialize(BinaryBuffer& _dst)
	{
		std::cout << __FUNCTION__ << " is NYI." << std::endl;
	}

	size_t deserialize(const BinaryBuffer& _src, size_t _offset)
	{
		_offset = Deserialize(_src, m_blockID, _offset);
		if(m_blockID == -1)
			return _offset;

		_offset = Deserialize(_src, m_itemCount, _offset);
		_offset = Deserialize(_src, m_itemDamage, _offset);
		_offset = Deserialize(_src, m_optionalDataSize, _offset);
		if(m_optionalDataSize == -1)
			return _offset;

		_offset = Deserialize(_src, m_optionalData, _offset, m_optionalDataSize);

		return _offset;
	}

private:
	int16_t m_blockID;
	int8_t m_itemCount;
	int16_t m_itemDamage;
	int16_t m_optionalDataSize;
	std::vector<uint8_t> m_optionalData;

};

class ObjectData
{
public:
	void serialize(BinaryBuffer& _dst)
	{
		std::cout << __FUNCTION__ << " is NYI." << std::endl;
	}
	
	size_t deserialize(const BinaryBuffer& _src, size_t _offset)
	{
		_offset = Deserialize(_src, m_code, _offset);
		if(m_code == 0)
			return _offset;

		_offset = Deserialize(_src, m_val1, _offset);
		_offset = Deserialize(_src, m_val2, _offset);
		_offset = Deserialize(_src, m_val3, _offset);

		return _offset;
	}

	int32_t m_code;
	int16_t m_val1;
	int16_t m_val2;
	int16_t m_val3;
};

template<class T>
struct Coordinates
{
	T m_x;
	T m_y;
	T m_z;

	void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_x);
		Serialize(_dst, m_y);
		Serialize(_dst, m_z);
	}

	size_t deserialize(const BinaryBuffer& _src, size_t _offset)
	{
		_offset = Deserialize(_src, m_x, _offset);
		_offset = Deserialize(_src, m_y, _offset);
		_offset = Deserialize(_src, m_z, _offset);

		return _offset;
	}
};

// Bad implementation
class Metadata
{
public:
	void serialize(BinaryBuffer& _dst)
	{
		std::cout << __FUNCTION__ << " is NYI." << std::endl;
	}
	
	size_t deserialize(const BinaryBuffer& _src, size_t _offset)
	{
		while(1)
		{
			_offset = Deserialize(_src, m_keytype, _offset);
			if(m_keytype == 127)
				return _offset;

			int8_t key = m_keytype & 0x1F;
			int8_t type = m_keytype >> 5;

			switch(type)
			{
				case 0:	_offset = Deserialize(_src, m_byte, _offset);	break;
				case 1:	_offset = Deserialize(_src, m_short, _offset);	break;
				case 2:	_offset = Deserialize(_src, m_int, _offset);	break;
				case 3:	_offset = Deserialize(_src, m_float, _offset);	break;
				case 4:	_offset = Deserialize(_src, m_string, _offset);	break;
				case 5:	_offset = m_slot.deserialize(_src, _offset);	break;
				case 6:	_offset = m_coords.deserialize(_src, _offset);	break;
			}
		}

		//return 0;
	}

private:
	uint8_t m_keytype;

	int8_t m_byte;
	int16_t m_short;
	int32_t m_int;
	float m_float;
	std::wstring m_string;
	SlotData m_slot;
	Coordinates<int32_t> m_coords;
};


class WrongMessageException {};


class BaseMessage
{
public:
	virtual void serialize(BinaryBuffer& _dst) = 0;
	virtual size_t deserialize(const BinaryBuffer& _src, size_t _offset) = 0;

private:
	//int8_t m_messageID;

};

} // namespace msg
} // namespace protocol


#endif // _PROTOCOL_BASE_MESSAGE_HPP_