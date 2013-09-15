#ifndef _PROTOCOL_MESSAGE_HANDLING_HPP_
#define _PROTOCOL_MESSAGE_HANDLING_HPP_

#include <cstdint>
#include <map>
#include "messages.hpp"


namespace protocol {

void SkipMessage(protocol::BinaryBuffer& _src);


template<class CallbackMapT, class ClientInfoT> // ClientInfoT should be renamed
void HandleMessage(protocol::BinaryBuffer& _src, const CallbackMapT& _callbacks, ClientInfoT& _clientInfo)
{
	auto itr = _callbacks.find(_src.atOffset());
	if(itr != _callbacks.end())
		itr->second(_src, _clientInfo);

	else
		SkipMessage(_src);
}


template<class CallbackMapT, class ClientInfoT>
void HandleMessages(protocol::BinaryBuffer& _buf, const CallbackMapT& _callbacks, ClientInfoT& _clientInfo)
{
	//static size_t offset = 0; // remove static if not necessary
	size_t msgBeginOff = 0;

	while(1)
	{
		if(_buf.getSize() == 0)
			return;
		if(_buf.getOffset() == _buf.getSize())
		{
			_buf.clear();
			return;
		}

		msgBeginOff = _buf.getOffset(); // to restore correct offset if reading fails
		try
		{			
			HandleMessage(_buf, _callbacks, _clientInfo);
		}
		catch(BinaryBuffer::PartialMessageException&)
		{
			_buf.removeDataUntil(msgBeginOff);
			return;
		}		
	}
}

} // namespace protocol

#endif // _PROTOCOL_MESSAGE_HANDLING_HPP_