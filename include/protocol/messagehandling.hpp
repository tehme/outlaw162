#ifndef _PROTOCOL_MESSAGE_HANDLING_HPP_
#define _PROTOCOL_MESSAGE_HANDLING_HPP_

#include <cstdint>
#include <map>
#include "messages.hpp"


namespace protocol {

size_t SkipMessage(const protocol::BinaryBuffer& _src, size_t _offset);


template<class CallbackMapT, class ClientInfoT> // ClientInfoT should be renamed
size_t HandleMessage(const protocol::BinaryBuffer& _src, size_t _offset, 
	const CallbackMapT& _callbacks, ClientInfoT& _clientInfo)
{
	auto itr = _callbacks.find(_src[_offset]);
	if(itr != _callbacks.end())
		return itr->second(_src, _offset, _clientInfo);

	else
		return SkipMessage(_src, _offset);
}


template<class CallbackMapT, class ClientInfoT>
void HandleMessages(protocol::BinaryBuffer& _buf, const CallbackMapT& _callbacks, ClientInfoT& _clientInfo)
{
	static size_t offset = 0; // remove static if not necessary

	while(1)
	{
		if(_buf.size() == 0)
			break;
		if(offset == _buf.size())
		{
			_buf.clear();
			offset = 0;
			break;
		}

		try
		{			
			offset = HandleMessage(_buf, offset, _callbacks, _clientInfo);
		}
		catch(PartialMessageException)
		{
			_buf.erase(_buf.begin(), _buf.begin() + offset);
			offset = 0;
			break;
		}		
	}
}

} // namespace protocol

#endif // _PROTOCOL_MESSAGE_HANDLING_HPP_