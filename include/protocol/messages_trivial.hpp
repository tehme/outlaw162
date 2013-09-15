#ifndef _PROTOCOL_MESSAGES_TRIVIAL_HPP_
#define _PROTOCOL_MESSAGES_TRIVIAL_HPP_

#include "basemessage.hpp"

namespace protocol {
namespace msg {

// 0x00
// Direction: Two-Way
class KeepAlive : public BaseMessage
{
public:
	KeepAlive(){}
	KeepAlive(const int32_t& _keepAliveID);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_keepAliveID() const;

	void set_keepAliveID(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x00;
	int32_t m_keepAliveID;
};

// 0x01
// Direction: Server to Client'' ''(and Client to Server in some mods, see below)
class LoginRequest : public BaseMessage
{
public:
	LoginRequest(){}
	LoginRequest(const int32_t& _entityID, const std::wstring& _levelType, const int8_t& _gameMode, const int8_t& _dimension, const int8_t& _difficulty, const int8_t& _notUsed, const int8_t& _maxPlayers);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const std::wstring& get_levelType() const;
	const int8_t& get_gameMode() const;
	const int8_t& get_dimension() const;
	const int8_t& get_difficulty() const;
	const int8_t& get_notUsed() const;
	const int8_t& get_maxPlayers() const;

	void set_entityID(const int32_t& _val);
	void set_levelType(const std::wstring& _val);
	void set_gameMode(const int8_t& _val);
	void set_dimension(const int8_t& _val);
	void set_difficulty(const int8_t& _val);
	void set_notUsed(const int8_t& _val);
	void set_maxPlayers(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x01;
	int32_t m_entityID;
	std::wstring m_levelType;
	int8_t m_gameMode;
	int8_t m_dimension;
	int8_t m_difficulty;
	int8_t m_notUsed;
	int8_t m_maxPlayers;
};

// 0x02
// Direction: Client to server
class Handshake : public BaseMessage
{
public:
	Handshake(){}
	Handshake(const int8_t& _protocolVersion, const std::wstring& _username, const std::wstring& _serverHost, const int32_t& _serverPort);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_protocolVersion() const;
	const std::wstring& get_username() const;
	const std::wstring& get_serverHost() const;
	const int32_t& get_serverPort() const;

	void set_protocolVersion(const int8_t& _val);
	void set_username(const std::wstring& _val);
	void set_serverHost(const std::wstring& _val);
	void set_serverPort(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x02;
	int8_t m_protocolVersion;
	std::wstring m_username;
	std::wstring m_serverHost;
	int32_t m_serverPort;
};

// 0x04
// Direction: Server to Client
class TimeUpdate : public BaseMessage
{
public:
	TimeUpdate(){}
	TimeUpdate(const int64_t& _ageOfTheWorld, const int64_t& _timeOfDay);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int64_t& get_ageOfTheWorld() const;
	const int64_t& get_timeOfDay() const;

	void set_ageOfTheWorld(const int64_t& _val);
	void set_timeOfDay(const int64_t& _val);

private:
	static const uint8_t m_messageCode = 0x04;
	int64_t m_ageOfTheWorld;
	int64_t m_timeOfDay;
};

// 0x05
// Direction: Server to Client
class EntityEquipment : public BaseMessage
{
public:
	EntityEquipment(){}
	EntityEquipment(const int32_t& _entityID, const int16_t& _slot, const SlotData& _item);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const int16_t& get_slot() const;
	const SlotData& get_item() const;

	void set_entityID(const int32_t& _val);
	void set_slot(const int16_t& _val);
	void set_item(const SlotData& _val);

private:
	static const uint8_t m_messageCode = 0x05;
	int32_t m_entityID;
	int16_t m_slot;
	SlotData m_item;
};

// 0x06
// Direction: Server to Client
class SpawnPosition : public BaseMessage
{
public:
	SpawnPosition(){}
	SpawnPosition(const int32_t& _x, const int32_t& _y, const int32_t& _z);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_x() const;
	const int32_t& get_y() const;
	const int32_t& get_z() const;

	void set_x(const int32_t& _val);
	void set_y(const int32_t& _val);
	void set_z(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x06;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
};

// 0x07
// Direction: Client to Server
class UseEntity : public BaseMessage
{
public:
	UseEntity(){}
	UseEntity(const int32_t& _user, const int32_t& _target, const bool& _mouseButton);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_user() const;
	const int32_t& get_target() const;
	const bool& get_mouseButton() const;

	void set_user(const int32_t& _val);
	void set_target(const int32_t& _val);
	void set_mouseButton(const bool& _val);

private:
	static const uint8_t m_messageCode = 0x07;
	int32_t m_user;
	int32_t m_target;
	bool m_mouseButton;
};

// 0x08
// Direction: Server to Client
class UpdateHealth : public BaseMessage
{
public:
	UpdateHealth(){}
	UpdateHealth(const float& _health, const int16_t& _food, const float& _foodSaturation);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const float& get_health() const;
	const int16_t& get_food() const;
	const float& get_foodSaturation() const;

	void set_health(const float& _val);
	void set_food(const int16_t& _val);
	void set_foodSaturation(const float& _val);

private:
	static const uint8_t m_messageCode = 0x08;
	float m_health;
	int16_t m_food;
	float m_foodSaturation;
};

// 0x09
// Direction: Server to Client
class Respawn : public BaseMessage
{
public:
	Respawn(){}
	Respawn(const int32_t& _dimension, const int8_t& _difficulty, const int8_t& _gameMode, const int16_t& _worldHeight, const std::wstring& _levelType);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_dimension() const;
	const int8_t& get_difficulty() const;
	const int8_t& get_gameMode() const;
	const int16_t& get_worldHeight() const;
	const std::wstring& get_levelType() const;

	void set_dimension(const int32_t& _val);
	void set_difficulty(const int8_t& _val);
	void set_gameMode(const int8_t& _val);
	void set_worldHeight(const int16_t& _val);
	void set_levelType(const std::wstring& _val);

private:
	static const uint8_t m_messageCode = 0x09;
	int32_t m_dimension;
	int8_t m_difficulty;
	int8_t m_gameMode;
	int16_t m_worldHeight;
	std::wstring m_levelType;
};

// 0x0A
// Direction: Client to Server
class Player : public BaseMessage
{
public:
	Player(){}
	Player(const bool& _onGround);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const bool& get_onGround() const;

	void set_onGround(const bool& _val);

private:
	static const uint8_t m_messageCode = 0x0A;
	bool m_onGround;
};

// 0x0B
// Direction: Client to Server
class PlayerPosition : public BaseMessage
{
public:
	PlayerPosition(){}
	PlayerPosition(const double& _x, const double& _y, const double& _stance, const double& _z, const bool& _onGround);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const double& get_x() const;
	const double& get_y() const;
	const double& get_stance() const;
	const double& get_z() const;
	const bool& get_onGround() const;

	void set_x(const double& _val);
	void set_y(const double& _val);
	void set_stance(const double& _val);
	void set_z(const double& _val);
	void set_onGround(const bool& _val);

private:
	static const uint8_t m_messageCode = 0x0B;
	double m_x;
	double m_y;
	double m_stance;
	double m_z;
	bool m_onGround;
};

// 0x0C
// Direction: Client to Server
class PlayerLook : public BaseMessage
{
public:
	PlayerLook(){}
	PlayerLook(const float& _yaw, const float& _pitch, const bool& _onGround);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const float& get_yaw() const;
	const float& get_pitch() const;
	const bool& get_onGround() const;

	void set_yaw(const float& _val);
	void set_pitch(const float& _val);
	void set_onGround(const bool& _val);

private:
	static const uint8_t m_messageCode = 0x0C;
	float m_yaw;
	float m_pitch;
	bool m_onGround;
};

// 0x0E
// Direction: Client to Server
class PlayerDigging : public BaseMessage
{
public:
	PlayerDigging(){}
	PlayerDigging(const int8_t& _status, const int32_t& _x, const int8_t& _y, const int32_t& _z, const int8_t& _face);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_status() const;
	const int32_t& get_x() const;
	const int8_t& get_y() const;
	const int32_t& get_z() const;
	const int8_t& get_face() const;

	void set_status(const int8_t& _val);
	void set_x(const int32_t& _val);
	void set_y(const int8_t& _val);
	void set_z(const int32_t& _val);
	void set_face(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x0E;
	int8_t m_status;
	int32_t m_x;
	int8_t m_y;
	int32_t m_z;
	int8_t m_face;
};

// 0x0F
// Direction: Client to Server
class PlayerBlockPlacement : public BaseMessage
{
public:
	PlayerBlockPlacement(){}
	PlayerBlockPlacement(const int32_t& _x, const uint8_t& _y, const int32_t& _z, const int8_t& _direction, const SlotData& _heldItem, const int8_t& _cursorPositionX, const int8_t& _cursorPositionY, const int8_t& _cursorPositionZ);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_x() const;
	const uint8_t& get_y() const;
	const int32_t& get_z() const;
	const int8_t& get_direction() const;
	const SlotData& get_heldItem() const;
	const int8_t& get_cursorPositionX() const;
	const int8_t& get_cursorPositionY() const;
	const int8_t& get_cursorPositionZ() const;

	void set_x(const int32_t& _val);
	void set_y(const uint8_t& _val);
	void set_z(const int32_t& _val);
	void set_direction(const int8_t& _val);
	void set_heldItem(const SlotData& _val);
	void set_cursorPositionX(const int8_t& _val);
	void set_cursorPositionY(const int8_t& _val);
	void set_cursorPositionZ(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x0F;
	int32_t m_x;
	uint8_t m_y;
	int32_t m_z;
	int8_t m_direction;
	SlotData m_heldItem;
	int8_t m_cursorPositionX;
	int8_t m_cursorPositionY;
	int8_t m_cursorPositionZ;
};

// 0x10
// Direction: Two-Way
class HeldItemChange : public BaseMessage
{
public:
	HeldItemChange(){}
	HeldItemChange(const int16_t& _slotID);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int16_t& get_slotID() const;

	void set_slotID(const int16_t& _val);

private:
	static const uint8_t m_messageCode = 0x10;
	int16_t m_slotID;
};

// 0x11
// Direction: Server to Client
class UseBed : public BaseMessage
{
public:
	UseBed(){}
	UseBed(const int32_t& _entityID, const int8_t& _unknown, const int32_t& _bedX, const int8_t& _bedY, const int32_t& _bedZ);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const int8_t& get_unknown() const;
	const int32_t& get_bedX() const;
	const int8_t& get_bedY() const;
	const int32_t& get_bedZ() const;

	void set_entityID(const int32_t& _val);
	void set_unknown(const int8_t& _val);
	void set_bedX(const int32_t& _val);
	void set_bedY(const int8_t& _val);
	void set_bedZ(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x11;
	int32_t m_entityID;
	int8_t m_unknown;
	int32_t m_bedX;
	int8_t m_bedY;
	int32_t m_bedZ;
};

// 0x12
// Direction: Two-Way
class Animation : public BaseMessage
{
public:
	Animation(){}
	Animation(const int32_t& _eid, const int8_t& _animation);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid() const;
	const int8_t& get_animation() const;

	void set_eid(const int32_t& _val);
	void set_animation(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x12;
	int32_t m_eid;
	int8_t m_animation;
};

// 0x13
// Direction: Client to Server
class EntityAction : public BaseMessage
{
public:
	EntityAction(){}
	EntityAction(const int32_t& _eid, const int8_t& _actionID, const int32_t& _jumpboost);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid() const;
	const int8_t& get_actionID() const;
	const int32_t& get_jumpboost() const;

	void set_eid(const int32_t& _val);
	void set_actionID(const int8_t& _val);
	void set_jumpboost(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x13;
	int32_t m_eid;
	int8_t m_actionID;
	int32_t m_jumpboost;
};

// 0x14
// Direction: Server to Client
class SpawnNamedEntity : public BaseMessage
{
public:
	SpawnNamedEntity(){}
	SpawnNamedEntity(const int32_t& _eid, const std::wstring& _playerName, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int8_t& _yaw, const int8_t& _pitch, const int16_t& _currentItem, const Metadata& _metadata);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid() const;
	const std::wstring& get_playerName() const;
	const int32_t& get_x() const;
	const int32_t& get_y() const;
	const int32_t& get_z() const;
	const int8_t& get_yaw() const;
	const int8_t& get_pitch() const;
	const int16_t& get_currentItem() const;
	const Metadata& get_metadata() const;

	void set_eid(const int32_t& _val);
	void set_playerName(const std::wstring& _val);
	void set_x(const int32_t& _val);
	void set_y(const int32_t& _val);
	void set_z(const int32_t& _val);
	void set_yaw(const int8_t& _val);
	void set_pitch(const int8_t& _val);
	void set_currentItem(const int16_t& _val);
	void set_metadata(const Metadata& _val);

private:
	static const uint8_t m_messageCode = 0x14;
	int32_t m_eid;
	std::wstring m_playerName;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
	int8_t m_yaw;
	int8_t m_pitch;
	int16_t m_currentItem;
	Metadata m_metadata;
};

// 0x16
// Direction: Server to Client
class CollectItem : public BaseMessage
{
public:
	CollectItem(){}
	CollectItem(const int32_t& _collectedEID, const int32_t& _collectorEID);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_collectedEID() const;
	const int32_t& get_collectorEID() const;

	void set_collectedEID(const int32_t& _val);
	void set_collectorEID(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x16;
	int32_t m_collectedEID;
	int32_t m_collectorEID;
};

// 0x17
// Direction: Server to Client
class SpawnObjectOrVehicle : public BaseMessage
{
public:
	SpawnObjectOrVehicle(){}
	SpawnObjectOrVehicle(const int32_t& _eid, const int8_t& _type, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int8_t& _pitch, const int8_t& _yaw, const ObjectData& _objectData);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid() const;
	const int8_t& get_type() const;
	const int32_t& get_x() const;
	const int32_t& get_y() const;
	const int32_t& get_z() const;
	const int8_t& get_pitch() const;
	const int8_t& get_yaw() const;
	const ObjectData& get_objectData() const;

	void set_eid(const int32_t& _val);
	void set_type(const int8_t& _val);
	void set_x(const int32_t& _val);
	void set_y(const int32_t& _val);
	void set_z(const int32_t& _val);
	void set_pitch(const int8_t& _val);
	void set_yaw(const int8_t& _val);
	void set_objectData(const ObjectData& _val);

private:
	static const uint8_t m_messageCode = 0x17;
	int32_t m_eid;
	int8_t m_type;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
	int8_t m_pitch;
	int8_t m_yaw;
	ObjectData m_objectData;
};

// 0x18
// Direction: Server to Client
class SpawnMob : public BaseMessage
{
public:
	SpawnMob(){}
	SpawnMob(const int32_t& _eid, const int8_t& _type, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int8_t& _pitch, const int8_t& _headPitch, const int8_t& _yaw, const int16_t& _velocityX, const int16_t& _velocityY, const int16_t& _velocityZ, const Metadata& _metadata);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid() const;
	const int8_t& get_type() const;
	const int32_t& get_x() const;
	const int32_t& get_y() const;
	const int32_t& get_z() const;
	const int8_t& get_pitch() const;
	const int8_t& get_headPitch() const;
	const int8_t& get_yaw() const;
	const int16_t& get_velocityX() const;
	const int16_t& get_velocityY() const;
	const int16_t& get_velocityZ() const;
	const Metadata& get_metadata() const;

	void set_eid(const int32_t& _val);
	void set_type(const int8_t& _val);
	void set_x(const int32_t& _val);
	void set_y(const int32_t& _val);
	void set_z(const int32_t& _val);
	void set_pitch(const int8_t& _val);
	void set_headPitch(const int8_t& _val);
	void set_yaw(const int8_t& _val);
	void set_velocityX(const int16_t& _val);
	void set_velocityY(const int16_t& _val);
	void set_velocityZ(const int16_t& _val);
	void set_metadata(const Metadata& _val);

private:
	static const uint8_t m_messageCode = 0x18;
	int32_t m_eid;
	int8_t m_type;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
	int8_t m_pitch;
	int8_t m_headPitch;
	int8_t m_yaw;
	int16_t m_velocityX;
	int16_t m_velocityY;
	int16_t m_velocityZ;
	Metadata m_metadata;
};

// 0x19
// Direction: Server to Client
class SpawnPainting : public BaseMessage
{
public:
	SpawnPainting(){}
	SpawnPainting(const int32_t& _entityID, const std::wstring& _title, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int32_t& _direction);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const std::wstring& get_title() const;
	const int32_t& get_x() const;
	const int32_t& get_y() const;
	const int32_t& get_z() const;
	const int32_t& get_direction() const;

	void set_entityID(const int32_t& _val);
	void set_title(const std::wstring& _val);
	void set_x(const int32_t& _val);
	void set_y(const int32_t& _val);
	void set_z(const int32_t& _val);
	void set_direction(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x19;
	int32_t m_entityID;
	std::wstring m_title;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
	int32_t m_direction;
};

// 0x1A
// Direction: Server to Client
class SpawnExperienceOrb : public BaseMessage
{
public:
	SpawnExperienceOrb(){}
	SpawnExperienceOrb(const int32_t& _entityID, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int16_t& _count);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const int32_t& get_x() const;
	const int32_t& get_y() const;
	const int32_t& get_z() const;
	const int16_t& get_count() const;

	void set_entityID(const int32_t& _val);
	void set_x(const int32_t& _val);
	void set_y(const int32_t& _val);
	void set_z(const int32_t& _val);
	void set_count(const int16_t& _val);

private:
	static const uint8_t m_messageCode = 0x1A;
	int32_t m_entityID;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
	int16_t m_count;
};

// 0x1B
// Direction: Client to Server
class SteerVehicle : public BaseMessage
{
public:
	SteerVehicle(){}
	SteerVehicle(const float& _sideways, const float& _forward, const bool& _jump, const bool& _unmount);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const float& get_sideways() const;
	const float& get_forward() const;
	const bool& get_jump() const;
	const bool& get_unmount() const;

	void set_sideways(const float& _val);
	void set_forward(const float& _val);
	void set_jump(const bool& _val);
	void set_unmount(const bool& _val);

private:
	static const uint8_t m_messageCode = 0x1B;
	float m_sideways;
	float m_forward;
	bool m_jump;
	bool m_unmount;
};

// 0x1C
// Direction: Server to Client
class EntityVelocity : public BaseMessage
{
public:
	EntityVelocity(){}
	EntityVelocity(const int32_t& _entityID, const int16_t& _velocityX, const int16_t& _velocityY, const int16_t& _velocityZ);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const int16_t& get_velocityX() const;
	const int16_t& get_velocityY() const;
	const int16_t& get_velocityZ() const;

	void set_entityID(const int32_t& _val);
	void set_velocityX(const int16_t& _val);
	void set_velocityY(const int16_t& _val);
	void set_velocityZ(const int16_t& _val);

private:
	static const uint8_t m_messageCode = 0x1C;
	int32_t m_entityID;
	int16_t m_velocityX;
	int16_t m_velocityY;
	int16_t m_velocityZ;
};

// 0x1D
// Direction: Server to Client
class DestroyEntity : public BaseMessage
{
public:
	DestroyEntity(){}
	DestroyEntity(const int8_t& _entityCount, const std::vector<int32_t>& _entityIDs);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_entityCount() const;
	const std::vector<int32_t>& get_entityIDs() const;

	void set_entityCount(const int8_t& _val);
	void set_entityIDs(const std::vector<int32_t>& _val);

private:
	static const uint8_t m_messageCode = 0x1D;
	int8_t m_entityCount;
	std::vector<int32_t> m_entityIDs;
};

// 0x1E
// Direction: Server to Client
class Entity : public BaseMessage
{
public:
	Entity(){}
	Entity(const int32_t& _eid);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid() const;

	void set_eid(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x1E;
	int32_t m_eid;
};

// 0x1F
// Direction: Server to Client
class EntityRelativeMove : public BaseMessage
{
public:
	EntityRelativeMove(){}
	EntityRelativeMove(const int32_t& _eid, const int8_t& _dx, const int8_t& _dy, const int8_t& _dz);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid() const;
	const int8_t& get_dx() const;
	const int8_t& get_dy() const;
	const int8_t& get_dz() const;

	void set_eid(const int32_t& _val);
	void set_dx(const int8_t& _val);
	void set_dy(const int8_t& _val);
	void set_dz(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x1F;
	int32_t m_eid;
	int8_t m_dx;
	int8_t m_dy;
	int8_t m_dz;
};

// 0x20
// Direction: Server to Client
class EntityLook : public BaseMessage
{
public:
	EntityLook(){}
	EntityLook(const int32_t& _eid, const int8_t& _yaw, const int8_t& _pitch);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid() const;
	const int8_t& get_yaw() const;
	const int8_t& get_pitch() const;

	void set_eid(const int32_t& _val);
	void set_yaw(const int8_t& _val);
	void set_pitch(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x20;
	int32_t m_eid;
	int8_t m_yaw;
	int8_t m_pitch;
};

// 0x21
// Direction: Server to Client
class EntityLookAndRelativeMove : public BaseMessage
{
public:
	EntityLookAndRelativeMove(){}
	EntityLookAndRelativeMove(const int32_t& _eid, const int8_t& _dx, const int8_t& _dy, const int8_t& _dz, const int8_t& _yaw, const int8_t& _pitch);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid() const;
	const int8_t& get_dx() const;
	const int8_t& get_dy() const;
	const int8_t& get_dz() const;
	const int8_t& get_yaw() const;
	const int8_t& get_pitch() const;

	void set_eid(const int32_t& _val);
	void set_dx(const int8_t& _val);
	void set_dy(const int8_t& _val);
	void set_dz(const int8_t& _val);
	void set_yaw(const int8_t& _val);
	void set_pitch(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x21;
	int32_t m_eid;
	int8_t m_dx;
	int8_t m_dy;
	int8_t m_dz;
	int8_t m_yaw;
	int8_t m_pitch;
};

// 0x22
// Direction: Server to Client
class EntityTeleport : public BaseMessage
{
public:
	EntityTeleport(){}
	EntityTeleport(const int32_t& _eid, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int8_t& _yaw, const int8_t& _pitch);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid() const;
	const int32_t& get_x() const;
	const int32_t& get_y() const;
	const int32_t& get_z() const;
	const int8_t& get_yaw() const;
	const int8_t& get_pitch() const;

	void set_eid(const int32_t& _val);
	void set_x(const int32_t& _val);
	void set_y(const int32_t& _val);
	void set_z(const int32_t& _val);
	void set_yaw(const int8_t& _val);
	void set_pitch(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x22;
	int32_t m_eid;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
	int8_t m_yaw;
	int8_t m_pitch;
};

// 0x23
// Direction: Server to Client
class EntityHeadLook : public BaseMessage
{
public:
	EntityHeadLook(){}
	EntityHeadLook(const int32_t& _entityID, const int8_t& _headYaw);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const int8_t& get_headYaw() const;

	void set_entityID(const int32_t& _val);
	void set_headYaw(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x23;
	int32_t m_entityID;
	int8_t m_headYaw;
};

// 0x26
// Direction: Server to Client
class EntityStatus : public BaseMessage
{
public:
	EntityStatus(){}
	EntityStatus(const int32_t& _entityID, const int8_t& _entityStatus);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const int8_t& get_entityStatus() const;

	void set_entityID(const int32_t& _val);
	void set_entityStatus(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x26;
	int32_t m_entityID;
	int8_t m_entityStatus;
};

// 0x27
// Direction: Server to Client
class AttachEntity : public BaseMessage
{
public:
	AttachEntity(){}
	AttachEntity(const int32_t& _entityID, const int32_t& _vehicleID, const uint8_t& _leash);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const int32_t& get_vehicleID() const;
	const uint8_t& get_leash() const;

	void set_entityID(const int32_t& _val);
	void set_vehicleID(const int32_t& _val);
	void set_leash(const uint8_t& _val);

private:
	static const uint8_t m_messageCode = 0x27;
	int32_t m_entityID;
	int32_t m_vehicleID;
	uint8_t m_leash;
};

// 0x28
// Direction: Server to Client
class EntityMetadata : public BaseMessage
{
public:
	EntityMetadata(){}
	EntityMetadata(const int32_t& _entityID, const Metadata& _entityMetadata);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const Metadata& get_entityMetadata() const;

	void set_entityID(const int32_t& _val);
	void set_entityMetadata(const Metadata& _val);

private:
	static const uint8_t m_messageCode = 0x28;
	int32_t m_entityID;
	Metadata m_entityMetadata;
};

// 0x29
// Direction: Server to Client
class EntityEffect : public BaseMessage
{
public:
	EntityEffect(){}
	EntityEffect(const int32_t& _entityID, const int8_t& _effectID, const int8_t& _amplifier, const int16_t& _duration);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const int8_t& get_effectID() const;
	const int8_t& get_amplifier() const;
	const int16_t& get_duration() const;

	void set_entityID(const int32_t& _val);
	void set_effectID(const int8_t& _val);
	void set_amplifier(const int8_t& _val);
	void set_duration(const int16_t& _val);

private:
	static const uint8_t m_messageCode = 0x29;
	int32_t m_entityID;
	int8_t m_effectID;
	int8_t m_amplifier;
	int16_t m_duration;
};

// 0x2A
// Direction: Server to Client
class RemoveEntityEffect : public BaseMessage
{
public:
	RemoveEntityEffect(){}
	RemoveEntityEffect(const int32_t& _entityID, const int8_t& _effectID);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const int8_t& get_effectID() const;

	void set_entityID(const int32_t& _val);
	void set_effectID(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x2A;
	int32_t m_entityID;
	int8_t m_effectID;
};

// 0x2B
// Direction: Server to Client
class SetExperience : public BaseMessage
{
public:
	SetExperience(){}
	SetExperience(const float& _experienceBar, const int16_t& _level, const int16_t& _totalExperience);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const float& get_experienceBar() const;
	const int16_t& get_level() const;
	const int16_t& get_totalExperience() const;

	void set_experienceBar(const float& _val);
	void set_level(const int16_t& _val);
	void set_totalExperience(const int16_t& _val);

private:
	static const uint8_t m_messageCode = 0x2B;
	float m_experienceBar;
	int16_t m_level;
	int16_t m_totalExperience;
};

// 0x35
// Direction: Server to Client
class BlockChange : public BaseMessage
{
public:
	BlockChange(){}
	BlockChange(const int32_t& _x, const int8_t& _y, const int32_t& _z, const int16_t& _blockType, const int8_t& _blockMetadata);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_x() const;
	const int8_t& get_y() const;
	const int32_t& get_z() const;
	const int16_t& get_blockType() const;
	const int8_t& get_blockMetadata() const;

	void set_x(const int32_t& _val);
	void set_y(const int8_t& _val);
	void set_z(const int32_t& _val);
	void set_blockType(const int16_t& _val);
	void set_blockMetadata(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x35;
	int32_t m_x;
	int8_t m_y;
	int32_t m_z;
	int16_t m_blockType;
	int8_t m_blockMetadata;
};

// 0x36
// Direction: Server to Client
class BlockAction : public BaseMessage
{
public:
	BlockAction(){}
	BlockAction(const int32_t& _x, const int16_t& _y, const int32_t& _z, const int8_t& _byte1, const int8_t& _byte2, const int16_t& _blockID);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_x() const;
	const int16_t& get_y() const;
	const int32_t& get_z() const;
	const int8_t& get_byte1() const;
	const int8_t& get_byte2() const;
	const int16_t& get_blockID() const;

	void set_x(const int32_t& _val);
	void set_y(const int16_t& _val);
	void set_z(const int32_t& _val);
	void set_byte1(const int8_t& _val);
	void set_byte2(const int8_t& _val);
	void set_blockID(const int16_t& _val);

private:
	static const uint8_t m_messageCode = 0x36;
	int32_t m_x;
	int16_t m_y;
	int32_t m_z;
	int8_t m_byte1;
	int8_t m_byte2;
	int16_t m_blockID;
};

// 0x37
// Direction: Server to Client
class BlockBreakAnimation : public BaseMessage
{
public:
	BlockBreakAnimation(){}
	BlockBreakAnimation(const int32_t& _eid_qm, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int8_t& _destroyStage);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_eid_qm() const;
	const int32_t& get_x() const;
	const int32_t& get_y() const;
	const int32_t& get_z() const;
	const int8_t& get_destroyStage() const;

	void set_eid_qm(const int32_t& _val);
	void set_x(const int32_t& _val);
	void set_y(const int32_t& _val);
	void set_z(const int32_t& _val);
	void set_destroyStage(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x37;
	int32_t m_eid_qm;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
	int8_t m_destroyStage;
};

// 0x3D
// Direction: Server to Client
class SoundOrParticleEffect : public BaseMessage
{
public:
	SoundOrParticleEffect(){}
	SoundOrParticleEffect(const int32_t& _effectID, const int32_t& _x, const int8_t& _y, const int32_t& _z, const int32_t& _data, const bool& _disableRelativeVolume);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_effectID() const;
	const int32_t& get_x() const;
	const int8_t& get_y() const;
	const int32_t& get_z() const;
	const int32_t& get_data() const;
	const bool& get_disableRelativeVolume() const;

	void set_effectID(const int32_t& _val);
	void set_x(const int32_t& _val);
	void set_y(const int8_t& _val);
	void set_z(const int32_t& _val);
	void set_data(const int32_t& _val);
	void set_disableRelativeVolume(const bool& _val);

private:
	static const uint8_t m_messageCode = 0x3D;
	int32_t m_effectID;
	int32_t m_x;
	int8_t m_y;
	int32_t m_z;
	int32_t m_data;
	bool m_disableRelativeVolume;
};

// 0x3E
// Direction: Server to client
class NamedSoundEffect : public BaseMessage
{
public:
	NamedSoundEffect(){}
	NamedSoundEffect(const std::wstring& _soundName, const int32_t& _effectPositionX, const int32_t& _effectPositionY, const int32_t& _effectPositionZ, const float& _volume, const int8_t& _pitch);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_soundName() const;
	const int32_t& get_effectPositionX() const;
	const int32_t& get_effectPositionY() const;
	const int32_t& get_effectPositionZ() const;
	const float& get_volume() const;
	const int8_t& get_pitch() const;

	void set_soundName(const std::wstring& _val);
	void set_effectPositionX(const int32_t& _val);
	void set_effectPositionY(const int32_t& _val);
	void set_effectPositionZ(const int32_t& _val);
	void set_volume(const float& _val);
	void set_pitch(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x3E;
	std::wstring m_soundName;
	int32_t m_effectPositionX;
	int32_t m_effectPositionY;
	int32_t m_effectPositionZ;
	float m_volume;
	int8_t m_pitch;
};

// 0x3F
// Direction: Server to Client
class Particle : public BaseMessage
{
public:
	Particle(){}
	Particle(const std::wstring& _particleName, const float& _x, const float& _y, const float& _z, const float& _offsetX, const float& _offsetY, const float& _offsetZ, const float& _particleSpeed, const int32_t& _numberOfParticles);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_particleName() const;
	const float& get_x() const;
	const float& get_y() const;
	const float& get_z() const;
	const float& get_offsetX() const;
	const float& get_offsetY() const;
	const float& get_offsetZ() const;
	const float& get_particleSpeed() const;
	const int32_t& get_numberOfParticles() const;

	void set_particleName(const std::wstring& _val);
	void set_x(const float& _val);
	void set_y(const float& _val);
	void set_z(const float& _val);
	void set_offsetX(const float& _val);
	void set_offsetY(const float& _val);
	void set_offsetZ(const float& _val);
	void set_particleSpeed(const float& _val);
	void set_numberOfParticles(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x3F;
	std::wstring m_particleName;
	float m_x;
	float m_y;
	float m_z;
	float m_offsetX;
	float m_offsetY;
	float m_offsetZ;
	float m_particleSpeed;
	int32_t m_numberOfParticles;
};

// 0x46
// Direction: Server to Client
class ChangeGameState : public BaseMessage
{
public:
	ChangeGameState(){}
	ChangeGameState(const int8_t& _reason, const int8_t& _gameMode);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_reason() const;
	const int8_t& get_gameMode() const;

	void set_reason(const int8_t& _val);
	void set_gameMode(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x46;
	int8_t m_reason;
	int8_t m_gameMode;
};

// 0x47
// Direction: Server to Client
class SpawnGlobalEntity : public BaseMessage
{
public:
	SpawnGlobalEntity(){}
	SpawnGlobalEntity(const int32_t& _entityID, const int8_t& _type, const int32_t& _x, const int32_t& _y, const int32_t& _z);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_entityID() const;
	const int8_t& get_type() const;
	const int32_t& get_x() const;
	const int32_t& get_y() const;
	const int32_t& get_z() const;

	void set_entityID(const int32_t& _val);
	void set_type(const int8_t& _val);
	void set_x(const int32_t& _val);
	void set_y(const int32_t& _val);
	void set_z(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x47;
	int32_t m_entityID;
	int8_t m_type;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
};

// 0x64
// Direction: Server to Client
class OpenWindow : public BaseMessage
{
public:
	OpenWindow(){}
	OpenWindow(const int8_t& _windowId, const int8_t& _inventoryType, const std::wstring& _windowTitle, const int8_t& _numberOfSlots, const bool& _useProvidedWindowTitle, const int32_t& _entityid);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_windowId() const;
	const int8_t& get_inventoryType() const;
	const std::wstring& get_windowTitle() const;
	const int8_t& get_numberOfSlots() const;
	const bool& get_useProvidedWindowTitle() const;
	const int32_t& get_entityid() const;

	void set_windowId(const int8_t& _val);
	void set_inventoryType(const int8_t& _val);
	void set_windowTitle(const std::wstring& _val);
	void set_numberOfSlots(const int8_t& _val);
	void set_useProvidedWindowTitle(const bool& _val);
	void set_entityid(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x64;
	int8_t m_windowId;
	int8_t m_inventoryType;
	std::wstring m_windowTitle;
	int8_t m_numberOfSlots;
	bool m_useProvidedWindowTitle;
	int32_t m_entityid;
};

// 0x65
// Direction: Two-Way
class CloseWindow : public BaseMessage
{
public:
	CloseWindow(){}
	CloseWindow(const int8_t& _windowId);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_windowId() const;

	void set_windowId(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x65;
	int8_t m_windowId;
};

// 0x66
// Direction: Client to Server
class ClickWindow : public BaseMessage
{
public:
	ClickWindow(){}
	ClickWindow(const int8_t& _windowId, const int16_t& _slot, const int8_t& _button, const int16_t& _actionNumber, const int8_t& _mode, const SlotData& _clickedItem);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_windowId() const;
	const int16_t& get_slot() const;
	const int8_t& get_button() const;
	const int16_t& get_actionNumber() const;
	const int8_t& get_mode() const;
	const SlotData& get_clickedItem() const;

	void set_windowId(const int8_t& _val);
	void set_slot(const int16_t& _val);
	void set_button(const int8_t& _val);
	void set_actionNumber(const int16_t& _val);
	void set_mode(const int8_t& _val);
	void set_clickedItem(const SlotData& _val);

private:
	static const uint8_t m_messageCode = 0x66;
	int8_t m_windowId;
	int16_t m_slot;
	int8_t m_button;
	int16_t m_actionNumber;
	int8_t m_mode;
	SlotData m_clickedItem;
};

// 0x67
// Direction: Server to Client
class SetSlot : public BaseMessage
{
public:
	SetSlot(){}
	SetSlot(const int8_t& _windowId, const int16_t& _slot, const SlotData& _slotData);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_windowId() const;
	const int16_t& get_slot() const;
	const SlotData& get_slotData() const;

	void set_windowId(const int8_t& _val);
	void set_slot(const int16_t& _val);
	void set_slotData(const SlotData& _val);

private:
	static const uint8_t m_messageCode = 0x67;
	int8_t m_windowId;
	int16_t m_slot;
	SlotData m_slotData;
};

// 0x68
// Direction: Server to Client
class SetWindowItems : public BaseMessage
{
public:
	SetWindowItems(){}
	SetWindowItems(const int8_t& _windowId, const int16_t& _count, const std::vector<SlotData>& _slotData);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_windowId() const;
	const int16_t& get_count() const;
	const std::vector<SlotData>& get_slotData() const;

	void set_windowId(const int8_t& _val);
	void set_count(const int16_t& _val);
	void set_slotData(const std::vector<SlotData>& _val);

private:
	static const uint8_t m_messageCode = 0x68;
	int8_t m_windowId;
	int16_t m_count;
	std::vector<SlotData> m_slotData;
};

// 0x69
// Direction: Server to Client
class UpdateWindowProperty : public BaseMessage
{
public:
	UpdateWindowProperty(){}
	UpdateWindowProperty(const int8_t& _windowId, const int16_t& _property, const int16_t& _value);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_windowId() const;
	const int16_t& get_property() const;
	const int16_t& get_value() const;

	void set_windowId(const int8_t& _val);
	void set_property(const int16_t& _val);
	void set_value(const int16_t& _val);

private:
	static const uint8_t m_messageCode = 0x69;
	int8_t m_windowId;
	int16_t m_property;
	int16_t m_value;
};

// 0x6A
// Direction: Two-Way
class ConfirmTransaction : public BaseMessage
{
public:
	ConfirmTransaction(){}
	ConfirmTransaction(const int8_t& _windowId, const int16_t& _actionNumber, const bool& _accepted_qm);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_windowId() const;
	const int16_t& get_actionNumber() const;
	const bool& get_accepted_qm() const;

	void set_windowId(const int8_t& _val);
	void set_actionNumber(const int16_t& _val);
	void set_accepted_qm(const bool& _val);

private:
	static const uint8_t m_messageCode = 0x6A;
	int8_t m_windowId;
	int16_t m_actionNumber;
	bool m_accepted_qm;
};

// 0x6B
// Direction: Two-Way
class CreativeInventoryAction : public BaseMessage
{
public:
	CreativeInventoryAction(){}
	CreativeInventoryAction(const int16_t& _slot, const SlotData& _clickedItem);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int16_t& get_slot() const;
	const SlotData& get_clickedItem() const;

	void set_slot(const int16_t& _val);
	void set_clickedItem(const SlotData& _val);

private:
	static const uint8_t m_messageCode = 0x6B;
	int16_t m_slot;
	SlotData m_clickedItem;
};

// 0x6C
// Direction: Client to Server
class EnchantItem : public BaseMessage
{
public:
	EnchantItem(){}
	EnchantItem(const int8_t& _windowID, const int8_t& _enchantment);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_windowID() const;
	const int8_t& get_enchantment() const;

	void set_windowID(const int8_t& _val);
	void set_enchantment(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0x6C;
	int8_t m_windowID;
	int8_t m_enchantment;
};

// 0x82
// Direction: Two-Way
class UpdateSign : public BaseMessage
{
public:
	UpdateSign(){}
	UpdateSign(const int32_t& _x, const int16_t& _y, const int32_t& _z, const std::wstring& _text1, const std::wstring& _text2, const std::wstring& _text3, const std::wstring& _text4);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_x() const;
	const int16_t& get_y() const;
	const int32_t& get_z() const;
	const std::wstring& get_text1() const;
	const std::wstring& get_text2() const;
	const std::wstring& get_text3() const;
	const std::wstring& get_text4() const;

	void set_x(const int32_t& _val);
	void set_y(const int16_t& _val);
	void set_z(const int32_t& _val);
	void set_text1(const std::wstring& _val);
	void set_text2(const std::wstring& _val);
	void set_text3(const std::wstring& _val);
	void set_text4(const std::wstring& _val);

private:
	static const uint8_t m_messageCode = 0x82;
	int32_t m_x;
	int16_t m_y;
	int32_t m_z;
	std::wstring m_text1;
	std::wstring m_text2;
	std::wstring m_text3;
	std::wstring m_text4;
};

// 0x83
// Direction: Server to Client
class ItemData : public BaseMessage
{
public:
	ItemData(){}
	ItemData(const int16_t& _itemType, const int16_t& _itemID, const int16_t& _textLength, const std::vector<int8_t>& _text);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int16_t& get_itemType() const;
	const int16_t& get_itemID() const;
	const int16_t& get_textLength() const;
	const std::vector<int8_t>& get_text() const;

	void set_itemType(const int16_t& _val);
	void set_itemID(const int16_t& _val);
	void set_textLength(const int16_t& _val);
	void set_text(const std::vector<int8_t>& _val);

private:
	static const uint8_t m_messageCode = 0x83;
	int16_t m_itemType;
	int16_t m_itemID;
	int16_t m_textLength;
	std::vector<int8_t> m_text;
};

// 0x84
// Direction: Server to Client
class UpdateTileEntity : public BaseMessage
{
public:
	UpdateTileEntity(){}
	UpdateTileEntity(const int32_t& _x, const int16_t& _y, const int32_t& _z, const int8_t& _action, const int16_t& _dataLength, const std::vector<int8_t>& _nbtData);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_x() const;
	const int16_t& get_y() const;
	const int32_t& get_z() const;
	const int8_t& get_action() const;
	const int16_t& get_dataLength() const;
	const std::vector<int8_t>& get_nbtData() const;

	void set_x(const int32_t& _val);
	void set_y(const int16_t& _val);
	void set_z(const int32_t& _val);
	void set_action(const int8_t& _val);
	void set_dataLength(const int16_t& _val);
	void set_nbtData(const std::vector<int8_t>& _val);

private:
	static const uint8_t m_messageCode = 0x84;
	int32_t m_x;
	int16_t m_y;
	int32_t m_z;
	int8_t m_action;
	int16_t m_dataLength;
	std::vector<int8_t> m_nbtData;
};

// 0x85
// Direction: Server to Client
class TileEditorOpen_qm : public BaseMessage
{
public:
	TileEditorOpen_qm(){}
	TileEditorOpen_qm(const int8_t& _tileEntityId, const int32_t& _x, const int32_t& _y, const int32_t& _z);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_tileEntityId() const;
	const int32_t& get_x() const;
	const int32_t& get_y() const;
	const int32_t& get_z() const;

	void set_tileEntityId(const int8_t& _val);
	void set_x(const int32_t& _val);
	void set_y(const int32_t& _val);
	void set_z(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0x85;
	int8_t m_tileEntityId;
	int32_t m_x;
	int32_t m_y;
	int32_t m_z;
};

// 0xC8
// Direction: Server to Client
class IncrementStatistic : public BaseMessage
{
public:
	IncrementStatistic(){}
	IncrementStatistic(const int32_t& _statisticID, const int32_t& _amount);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int32_t& get_statisticID() const;
	const int32_t& get_amount() const;

	void set_statisticID(const int32_t& _val);
	void set_amount(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0xC8;
	int32_t m_statisticID;
	int32_t m_amount;
};

// 0xC9
// Direction: Server to Client
class PlayerListItem : public BaseMessage
{
public:
	PlayerListItem(){}
	PlayerListItem(const std::wstring& _playerName, const bool& _online, const int16_t& _ping);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_playerName() const;
	const bool& get_online() const;
	const int16_t& get_ping() const;

	void set_playerName(const std::wstring& _val);
	void set_online(const bool& _val);
	void set_ping(const int16_t& _val);

private:
	static const uint8_t m_messageCode = 0xC9;
	std::wstring m_playerName;
	bool m_online;
	int16_t m_ping;
};

// 0xCA
// Direction: Two-Way
class PlayerAbilities : public BaseMessage
{
public:
	PlayerAbilities(){}
	PlayerAbilities(const int8_t& _flags, const float& _flyingSpeed, const float& _walkingSpeed);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_flags() const;
	const float& get_flyingSpeed() const;
	const float& get_walkingSpeed() const;

	void set_flags(const int8_t& _val);
	void set_flyingSpeed(const float& _val);
	void set_walkingSpeed(const float& _val);

private:
	static const uint8_t m_messageCode = 0xCA;
	int8_t m_flags;
	float m_flyingSpeed;
	float m_walkingSpeed;
};

// 0xCB
// Direction: Two-way
class TabComplete : public BaseMessage
{
public:
	TabComplete(){}
	TabComplete(const std::wstring& _text);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_text() const;

	void set_text(const std::wstring& _val);

private:
	static const uint8_t m_messageCode = 0xCB;
	std::wstring m_text;
};

// 0xCC
// Direction: Client to server
class ClientSettings : public BaseMessage
{
public:
	ClientSettings(){}
	ClientSettings(const std::wstring& _locale, const int8_t& _viewDistance, const int8_t& _chatFlags, const int8_t& _difficulty, const bool& _showCape);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_locale() const;
	const int8_t& get_viewDistance() const;
	const int8_t& get_chatFlags() const;
	const int8_t& get_difficulty() const;
	const bool& get_showCape() const;

	void set_locale(const std::wstring& _val);
	void set_viewDistance(const int8_t& _val);
	void set_chatFlags(const int8_t& _val);
	void set_difficulty(const int8_t& _val);
	void set_showCape(const bool& _val);

private:
	static const uint8_t m_messageCode = 0xCC;
	std::wstring m_locale;
	int8_t m_viewDistance;
	int8_t m_chatFlags;
	int8_t m_difficulty;
	bool m_showCape;
};

// 0xCD
// Direction: Client to server
class ClientStatuses : public BaseMessage
{
public:
	ClientStatuses(){}
	ClientStatuses(const int8_t& _payload);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_payload() const;

	void set_payload(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0xCD;
	int8_t m_payload;
};

// 0xCE
// Direction: Server to Client
class ScoreboardObjective : public BaseMessage
{
public:
	ScoreboardObjective(){}
	ScoreboardObjective(const std::wstring& _objectiveName, const std::wstring& _objectiveValue, const int8_t& _createOrRemove);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_objectiveName() const;
	const std::wstring& get_objectiveValue() const;
	const int8_t& get_createOrRemove() const;

	void set_objectiveName(const std::wstring& _val);
	void set_objectiveValue(const std::wstring& _val);
	void set_createOrRemove(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0xCE;
	std::wstring m_objectiveName;
	std::wstring m_objectiveValue;
	int8_t m_createOrRemove;
};

// 0xCF
// Direction: Server to Client
class UpdateScore : public BaseMessage
{
public:
	UpdateScore(){}
	UpdateScore(const std::wstring& _itemName, const int8_t& _updateOrRemove, const std::wstring& _scoreName, const int32_t& _value);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_itemName() const;
	const int8_t& get_updateOrRemove() const;
	const std::wstring& get_scoreName() const;
	const int32_t& get_value() const;

	void set_itemName(const std::wstring& _val);
	void set_updateOrRemove(const int8_t& _val);
	void set_scoreName(const std::wstring& _val);
	void set_value(const int32_t& _val);

private:
	static const uint8_t m_messageCode = 0xCF;
	std::wstring m_itemName;
	int8_t m_updateOrRemove;
	std::wstring m_scoreName;
	int32_t m_value;
};

// 0xD0
// Direction: Server to Client
class DisplayScoreboard : public BaseMessage
{
public:
	DisplayScoreboard(){}
	DisplayScoreboard(const int8_t& _position, const std::wstring& _scoreName);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_position() const;
	const std::wstring& get_scoreName() const;

	void set_position(const int8_t& _val);
	void set_scoreName(const std::wstring& _val);

private:
	static const uint8_t m_messageCode = 0xD0;
	int8_t m_position;
	std::wstring m_scoreName;
};

// 0xFA
// Direction: Two-Way
class PluginMessage : public BaseMessage
{
public:
	PluginMessage(){}
	PluginMessage(const std::wstring& _channel, const int16_t& _length, const std::vector<int8_t>& _data);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_channel() const;
	const int16_t& get_length() const;
	const std::vector<int8_t>& get_data() const;

	void set_channel(const std::wstring& _val);
	void set_length(const int16_t& _val);
	void set_data(const std::vector<int8_t>& _val);

private:
	static const uint8_t m_messageCode = 0xFA;
	std::wstring m_channel;
	int16_t m_length;
	std::vector<int8_t> m_data;
};

// 0xFC
// Direction: Two-Way
class EncryptionKeyResponse : public BaseMessage
{
public:
	EncryptionKeyResponse(){}
	EncryptionKeyResponse(const int16_t& _sharedSecretLength, const std::vector<int8_t>& _sharedSecret, const int16_t& _verifyTokenLength, const std::vector<int8_t>& _verifyTokenResponse);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int16_t& get_sharedSecretLength() const;
	const std::vector<int8_t>& get_sharedSecret() const;
	const int16_t& get_verifyTokenLength() const;
	const std::vector<int8_t>& get_verifyTokenResponse() const;

	void set_sharedSecretLength(const int16_t& _val);
	void set_sharedSecret(const std::vector<int8_t>& _val);
	void set_verifyTokenLength(const int16_t& _val);
	void set_verifyTokenResponse(const std::vector<int8_t>& _val);

private:
	static const uint8_t m_messageCode = 0xFC;
	int16_t m_sharedSecretLength;
	std::vector<int8_t> m_sharedSecret;
	int16_t m_verifyTokenLength;
	std::vector<int8_t> m_verifyTokenResponse;
};

// 0xFD
// Direction: Server to client
class EncryptionKeyRequest : public BaseMessage
{
public:
	EncryptionKeyRequest(){}
	EncryptionKeyRequest(const std::wstring& _serverId, const int16_t& _publicKeyLength, const std::vector<int8_t>& _publicKey, const int16_t& _verifyTokenLength, const std::vector<int8_t>& _verifyToken);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_serverId() const;
	const int16_t& get_publicKeyLength() const;
	const std::vector<int8_t>& get_publicKey() const;
	const int16_t& get_verifyTokenLength() const;
	const std::vector<int8_t>& get_verifyToken() const;

	void set_serverId(const std::wstring& _val);
	void set_publicKeyLength(const int16_t& _val);
	void set_publicKey(const std::vector<int8_t>& _val);
	void set_verifyTokenLength(const int16_t& _val);
	void set_verifyToken(const std::vector<int8_t>& _val);

private:
	static const uint8_t m_messageCode = 0xFD;
	std::wstring m_serverId;
	int16_t m_publicKeyLength;
	std::vector<int8_t> m_publicKey;
	int16_t m_verifyTokenLength;
	std::vector<int8_t> m_verifyToken;
};

// 0xFE
// Direction: Client to Server
class ServerListPing : public BaseMessage
{
public:
	ServerListPing(){}
	ServerListPing(const int8_t& _magic);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const int8_t& get_magic() const;

	void set_magic(const int8_t& _val);

private:
	static const uint8_t m_messageCode = 0xFE;
	int8_t m_magic;
};

// 0xFF
// Direction: Two-Way
class DisconnectOrKick : public BaseMessage
{
public:
	DisconnectOrKick(){}
	DisconnectOrKick(const std::wstring& _reason);

	virtual void serialize(SimpleBinaryBuffer& _dst);

	virtual size_t deserialize(const SimpleBinaryBuffer& _src, size_t _offset = 0);

	static const uint8_t& get_messageCode()	{ return m_messageCode; }
	const std::wstring& get_reason() const;

	void set_reason(const std::wstring& _val);

private:
	static const uint8_t m_messageCode = 0xFF;
	std::wstring m_reason;
};


} // namespace msg
} // namespace protocol

#endif // _PROTOCOL_MESSAGES_TRIVIAL_HPP_
