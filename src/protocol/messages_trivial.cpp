#include "messages_trivial.hpp"


namespace protocol {
namespace msg {

// Implementation of class 0x00 KeepAlive
KeepAlive::KeepAlive(const int32_t& _keepAliveID)
	:	m_keepAliveID(_keepAliveID)
{}

void KeepAlive::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_keepAliveID);
}

void KeepAlive::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_keepAliveID);
}

const int32_t& KeepAlive::get_keepAliveID() const	{ return m_keepAliveID; }

void KeepAlive::set_keepAliveID(const int32_t& _val)	{ m_keepAliveID = _val; }

// Implementation of class 0x01 LoginRequest
LoginRequest::LoginRequest(const int32_t& _entityID, const std::wstring& _levelType, const int8_t& _gameMode, const int8_t& _dimension, const int8_t& _difficulty, const int8_t& _notUsed, const int8_t& _maxPlayers)
	:	m_entityID(_entityID)
	,	m_levelType(_levelType)
	,	m_gameMode(_gameMode)
	,	m_dimension(_dimension)
	,	m_difficulty(_difficulty)
	,	m_notUsed(_notUsed)
	,	m_maxPlayers(_maxPlayers)
{}

void LoginRequest::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_levelType);
	_dst.write(m_gameMode);
	_dst.write(m_dimension);
	_dst.write(m_difficulty);
	_dst.write(m_notUsed);
	_dst.write(m_maxPlayers);
}

void LoginRequest::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_levelType);
	_src.read(m_gameMode);
	_src.read(m_dimension);
	_src.read(m_difficulty);
	_src.read(m_notUsed);
	_src.read(m_maxPlayers);

}

const int32_t& LoginRequest::get_entityID() const	{ return m_entityID; }
const std::wstring& LoginRequest::get_levelType() const	{ return m_levelType; }
const int8_t& LoginRequest::get_gameMode() const	{ return m_gameMode; }
const int8_t& LoginRequest::get_dimension() const	{ return m_dimension; }
const int8_t& LoginRequest::get_difficulty() const	{ return m_difficulty; }
const int8_t& LoginRequest::get_notUsed() const	{ return m_notUsed; }
const int8_t& LoginRequest::get_maxPlayers() const	{ return m_maxPlayers; }

void LoginRequest::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void LoginRequest::set_levelType(const std::wstring& _val)	{ m_levelType = _val; }
void LoginRequest::set_gameMode(const int8_t& _val)	{ m_gameMode = _val; }
void LoginRequest::set_dimension(const int8_t& _val)	{ m_dimension = _val; }
void LoginRequest::set_difficulty(const int8_t& _val)	{ m_difficulty = _val; }
void LoginRequest::set_notUsed(const int8_t& _val)	{ m_notUsed = _val; }
void LoginRequest::set_maxPlayers(const int8_t& _val)	{ m_maxPlayers = _val; }

// Implementation of class 0x02 Handshake
Handshake::Handshake(const int8_t& _protocolVersion, const std::wstring& _username, const std::wstring& _serverHost, const int32_t& _serverPort)
	:	m_protocolVersion(_protocolVersion)
	,	m_username(_username)
	,	m_serverHost(_serverHost)
	,	m_serverPort(_serverPort)
{}

void Handshake::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_protocolVersion);
	_dst.write(m_username);
	_dst.write(m_serverHost);
	_dst.write(m_serverPort);
}

void Handshake::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_protocolVersion);
	_src.read(m_username);
	_src.read(m_serverHost);
	_src.read(m_serverPort);
}

const int8_t& Handshake::get_protocolVersion() const	{ return m_protocolVersion; }
const std::wstring& Handshake::get_username() const	{ return m_username; }
const std::wstring& Handshake::get_serverHost() const	{ return m_serverHost; }
const int32_t& Handshake::get_serverPort() const	{ return m_serverPort; }

void Handshake::set_protocolVersion(const int8_t& _val)	{ m_protocolVersion = _val; }
void Handshake::set_username(const std::wstring& _val)	{ m_username = _val; }
void Handshake::set_serverHost(const std::wstring& _val)	{ m_serverHost = _val; }
void Handshake::set_serverPort(const int32_t& _val)	{ m_serverPort = _val; }

// Implementation of class 0x04 TimeUpdate
TimeUpdate::TimeUpdate(const int64_t& _ageOfTheWorld, const int64_t& _timeOfDay)
	:	m_ageOfTheWorld(_ageOfTheWorld)
	,	m_timeOfDay(_timeOfDay)
{}

void TimeUpdate::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_ageOfTheWorld);
	_dst.write(m_timeOfDay);
}

void TimeUpdate::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_ageOfTheWorld);
	_src.read(m_timeOfDay);

}

const int64_t& TimeUpdate::get_ageOfTheWorld() const	{ return m_ageOfTheWorld; }
const int64_t& TimeUpdate::get_timeOfDay() const	{ return m_timeOfDay; }

void TimeUpdate::set_ageOfTheWorld(const int64_t& _val)	{ m_ageOfTheWorld = _val; }
void TimeUpdate::set_timeOfDay(const int64_t& _val)	{ m_timeOfDay = _val; }

// Implementation of class 0x05 EntityEquipment
EntityEquipment::EntityEquipment(const int32_t& _entityID, const int16_t& _slot, const SlotData& _item)
	:	m_entityID(_entityID)
	,	m_slot(_slot)
	,	m_item(_item)
{}

void EntityEquipment::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_slot);
	m_item.serialize(_dst);
}

void EntityEquipment::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_slot);
	m_item.deserialize(_src);

}

const int32_t& EntityEquipment::get_entityID() const	{ return m_entityID; }
const int16_t& EntityEquipment::get_slot() const	{ return m_slot; }
const SlotData& EntityEquipment::get_item() const	{ return m_item; }

void EntityEquipment::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void EntityEquipment::set_slot(const int16_t& _val)	{ m_slot = _val; }
void EntityEquipment::set_item(const SlotData& _val)	{ m_item = _val; }

// Implementation of class 0x06 SpawnPosition
SpawnPosition::SpawnPosition(const int32_t& _x, const int32_t& _y, const int32_t& _z)
	:	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
{}

void SpawnPosition::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
}

void SpawnPosition::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);

}

const int32_t& SpawnPosition::get_x() const	{ return m_x; }
const int32_t& SpawnPosition::get_y() const	{ return m_y; }
const int32_t& SpawnPosition::get_z() const	{ return m_z; }

void SpawnPosition::set_x(const int32_t& _val)	{ m_x = _val; }
void SpawnPosition::set_y(const int32_t& _val)	{ m_y = _val; }
void SpawnPosition::set_z(const int32_t& _val)	{ m_z = _val; }

// Implementation of class 0x07 UseEntity
UseEntity::UseEntity(const int32_t& _user, const int32_t& _target, const bool& _mouseButton)
	:	m_user(_user)
	,	m_target(_target)
	,	m_mouseButton(_mouseButton)
{}

void UseEntity::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_user);
	_dst.write(m_target);
	_dst.write(m_mouseButton);
}

void UseEntity::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_user);
	_src.read(m_target);
	_src.read(m_mouseButton);

}

const int32_t& UseEntity::get_user() const	{ return m_user; }
const int32_t& UseEntity::get_target() const	{ return m_target; }
const bool& UseEntity::get_mouseButton() const	{ return m_mouseButton; }

void UseEntity::set_user(const int32_t& _val)	{ m_user = _val; }
void UseEntity::set_target(const int32_t& _val)	{ m_target = _val; }
void UseEntity::set_mouseButton(const bool& _val)	{ m_mouseButton = _val; }

// Implementation of class 0x08 UpdateHealth
UpdateHealth::UpdateHealth(const float& _health, const int16_t& _food, const float& _foodSaturation)
	:	m_health(_health)
	,	m_food(_food)
	,	m_foodSaturation(_foodSaturation)
{}

void UpdateHealth::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_health);
	_dst.write(m_food);
	_dst.write(m_foodSaturation);
}

void UpdateHealth::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_health);
	_src.read(m_food);
	_src.read(m_foodSaturation);

}

const float& UpdateHealth::get_health() const	{ return m_health; }
const int16_t& UpdateHealth::get_food() const	{ return m_food; }
const float& UpdateHealth::get_foodSaturation() const	{ return m_foodSaturation; }

void UpdateHealth::set_health(const float& _val)	{ m_health = _val; }
void UpdateHealth::set_food(const int16_t& _val)	{ m_food = _val; }
void UpdateHealth::set_foodSaturation(const float& _val)	{ m_foodSaturation = _val; }

// Implementation of class 0x09 Respawn
Respawn::Respawn(const int32_t& _dimension, const int8_t& _difficulty, const int8_t& _gameMode, const int16_t& _worldHeight, const std::wstring& _levelType)
	:	m_dimension(_dimension)
	,	m_difficulty(_difficulty)
	,	m_gameMode(_gameMode)
	,	m_worldHeight(_worldHeight)
	,	m_levelType(_levelType)
{}

void Respawn::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_dimension);
	_dst.write(m_difficulty);
	_dst.write(m_gameMode);
	_dst.write(m_worldHeight);
	_dst.write(m_levelType);
}

void Respawn::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_dimension);
	_src.read(m_difficulty);
	_src.read(m_gameMode);
	_src.read(m_worldHeight);
	_src.read(m_levelType);

}

const int32_t& Respawn::get_dimension() const	{ return m_dimension; }
const int8_t& Respawn::get_difficulty() const	{ return m_difficulty; }
const int8_t& Respawn::get_gameMode() const	{ return m_gameMode; }
const int16_t& Respawn::get_worldHeight() const	{ return m_worldHeight; }
const std::wstring& Respawn::get_levelType() const	{ return m_levelType; }

void Respawn::set_dimension(const int32_t& _val)	{ m_dimension = _val; }
void Respawn::set_difficulty(const int8_t& _val)	{ m_difficulty = _val; }
void Respawn::set_gameMode(const int8_t& _val)	{ m_gameMode = _val; }
void Respawn::set_worldHeight(const int16_t& _val)	{ m_worldHeight = _val; }
void Respawn::set_levelType(const std::wstring& _val)	{ m_levelType = _val; }

// Implementation of class 0x0A Player
Player::Player(const bool& _onGround)
	:	m_onGround(_onGround)
{}

void Player::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_onGround);
}

void Player::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_onGround);

}

const bool& Player::get_onGround() const	{ return m_onGround; }

void Player::set_onGround(const bool& _val)	{ m_onGround = _val; }

// Implementation of class 0x0B PlayerPosition
PlayerPosition::PlayerPosition(const double& _x, const double& _y, const double& _stance, const double& _z, const bool& _onGround)
	:	m_x(_x)
	,	m_y(_y)
	,	m_stance(_stance)
	,	m_z(_z)
	,	m_onGround(_onGround)
{}

void PlayerPosition::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_stance);
	_dst.write(m_z);
	_dst.write(m_onGround);
}

void PlayerPosition::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_stance);
	_src.read(m_z);
	_src.read(m_onGround);

}

const double& PlayerPosition::get_x() const	{ return m_x; }
const double& PlayerPosition::get_y() const	{ return m_y; }
const double& PlayerPosition::get_stance() const	{ return m_stance; }
const double& PlayerPosition::get_z() const	{ return m_z; }
const bool& PlayerPosition::get_onGround() const	{ return m_onGround; }

void PlayerPosition::set_x(const double& _val)	{ m_x = _val; }
void PlayerPosition::set_y(const double& _val)	{ m_y = _val; }
void PlayerPosition::set_stance(const double& _val)	{ m_stance = _val; }
void PlayerPosition::set_z(const double& _val)	{ m_z = _val; }
void PlayerPosition::set_onGround(const bool& _val)	{ m_onGround = _val; }

// Implementation of class 0x0C PlayerLook
PlayerLook::PlayerLook(const float& _yaw, const float& _pitch, const bool& _onGround)
	:	m_yaw(_yaw)
	,	m_pitch(_pitch)
	,	m_onGround(_onGround)
{}

void PlayerLook::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_yaw);
	_dst.write(m_pitch);
	_dst.write(m_onGround);
}

void PlayerLook::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_yaw);
	_src.read(m_pitch);
	_src.read(m_onGround);

}

const float& PlayerLook::get_yaw() const	{ return m_yaw; }
const float& PlayerLook::get_pitch() const	{ return m_pitch; }
const bool& PlayerLook::get_onGround() const	{ return m_onGround; }

void PlayerLook::set_yaw(const float& _val)	{ m_yaw = _val; }
void PlayerLook::set_pitch(const float& _val)	{ m_pitch = _val; }
void PlayerLook::set_onGround(const bool& _val)	{ m_onGround = _val; }

// Implementation of class 0x0E PlayerDigging
PlayerDigging::PlayerDigging(const int8_t& _status, const int32_t& _x, const int8_t& _y, const int32_t& _z, const int8_t& _face)
	:	m_status(_status)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_face(_face)
{}

void PlayerDigging::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_status);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_face);
}

void PlayerDigging::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_status);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_face);

}

const int8_t& PlayerDigging::get_status() const	{ return m_status; }
const int32_t& PlayerDigging::get_x() const	{ return m_x; }
const int8_t& PlayerDigging::get_y() const	{ return m_y; }
const int32_t& PlayerDigging::get_z() const	{ return m_z; }
const int8_t& PlayerDigging::get_face() const	{ return m_face; }

void PlayerDigging::set_status(const int8_t& _val)	{ m_status = _val; }
void PlayerDigging::set_x(const int32_t& _val)	{ m_x = _val; }
void PlayerDigging::set_y(const int8_t& _val)	{ m_y = _val; }
void PlayerDigging::set_z(const int32_t& _val)	{ m_z = _val; }
void PlayerDigging::set_face(const int8_t& _val)	{ m_face = _val; }

// Implementation of class 0x0F PlayerBlockPlacement
PlayerBlockPlacement::PlayerBlockPlacement(const int32_t& _x, const uint8_t& _y, const int32_t& _z, const int8_t& _direction, const SlotData& _heldItem, const int8_t& _cursorPositionX, const int8_t& _cursorPositionY, const int8_t& _cursorPositionZ)
	:	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_direction(_direction)
	,	m_heldItem(_heldItem)
	,	m_cursorPositionX(_cursorPositionX)
	,	m_cursorPositionY(_cursorPositionY)
	,	m_cursorPositionZ(_cursorPositionZ)
{}

void PlayerBlockPlacement::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_direction);
	m_heldItem.serialize(_dst);
	_dst.write(m_cursorPositionX);
	_dst.write(m_cursorPositionY);
	_dst.write(m_cursorPositionZ);
}

void PlayerBlockPlacement::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_direction);
	m_heldItem.deserialize(_src);
	_src.read(m_cursorPositionX);
	_src.read(m_cursorPositionY);
	_src.read(m_cursorPositionZ);

}

const int32_t& PlayerBlockPlacement::get_x() const	{ return m_x; }
const uint8_t& PlayerBlockPlacement::get_y() const	{ return m_y; }
const int32_t& PlayerBlockPlacement::get_z() const	{ return m_z; }
const int8_t& PlayerBlockPlacement::get_direction() const	{ return m_direction; }
const SlotData& PlayerBlockPlacement::get_heldItem() const	{ return m_heldItem; }
const int8_t& PlayerBlockPlacement::get_cursorPositionX() const	{ return m_cursorPositionX; }
const int8_t& PlayerBlockPlacement::get_cursorPositionY() const	{ return m_cursorPositionY; }
const int8_t& PlayerBlockPlacement::get_cursorPositionZ() const	{ return m_cursorPositionZ; }

void PlayerBlockPlacement::set_x(const int32_t& _val)	{ m_x = _val; }
void PlayerBlockPlacement::set_y(const uint8_t& _val)	{ m_y = _val; }
void PlayerBlockPlacement::set_z(const int32_t& _val)	{ m_z = _val; }
void PlayerBlockPlacement::set_direction(const int8_t& _val)	{ m_direction = _val; }
void PlayerBlockPlacement::set_heldItem(const SlotData& _val)	{ m_heldItem = _val; }
void PlayerBlockPlacement::set_cursorPositionX(const int8_t& _val)	{ m_cursorPositionX = _val; }
void PlayerBlockPlacement::set_cursorPositionY(const int8_t& _val)	{ m_cursorPositionY = _val; }
void PlayerBlockPlacement::set_cursorPositionZ(const int8_t& _val)	{ m_cursorPositionZ = _val; }

// Implementation of class 0x10 HeldItemChange
HeldItemChange::HeldItemChange(const int16_t& _slotID)
	:	m_slotID(_slotID)
{}

void HeldItemChange::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_slotID);
}

void HeldItemChange::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_slotID);

}

const int16_t& HeldItemChange::get_slotID() const	{ return m_slotID; }

void HeldItemChange::set_slotID(const int16_t& _val)	{ m_slotID = _val; }

// Implementation of class 0x11 UseBed
UseBed::UseBed(const int32_t& _entityID, const int8_t& _unknown, const int32_t& _bedX, const int8_t& _bedY, const int32_t& _bedZ)
	:	m_entityID(_entityID)
	,	m_unknown(_unknown)
	,	m_bedX(_bedX)
	,	m_bedY(_bedY)
	,	m_bedZ(_bedZ)
{}

void UseBed::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_unknown);
	_dst.write(m_bedX);
	_dst.write(m_bedY);
	_dst.write(m_bedZ);
}

void UseBed::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_unknown);
	_src.read(m_bedX);
	_src.read(m_bedY);
	_src.read(m_bedZ);

}

const int32_t& UseBed::get_entityID() const	{ return m_entityID; }
const int8_t& UseBed::get_unknown() const	{ return m_unknown; }
const int32_t& UseBed::get_bedX() const	{ return m_bedX; }
const int8_t& UseBed::get_bedY() const	{ return m_bedY; }
const int32_t& UseBed::get_bedZ() const	{ return m_bedZ; }

void UseBed::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void UseBed::set_unknown(const int8_t& _val)	{ m_unknown = _val; }
void UseBed::set_bedX(const int32_t& _val)	{ m_bedX = _val; }
void UseBed::set_bedY(const int8_t& _val)	{ m_bedY = _val; }
void UseBed::set_bedZ(const int32_t& _val)	{ m_bedZ = _val; }

// Implementation of class 0x12 Animation
Animation::Animation(const int32_t& _eid, const int8_t& _animation)
	:	m_eid(_eid)
	,	m_animation(_animation)
{}

void Animation::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid);
	_dst.write(m_animation);
}

void Animation::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid);
	_src.read(m_animation);

}

const int32_t& Animation::get_eid() const	{ return m_eid; }
const int8_t& Animation::get_animation() const	{ return m_animation; }

void Animation::set_eid(const int32_t& _val)	{ m_eid = _val; }
void Animation::set_animation(const int8_t& _val)	{ m_animation = _val; }

// Implementation of class 0x13 EntityAction
EntityAction::EntityAction(const int32_t& _eid, const int8_t& _actionID, const int32_t& _jumpboost)
	:	m_eid(_eid)
	,	m_actionID(_actionID)
	,	m_jumpboost(_jumpboost)
{}

void EntityAction::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid);
	_dst.write(m_actionID);
	_dst.write(m_jumpboost);
}

void EntityAction::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid);
	_src.read(m_actionID);
	_src.read(m_jumpboost);

}

const int32_t& EntityAction::get_eid() const	{ return m_eid; }
const int8_t& EntityAction::get_actionID() const	{ return m_actionID; }
const int32_t& EntityAction::get_jumpboost() const	{ return m_jumpboost; }

void EntityAction::set_eid(const int32_t& _val)	{ m_eid = _val; }
void EntityAction::set_actionID(const int8_t& _val)	{ m_actionID = _val; }
void EntityAction::set_jumpboost(const int32_t& _val)	{ m_jumpboost = _val; }

// Implementation of class 0x14 SpawnNamedEntity
SpawnNamedEntity::SpawnNamedEntity(const int32_t& _eid, const std::wstring& _playerName, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int8_t& _yaw, const int8_t& _pitch, const int16_t& _currentItem, const Metadata& _metadata)
	:	m_eid(_eid)
	,	m_playerName(_playerName)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_yaw(_yaw)
	,	m_pitch(_pitch)
	,	m_currentItem(_currentItem)
	,	m_metadata(_metadata)
{}

void SpawnNamedEntity::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid);
	_dst.write(m_playerName);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_yaw);
	_dst.write(m_pitch);
	_dst.write(m_currentItem);
	m_metadata.serialize(_dst);
}

void SpawnNamedEntity::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid);
	_src.read(m_playerName);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_yaw);
	_src.read(m_pitch);
	_src.read(m_currentItem);
	m_metadata.deserialize(_src);

}

const int32_t& SpawnNamedEntity::get_eid() const	{ return m_eid; }
const std::wstring& SpawnNamedEntity::get_playerName() const	{ return m_playerName; }
const int32_t& SpawnNamedEntity::get_x() const	{ return m_x; }
const int32_t& SpawnNamedEntity::get_y() const	{ return m_y; }
const int32_t& SpawnNamedEntity::get_z() const	{ return m_z; }
const int8_t& SpawnNamedEntity::get_yaw() const	{ return m_yaw; }
const int8_t& SpawnNamedEntity::get_pitch() const	{ return m_pitch; }
const int16_t& SpawnNamedEntity::get_currentItem() const	{ return m_currentItem; }
const Metadata& SpawnNamedEntity::get_metadata() const	{ return m_metadata; }

void SpawnNamedEntity::set_eid(const int32_t& _val)	{ m_eid = _val; }
void SpawnNamedEntity::set_playerName(const std::wstring& _val)	{ m_playerName = _val; }
void SpawnNamedEntity::set_x(const int32_t& _val)	{ m_x = _val; }
void SpawnNamedEntity::set_y(const int32_t& _val)	{ m_y = _val; }
void SpawnNamedEntity::set_z(const int32_t& _val)	{ m_z = _val; }
void SpawnNamedEntity::set_yaw(const int8_t& _val)	{ m_yaw = _val; }
void SpawnNamedEntity::set_pitch(const int8_t& _val)	{ m_pitch = _val; }
void SpawnNamedEntity::set_currentItem(const int16_t& _val)	{ m_currentItem = _val; }
void SpawnNamedEntity::set_metadata(const Metadata& _val)	{ m_metadata = _val; }

// Implementation of class 0x16 CollectItem
CollectItem::CollectItem(const int32_t& _collectedEID, const int32_t& _collectorEID)
	:	m_collectedEID(_collectedEID)
	,	m_collectorEID(_collectorEID)
{}

void CollectItem::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_collectedEID);
	_dst.write(m_collectorEID);
}

void CollectItem::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_collectedEID);
	_src.read(m_collectorEID);

}

const int32_t& CollectItem::get_collectedEID() const	{ return m_collectedEID; }
const int32_t& CollectItem::get_collectorEID() const	{ return m_collectorEID; }

void CollectItem::set_collectedEID(const int32_t& _val)	{ m_collectedEID = _val; }
void CollectItem::set_collectorEID(const int32_t& _val)	{ m_collectorEID = _val; }

// Implementation of class 0x17 SpawnObjectOrVehicle
SpawnObjectOrVehicle::SpawnObjectOrVehicle(const int32_t& _eid, const int8_t& _type, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int8_t& _pitch, const int8_t& _yaw, const ObjectData& _objectData)
	:	m_eid(_eid)
	,	m_type(_type)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_pitch(_pitch)
	,	m_yaw(_yaw)
	,	m_objectData(_objectData)
{}

void SpawnObjectOrVehicle::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid);
	_dst.write(m_type);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_pitch);
	_dst.write(m_yaw);
	m_objectData.serialize(_dst);
}

void SpawnObjectOrVehicle::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid);
	_src.read(m_type);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_pitch);
	_src.read(m_yaw);
	m_objectData.deserialize(_src);

}

const int32_t& SpawnObjectOrVehicle::get_eid() const	{ return m_eid; }
const int8_t& SpawnObjectOrVehicle::get_type() const	{ return m_type; }
const int32_t& SpawnObjectOrVehicle::get_x() const	{ return m_x; }
const int32_t& SpawnObjectOrVehicle::get_y() const	{ return m_y; }
const int32_t& SpawnObjectOrVehicle::get_z() const	{ return m_z; }
const int8_t& SpawnObjectOrVehicle::get_pitch() const	{ return m_pitch; }
const int8_t& SpawnObjectOrVehicle::get_yaw() const	{ return m_yaw; }
const ObjectData& SpawnObjectOrVehicle::get_objectData() const	{ return m_objectData; }

void SpawnObjectOrVehicle::set_eid(const int32_t& _val)	{ m_eid = _val; }
void SpawnObjectOrVehicle::set_type(const int8_t& _val)	{ m_type = _val; }
void SpawnObjectOrVehicle::set_x(const int32_t& _val)	{ m_x = _val; }
void SpawnObjectOrVehicle::set_y(const int32_t& _val)	{ m_y = _val; }
void SpawnObjectOrVehicle::set_z(const int32_t& _val)	{ m_z = _val; }
void SpawnObjectOrVehicle::set_pitch(const int8_t& _val)	{ m_pitch = _val; }
void SpawnObjectOrVehicle::set_yaw(const int8_t& _val)	{ m_yaw = _val; }
void SpawnObjectOrVehicle::set_objectData(const ObjectData& _val)	{ m_objectData = _val; }

// Implementation of class 0x18 SpawnMob
SpawnMob::SpawnMob(const int32_t& _eid, const int8_t& _type, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int8_t& _pitch, const int8_t& _headPitch, const int8_t& _yaw, const int16_t& _velocityX, const int16_t& _velocityY, const int16_t& _velocityZ, const Metadata& _metadata)
	:	m_eid(_eid)
	,	m_type(_type)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_pitch(_pitch)
	,	m_headPitch(_headPitch)
	,	m_yaw(_yaw)
	,	m_velocityX(_velocityX)
	,	m_velocityY(_velocityY)
	,	m_velocityZ(_velocityZ)
	,	m_metadata(_metadata)
{}

void SpawnMob::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid);
	_dst.write(m_type);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_pitch);
	_dst.write(m_headPitch);
	_dst.write(m_yaw);
	_dst.write(m_velocityX);
	_dst.write(m_velocityY);
	_dst.write(m_velocityZ);
	m_metadata.serialize(_dst);
}

void SpawnMob::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid);
	_src.read(m_type);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_pitch);
	_src.read(m_headPitch);
	_src.read(m_yaw);
	_src.read(m_velocityX);
	_src.read(m_velocityY);
	_src.read(m_velocityZ);
	m_metadata.deserialize(_src);

}

const int32_t& SpawnMob::get_eid() const	{ return m_eid; }
const int8_t& SpawnMob::get_type() const	{ return m_type; }
const int32_t& SpawnMob::get_x() const	{ return m_x; }
const int32_t& SpawnMob::get_y() const	{ return m_y; }
const int32_t& SpawnMob::get_z() const	{ return m_z; }
const int8_t& SpawnMob::get_pitch() const	{ return m_pitch; }
const int8_t& SpawnMob::get_headPitch() const	{ return m_headPitch; }
const int8_t& SpawnMob::get_yaw() const	{ return m_yaw; }
const int16_t& SpawnMob::get_velocityX() const	{ return m_velocityX; }
const int16_t& SpawnMob::get_velocityY() const	{ return m_velocityY; }
const int16_t& SpawnMob::get_velocityZ() const	{ return m_velocityZ; }
const Metadata& SpawnMob::get_metadata() const	{ return m_metadata; }

void SpawnMob::set_eid(const int32_t& _val)	{ m_eid = _val; }
void SpawnMob::set_type(const int8_t& _val)	{ m_type = _val; }
void SpawnMob::set_x(const int32_t& _val)	{ m_x = _val; }
void SpawnMob::set_y(const int32_t& _val)	{ m_y = _val; }
void SpawnMob::set_z(const int32_t& _val)	{ m_z = _val; }
void SpawnMob::set_pitch(const int8_t& _val)	{ m_pitch = _val; }
void SpawnMob::set_headPitch(const int8_t& _val)	{ m_headPitch = _val; }
void SpawnMob::set_yaw(const int8_t& _val)	{ m_yaw = _val; }
void SpawnMob::set_velocityX(const int16_t& _val)	{ m_velocityX = _val; }
void SpawnMob::set_velocityY(const int16_t& _val)	{ m_velocityY = _val; }
void SpawnMob::set_velocityZ(const int16_t& _val)	{ m_velocityZ = _val; }
void SpawnMob::set_metadata(const Metadata& _val)	{ m_metadata = _val; }

// Implementation of class 0x19 SpawnPainting
SpawnPainting::SpawnPainting(const int32_t& _entityID, const std::wstring& _title, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int32_t& _direction)
	:	m_entityID(_entityID)
	,	m_title(_title)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_direction(_direction)
{}

void SpawnPainting::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_title);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_direction);
}

void SpawnPainting::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_title);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_direction);

}

const int32_t& SpawnPainting::get_entityID() const	{ return m_entityID; }
const std::wstring& SpawnPainting::get_title() const	{ return m_title; }
const int32_t& SpawnPainting::get_x() const	{ return m_x; }
const int32_t& SpawnPainting::get_y() const	{ return m_y; }
const int32_t& SpawnPainting::get_z() const	{ return m_z; }
const int32_t& SpawnPainting::get_direction() const	{ return m_direction; }

void SpawnPainting::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void SpawnPainting::set_title(const std::wstring& _val)	{ m_title = _val; }
void SpawnPainting::set_x(const int32_t& _val)	{ m_x = _val; }
void SpawnPainting::set_y(const int32_t& _val)	{ m_y = _val; }
void SpawnPainting::set_z(const int32_t& _val)	{ m_z = _val; }
void SpawnPainting::set_direction(const int32_t& _val)	{ m_direction = _val; }

// Implementation of class 0x1A SpawnExperienceOrb
SpawnExperienceOrb::SpawnExperienceOrb(const int32_t& _entityID, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int16_t& _count)
	:	m_entityID(_entityID)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_count(_count)
{}

void SpawnExperienceOrb::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_count);
}

void SpawnExperienceOrb::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_count);

}

const int32_t& SpawnExperienceOrb::get_entityID() const	{ return m_entityID; }
const int32_t& SpawnExperienceOrb::get_x() const	{ return m_x; }
const int32_t& SpawnExperienceOrb::get_y() const	{ return m_y; }
const int32_t& SpawnExperienceOrb::get_z() const	{ return m_z; }
const int16_t& SpawnExperienceOrb::get_count() const	{ return m_count; }

void SpawnExperienceOrb::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void SpawnExperienceOrb::set_x(const int32_t& _val)	{ m_x = _val; }
void SpawnExperienceOrb::set_y(const int32_t& _val)	{ m_y = _val; }
void SpawnExperienceOrb::set_z(const int32_t& _val)	{ m_z = _val; }
void SpawnExperienceOrb::set_count(const int16_t& _val)	{ m_count = _val; }

// Implementation of class 0x1B SteerVehicle
SteerVehicle::SteerVehicle(const float& _sideways, const float& _forward, const bool& _jump, const bool& _unmount)
	:	m_sideways(_sideways)
	,	m_forward(_forward)
	,	m_jump(_jump)
	,	m_unmount(_unmount)
{}

void SteerVehicle::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_sideways);
	_dst.write(m_forward);
	_dst.write(m_jump);
	_dst.write(m_unmount);
}

void SteerVehicle::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_sideways);
	_src.read(m_forward);
	_src.read(m_jump);
	_src.read(m_unmount);

}

const float& SteerVehicle::get_sideways() const	{ return m_sideways; }
const float& SteerVehicle::get_forward() const	{ return m_forward; }
const bool& SteerVehicle::get_jump() const	{ return m_jump; }
const bool& SteerVehicle::get_unmount() const	{ return m_unmount; }

void SteerVehicle::set_sideways(const float& _val)	{ m_sideways = _val; }
void SteerVehicle::set_forward(const float& _val)	{ m_forward = _val; }
void SteerVehicle::set_jump(const bool& _val)	{ m_jump = _val; }
void SteerVehicle::set_unmount(const bool& _val)	{ m_unmount = _val; }

// Implementation of class 0x1C EntityVelocity
EntityVelocity::EntityVelocity(const int32_t& _entityID, const int16_t& _velocityX, const int16_t& _velocityY, const int16_t& _velocityZ)
	:	m_entityID(_entityID)
	,	m_velocityX(_velocityX)
	,	m_velocityY(_velocityY)
	,	m_velocityZ(_velocityZ)
{}

void EntityVelocity::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_velocityX);
	_dst.write(m_velocityY);
	_dst.write(m_velocityZ);
}

void EntityVelocity::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_velocityX);
	_src.read(m_velocityY);
	_src.read(m_velocityZ);

}

const int32_t& EntityVelocity::get_entityID() const	{ return m_entityID; }
const int16_t& EntityVelocity::get_velocityX() const	{ return m_velocityX; }
const int16_t& EntityVelocity::get_velocityY() const	{ return m_velocityY; }
const int16_t& EntityVelocity::get_velocityZ() const	{ return m_velocityZ; }

void EntityVelocity::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void EntityVelocity::set_velocityX(const int16_t& _val)	{ m_velocityX = _val; }
void EntityVelocity::set_velocityY(const int16_t& _val)	{ m_velocityY = _val; }
void EntityVelocity::set_velocityZ(const int16_t& _val)	{ m_velocityZ = _val; }

// Implementation of class 0x1D DestroyEntity
DestroyEntity::DestroyEntity(const int8_t& _entityCount, const std::vector<int32_t>& _entityIDs)
	:	m_entityCount(_entityCount)
	,	m_entityIDs(_entityIDs)
{}

void DestroyEntity::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityCount);
	_dst.write(m_entityIDs);
}

void DestroyEntity::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityCount);
	_src.read(m_entityIDs, m_entityCount);
}

const int8_t& DestroyEntity::get_entityCount() const	{ return m_entityCount; }
const std::vector<int32_t>& DestroyEntity::get_entityIDs() const	{ return m_entityIDs; }

void DestroyEntity::set_entityCount(const int8_t& _val)	{ m_entityCount = _val; }
void DestroyEntity::set_entityIDs(const std::vector<int32_t>& _val)	{ m_entityIDs = _val; }

// Implementation of class 0x1E Entity
Entity::Entity(const int32_t& _eid)
	:	m_eid(_eid)
{}

void Entity::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid);
}

void Entity::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid);

}

const int32_t& Entity::get_eid() const	{ return m_eid; }

void Entity::set_eid(const int32_t& _val)	{ m_eid = _val; }

// Implementation of class 0x1F EntityRelativeMove
EntityRelativeMove::EntityRelativeMove(const int32_t& _eid, const int8_t& _dx, const int8_t& _dy, const int8_t& _dz)
	:	m_eid(_eid)
	,	m_dx(_dx)
	,	m_dy(_dy)
	,	m_dz(_dz)
{}

void EntityRelativeMove::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid);
	_dst.write(m_dx);
	_dst.write(m_dy);
	_dst.write(m_dz);
}

void EntityRelativeMove::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid);
	_src.read(m_dx);
	_src.read(m_dy);
	_src.read(m_dz);

}

const int32_t& EntityRelativeMove::get_eid() const	{ return m_eid; }
const int8_t& EntityRelativeMove::get_dx() const	{ return m_dx; }
const int8_t& EntityRelativeMove::get_dy() const	{ return m_dy; }
const int8_t& EntityRelativeMove::get_dz() const	{ return m_dz; }

void EntityRelativeMove::set_eid(const int32_t& _val)	{ m_eid = _val; }
void EntityRelativeMove::set_dx(const int8_t& _val)	{ m_dx = _val; }
void EntityRelativeMove::set_dy(const int8_t& _val)	{ m_dy = _val; }
void EntityRelativeMove::set_dz(const int8_t& _val)	{ m_dz = _val; }

// Implementation of class 0x20 EntityLook
EntityLook::EntityLook(const int32_t& _eid, const int8_t& _yaw, const int8_t& _pitch)
	:	m_eid(_eid)
	,	m_yaw(_yaw)
	,	m_pitch(_pitch)
{}

void EntityLook::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid);
	_dst.write(m_yaw);
	_dst.write(m_pitch);
}

void EntityLook::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid);
	_src.read(m_yaw);
	_src.read(m_pitch);

}

const int32_t& EntityLook::get_eid() const	{ return m_eid; }
const int8_t& EntityLook::get_yaw() const	{ return m_yaw; }
const int8_t& EntityLook::get_pitch() const	{ return m_pitch; }

void EntityLook::set_eid(const int32_t& _val)	{ m_eid = _val; }
void EntityLook::set_yaw(const int8_t& _val)	{ m_yaw = _val; }
void EntityLook::set_pitch(const int8_t& _val)	{ m_pitch = _val; }

// Implementation of class 0x21 EntityLookAndRelativeMove
EntityLookAndRelativeMove::EntityLookAndRelativeMove(const int32_t& _eid, const int8_t& _dx, const int8_t& _dy, const int8_t& _dz, const int8_t& _yaw, const int8_t& _pitch)
	:	m_eid(_eid)
	,	m_dx(_dx)
	,	m_dy(_dy)
	,	m_dz(_dz)
	,	m_yaw(_yaw)
	,	m_pitch(_pitch)
{}

void EntityLookAndRelativeMove::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid);
	_dst.write(m_dx);
	_dst.write(m_dy);
	_dst.write(m_dz);
	_dst.write(m_yaw);
	_dst.write(m_pitch);
}

void EntityLookAndRelativeMove::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid);
	_src.read(m_dx);
	_src.read(m_dy);
	_src.read(m_dz);
	_src.read(m_yaw);
	_src.read(m_pitch);
}

const int32_t& EntityLookAndRelativeMove::get_eid() const	{ return m_eid; }
const int8_t& EntityLookAndRelativeMove::get_dx() const	{ return m_dx; }
const int8_t& EntityLookAndRelativeMove::get_dy() const	{ return m_dy; }
const int8_t& EntityLookAndRelativeMove::get_dz() const	{ return m_dz; }
const int8_t& EntityLookAndRelativeMove::get_yaw() const	{ return m_yaw; }
const int8_t& EntityLookAndRelativeMove::get_pitch() const	{ return m_pitch; }

void EntityLookAndRelativeMove::set_eid(const int32_t& _val)	{ m_eid = _val; }
void EntityLookAndRelativeMove::set_dx(const int8_t& _val)	{ m_dx = _val; }
void EntityLookAndRelativeMove::set_dy(const int8_t& _val)	{ m_dy = _val; }
void EntityLookAndRelativeMove::set_dz(const int8_t& _val)	{ m_dz = _val; }
void EntityLookAndRelativeMove::set_yaw(const int8_t& _val)	{ m_yaw = _val; }
void EntityLookAndRelativeMove::set_pitch(const int8_t& _val)	{ m_pitch = _val; }

// Implementation of class 0x22 EntityTeleport
EntityTeleport::EntityTeleport(const int32_t& _eid, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int8_t& _yaw, const int8_t& _pitch)
	:	m_eid(_eid)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_yaw(_yaw)
	,	m_pitch(_pitch)
{}

void EntityTeleport::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_yaw);
	_dst.write(m_pitch);
}

void EntityTeleport::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_yaw);
	_src.read(m_pitch);

}

const int32_t& EntityTeleport::get_eid() const	{ return m_eid; }
const int32_t& EntityTeleport::get_x() const	{ return m_x; }
const int32_t& EntityTeleport::get_y() const	{ return m_y; }
const int32_t& EntityTeleport::get_z() const	{ return m_z; }
const int8_t& EntityTeleport::get_yaw() const	{ return m_yaw; }
const int8_t& EntityTeleport::get_pitch() const	{ return m_pitch; }

void EntityTeleport::set_eid(const int32_t& _val)	{ m_eid = _val; }
void EntityTeleport::set_x(const int32_t& _val)	{ m_x = _val; }
void EntityTeleport::set_y(const int32_t& _val)	{ m_y = _val; }
void EntityTeleport::set_z(const int32_t& _val)	{ m_z = _val; }
void EntityTeleport::set_yaw(const int8_t& _val)	{ m_yaw = _val; }
void EntityTeleport::set_pitch(const int8_t& _val)	{ m_pitch = _val; }

// Implementation of class 0x23 EntityHeadLook
EntityHeadLook::EntityHeadLook(const int32_t& _entityID, const int8_t& _headYaw)
	:	m_entityID(_entityID)
	,	m_headYaw(_headYaw)
{}

void EntityHeadLook::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_headYaw);
}

void EntityHeadLook::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_headYaw);

}

const int32_t& EntityHeadLook::get_entityID() const	{ return m_entityID; }
const int8_t& EntityHeadLook::get_headYaw() const	{ return m_headYaw; }

void EntityHeadLook::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void EntityHeadLook::set_headYaw(const int8_t& _val)	{ m_headYaw = _val; }

// Implementation of class 0x26 EntityStatus
EntityStatus::EntityStatus(const int32_t& _entityID, const int8_t& _entityStatus)
	:	m_entityID(_entityID)
	,	m_entityStatus(_entityStatus)
{}

void EntityStatus::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_entityStatus);
}

void EntityStatus::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_entityStatus);

}

const int32_t& EntityStatus::get_entityID() const	{ return m_entityID; }
const int8_t& EntityStatus::get_entityStatus() const	{ return m_entityStatus; }

void EntityStatus::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void EntityStatus::set_entityStatus(const int8_t& _val)	{ m_entityStatus = _val; }

// Implementation of class 0x27 AttachEntity
AttachEntity::AttachEntity(const int32_t& _entityID, const int32_t& _vehicleID, const uint8_t& _leash)
	:	m_entityID(_entityID)
	,	m_vehicleID(_vehicleID)
	,	m_leash(_leash)
{}

void AttachEntity::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_vehicleID);
	_dst.write(m_leash);
}

void AttachEntity::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_vehicleID);
	_src.read(m_leash);

}

const int32_t& AttachEntity::get_entityID() const	{ return m_entityID; }
const int32_t& AttachEntity::get_vehicleID() const	{ return m_vehicleID; }
const uint8_t& AttachEntity::get_leash() const	{ return m_leash; }

void AttachEntity::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void AttachEntity::set_vehicleID(const int32_t& _val)	{ m_vehicleID = _val; }
void AttachEntity::set_leash(const uint8_t& _val)	{ m_leash = _val; }

// Implementation of class 0x28 EntityMetadata
EntityMetadata::EntityMetadata(const int32_t& _entityID, const Metadata& _entityMetadata)
	:	m_entityID(_entityID)
	,	m_entityMetadata(_entityMetadata)
{}

void EntityMetadata::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	m_entityMetadata.serialize(_dst);
}

void EntityMetadata::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	m_entityMetadata.deserialize(_src);

}

const int32_t& EntityMetadata::get_entityID() const	{ return m_entityID; }
const Metadata& EntityMetadata::get_entityMetadata() const	{ return m_entityMetadata; }

void EntityMetadata::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void EntityMetadata::set_entityMetadata(const Metadata& _val)	{ m_entityMetadata = _val; }

// Implementation of class 0x29 EntityEffect
EntityEffect::EntityEffect(const int32_t& _entityID, const int8_t& _effectID, const int8_t& _amplifier, const int16_t& _duration)
	:	m_entityID(_entityID)
	,	m_effectID(_effectID)
	,	m_amplifier(_amplifier)
	,	m_duration(_duration)
{}

void EntityEffect::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_effectID);
	_dst.write(m_amplifier);
	_dst.write(m_duration);
}

void EntityEffect::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_effectID);
	_src.read(m_amplifier);
	_src.read(m_duration);

}

const int32_t& EntityEffect::get_entityID() const	{ return m_entityID; }
const int8_t& EntityEffect::get_effectID() const	{ return m_effectID; }
const int8_t& EntityEffect::get_amplifier() const	{ return m_amplifier; }
const int16_t& EntityEffect::get_duration() const	{ return m_duration; }

void EntityEffect::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void EntityEffect::set_effectID(const int8_t& _val)	{ m_effectID = _val; }
void EntityEffect::set_amplifier(const int8_t& _val)	{ m_amplifier = _val; }
void EntityEffect::set_duration(const int16_t& _val)	{ m_duration = _val; }

// Implementation of class 0x2A RemoveEntityEffect
RemoveEntityEffect::RemoveEntityEffect(const int32_t& _entityID, const int8_t& _effectID)
	:	m_entityID(_entityID)
	,	m_effectID(_effectID)
{}

void RemoveEntityEffect::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_effectID);
}

void RemoveEntityEffect::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_effectID);

}

const int32_t& RemoveEntityEffect::get_entityID() const	{ return m_entityID; }
const int8_t& RemoveEntityEffect::get_effectID() const	{ return m_effectID; }

void RemoveEntityEffect::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void RemoveEntityEffect::set_effectID(const int8_t& _val)	{ m_effectID = _val; }

// Implementation of class 0x2B SetExperience
SetExperience::SetExperience(const float& _experienceBar, const int16_t& _level, const int16_t& _totalExperience)
	:	m_experienceBar(_experienceBar)
	,	m_level(_level)
	,	m_totalExperience(_totalExperience)
{}

void SetExperience::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_experienceBar);
	_dst.write(m_level);
	_dst.write(m_totalExperience);
}

void SetExperience::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_experienceBar);
	_src.read(m_level);
	_src.read(m_totalExperience);

}

const float& SetExperience::get_experienceBar() const	{ return m_experienceBar; }
const int16_t& SetExperience::get_level() const	{ return m_level; }
const int16_t& SetExperience::get_totalExperience() const	{ return m_totalExperience; }

void SetExperience::set_experienceBar(const float& _val)	{ m_experienceBar = _val; }
void SetExperience::set_level(const int16_t& _val)	{ m_level = _val; }
void SetExperience::set_totalExperience(const int16_t& _val)	{ m_totalExperience = _val; }

// Implementation of class 0x35 BlockChange
BlockChange::BlockChange(const int32_t& _x, const int8_t& _y, const int32_t& _z, const int16_t& _blockType, const int8_t& _blockMetadata)
	:	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_blockType(_blockType)
	,	m_blockMetadata(_blockMetadata)
{}

void BlockChange::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_blockType);
	_dst.write(m_blockMetadata);
}

void BlockChange::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_blockType);
	_src.read(m_blockMetadata);

}

const int32_t& BlockChange::get_x() const	{ return m_x; }
const int8_t& BlockChange::get_y() const	{ return m_y; }
const int32_t& BlockChange::get_z() const	{ return m_z; }
const int16_t& BlockChange::get_blockType() const	{ return m_blockType; }
const int8_t& BlockChange::get_blockMetadata() const	{ return m_blockMetadata; }

void BlockChange::set_x(const int32_t& _val)	{ m_x = _val; }
void BlockChange::set_y(const int8_t& _val)	{ m_y = _val; }
void BlockChange::set_z(const int32_t& _val)	{ m_z = _val; }
void BlockChange::set_blockType(const int16_t& _val)	{ m_blockType = _val; }
void BlockChange::set_blockMetadata(const int8_t& _val)	{ m_blockMetadata = _val; }

// Implementation of class 0x36 BlockAction
BlockAction::BlockAction(const int32_t& _x, const int16_t& _y, const int32_t& _z, const int8_t& _byte1, const int8_t& _byte2, const int16_t& _blockID)
	:	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_byte1(_byte1)
	,	m_byte2(_byte2)
	,	m_blockID(_blockID)
{}

void BlockAction::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_byte1);
	_dst.write(m_byte2);
	_dst.write(m_blockID);
}

void BlockAction::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_byte1);
	_src.read(m_byte2);
	_src.read(m_blockID);

}

const int32_t& BlockAction::get_x() const	{ return m_x; }
const int16_t& BlockAction::get_y() const	{ return m_y; }
const int32_t& BlockAction::get_z() const	{ return m_z; }
const int8_t& BlockAction::get_byte1() const	{ return m_byte1; }
const int8_t& BlockAction::get_byte2() const	{ return m_byte2; }
const int16_t& BlockAction::get_blockID() const	{ return m_blockID; }

void BlockAction::set_x(const int32_t& _val)	{ m_x = _val; }
void BlockAction::set_y(const int16_t& _val)	{ m_y = _val; }
void BlockAction::set_z(const int32_t& _val)	{ m_z = _val; }
void BlockAction::set_byte1(const int8_t& _val)	{ m_byte1 = _val; }
void BlockAction::set_byte2(const int8_t& _val)	{ m_byte2 = _val; }
void BlockAction::set_blockID(const int16_t& _val)	{ m_blockID = _val; }

// Implementation of class 0x37 BlockBreakAnimation
BlockBreakAnimation::BlockBreakAnimation(const int32_t& _eid_qm, const int32_t& _x, const int32_t& _y, const int32_t& _z, const int8_t& _destroyStage)
	:	m_eid_qm(_eid_qm)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_destroyStage(_destroyStage)
{}

void BlockBreakAnimation::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_eid_qm);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_destroyStage);
}

void BlockBreakAnimation::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_eid_qm);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_destroyStage);

}

const int32_t& BlockBreakAnimation::get_eid_qm() const	{ return m_eid_qm; }
const int32_t& BlockBreakAnimation::get_x() const	{ return m_x; }
const int32_t& BlockBreakAnimation::get_y() const	{ return m_y; }
const int32_t& BlockBreakAnimation::get_z() const	{ return m_z; }
const int8_t& BlockBreakAnimation::get_destroyStage() const	{ return m_destroyStage; }

void BlockBreakAnimation::set_eid_qm(const int32_t& _val)	{ m_eid_qm = _val; }
void BlockBreakAnimation::set_x(const int32_t& _val)	{ m_x = _val; }
void BlockBreakAnimation::set_y(const int32_t& _val)	{ m_y = _val; }
void BlockBreakAnimation::set_z(const int32_t& _val)	{ m_z = _val; }
void BlockBreakAnimation::set_destroyStage(const int8_t& _val)	{ m_destroyStage = _val; }

// Implementation of class 0x3D SoundOrParticleEffect
SoundOrParticleEffect::SoundOrParticleEffect(const int32_t& _effectID, const int32_t& _x, const int8_t& _y, const int32_t& _z, const int32_t& _data, const bool& _disableRelativeVolume)
	:	m_effectID(_effectID)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_data(_data)
	,	m_disableRelativeVolume(_disableRelativeVolume)
{}

void SoundOrParticleEffect::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_effectID);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_data);
	_dst.write(m_disableRelativeVolume);
}

void SoundOrParticleEffect::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_effectID);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_data);
	_src.read(m_disableRelativeVolume);

}

const int32_t& SoundOrParticleEffect::get_effectID() const	{ return m_effectID; }
const int32_t& SoundOrParticleEffect::get_x() const	{ return m_x; }
const int8_t& SoundOrParticleEffect::get_y() const	{ return m_y; }
const int32_t& SoundOrParticleEffect::get_z() const	{ return m_z; }
const int32_t& SoundOrParticleEffect::get_data() const	{ return m_data; }
const bool& SoundOrParticleEffect::get_disableRelativeVolume() const	{ return m_disableRelativeVolume; }

void SoundOrParticleEffect::set_effectID(const int32_t& _val)	{ m_effectID = _val; }
void SoundOrParticleEffect::set_x(const int32_t& _val)	{ m_x = _val; }
void SoundOrParticleEffect::set_y(const int8_t& _val)	{ m_y = _val; }
void SoundOrParticleEffect::set_z(const int32_t& _val)	{ m_z = _val; }
void SoundOrParticleEffect::set_data(const int32_t& _val)	{ m_data = _val; }
void SoundOrParticleEffect::set_disableRelativeVolume(const bool& _val)	{ m_disableRelativeVolume = _val; }

// Implementation of class 0x3E NamedSoundEffect
NamedSoundEffect::NamedSoundEffect(const std::wstring& _soundName, const int32_t& _effectPositionX, const int32_t& _effectPositionY, const int32_t& _effectPositionZ, const float& _volume, const int8_t& _pitch)
	:	m_soundName(_soundName)
	,	m_effectPositionX(_effectPositionX)
	,	m_effectPositionY(_effectPositionY)
	,	m_effectPositionZ(_effectPositionZ)
	,	m_volume(_volume)
	,	m_pitch(_pitch)
{}

void NamedSoundEffect::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_soundName);
	_dst.write(m_effectPositionX);
	_dst.write(m_effectPositionY);
	_dst.write(m_effectPositionZ);
	_dst.write(m_volume);
	_dst.write(m_pitch);
}

void NamedSoundEffect::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_soundName);
	_src.read(m_effectPositionX);
	_src.read(m_effectPositionY);
	_src.read(m_effectPositionZ);
	_src.read(m_volume);
	_src.read(m_pitch);

}

const std::wstring& NamedSoundEffect::get_soundName() const	{ return m_soundName; }
const int32_t& NamedSoundEffect::get_effectPositionX() const	{ return m_effectPositionX; }
const int32_t& NamedSoundEffect::get_effectPositionY() const	{ return m_effectPositionY; }
const int32_t& NamedSoundEffect::get_effectPositionZ() const	{ return m_effectPositionZ; }
const float& NamedSoundEffect::get_volume() const	{ return m_volume; }
const int8_t& NamedSoundEffect::get_pitch() const	{ return m_pitch; }

void NamedSoundEffect::set_soundName(const std::wstring& _val)	{ m_soundName = _val; }
void NamedSoundEffect::set_effectPositionX(const int32_t& _val)	{ m_effectPositionX = _val; }
void NamedSoundEffect::set_effectPositionY(const int32_t& _val)	{ m_effectPositionY = _val; }
void NamedSoundEffect::set_effectPositionZ(const int32_t& _val)	{ m_effectPositionZ = _val; }
void NamedSoundEffect::set_volume(const float& _val)	{ m_volume = _val; }
void NamedSoundEffect::set_pitch(const int8_t& _val)	{ m_pitch = _val; }

// Implementation of class 0x3F Particle
Particle::Particle(const std::wstring& _particleName, const float& _x, const float& _y, const float& _z, const float& _offsetX, const float& _offsetY, const float& _offsetZ, const float& _particleSpeed, const int32_t& _numberOfParticles)
	:	m_particleName(_particleName)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_offsetX(_offsetX)
	,	m_offsetY(_offsetY)
	,	m_offsetZ(_offsetZ)
	,	m_particleSpeed(_particleSpeed)
	,	m_numberOfParticles(_numberOfParticles)
{}

void Particle::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_particleName);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_offsetX);
	_dst.write(m_offsetY);
	_dst.write(m_offsetZ);
	_dst.write(m_particleSpeed);
	_dst.write(m_numberOfParticles);
}

void Particle::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_particleName);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_offsetX);
	_src.read(m_offsetY);
	_src.read(m_offsetZ);
	_src.read(m_particleSpeed);
	_src.read(m_numberOfParticles);

}

const std::wstring& Particle::get_particleName() const	{ return m_particleName; }
const float& Particle::get_x() const	{ return m_x; }
const float& Particle::get_y() const	{ return m_y; }
const float& Particle::get_z() const	{ return m_z; }
const float& Particle::get_offsetX() const	{ return m_offsetX; }
const float& Particle::get_offsetY() const	{ return m_offsetY; }
const float& Particle::get_offsetZ() const	{ return m_offsetZ; }
const float& Particle::get_particleSpeed() const	{ return m_particleSpeed; }
const int32_t& Particle::get_numberOfParticles() const	{ return m_numberOfParticles; }

void Particle::set_particleName(const std::wstring& _val)	{ m_particleName = _val; }
void Particle::set_x(const float& _val)	{ m_x = _val; }
void Particle::set_y(const float& _val)	{ m_y = _val; }
void Particle::set_z(const float& _val)	{ m_z = _val; }
void Particle::set_offsetX(const float& _val)	{ m_offsetX = _val; }
void Particle::set_offsetY(const float& _val)	{ m_offsetY = _val; }
void Particle::set_offsetZ(const float& _val)	{ m_offsetZ = _val; }
void Particle::set_particleSpeed(const float& _val)	{ m_particleSpeed = _val; }
void Particle::set_numberOfParticles(const int32_t& _val)	{ m_numberOfParticles = _val; }

// Implementation of class 0x46 ChangeGameState
ChangeGameState::ChangeGameState(const int8_t& _reason, const int8_t& _gameMode)
	:	m_reason(_reason)
	,	m_gameMode(_gameMode)
{}

void ChangeGameState::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_reason);
	_dst.write(m_gameMode);
}

void ChangeGameState::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_reason);
	_src.read(m_gameMode);

}

const int8_t& ChangeGameState::get_reason() const	{ return m_reason; }
const int8_t& ChangeGameState::get_gameMode() const	{ return m_gameMode; }

void ChangeGameState::set_reason(const int8_t& _val)	{ m_reason = _val; }
void ChangeGameState::set_gameMode(const int8_t& _val)	{ m_gameMode = _val; }

// Implementation of class 0x47 SpawnGlobalEntity
SpawnGlobalEntity::SpawnGlobalEntity(const int32_t& _entityID, const int8_t& _type, const int32_t& _x, const int32_t& _y, const int32_t& _z)
	:	m_entityID(_entityID)
	,	m_type(_type)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
{}

void SpawnGlobalEntity::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_entityID);
	_dst.write(m_type);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
}

void SpawnGlobalEntity::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_entityID);
	_src.read(m_type);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);

}

const int32_t& SpawnGlobalEntity::get_entityID() const	{ return m_entityID; }
const int8_t& SpawnGlobalEntity::get_type() const	{ return m_type; }
const int32_t& SpawnGlobalEntity::get_x() const	{ return m_x; }
const int32_t& SpawnGlobalEntity::get_y() const	{ return m_y; }
const int32_t& SpawnGlobalEntity::get_z() const	{ return m_z; }

void SpawnGlobalEntity::set_entityID(const int32_t& _val)	{ m_entityID = _val; }
void SpawnGlobalEntity::set_type(const int8_t& _val)	{ m_type = _val; }
void SpawnGlobalEntity::set_x(const int32_t& _val)	{ m_x = _val; }
void SpawnGlobalEntity::set_y(const int32_t& _val)	{ m_y = _val; }
void SpawnGlobalEntity::set_z(const int32_t& _val)	{ m_z = _val; }

// Implementation of class 0x64 OpenWindow
OpenWindow::OpenWindow(const int8_t& _windowId, const int8_t& _inventoryType, const std::wstring& _windowTitle, const int8_t& _numberOfSlots, const bool& _useProvidedWindowTitle, const int32_t& _entityid)
	:	m_windowId(_windowId)
	,	m_inventoryType(_inventoryType)
	,	m_windowTitle(_windowTitle)
	,	m_numberOfSlots(_numberOfSlots)
	,	m_useProvidedWindowTitle(_useProvidedWindowTitle)
	,	m_entityid(_entityid)
{}

void OpenWindow::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_windowId);
	_dst.write(m_inventoryType);
	_dst.write(m_windowTitle);
	_dst.write(m_numberOfSlots);
	_dst.write(m_useProvidedWindowTitle);
	_dst.write(m_entityid);
}

void OpenWindow::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_windowId);
	_src.read(m_inventoryType);
	_src.read(m_windowTitle);
	_src.read(m_numberOfSlots);
	_src.read(m_useProvidedWindowTitle);
	_src.read(m_entityid);

}

const int8_t& OpenWindow::get_windowId() const	{ return m_windowId; }
const int8_t& OpenWindow::get_inventoryType() const	{ return m_inventoryType; }
const std::wstring& OpenWindow::get_windowTitle() const	{ return m_windowTitle; }
const int8_t& OpenWindow::get_numberOfSlots() const	{ return m_numberOfSlots; }
const bool& OpenWindow::get_useProvidedWindowTitle() const	{ return m_useProvidedWindowTitle; }
const int32_t& OpenWindow::get_entityid() const	{ return m_entityid; }

void OpenWindow::set_windowId(const int8_t& _val)	{ m_windowId = _val; }
void OpenWindow::set_inventoryType(const int8_t& _val)	{ m_inventoryType = _val; }
void OpenWindow::set_windowTitle(const std::wstring& _val)	{ m_windowTitle = _val; }
void OpenWindow::set_numberOfSlots(const int8_t& _val)	{ m_numberOfSlots = _val; }
void OpenWindow::set_useProvidedWindowTitle(const bool& _val)	{ m_useProvidedWindowTitle = _val; }
void OpenWindow::set_entityid(const int32_t& _val)	{ m_entityid = _val; }

// Implementation of class 0x65 CloseWindow
CloseWindow::CloseWindow(const int8_t& _windowId)
	:	m_windowId(_windowId)
{}

void CloseWindow::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_windowId);
}

void CloseWindow::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_windowId);

}

const int8_t& CloseWindow::get_windowId() const	{ return m_windowId; }

void CloseWindow::set_windowId(const int8_t& _val)	{ m_windowId = _val; }

// Implementation of class 0x66 ClickWindow
ClickWindow::ClickWindow(const int8_t& _windowId, const int16_t& _slot, const int8_t& _button, const int16_t& _actionNumber, const int8_t& _mode, const SlotData& _clickedItem)
	:	m_windowId(_windowId)
	,	m_slot(_slot)
	,	m_button(_button)
	,	m_actionNumber(_actionNumber)
	,	m_mode(_mode)
	,	m_clickedItem(_clickedItem)
{}

void ClickWindow::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_windowId);
	_dst.write(m_slot);
	_dst.write(m_button);
	_dst.write(m_actionNumber);
	_dst.write(m_mode);
	m_clickedItem.serialize(_dst);
}

void ClickWindow::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_windowId);
	_src.read(m_slot);
	_src.read(m_button);
	_src.read(m_actionNumber);
	_src.read(m_mode);
	m_clickedItem.deserialize(_src);

}

const int8_t& ClickWindow::get_windowId() const	{ return m_windowId; }
const int16_t& ClickWindow::get_slot() const	{ return m_slot; }
const int8_t& ClickWindow::get_button() const	{ return m_button; }
const int16_t& ClickWindow::get_actionNumber() const	{ return m_actionNumber; }
const int8_t& ClickWindow::get_mode() const	{ return m_mode; }
const SlotData& ClickWindow::get_clickedItem() const	{ return m_clickedItem; }

void ClickWindow::set_windowId(const int8_t& _val)	{ m_windowId = _val; }
void ClickWindow::set_slot(const int16_t& _val)	{ m_slot = _val; }
void ClickWindow::set_button(const int8_t& _val)	{ m_button = _val; }
void ClickWindow::set_actionNumber(const int16_t& _val)	{ m_actionNumber = _val; }
void ClickWindow::set_mode(const int8_t& _val)	{ m_mode = _val; }
void ClickWindow::set_clickedItem(const SlotData& _val)	{ m_clickedItem = _val; }

// Implementation of class 0x67 SetSlot
SetSlot::SetSlot(const int8_t& _windowId, const int16_t& _slot, const SlotData& _slotData)
	:	m_windowId(_windowId)
	,	m_slot(_slot)
	,	m_slotData(_slotData)
{}

void SetSlot::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_windowId);
	_dst.write(m_slot);
	m_slotData.serialize(_dst);
}

void SetSlot::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_windowId);
	_src.read(m_slot);
	m_slotData.deserialize(_src);

}

const int8_t& SetSlot::get_windowId() const	{ return m_windowId; }
const int16_t& SetSlot::get_slot() const	{ return m_slot; }
const SlotData& SetSlot::get_slotData() const	{ return m_slotData; }

void SetSlot::set_windowId(const int8_t& _val)	{ m_windowId = _val; }
void SetSlot::set_slot(const int16_t& _val)	{ m_slot = _val; }
void SetSlot::set_slotData(const SlotData& _val)	{ m_slotData = _val; }

// Implementation of class 0x68 SetWindowItems
SetWindowItems::SetWindowItems(const int8_t& _windowId, const int16_t& _count, const std::vector<SlotData>& _slotData)
	:	m_windowId(_windowId)
	,	m_count(_count)
	,	m_slotData(_slotData)
{}

void SetWindowItems::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_windowId);
	_dst.write(m_count);
	for(auto itr = m_slotData.begin(); itr != m_slotData.end(); ++itr)
		itr->serialize(_dst);
}

void SetWindowItems::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_windowId);
	_src.read(m_count);
	m_slotData.resize(m_count);
	for(auto itr = m_slotData.begin(); itr != m_slotData.end(); ++itr)
		itr->deserialize(_src);
}

const int8_t& SetWindowItems::get_windowId() const	{ return m_windowId; }
const int16_t& SetWindowItems::get_count() const	{ return m_count; }
const std::vector<SlotData>& SetWindowItems::get_slotData() const	{ return m_slotData; }

void SetWindowItems::set_windowId(const int8_t& _val)	{ m_windowId = _val; }
void SetWindowItems::set_count(const int16_t& _val)	{ m_count = _val; }
void SetWindowItems::set_slotData(const std::vector<SlotData>& _val)	{ m_slotData = _val; }

// Implementation of class 0x69 UpdateWindowProperty
UpdateWindowProperty::UpdateWindowProperty(const int8_t& _windowId, const int16_t& _property, const int16_t& _value)
	:	m_windowId(_windowId)
	,	m_property(_property)
	,	m_value(_value)
{}

void UpdateWindowProperty::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_windowId);
	_dst.write(m_property);
	_dst.write(m_value);
}

void UpdateWindowProperty::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_windowId);
	_src.read(m_property);
	_src.read(m_value);

}

const int8_t& UpdateWindowProperty::get_windowId() const	{ return m_windowId; }
const int16_t& UpdateWindowProperty::get_property() const	{ return m_property; }
const int16_t& UpdateWindowProperty::get_value() const	{ return m_value; }

void UpdateWindowProperty::set_windowId(const int8_t& _val)	{ m_windowId = _val; }
void UpdateWindowProperty::set_property(const int16_t& _val)	{ m_property = _val; }
void UpdateWindowProperty::set_value(const int16_t& _val)	{ m_value = _val; }

// Implementation of class 0x6A ConfirmTransaction
ConfirmTransaction::ConfirmTransaction(const int8_t& _windowId, const int16_t& _actionNumber, const bool& _accepted_qm)
	:	m_windowId(_windowId)
	,	m_actionNumber(_actionNumber)
	,	m_accepted_qm(_accepted_qm)
{}

void ConfirmTransaction::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_windowId);
	_dst.write(m_actionNumber);
	_dst.write(m_accepted_qm);
}

void ConfirmTransaction::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_windowId);
	_src.read(m_actionNumber);
	_src.read(m_accepted_qm);

}

const int8_t& ConfirmTransaction::get_windowId() const	{ return m_windowId; }
const int16_t& ConfirmTransaction::get_actionNumber() const	{ return m_actionNumber; }
const bool& ConfirmTransaction::get_accepted_qm() const	{ return m_accepted_qm; }

void ConfirmTransaction::set_windowId(const int8_t& _val)	{ m_windowId = _val; }
void ConfirmTransaction::set_actionNumber(const int16_t& _val)	{ m_actionNumber = _val; }
void ConfirmTransaction::set_accepted_qm(const bool& _val)	{ m_accepted_qm = _val; }

// Implementation of class 0x6B CreativeInventoryAction
CreativeInventoryAction::CreativeInventoryAction(const int16_t& _slot, const SlotData& _clickedItem)
	:	m_slot(_slot)
	,	m_clickedItem(_clickedItem)
{}

void CreativeInventoryAction::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_slot);
	m_clickedItem.serialize(_dst);
}

void CreativeInventoryAction::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_slot);
	m_clickedItem.deserialize(_src);

}

const int16_t& CreativeInventoryAction::get_slot() const	{ return m_slot; }
const SlotData& CreativeInventoryAction::get_clickedItem() const	{ return m_clickedItem; }

void CreativeInventoryAction::set_slot(const int16_t& _val)	{ m_slot = _val; }
void CreativeInventoryAction::set_clickedItem(const SlotData& _val)	{ m_clickedItem = _val; }

// Implementation of class 0x6C EnchantItem
EnchantItem::EnchantItem(const int8_t& _windowID, const int8_t& _enchantment)
	:	m_windowID(_windowID)
	,	m_enchantment(_enchantment)
{}

void EnchantItem::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_windowID);
	_dst.write(m_enchantment);
}

void EnchantItem::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_windowID);
	_src.read(m_enchantment);

}

const int8_t& EnchantItem::get_windowID() const	{ return m_windowID; }
const int8_t& EnchantItem::get_enchantment() const	{ return m_enchantment; }

void EnchantItem::set_windowID(const int8_t& _val)	{ m_windowID = _val; }
void EnchantItem::set_enchantment(const int8_t& _val)	{ m_enchantment = _val; }

// Implementation of class 0x82 UpdateSign
UpdateSign::UpdateSign(const int32_t& _x, const int16_t& _y, const int32_t& _z, const std::wstring& _text1, const std::wstring& _text2, const std::wstring& _text3, const std::wstring& _text4)
	:	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_text1(_text1)
	,	m_text2(_text2)
	,	m_text3(_text3)
	,	m_text4(_text4)
{}

void UpdateSign::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_text1);
	_dst.write(m_text2);
	_dst.write(m_text3);
	_dst.write(m_text4);
}

void UpdateSign::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_text1);
	_src.read(m_text2);
	_src.read(m_text3);
	_src.read(m_text4);

}

const int32_t& UpdateSign::get_x() const	{ return m_x; }
const int16_t& UpdateSign::get_y() const	{ return m_y; }
const int32_t& UpdateSign::get_z() const	{ return m_z; }
const std::wstring& UpdateSign::get_text1() const	{ return m_text1; }
const std::wstring& UpdateSign::get_text2() const	{ return m_text2; }
const std::wstring& UpdateSign::get_text3() const	{ return m_text3; }
const std::wstring& UpdateSign::get_text4() const	{ return m_text4; }

void UpdateSign::set_x(const int32_t& _val)	{ m_x = _val; }
void UpdateSign::set_y(const int16_t& _val)	{ m_y = _val; }
void UpdateSign::set_z(const int32_t& _val)	{ m_z = _val; }
void UpdateSign::set_text1(const std::wstring& _val)	{ m_text1 = _val; }
void UpdateSign::set_text2(const std::wstring& _val)	{ m_text2 = _val; }
void UpdateSign::set_text3(const std::wstring& _val)	{ m_text3 = _val; }
void UpdateSign::set_text4(const std::wstring& _val)	{ m_text4 = _val; }

// Implementation of class 0x83 ItemData
ItemData::ItemData(const int16_t& _itemType, const int16_t& _itemID, const int16_t& _textLength, const std::vector<int8_t>& _text)
	:	m_itemType(_itemType)
	,	m_itemID(_itemID)
	,	m_textLength(_textLength)
	,	m_text(_text)
{}

void ItemData::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_itemType);
	_dst.write(m_itemID);
	_dst.write(m_textLength);
	_dst.write(m_text);
}

void ItemData::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_itemType);
	_src.read(m_itemID);
	_src.read(m_textLength);
	_src.read(m_text, m_textLength);

}

const int16_t& ItemData::get_itemType() const	{ return m_itemType; }
const int16_t& ItemData::get_itemID() const	{ return m_itemID; }
const int16_t& ItemData::get_textLength() const	{ return m_textLength; }
const std::vector<int8_t>& ItemData::get_text() const	{ return m_text; }

void ItemData::set_itemType(const int16_t& _val)	{ m_itemType = _val; }
void ItemData::set_itemID(const int16_t& _val)	{ m_itemID = _val; }
void ItemData::set_textLength(const int16_t& _val)	{ m_textLength = _val; }
void ItemData::set_text(const std::vector<int8_t>& _val)	{ m_text = _val; }

// Implementation of class 0x84 UpdateTileEntity
UpdateTileEntity::UpdateTileEntity(const int32_t& _x, const int16_t& _y, const int32_t& _z, const int8_t& _action, const int16_t& _dataLength, const std::vector<int8_t>& _nbtData)
	:	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
	,	m_action(_action)
	,	m_dataLength(_dataLength)
	,	m_nbtData(_nbtData)
{}

void UpdateTileEntity::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
	_dst.write(m_action);
	_dst.write(m_dataLength);
	_dst.write(m_nbtData);
}

void UpdateTileEntity::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);
	_src.read(m_action);
	_src.read(m_dataLength);
	_src.read(m_nbtData, m_dataLength);

}

const int32_t& UpdateTileEntity::get_x() const	{ return m_x; }
const int16_t& UpdateTileEntity::get_y() const	{ return m_y; }
const int32_t& UpdateTileEntity::get_z() const	{ return m_z; }
const int8_t& UpdateTileEntity::get_action() const	{ return m_action; }
const int16_t& UpdateTileEntity::get_dataLength() const	{ return m_dataLength; }
const std::vector<int8_t>& UpdateTileEntity::get_nbtData() const	{ return m_nbtData; }

void UpdateTileEntity::set_x(const int32_t& _val)	{ m_x = _val; }
void UpdateTileEntity::set_y(const int16_t& _val)	{ m_y = _val; }
void UpdateTileEntity::set_z(const int32_t& _val)	{ m_z = _val; }
void UpdateTileEntity::set_action(const int8_t& _val)	{ m_action = _val; }
void UpdateTileEntity::set_dataLength(const int16_t& _val)	{ m_dataLength = _val; }
void UpdateTileEntity::set_nbtData(const std::vector<int8_t>& _val)	{ m_nbtData = _val; }

// Implementation of class 0x85 TileEditorOpen_qm
TileEditorOpen_qm::TileEditorOpen_qm(const int8_t& _tileEntityId, const int32_t& _x, const int32_t& _y, const int32_t& _z)
	:	m_tileEntityId(_tileEntityId)
	,	m_x(_x)
	,	m_y(_y)
	,	m_z(_z)
{}

void TileEditorOpen_qm::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_tileEntityId);
	_dst.write(m_x);
	_dst.write(m_y);
	_dst.write(m_z);
}

void TileEditorOpen_qm::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_tileEntityId);
	_src.read(m_x);
	_src.read(m_y);
	_src.read(m_z);

}

const int8_t& TileEditorOpen_qm::get_tileEntityId() const	{ return m_tileEntityId; }
const int32_t& TileEditorOpen_qm::get_x() const	{ return m_x; }
const int32_t& TileEditorOpen_qm::get_y() const	{ return m_y; }
const int32_t& TileEditorOpen_qm::get_z() const	{ return m_z; }

void TileEditorOpen_qm::set_tileEntityId(const int8_t& _val)	{ m_tileEntityId = _val; }
void TileEditorOpen_qm::set_x(const int32_t& _val)	{ m_x = _val; }
void TileEditorOpen_qm::set_y(const int32_t& _val)	{ m_y = _val; }
void TileEditorOpen_qm::set_z(const int32_t& _val)	{ m_z = _val; }

// Implementation of class 0xC8 IncrementStatistic
IncrementStatistic::IncrementStatistic(const int32_t& _statisticID, const int32_t& _amount)
	:	m_statisticID(_statisticID)
	,	m_amount(_amount)
{}

void IncrementStatistic::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_statisticID);
	_dst.write(m_amount);
}

void IncrementStatistic::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_statisticID);
	_src.read(m_amount);

}

const int32_t& IncrementStatistic::get_statisticID() const	{ return m_statisticID; }
const int32_t& IncrementStatistic::get_amount() const	{ return m_amount; }

void IncrementStatistic::set_statisticID(const int32_t& _val)	{ m_statisticID = _val; }
void IncrementStatistic::set_amount(const int32_t& _val)	{ m_amount = _val; }

// Implementation of class 0xC9 PlayerListItem
PlayerListItem::PlayerListItem(const std::wstring& _playerName, const bool& _online, const int16_t& _ping)
	:	m_playerName(_playerName)
	,	m_online(_online)
	,	m_ping(_ping)
{}

void PlayerListItem::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_playerName);
	_dst.write(m_online);
	_dst.write(m_ping);
}

void PlayerListItem::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_playerName);
	_src.read(m_online);
	_src.read(m_ping);

}

const std::wstring& PlayerListItem::get_playerName() const	{ return m_playerName; }
const bool& PlayerListItem::get_online() const	{ return m_online; }
const int16_t& PlayerListItem::get_ping() const	{ return m_ping; }

void PlayerListItem::set_playerName(const std::wstring& _val)	{ m_playerName = _val; }
void PlayerListItem::set_online(const bool& _val)	{ m_online = _val; }
void PlayerListItem::set_ping(const int16_t& _val)	{ m_ping = _val; }

// Implementation of class 0xCA PlayerAbilities
PlayerAbilities::PlayerAbilities(const int8_t& _flags, const float& _flyingSpeed, const float& _walkingSpeed)
	:	m_flags(_flags)
	,	m_flyingSpeed(_flyingSpeed)
	,	m_walkingSpeed(_walkingSpeed)
{}

void PlayerAbilities::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_flags);
	_dst.write(m_flyingSpeed);
	_dst.write(m_walkingSpeed);
}

void PlayerAbilities::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_flags);
	_src.read(m_flyingSpeed);
	_src.read(m_walkingSpeed);

}

const int8_t& PlayerAbilities::get_flags() const	{ return m_flags; }
const float& PlayerAbilities::get_flyingSpeed() const	{ return m_flyingSpeed; }
const float& PlayerAbilities::get_walkingSpeed() const	{ return m_walkingSpeed; }

void PlayerAbilities::set_flags(const int8_t& _val)	{ m_flags = _val; }
void PlayerAbilities::set_flyingSpeed(const float& _val)	{ m_flyingSpeed = _val; }
void PlayerAbilities::set_walkingSpeed(const float& _val)	{ m_walkingSpeed = _val; }

// Implementation of class 0xCB TabComplete
TabComplete::TabComplete(const std::wstring& _text)
	:	m_text(_text)
{}

void TabComplete::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_text);
}

void TabComplete::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_text);

}

const std::wstring& TabComplete::get_text() const	{ return m_text; }

void TabComplete::set_text(const std::wstring& _val)	{ m_text = _val; }

// Implementation of class 0xCC ClientSettings
ClientSettings::ClientSettings(const std::wstring& _locale, const int8_t& _viewDistance, const int8_t& _chatFlags, const int8_t& _difficulty, const bool& _showCape)
	:	m_locale(_locale)
	,	m_viewDistance(_viewDistance)
	,	m_chatFlags(_chatFlags)
	,	m_difficulty(_difficulty)
	,	m_showCape(_showCape)
{}

void ClientSettings::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_locale);
	_dst.write(m_viewDistance);
	_dst.write(m_chatFlags);
	_dst.write(m_difficulty);
	_dst.write(m_showCape);
}

void ClientSettings::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_locale);
	_src.read(m_viewDistance);
	_src.read(m_chatFlags);
	_src.read(m_difficulty);
	_src.read(m_showCape);

}

const std::wstring& ClientSettings::get_locale() const	{ return m_locale; }
const int8_t& ClientSettings::get_viewDistance() const	{ return m_viewDistance; }
const int8_t& ClientSettings::get_chatFlags() const	{ return m_chatFlags; }
const int8_t& ClientSettings::get_difficulty() const	{ return m_difficulty; }
const bool& ClientSettings::get_showCape() const	{ return m_showCape; }

void ClientSettings::set_locale(const std::wstring& _val)	{ m_locale = _val; }
void ClientSettings::set_viewDistance(const int8_t& _val)	{ m_viewDistance = _val; }
void ClientSettings::set_chatFlags(const int8_t& _val)	{ m_chatFlags = _val; }
void ClientSettings::set_difficulty(const int8_t& _val)	{ m_difficulty = _val; }
void ClientSettings::set_showCape(const bool& _val)	{ m_showCape = _val; }

// Implementation of class 0xCD ClientStatuses
ClientStatuses::ClientStatuses(const int8_t& _payload)
	:	m_payload(_payload)
{}

void ClientStatuses::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_payload);
}

void ClientStatuses::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_payload);

}

const int8_t& ClientStatuses::get_payload() const	{ return m_payload; }

void ClientStatuses::set_payload(const int8_t& _val)	{ m_payload = _val; }

// Implementation of class 0xCE ScoreboardObjective
ScoreboardObjective::ScoreboardObjective(const std::wstring& _objectiveName, const std::wstring& _objectiveValue, const int8_t& _createOrRemove)
	:	m_objectiveName(_objectiveName)
	,	m_objectiveValue(_objectiveValue)
	,	m_createOrRemove(_createOrRemove)
{}

void ScoreboardObjective::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_objectiveName);
	_dst.write(m_objectiveValue);
	_dst.write(m_createOrRemove);
}

void ScoreboardObjective::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_objectiveName);
	_src.read(m_objectiveValue);
	_src.read(m_createOrRemove);

}

const std::wstring& ScoreboardObjective::get_objectiveName() const	{ return m_objectiveName; }
const std::wstring& ScoreboardObjective::get_objectiveValue() const	{ return m_objectiveValue; }
const int8_t& ScoreboardObjective::get_createOrRemove() const	{ return m_createOrRemove; }

void ScoreboardObjective::set_objectiveName(const std::wstring& _val)	{ m_objectiveName = _val; }
void ScoreboardObjective::set_objectiveValue(const std::wstring& _val)	{ m_objectiveValue = _val; }
void ScoreboardObjective::set_createOrRemove(const int8_t& _val)	{ m_createOrRemove = _val; }

// Implementation of class 0xCF UpdateScore
UpdateScore::UpdateScore(const std::wstring& _itemName, const int8_t& _updateOrRemove, const std::wstring& _scoreName, const int32_t& _value)
	:	m_itemName(_itemName)
	,	m_updateOrRemove(_updateOrRemove)
	,	m_scoreName(_scoreName)
	,	m_value(_value)
{}

void UpdateScore::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_itemName);
	_dst.write(m_updateOrRemove);
	_dst.write(m_scoreName);
	_dst.write(m_value);
}

void UpdateScore::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_itemName);
	_src.read(m_updateOrRemove);
	_src.read(m_scoreName);
	_src.read(m_value);

}

const std::wstring& UpdateScore::get_itemName() const	{ return m_itemName; }
const int8_t& UpdateScore::get_updateOrRemove() const	{ return m_updateOrRemove; }
const std::wstring& UpdateScore::get_scoreName() const	{ return m_scoreName; }
const int32_t& UpdateScore::get_value() const	{ return m_value; }

void UpdateScore::set_itemName(const std::wstring& _val)	{ m_itemName = _val; }
void UpdateScore::set_updateOrRemove(const int8_t& _val)	{ m_updateOrRemove = _val; }
void UpdateScore::set_scoreName(const std::wstring& _val)	{ m_scoreName = _val; }
void UpdateScore::set_value(const int32_t& _val)	{ m_value = _val; }

// Implementation of class 0xD0 DisplayScoreboard
DisplayScoreboard::DisplayScoreboard(const int8_t& _position, const std::wstring& _scoreName)
	:	m_position(_position)
	,	m_scoreName(_scoreName)
{}

void DisplayScoreboard::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_position);
	_dst.write(m_scoreName);
}

void DisplayScoreboard::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_position);
	_src.read(m_scoreName);

}

const int8_t& DisplayScoreboard::get_position() const	{ return m_position; }
const std::wstring& DisplayScoreboard::get_scoreName() const	{ return m_scoreName; }

void DisplayScoreboard::set_position(const int8_t& _val)	{ m_position = _val; }
void DisplayScoreboard::set_scoreName(const std::wstring& _val)	{ m_scoreName = _val; }

// Implementation of class 0xFA PluginMessage
PluginMessage::PluginMessage(const std::wstring& _channel, const int16_t& _length, const std::vector<int8_t>& _data)
	:	m_channel(_channel)
	,	m_length(_length)
	,	m_data(_data)
{}

void PluginMessage::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_channel);
	_dst.write(m_length);
	_dst.write(m_data);
}

void PluginMessage::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_channel);
	_src.read(m_length);
	_src.read(m_data, m_length);

}

const std::wstring& PluginMessage::get_channel() const	{ return m_channel; }
const int16_t& PluginMessage::get_length() const	{ return m_length; }
const std::vector<int8_t>& PluginMessage::get_data() const	{ return m_data; }

void PluginMessage::set_channel(const std::wstring& _val)	{ m_channel = _val; }
void PluginMessage::set_length(const int16_t& _val)	{ m_length = _val; }
void PluginMessage::set_data(const std::vector<int8_t>& _val)	{ m_data = _val; }

// Implementation of class 0xFC EncryptionKeyResponse
EncryptionKeyResponse::EncryptionKeyResponse(const int16_t& _sharedSecretLength, const std::vector<int8_t>& _sharedSecret, const int16_t& _verifyTokenLength, const std::vector<int8_t>& _verifyTokenResponse)
	:	m_sharedSecretLength(_sharedSecretLength)
	,	m_sharedSecret(_sharedSecret)
	,	m_verifyTokenLength(_verifyTokenLength)
	,	m_verifyTokenResponse(_verifyTokenResponse)
{}

void EncryptionKeyResponse::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_sharedSecretLength);
	_dst.write(m_sharedSecret);
	_dst.write(m_verifyTokenLength);
	_dst.write(m_verifyTokenResponse);
}

void EncryptionKeyResponse::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_sharedSecretLength);
	_src.read(m_sharedSecret, m_sharedSecretLength);
	_src.read(m_verifyTokenLength);
	_src.read(m_verifyTokenResponse, m_verifyTokenLength);

}

const int16_t& EncryptionKeyResponse::get_sharedSecretLength() const	{ return m_sharedSecretLength; }
const std::vector<int8_t>& EncryptionKeyResponse::get_sharedSecret() const	{ return m_sharedSecret; }
const int16_t& EncryptionKeyResponse::get_verifyTokenLength() const	{ return m_verifyTokenLength; }
const std::vector<int8_t>& EncryptionKeyResponse::get_verifyTokenResponse() const	{ return m_verifyTokenResponse; }

void EncryptionKeyResponse::set_sharedSecretLength(const int16_t& _val)	{ m_sharedSecretLength = _val; }
void EncryptionKeyResponse::set_sharedSecret(const std::vector<int8_t>& _val)	{ m_sharedSecret = _val; }
void EncryptionKeyResponse::set_verifyTokenLength(const int16_t& _val)	{ m_verifyTokenLength = _val; }
void EncryptionKeyResponse::set_verifyTokenResponse(const std::vector<int8_t>& _val)	{ m_verifyTokenResponse = _val; }

// Implementation of class 0xFD EncryptionKeyRequest
EncryptionKeyRequest::EncryptionKeyRequest(const std::wstring& _serverId, const int16_t& _publicKeyLength, const std::vector<int8_t>& _publicKey, const int16_t& _verifyTokenLength, const std::vector<int8_t>& _verifyToken)
	:	m_serverId(_serverId)
	,	m_publicKeyLength(_publicKeyLength)
	,	m_publicKey(_publicKey)
	,	m_verifyTokenLength(_verifyTokenLength)
	,	m_verifyToken(_verifyToken)
{}

void EncryptionKeyRequest::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_serverId);
	_dst.write(m_publicKeyLength);
	_dst.write(m_publicKey);
	_dst.write(m_verifyTokenLength);
	_dst.write(m_verifyToken);
}

void EncryptionKeyRequest::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_serverId);
	_src.read(m_publicKeyLength);
	_src.read(m_publicKey, m_publicKeyLength);
	_src.read(m_verifyTokenLength);
	_src.read(m_verifyToken, m_verifyTokenLength);

}

const std::wstring& EncryptionKeyRequest::get_serverId() const	{ return m_serverId; }
const int16_t& EncryptionKeyRequest::get_publicKeyLength() const	{ return m_publicKeyLength; }
const std::vector<int8_t>& EncryptionKeyRequest::get_publicKey() const	{ return m_publicKey; }
const int16_t& EncryptionKeyRequest::get_verifyTokenLength() const	{ return m_verifyTokenLength; }
const std::vector<int8_t>& EncryptionKeyRequest::get_verifyToken() const	{ return m_verifyToken; }

void EncryptionKeyRequest::set_serverId(const std::wstring& _val)	{ m_serverId = _val; }
void EncryptionKeyRequest::set_publicKeyLength(const int16_t& _val)	{ m_publicKeyLength = _val; }
void EncryptionKeyRequest::set_publicKey(const std::vector<int8_t>& _val)	{ m_publicKey = _val; }
void EncryptionKeyRequest::set_verifyTokenLength(const int16_t& _val)	{ m_verifyTokenLength = _val; }
void EncryptionKeyRequest::set_verifyToken(const std::vector<int8_t>& _val)	{ m_verifyToken = _val; }

// Implementation of class 0xFE ServerListPing
ServerListPing::ServerListPing(const int8_t& _magic)
	:	m_magic(_magic)
{}

void ServerListPing::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_magic);
}

void ServerListPing::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_magic);

}

const int8_t& ServerListPing::get_magic() const	{ return m_magic; }

void ServerListPing::set_magic(const int8_t& _val)	{ m_magic = _val; }

// Implementation of class 0xFF DisconnectOrKick
DisconnectOrKick::DisconnectOrKick(const std::wstring& _reason)
	:	m_reason(_reason)
{}

void DisconnectOrKick::serialize(BinaryBuffer& _dst)
{
	_dst.write(m_messageCode);
	_dst.write(m_reason);
}

void DisconnectOrKick::deserialize(BinaryBuffer& _src)
{
	uint8_t code;
	_src.read(code);
	if(code != m_messageCode) throw WrongMessageException();

	_src.read(m_reason);

}

const std::wstring& DisconnectOrKick::get_reason() const	{ return m_reason; }

void DisconnectOrKick::set_reason(const std::wstring& _val)	{ m_reason = _val; }


} // namespace msg
} // namespace protocol
