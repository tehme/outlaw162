#ifndef _PROTOCOL_BASE_MESSAGE_HPP_
#define _PROTOCOL_BASE_MESSAGE_HPP_

#include <iostream>
//#include "marshalling.hpp"
#include "binarybuffer.hpp"

namespace protocol {
namespace msg {

class SlotData
{
public:
	void serialize(BinaryBuffer& _dst)
	{
		std::cout << __FUNCTION__ << " is NYI." << std::endl;
	}

	void deserialize(const BinaryBuffer& _src)
	{
		_src.read(m_blockID);
		if(m_blockID == -1)
			return;

		_src.read(m_itemCount);
		_src.read(m_itemDamage);
		_src.read(m_optionalDataSize);
		if(m_optionalDataSize == -1)
			return;

		_src.read(m_optionalData, m_optionalDataSize);
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
	
	void deserialize(const BinaryBuffer& _src)
	{
		_src.read(m_code);
		if(m_code == 0)
			return;

		_src.read(m_val1);
		_src.read(m_val2);
		_src.read(m_val3);
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
		_dst.write(m_x);
		_dst.write(m_y);
		_dst.write(m_z);
	}

	void deserialize(const BinaryBuffer& _src)
	{
		_src.read(m_x);
		_src.read(m_y);
		_src.read(m_z);
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
	
	void deserialize(const BinaryBuffer& _src)
	{
		while(1)
		{
			_src.read(m_keytype);
			if(m_keytype == 127)
				return;

			int8_t key = m_keytype & 0x1F;
			int8_t type = m_keytype >> 5;

			switch(type)
			{
				case 0:	_src.read(m_byte);	break;
				case 1:	_src.read(m_short);	break;
				case 2:	_src.read(m_int);	break;
				case 3:	_src.read(m_float);	break;
				case 4:	_src.read(m_string);	break;
				case 5:	m_slot.deserialize(_src);	break;
				case 6:	m_coords.deserialize(_src);	break;
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
	virtual void deserialize(const BinaryBuffer& _src) = 0;

private:

};

} // namespace msg
} // namespace protocol


#endif // _PROTOCOL_BASE_MESSAGE_HPP_