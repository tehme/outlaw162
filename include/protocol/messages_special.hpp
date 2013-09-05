#ifndef _PROTOCOL_MESSAGES_SPECIAL_HPP_
#define _PROTOCOL_MESSAGES_SPECIAL_HPP_

//#include <rapidjson.h>
#include "basemessage.hpp"

namespace protocol {
namespace msg {

// 0x03
// Direction: Two-way
// Special message.
class ChatMessage : public BaseMessage
{
public:
	ChatMessage(){}

	virtual void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_messageCode);
	}

	virtual size_t deserialize(const BinaryBuffer& _src, size_t _offset = 0)
	{
		int8_t code;
		_offset = Deserialize(_src, code, _offset);
		if(code != m_messageCode) throw WrongMessageException();

		_offset = Deserialize(_src, m_jsonStr, _offset);

		return _offset;
	}

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_jsonStr() const	{ return m_jsonStr; }


private:
	static const uint8_t m_messageCode = 0x03;
	std::wstring m_jsonStr;
};

// 0x0D
// Direction: Two-Way (cts version)
// Special message
class PlayerPositionAndLook : public BaseMessage
{
public:
	PlayerPositionAndLook(){}
	PlayerPositionAndLook(const double& _x, const double& _y, const double& _stance, const double& _z, const float& _yaw, const float& _pitch, const bool& _onGround)
		:	m_x(_x)
		,	m_y(_y)
		,	m_stance(_stance)
		,	m_z(_z)
		,	m_yaw(_yaw)
		,	m_pitch(_pitch)
		,	m_onGround(_onGround)
	{}

	virtual void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_messageCode);
		Serialize(_dst, m_x);
		Serialize(_dst, m_y);
		Serialize(_dst, m_stance);
		Serialize(_dst, m_z);
		Serialize(_dst, m_yaw);
		Serialize(_dst, m_pitch);
		Serialize(_dst, m_onGround);
	}

	virtual size_t deserialize(const BinaryBuffer& _src, size_t _offset = 0)
	{
		uint8_t code;
		_offset = Deserialize(_src, code, _offset);
		if(code != m_messageCode) throw WrongMessageException();

		_offset = Deserialize(_src, m_x, _offset);
		_offset = Deserialize(_src, m_stance, _offset);
		_offset = Deserialize(_src, m_y, _offset);		
		_offset = Deserialize(_src, m_z, _offset);
		_offset = Deserialize(_src, m_yaw, _offset);
		_offset = Deserialize(_src, m_pitch, _offset);
		_offset = Deserialize(_src, m_onGround, _offset);

		return _offset;
	}

	virtual size_t deserialize_cts(const BinaryBuffer& _src, size_t _offset = 0)
	{
		_offset = deserialize(_src, _offset);
		std::swap(m_stance, m_y);
		return _offset;
	}


	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const double& get_x() const	{ return m_x; }
	const double& get_y() const	{ return m_y; }
	const double& get_stance() const	{ return m_stance; }
	const double& get_z() const	{ return m_z; }
	const float& get_yaw() const	{ return m_yaw; }
	const float& get_pitch() const	{ return m_pitch; }
	const bool& get_onGround() const	{ return m_onGround; }

	void set_x(const double& _val)	{ m_x = _val; }
	void set_y(const double& _val)	{ m_y = _val; }
	void set_stance(const double& _val)	{ m_stance = _val; }
	void set_z(const double& _val)	{ m_z = _val; }
	void set_yaw(const float& _val)	{ m_yaw = _val; }
	void set_pitch(const float& _val)	{ m_pitch = _val; }
	void set_onGround(const bool& _val)	{ m_onGround = _val; }

protected:
	static const uint8_t m_messageCode = 0x0D;
	double m_x;
	double m_y;
	double m_stance;
	double m_z;
	float m_yaw;
	float m_pitch;
	bool m_onGround;
};


struct ModifierData
{
	int64_t m_uuidMsb;
	int64_t m_uuidLsb;
	double m_amount;
	int8_t m_operation;

	void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_uuidMsb);
		Serialize(_dst, m_uuidLsb);
		Serialize(_dst, m_amount);
		Serialize(_dst, m_operation);
	}

	size_t deserialize(const BinaryBuffer& _src, size_t _offset)
	{
		_offset = Deserialize(_src, m_uuidMsb, _offset);
		_offset = Deserialize(_src, m_uuidLsb, _offset);
		_offset = Deserialize(_src, m_amount, _offset);
		_offset = Deserialize(_src, m_operation, _offset);

		return _offset;
	}
};

// Too fat, may be reduced to struct later
class PropertyData
{
public:
	PropertyData(){}
	PropertyData(const std::wstring& _key, const double& _value, const int16_t& _modifiersCount, const std::vector<ModifierData>& _modifiers)
		:	m_key(_key)
		,	m_value(_value)
		,	m_modifiersCount(_modifiersCount)
		,	m_modifiers(_modifiers)
	{}

	virtual void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_key);
		Serialize(_dst, m_value);
		Serialize(_dst, m_modifiersCount);
		for(auto itr = m_modifiers.begin(); itr != m_modifiers.end(); ++itr)
			itr->serialize(_dst);
	}

	size_t deserialize(const BinaryBuffer& _src, size_t _offset)
	{
		_offset = Deserialize(_src, m_key, _offset);
		_offset = Deserialize(_src, m_value, _offset);
		_offset = Deserialize(_src, m_modifiersCount, _offset);
		m_modifiers.resize(m_modifiersCount);
		for(auto itr = m_modifiers.begin(); itr != m_modifiers.end(); ++itr)
			_offset = itr->deserialize(_src, _offset);

		return _offset;
	}

	const std::wstring& get_key() const	{ return m_key; }
	const double& get_value() const	{ return m_value; }
	const int16_t& get_modifiersCount() const	{ return m_modifiersCount; }
	const std::vector<ModifierData>& get_modifiers() const	{ return m_modifiers; }

	void set_key(const std::wstring& _val)	{ m_key = _val; }
	void set_value(const double& _val)	{ m_value = _val; }
	void set_modifiersCount(const int16_t& _val)	{ m_modifiersCount = _val; }
	void set_modifiers(const std::vector<ModifierData>& _val)	{ m_modifiers = _val; }

private:
	std::wstring m_key;
	double m_value;
	int16_t m_modifiersCount;
	std::vector<ModifierData> m_modifiers;
};

// 0x2C
// Special class.
class EntityProperties : public BaseMessage
{
public:
	EntityProperties(){}
	EntityProperties(const int32_t& _entityid, const int32_t& _propertiesCount, const std::vector<PropertyData>& _properties)
		:	m_entityid(_entityid)
		,	m_propertiesCount(_propertiesCount)
		,	m_properties(_properties)
	{}

	virtual void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_messageCode);
		Serialize(_dst, m_entityid);
		Serialize(_dst, m_propertiesCount);
		for(auto itr = m_properties.begin(); itr != m_properties.end(); ++itr)
			itr->serialize(_dst);
	}

	virtual size_t deserialize(const BinaryBuffer& _src, size_t _offset = 0)
	{
		uint8_t code;
		_offset = Deserialize(_src, code, _offset);
		if(code != m_messageCode) throw WrongMessageException();

		_offset = Deserialize(_src, m_entityid, _offset);
		_offset = Deserialize(_src, m_propertiesCount, _offset);
		m_properties.resize(m_propertiesCount);
		for(auto itr = m_properties.begin(); itr != m_properties.end(); ++itr)
			_offset = itr->deserialize(_src, _offset);

		return _offset;
	}

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityid() const	{ return m_entityid; }
	const int32_t& get_propertiesCount() const	{ return m_propertiesCount; }
	const std::vector<PropertyData>& get_properties()	{ return m_properties; }

	void set_entityid(const int32_t& _val)	{ m_entityid = _val; }
	void set_propertiesCount(const int32_t& _val)	{ m_propertiesCount = _val; }
	void set_properties(const std::vector<PropertyData>& _val)	{ m_properties = _val; }

private:
	static const uint8_t m_messageCode = 0x2C;
	int32_t m_entityid;
	int32_t m_propertiesCount;
	std::vector<PropertyData> m_properties;
};

// 0x33
// Special class.
// Add better accessing bit map stuff later.
class ChunkColumnData : public BaseMessage
{
public:
	ChunkColumnData(){}
	ChunkColumnData(const int32_t& _x, const int32_t& _z, const bool& _groundUpContinuous, const uint16_t& _primaryBitMap, const uint16_t& _addBitMap, const int32_t& _compressedSize, const std::vector<uint8_t>& _compressedData)
		:	m_x(_x)
		,	m_z(_z)
		,	m_groundUpContinuous(_groundUpContinuous)
		,	m_primaryBitMap(_primaryBitMap)
		,	m_addBitMap(_addBitMap)
		,	m_compressedSize(_compressedSize)
		,	m_compressedData(_compressedData)
	{}

	virtual void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_messageCode);
		Serialize(_dst, m_x);
		Serialize(_dst, m_z);
		Serialize(_dst, m_groundUpContinuous);
		Serialize(_dst, m_primaryBitMap);
		Serialize(_dst, m_addBitMap);
		Serialize(_dst, m_compressedSize);
		Serialize(_dst, m_compressedData);
	}

	virtual size_t deserialize(const BinaryBuffer& _src, size_t _offset)
	{
		int8_t code;
		_offset = Deserialize(_src, code, _offset);
		if(code != m_messageCode) throw WrongMessageException();

		_offset = Deserialize(_src, m_x, _offset);
		_offset = Deserialize(_src, m_z, _offset);
		_offset = Deserialize(_src, m_groundUpContinuous, _offset);
		_offset = Deserialize(_src, m_primaryBitMap, _offset);
		_offset = Deserialize(_src, m_addBitMap, _offset);
		_offset = Deserialize(_src, m_compressedSize, _offset);
		_offset = Deserialize(_src, m_compressedData, _offset, m_compressedSize);

		return _offset;
	}

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_x() const	{ return m_x; }
	const int32_t& get_z() const	{ return m_z; }
	const bool& get_groundUpContinuous() const	{ return m_groundUpContinuous; }
	const uint16_t& get_primaryBitMap() const	{ return m_primaryBitMap; }
	const uint16_t& get_addBitMap() const	{ return m_addBitMap; }
	const int32_t& get_compressedSize() const	{ return m_compressedSize; }
	const std::vector<uint8_t>& get_compressedData() const	{ return m_compressedData; }

	void set_x(const int32_t& _val)	{ m_x = _val; }
	void set_z(const int32_t& _val)	{ m_z = _val; }
	void set_groundUpContinuous(const bool& _val)	{ m_groundUpContinuous = _val; }
	void set_primaryBitMap(const uint16_t& _val)	{ m_primaryBitMap = _val; }
	void set_addBitMap(const uint16_t& _val)	{ m_addBitMap = _val; }
	void set_compressedSize(const int32_t& _val)	{ m_compressedSize = _val; }
	void set_compressedData(const std::vector<uint8_t>& _val)	{ m_compressedData = _val; }

private:
	static const uint8_t m_messageCode = 0x33;
	int32_t m_x;
	int32_t m_z;
	bool m_groundUpContinuous;
	uint16_t m_primaryBitMap;
	uint16_t m_addBitMap;
	int32_t m_compressedSize;
	std::vector<uint8_t> m_compressedData;
};


// Struct with bit fields for 0x34.
struct MultiBlockData
{
	int m_blockMetadata	: 4;
	int blockID			: 12;
	int chunkRelY		: 8;
	int chunkRelZ		: 4;
	int chunkRelX		: 4;
};

// 0x34
// Special class.
class MultiBlockChange : public BaseMessage
{
public:
	MultiBlockChange(){}
	MultiBlockChange(const int32_t& _chunkX, const int32_t& _chunkZ, const int16_t& _recordCount, const int32_t& _dataSize, const std::vector<MultiBlockData>& _data)
		:	m_chunkX(_chunkX)
		,	m_chunkZ(_chunkZ)
		,	m_recordCount(_recordCount)
		,	m_dataSize(_dataSize)
		,	m_data(_data)
	{}

	virtual void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_messageCode);
		Serialize(_dst, m_chunkX);
		Serialize(_dst, m_chunkZ);
		Serialize(_dst, m_recordCount);
		Serialize(_dst, m_dataSize);
		Serialize(_dst, m_data);
	}

	virtual size_t deserialize(const BinaryBuffer& _src, size_t _offset = 0)
	{
		int8_t code;
		_offset = Deserialize(_src, code, _offset);
		if(code != m_messageCode) throw WrongMessageException();

		_offset = Deserialize(_src, m_chunkX, _offset);
		_offset = Deserialize(_src, m_chunkZ, _offset);
		_offset = Deserialize(_src, m_recordCount, _offset);
		_offset = Deserialize(_src, m_dataSize, _offset);
		_offset = Deserialize(_src, m_data, _offset, m_dataSize / 4);

		return _offset;
	}

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_chunkX() const	{ return m_chunkX; }
	const int32_t& get_chunkZ() const	{ return m_chunkZ; }
	const int16_t& get_recordCount() const	{ return m_recordCount; }
	const int32_t& get_dataSize() const	{ return m_dataSize; }
	const std::vector<MultiBlockData>& get_data() const	{ return m_data; }

	void set_chunkX(const int32_t& _val)	{ m_chunkX = _val; }
	void set_chunkZ(const int32_t& _val)	{ m_chunkZ = _val; }
	void set_recordCount(const int16_t& _val)	{ m_recordCount = _val; }
	void set_dataSize(const int32_t& _val)	{ m_dataSize = _val; }
	void set_data(const std::vector<MultiBlockData>& _val)	{ m_data = _val; }

private:
	static const uint8_t m_messageCode = 0x34;
	int32_t m_chunkX;
	int32_t m_chunkZ;
	int16_t m_recordCount;
	int32_t m_dataSize;
	std::vector<MultiBlockData> m_data;
};


struct ChunkMetaInfo
{
	int32_t m_chunkX;	
	int32_t m_chunkZ;
	uint16_t m_primaryBitmap; 
	uint16_t m_addBitmap;

	void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_chunkX);
		Serialize(_dst, m_chunkZ);
		Serialize(_dst, m_primaryBitmap);
		Serialize(_dst, m_addBitmap);
	}

	size_t deserialize(const BinaryBuffer& _src, size_t _offset)
	{
		_offset = Deserialize(_src, m_chunkX, _offset);
		_offset = Deserialize(_src, m_chunkZ, _offset);
		_offset = Deserialize(_src, m_primaryBitmap, _offset);
		_offset = Deserialize(_src, m_addBitmap, _offset);

		return _offset;
	}

};

// 0x38
// Special class.
class MapChunkBulk : public BaseMessage
{
public:
	MapChunkBulk(){}
	MapChunkBulk(const int16_t& _chunkColumnCount, const int32_t& _dataLength, const bool& _skyLightSent, const std::vector<uint8_t>& _data, const std::vector<ChunkMetaInfo>& _metaInformation)
		:	m_chunkColumnCount(_chunkColumnCount)
		,	m_dataLength(_dataLength)
		,	m_skyLightSent(_skyLightSent)
		,	m_data(_data)
		,	m_metaInformation(_metaInformation)
	{}

	virtual void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_messageCode);
		Serialize(_dst, m_chunkColumnCount);
		Serialize(_dst, m_dataLength);
		Serialize(_dst, m_skyLightSent);
		Serialize(_dst, m_data);
		Serialize(_dst, m_metaInformation);
	}

	virtual size_t deserialize(const BinaryBuffer& _src, size_t _offset = 0)
	{
		int8_t code;
		_offset = Deserialize(_src, code, _offset);
		if(code != m_messageCode) throw WrongMessageException();

		_offset = Deserialize(_src, m_chunkColumnCount, _offset);
		_offset = Deserialize(_src, m_dataLength, _offset);
		_offset = Deserialize(_src, m_skyLightSent, _offset);
		_offset = Deserialize(_src, m_data, _offset, m_dataLength);
		m_metaInformation.resize(m_chunkColumnCount);
		for(auto itr = m_metaInformation.begin(); itr != m_metaInformation.end(); ++itr)
			_offset = itr->deserialize(_src, _offset);

		return _offset;
	}

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int16_t& get_chunkColumnCount() const	{ return m_chunkColumnCount; }
	const int32_t& get_dataLength() const	{ return m_dataLength; }
	const bool& get_skyLightSent() const	{ return m_skyLightSent; }
	const std::vector<uint8_t>& get_data() const	{ return m_data; }
	const std::vector<ChunkMetaInfo>& get_metaInformation() const	{ return m_metaInformation; }

	void set_chunkColumnCount(const int16_t& _val)	{ m_chunkColumnCount = _val; }
	void set_dataLength(const int32_t& _val)	{ m_dataLength = _val; }
	void set_skyLightSent(const bool& _val)	{ m_skyLightSent = _val; }
	void set_data(const std::vector<uint8_t>& _val)	{ m_data = _val; }
	void set_metaInformation(const std::vector<ChunkMetaInfo>& _val)	{ m_metaInformation = _val; }

private:
	static const uint8_t m_messageCode = 0x38;
	int16_t m_chunkColumnCount;
	int32_t m_dataLength;
	bool m_skyLightSent;
	std::vector<uint8_t> m_data;
	std::vector<ChunkMetaInfo> m_metaInformation;
};

// 0x3C
// Special class.
class Explosion : public BaseMessage
{
public:
	Explosion(){}
	Explosion(const double& _x, const double& _y, const double& _z, const float& _radius, const int32_t& _recordCount, const std::vector<Coordinates<int8_t>>& _records, const float& _playerMotionX, const float& _playerMotionY, const float& _playerMotionZ)
		:	m_x(_x)
		,	m_y(_y)
		,	m_z(_z)
		,	m_radius(_radius)
		,	m_recordCount(_recordCount)
		,	m_records(_records)
		,	m_playerMotionX(_playerMotionX)
		,	m_playerMotionY(_playerMotionY)
		,	m_playerMotionZ(_playerMotionZ)
	{}

	virtual void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_messageCode);
		Serialize(_dst, m_x);
		Serialize(_dst, m_y);
		Serialize(_dst, m_z);
		Serialize(_dst, m_radius);
		Serialize(_dst, m_recordCount);
		for(auto itr = m_records.begin(); itr != m_records.end(); ++itr)
			itr->serialize(_dst);
		Serialize(_dst, m_playerMotionX);
		Serialize(_dst, m_playerMotionY);
		Serialize(_dst, m_playerMotionZ);
	}

	virtual size_t deserialize(const BinaryBuffer& _src, size_t _offset)
	{
		int8_t code;
		_offset = Deserialize(_src, code, _offset);
		if(code != m_messageCode) throw WrongMessageException();

		_offset = Deserialize(_src, m_x, _offset);
		_offset = Deserialize(_src, m_y, _offset);
		_offset = Deserialize(_src, m_z, _offset);
		_offset = Deserialize(_src, m_radius, _offset);
		_offset = Deserialize(_src, m_recordCount, _offset);
		m_records.resize(m_recordCount);
		for(auto itr = m_records.begin(); itr != m_records.end(); ++itr)
			_offset = itr->deserialize(_src, _offset);
		_offset = Deserialize(_src, m_playerMotionX, _offset);
		_offset = Deserialize(_src, m_playerMotionY, _offset);
		_offset = Deserialize(_src, m_playerMotionZ, _offset);

		return _offset;
	}

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const double& get_x() const	{ return m_x; }
	const double& get_y() const	{ return m_y; }
	const double& get_z() const	{ return m_z; }
	const float& get_radius() const	{ return m_radius; }
	const int32_t& get_recordCount() const	{ return m_recordCount; }
	const std::vector<Coordinates<int8_t>>& get_records() const	{ return m_records; }
	const float& get_playerMotionX() const	{ return m_playerMotionX; }
	const float& get_playerMotionY() const	{ return m_playerMotionY; }
	const float& get_playerMotionZ() const	{ return m_playerMotionZ; }

	void set_x(const double& _val)	{ m_x = _val; }
	void set_y(const double& _val)	{ m_y = _val; }
	void set_z(const double& _val)	{ m_z = _val; }
	void set_radius(const float& _val)	{ m_radius = _val; }
	void set_recordCount(const int32_t& _val)	{ m_recordCount = _val; }
	void set_records(const std::vector<Coordinates<int8_t>>& _val)	{ m_records = _val; }
	void set_playerMotionX(const float& _val)	{ m_playerMotionX = _val; }
	void set_playerMotionY(const float& _val)	{ m_playerMotionY = _val; }
	void set_playerMotionZ(const float& _val)	{ m_playerMotionZ = _val; }

private:
	static const uint8_t m_messageCode = 0x3C;
	double m_x;
	double m_y;
	double m_z;
	float m_radius;
	int32_t m_recordCount;
	std::vector<Coordinates<int8_t>> m_records;
	float m_playerMotionX;
	float m_playerMotionY;
	float m_playerMotionZ;
};

// 0xD1
// Special class.
class Teams : public BaseMessage
{
public:
	Teams(){}
	Teams(const std::wstring& _teamName, const int8_t& _mode, const std::wstring& _teamDisplayName, const std::wstring& _teamPrefix, const std::wstring& _teamSuffix, const int8_t& _friendlyFire, const int16_t& _playerCount, const std::vector<std::wstring>& _players)
		:	m_teamName(_teamName)
		,	m_mode(_mode)
		,	m_teamDisplayName(_teamDisplayName)
		,	m_teamPrefix(_teamPrefix)
		,	m_teamSuffix(_teamSuffix)
		,	m_friendlyFire(_friendlyFire)
		,	m_playerCount(_playerCount)
		,	m_players(_players)
	{}

	virtual void serialize(BinaryBuffer& _dst)
	{
		Serialize(_dst, m_messageCode);
		Serialize(_dst, m_teamName);
		Serialize(_dst, m_mode);

		if(m_mode == 0 || m_mode == 2)
		{
			Serialize(_dst, m_teamDisplayName);
			Serialize(_dst, m_teamPrefix);
			Serialize(_dst, m_teamSuffix);
			Serialize(_dst, m_friendlyFire);
		}

		if(m_mode == 0 || m_mode == 3 || m_mode == 4)
		{
			Serialize(_dst, m_playerCount);
			Serialize(_dst, m_players);
		}
	}

	virtual size_t deserialize(const BinaryBuffer& _src, size_t _offset = 0)
	{
		int8_t code;
		_offset = Deserialize(_src, code, _offset);
		if(code != m_messageCode) throw WrongMessageException();

		_offset = Deserialize(_src, m_teamName, _offset);
		_offset = Deserialize(_src, m_mode, _offset);

		if(m_mode == 0 || m_mode == 2)
		{
			_offset = Deserialize(_src, m_teamDisplayName, _offset);
			_offset = Deserialize(_src, m_teamPrefix, _offset);
			_offset = Deserialize(_src, m_teamSuffix, _offset);
			_offset = Deserialize(_src, m_friendlyFire, _offset);
		}

		if(m_mode == 0 || m_mode == 3 || m_mode == 4)
		{
			_offset = Deserialize(_src, m_playerCount, _offset);
			_offset = Deserialize(_src, m_players, _offset, m_playerCount);
		}

		return _offset;
	}

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_teamName() const	{ return m_teamName; }
	const int8_t& get_mode() const	{ return m_mode; }
	const std::wstring& get_teamDisplayName() const	{ return m_teamDisplayName; }
	const std::wstring& get_teamPrefix() const	{ return m_teamPrefix; }
	const std::wstring& get_teamSuffix() const	{ return m_teamSuffix; }
	const int8_t& get_friendlyFire() const	{ return m_friendlyFire; }
	const int16_t& get_playerCount() const	{ return m_playerCount; }
	const std::vector<std::wstring>& get_players() const	{ return m_players; }

	void set_teamName(const std::wstring& _val)	{ m_teamName = _val; }
	void set_mode(const int8_t& _val)	{ m_mode = _val; }
	void set_teamDisplayName(const std::wstring& _val)	{ m_teamDisplayName = _val; }
	void set_teamPrefix(const std::wstring& _val)	{ m_teamPrefix = _val; }
	void set_teamSuffix(const std::wstring& _val)	{ m_teamSuffix = _val; }
	void set_friendlyFire(const int8_t& _val)	{ m_friendlyFire = _val; }
	void set_playerCount(const int16_t& _val)	{ m_playerCount = _val; }
	void set_players(const std::vector<std::wstring>& _val)	{ m_players = _val; }

private:
	static const uint8_t m_messageCode = 0xD1;
	std::wstring m_teamName;
	int8_t m_mode;
	std::wstring m_teamDisplayName;
	std::wstring m_teamPrefix;
	std::wstring m_teamSuffix;
	int8_t m_friendlyFire;
	int16_t m_playerCount;
	std::vector<std::wstring> m_players;
};

} // namespace msg
} // namespace protocol



#endif // _PROTOCOL_MESSAGES_SPECIAL_HPP_
