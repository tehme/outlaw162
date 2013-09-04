//#include "callbacks.hpp"
//
//
//size_t Handler_0x00_KeepAlive(const protocol::BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
//{
//	std::cout << "Keep alive!" << std::endl;
//	return protocol::msg::KeepAlive().deserialize(_src, _offset);
//}
//
//size_t Handler_0x03_Chat(const protocol::BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
//{
//	protocol::msg::ChatMessage chatMsg;
//	_offset = chatMsg.deserialize(_src, _offset);
//	std::wcout << L"Chat message." << std::endl << chatMsg.get_jsonStr() << std::endl;
//	return _offset;
//}
//
//size_t Handler_0x06_SpawnPosition(const protocol::BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
//{
//	protocol::msg::SpawnPosition sp;
//	_offset = sp.deserialize(_src, _offset);
//	std::cout << "Spawn Position: " << sp.get_x() << " " << sp.get_y() << " " << sp.get_z() << std::endl;
//	return _offset;
//}
//
//size_t Handler_0x08_UpdateHealth(const protocol::BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
//{
//	protocol::msg::UpdateHealth tmp;
//	_offset = tmp.deserialize(_src, _offset);
//	std::cout << "Health updated! Health: " << tmp.get_health() << "; Food: " << tmp.get_food() << std::endl;
//	_clientInfo.m_hp = tmp.get_health();
//
//	return _offset;
//}
//
//size_t Handler_0x0D_PlayerPositionAndLook(const protocol::BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
//{
//	if(_clientInfo.m_initialPosGot == false)
//		_clientInfo.m_initialPosGot = true;
//
//	_offset = _clientInfo.m_playerPosLook.deserialize_stc(_src, _offset);
//
//	std::cout	<< "Player position: " 
//				<< _clientInfo.m_playerPosLook.get_x() << " "
//				<< _clientInfo.m_playerPosLook.get_y() << " "
//				<< _clientInfo.m_playerPosLook.get_z() << std::endl;
//
//	return _offset;
//}
//
//size_t Handler_0xFF_DisconnectOrKick(const protocol::BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo)
//{
//	protocol::msg::DisconnectOrKick dok;
//	_offset = dok.deserialize(_src, _offset);
//	std::cout << "Disconnected." << std::endl;
//
//	return _offset;
//}