#include "messagehandling.hpp"


namespace protocol {

size_t SkipMessage(const protocol::BinaryBuffer& _src, size_t _offset)
{

	switch(_src[_offset])
	{
		case 0x00:	_offset = msg::KeepAlive().deserialize(_src, _offset);					break;
		case 0x01:	_offset = msg::LoginRequest().deserialize(_src, _offset);				break;
		case 0x03:	_offset = msg::ChatMessage().deserialize(_src, _offset);				break;
		case 0x04:	_offset = msg::TimeUpdate().deserialize(_src, _offset);					break;
		case 0x05:	_offset = msg::EntityEquipment().deserialize(_src, _offset);			break;
		case 0x06:	_offset = msg::SpawnPosition().deserialize(_src, _offset);				break;
		case 0x08:	_offset = msg::UpdateHealth().deserialize(_src, _offset);				break;
		case 0x09:	_offset = msg::Respawn().deserialize(_src, _offset);					break;
		case 0x0D:	_offset = msg::PlayerPositionAndLook().deserialize(_src, _offset);		break;
		case 0x10:	_offset = msg::HeldItemChange().deserialize(_src, _offset);				break;
		case 0x11:	_offset = msg::UseBed().deserialize(_src, _offset);						break;
		case 0x12:	_offset = msg::Animation().deserialize(_src, _offset);					break;
		case 0x14:	_offset = msg::SpawnNamedEntity().deserialize(_src, _offset);			break;
		case 0x16:	_offset = msg::CollectItem().deserialize(_src, _offset);				break;
		case 0x17:	_offset = msg::SpawnObjectOrVehicle().deserialize(_src, _offset);		break;
		case 0x18:	_offset = msg::SpawnMob().deserialize(_src, _offset);					break;
		case 0x19:	_offset = msg::SpawnPainting().deserialize(_src, _offset);				break;
		case 0x1A:	_offset = msg::SpawnExperienceOrb().deserialize(_src, _offset);			break;
		case 0x1C:	_offset = msg::EntityVelocity().deserialize(_src, _offset);				break;
		case 0x1D:	_offset = msg::DestroyEntity().deserialize(_src, _offset);				break;
		case 0x1E:	_offset = msg::Entity().deserialize(_src, _offset);						break;
		case 0x1F:	_offset = msg::EntityRelativeMove().deserialize(_src, _offset);			break;
		case 0x20:	_offset = msg::EntityLook().deserialize(_src, _offset);					break;
		case 0x21:	_offset = msg::EntityLookAndRelativeMove().deserialize(_src, _offset);	break;
		case 0x22:	_offset = msg::EntityTeleport().deserialize(_src, _offset);				break;
		case 0x23:	_offset = msg::EntityHeadLook().deserialize(_src, _offset);				break;
		case 0x26:	_offset = msg::EntityStatus().deserialize(_src, _offset);				break;
		case 0x27:	_offset = msg::AttachEntity().deserialize(_src, _offset);				break;
		case 0x28:	_offset = msg::EntityMetadata().deserialize(_src, _offset);				break;
		case 0x29:	_offset = msg::EntityEffect().deserialize(_src, _offset);				break;
		case 0x2A:	_offset = msg::RemoveEntityEffect().deserialize(_src, _offset);			break;
		case 0x2B:	_offset = msg::SetExperience().deserialize(_src, _offset);				break;
		case 0x2C:	_offset = msg::EntityProperties().deserialize(_src, _offset);			break;
		case 0x33:	_offset = msg::ChunkColumnData().deserialize(_src, _offset);			break;
		case 0x34:	_offset = msg::MultiBlockChange().deserialize(_src, _offset);			break;
		case 0x35:	_offset = msg::BlockChange().deserialize(_src, _offset);				break;
		case 0x36:	_offset = msg::BlockAction().deserialize(_src, _offset);				break;
		case 0x37:	_offset = msg::BlockBreakAnimation().deserialize(_src, _offset);		break;
		case 0x38:	_offset = msg::MapChunkBulk().deserialize(_src, _offset);				break;
		case 0x3C:	_offset = msg::Explosion().deserialize(_src, _offset);					break;
		case 0x3D:	_offset = msg::SoundOrParticleEffect().deserialize(_src, _offset);		break;
		case 0x3E:	_offset = msg::NamedSoundEffect().deserialize(_src, _offset);			break;
		case 0x46:	_offset = msg::ChangeGameState().deserialize(_src, _offset);			break;
		case 0x67:	_offset = msg::SetSlot().deserialize(_src, _offset);					break;
		case 0x68:	_offset = msg::SetWindowItems().deserialize(_src, _offset);				break;
		case 0x84:	_offset = msg::UpdateTileEntity().deserialize(_src, _offset);			break;
		case 0xC8:	_offset = msg::IncrementStatistic().deserialize(_src, _offset);			break;
		case 0xC9:	_offset = msg::PlayerListItem().deserialize(_src, _offset);				break;
		case 0xCA:	_offset = msg::PlayerAbilities().deserialize(_src, _offset);			break;
		case 0xD1:	_offset = msg::Teams().deserialize(_src, _offset);						break;
		case 0xFA:	_offset = msg::PluginMessage().deserialize(_src, _offset);				break;
		case 0xFD:	_offset = msg::EncryptionKeyRequest().deserialize(_src, _offset);		break;
		case 0xFF:	_offset = msg::DisconnectOrKick().deserialize(_src, _offset);			break;

		default:
		{
			std::cout << __FUNCTION__ << ": unknown message: " << std::hex << _src[_offset] << std::dec << std::endl;
			return UINT32_MAX;
		}
	}

	return _offset;
}

} // namespace protocol