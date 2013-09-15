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
		_dst.write(m_messageCode);
	}

	void deserialize(BinaryBuffer& _src)
	{
		int8_t code;
		_src.read(code);
		if(code != m_messageCode) throw WrongMessageException();

		_src.read(m_jsonStr);
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
		_dst.write(m_messageCode);
		_dst.write(m_x);
		_dst.write(m_y);
		_dst.write(m_stance);
		_dst.write(m_z);
		_dst.write(m_yaw);
		_dst.write(m_pitch);
		_dst.write(m_onGround);
	}

	void deserialize(BinaryBuffer& _src)
	{
		uint8_t code;
		_src.read(code);
		if(code != m_messageCode) throw WrongMessageException();

		_src.read(m_x);
		_src.read(m_stance);
		_src.read(m_y);		
		_src.read(m_z);
		_src.read(m_yaw);
		_src.read(m_pitch);
		_src.read(m_onGround);
	}

	void deserialize_cts(BinaryBuffer& _src)
	{
		deserialize(_src);
		std::swap(m_stance, m_y);
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
		_dst.write(m_uuidMsb);
		_dst.write(m_uuidLsb);
		_dst.write(m_amount);
		_dst.write(m_operation);
	}

	void deserialize(BinaryBuffer& _src)
	{
		_src.read(m_uuidMsb);
		_src.read(m_uuidLsb);
		_src.read(m_amount);
		_src.read(m_operation);
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
		_dst.write(m_key);
		_dst.write(m_value);
		_dst.write(m_modifiersCount);
		for(auto itr = m_modifiers.begin(); itr != m_modifiers.end(); ++itr)
			itr->serialize(_dst);
	}

	void deserialize(BinaryBuffer& _src)
	{
		_src.read(m_key);
		_src.read(m_value);
		_src.read(m_modifiersCount);
		m_modifiers.resize(m_modifiersCount);
		for(auto itr = m_modifiers.begin(); itr != m_modifiers.end(); ++itr)
			itr->deserialize(_src);
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
		_dst.write(m_messageCode);
		_dst.write(m_entityid);
		_dst.write(m_propertiesCount);
		for(auto itr = m_properties.begin(); itr != m_properties.end(); ++itr)
			itr->serialize(_dst);
	}

	void deserialize(BinaryBuffer& _src)
	{
		uint8_t code;
		_src.read(code);
		if(code != m_messageCode) throw WrongMessageException();

		_src.read(m_entityid);
		_src.read(m_propertiesCount);
		m_properties.resize(m_propertiesCount);
		for(auto itr = m_properties.begin(); itr != m_properties.end(); ++itr)
			itr->deserialize(_src);
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
		_dst.write(m_messageCode);
		_dst.write(m_x);
		_dst.write(m_z);
		_dst.write(m_groundUpContinuous);
		_dst.write(m_primaryBitMap);
		_dst.write(m_addBitMap);
		_dst.write(m_compressedSize);
		_dst.write(m_compressedData);
	}

	virtual void deserialize(BinaryBuffer& _src)
	{
		int8_t code;
		_src.read(code);
		if(code != m_messageCode) throw WrongMessageException();

		_src.read(m_x);
		_src.read(m_z);
		_src.read(m_groundUpContinuous);
		_src.read(m_primaryBitMap);
		_src.read(m_addBitMap);
		_src.read(m_compressedSize);
		_src.read(m_compressedData, m_compressedSize);
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
// 32 bits
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
// MultiBlockData may be bugged, check it.
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
		_dst.write(m_messageCode);
		_dst.write(m_chunkX);
		_dst.write(m_chunkZ);
		_dst.write(m_recordCount);
		_dst.write(m_dataSize);
		//_dst.write(m_data);
		for(auto itr = m_data.begin(); itr != m_data.end(); ++itr)
			_dst.write(reinterpret_cast<const uint32_t&>(*itr));
	}

	void deserialize(BinaryBuffer& _src)
	{
		int8_t code;
		_src.read(code);
		if(code != m_messageCode) throw WrongMessageException();

		_src.read(m_chunkX);
		_src.read(m_chunkZ);
		_src.read(m_recordCount);
		_src.read(m_dataSize);
		//_src.read(m_data, m_dataSize / 4);
		m_data.resize(m_dataSize / 4);
		for(auto itr = m_data.begin(); itr != m_data.end(); ++itr)
			_src.read(reinterpret_cast<uint32_t&>(*itr));
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
		_dst.write(m_chunkX);
		_dst.write(m_chunkZ);
		_dst.write(m_primaryBitmap);
		_dst.write(m_addBitmap);
	}

	void deserialize(BinaryBuffer& _src)
	{
		_src.read(m_chunkX);
		_src.read(m_chunkZ);
		_src.read(m_primaryBitmap);
		_src.read(m_addBitmap);
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
		_dst.write(m_messageCode);
		_dst.write(m_chunkColumnCount);
		_dst.write(m_dataLength);
		_dst.write(m_skyLightSent);
		_dst.write(m_data);
		//_dst.write(m_metaInformation);
		for(auto itr = m_metaInformation.begin(); itr != m_metaInformation.end(); ++itr)
			itr->serialize(_dst);
	}

	void deserialize(BinaryBuffer& _src)
	{
		int8_t code;
		_src.read(code);
		if(code != m_messageCode) throw WrongMessageException();

		_src.read(m_chunkColumnCount);
		_src.read(m_dataLength);
		_src.read(m_skyLightSent);
		_src.read(m_data, m_dataLength);
		m_metaInformation.resize(m_chunkColumnCount);
		for(auto itr = m_metaInformation.begin(); itr != m_metaInformation.end(); ++itr)
			itr->deserialize(_src);
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
		_dst.write(m_messageCode);
		_dst.write(m_x);
		_dst.write(m_y);
		_dst.write(m_z);
		_dst.write(m_radius);
		_dst.write(m_recordCount);
		for(auto itr = m_records.begin(); itr != m_records.end(); ++itr)
			itr->serialize(_dst);
		_dst.write(m_playerMotionX);
		_dst.write(m_playerMotionY);
		_dst.write(m_playerMotionZ);
	}

	virtual void deserialize(BinaryBuffer& _src)
	{
		int8_t code;
		_src.read(code);
		if(code != m_messageCode) throw WrongMessageException();

		_src.read(m_x);
		_src.read(m_y);
		_src.read(m_z);
		_src.read(m_radius);
		_src.read(m_recordCount);
		m_records.resize(m_recordCount);
		for(auto itr = m_records.begin(); itr != m_records.end(); ++itr)
			itr->deserialize(_src);
		_src.read(m_playerMotionX);
		_src.read(m_playerMotionY);
		_src.read(m_playerMotionZ);
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
		_dst.write(m_messageCode);
		_dst.write(m_teamName);
		_dst.write(m_mode);

		if(m_mode == 0 || m_mode == 2)
		{
			_dst.write(m_teamDisplayName);
			_dst.write(m_teamPrefix);
			_dst.write(m_teamSuffix);
			_dst.write(m_friendlyFire);
		}

		if(m_mode == 0 || m_mode == 3 || m_mode == 4)
		{
			_dst.write(m_playerCount);
			_dst.write(m_players);
		}
	}

	void deserialize(BinaryBuffer& _src)
	{
		int8_t code;
		_src.read(code);
		if(code != m_messageCode) throw WrongMessageException();

		_src.read(m_teamName);
		_src.read(m_mode);

		if(m_mode == 0 || m_mode == 2)
		{
			_src.read(m_teamDisplayName);
			_src.read(m_teamPrefix);
			_src.read(m_teamSuffix);
			_src.read(m_friendlyFire);
		}

		if(m_mode == 0 || m_mode == 3 || m_mode == 4)
		{
			_src.read(m_playerCount);
			_src.read(m_players, m_playerCount);
		}
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
