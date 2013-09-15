#include "messagehandling.hpp"


namespace protocol {

void SkipMessage(protocol::BinaryBuffer& _src)
{

	switch(_src.atOffset())
	{
		case 0x00:	msg::KeepAlive().deserialize(_src);					break;
		case 0x01:	msg::LoginRequest().deserialize(_src);				break;
		case 0x03:	msg::ChatMessage().deserialize(_src);				break;
		case 0x04:	msg::TimeUpdate().deserialize(_src);				break;
		case 0x05:	msg::EntityEquipment().deserialize(_src);			break;
		case 0x06:	msg::SpawnPosition().deserialize(_src);				break;
		case 0x08:	msg::UpdateHealth().deserialize(_src);				break;
		case 0x09:	msg::Respawn().deserialize(_src);					break;
		case 0x0D:	msg::PlayerPositionAndLook().deserialize(_src);		break;
		case 0x10:	msg::HeldItemChange().deserialize(_src);			break;
		case 0x11:	msg::UseBed().deserialize(_src);					break;
		case 0x12:	msg::Animation().deserialize(_src);					break;
		case 0x14:	msg::SpawnNamedEntity().deserialize(_src);			break;
		case 0x16:	msg::CollectItem().deserialize(_src);				break;
		case 0x17:	msg::SpawnObjectOrVehicle().deserialize(_src);		break;
		case 0x18:	msg::SpawnMob().deserialize(_src);					break;
		case 0x19:	msg::SpawnPainting().deserialize(_src);				break;
		case 0x1A:	msg::SpawnExperienceOrb().deserialize(_src);		break;
		case 0x1C:	msg::EntityVelocity().deserialize(_src);			break;
		case 0x1D:	msg::DestroyEntity().deserialize(_src);				break;
		case 0x1E:	msg::Entity().deserialize(_src);					break;
		case 0x1F:	msg::EntityRelativeMove().deserialize(_src);		break;
		case 0x20:	msg::EntityLook().deserialize(_src);				break;
		case 0x21:	msg::EntityLookAndRelativeMove().deserialize(_src);	break;
		case 0x22:	msg::EntityTeleport().deserialize(_src);			break;
		case 0x23:	msg::EntityHeadLook().deserialize(_src);			break;
		case 0x26:	msg::EntityStatus().deserialize(_src);				break;
		case 0x27:	msg::AttachEntity().deserialize(_src);				break;
		case 0x28:	msg::EntityMetadata().deserialize(_src);			break;
		case 0x29:	msg::EntityEffect().deserialize(_src);				break;
		case 0x2A:	msg::RemoveEntityEffect().deserialize(_src);		break;
		case 0x2B:	msg::SetExperience().deserialize(_src);				break;
		case 0x2C:	msg::EntityProperties().deserialize(_src);			break;
		case 0x33:	msg::ChunkColumnData().deserialize(_src);			break;
		case 0x34:	msg::MultiBlockChange().deserialize(_src);			break;
		case 0x35:	msg::BlockChange().deserialize(_src);				break;
		case 0x36:	msg::BlockAction().deserialize(_src);				break;
		case 0x37:	msg::BlockBreakAnimation().deserialize(_src);		break;
		case 0x38:	msg::MapChunkBulk().deserialize(_src);				break;
		case 0x3C:	msg::Explosion().deserialize(_src);					break;
		case 0x3D:	msg::SoundOrParticleEffect().deserialize(_src);		break;
		case 0x3E:	msg::NamedSoundEffect().deserialize(_src);			break;
		case 0x46:	msg::ChangeGameState().deserialize(_src);			break;
		case 0x67:	msg::SetSlot().deserialize(_src);					break;
		case 0x68:	msg::SetWindowItems().deserialize(_src);			break;
		case 0x84:	msg::UpdateTileEntity().deserialize(_src);			break;
		case 0xC8:	msg::IncrementStatistic().deserialize(_src);		break;
		case 0xC9:	msg::PlayerListItem().deserialize(_src);			break;
		case 0xCA:	msg::PlayerAbilities().deserialize(_src);			break;
		case 0xD1:	msg::Teams().deserialize(_src);						break;
		case 0xFA:	msg::PluginMessage().deserialize(_src);				break;
		case 0xFD:	msg::EncryptionKeyRequest().deserialize(_src);		break;
		case 0xFF:	msg::DisconnectOrKick().deserialize(_src);			break;

		default:
		{
			std::cout << __FUNCTION__ << ": unknown message: " << std::hex << uint32_t(_src.atOffset()) << std::dec << std::endl;
		}
	}

}

} // namespace protocol