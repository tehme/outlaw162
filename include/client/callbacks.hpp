#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

#include <iostream>
#include "../protocol/protocol.hpp"

struct ClientInfo;

size_t Handler_0x00_KeepAlive(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo);
size_t Handler_0x03_Chat(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo);
size_t Handler_0x06_SpawnPosition(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo);
size_t Handler_0x08_UpdateHealth(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo);
size_t Handler_0x0D_PlayerPositionAndLook(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo);
size_t Handler_0xFF_DisconnectOrKick(const BinaryBuffer& _src, size_t _offset, ClientInfo& _clientInfo);


#endif // _CALLBACKS_HPP_