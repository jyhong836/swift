/*
 * Copyright (c) 2011 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swiften/Serializer/PayloadSerializers/MUCInvitationPayloadSerializer.h>

#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>

#include <Swiften/Base/foreach.h>
#include <Swiften/Serializer/XML/XMLElement.h>
#include <Swiften/Serializer/XML/XMLTextNode.h>
#include <Swiften/Serializer/PayloadSerializers/MUCItemSerializer.h>


namespace Swift {

MUCInvitationPayloadSerializer::MUCInvitationPayloadSerializer() : GenericPayloadSerializer<MUCInvitationPayload>() {
}

std::string MUCInvitationPayloadSerializer::serializePayload(boost::shared_ptr<MUCInvitationPayload> payload)  const {
	XMLElement mucElement("x", "jabber:x:conference");
	if (payload->getIsContinuation()) {
		mucElement.setAttribute("continue", "true");
	}
	if (payload->getJID().isValid()) {
		mucElement.setAttribute("jid", payload->getJID().toString());
	}
	if (!payload->getPassword().empty()) {
		mucElement.setAttribute("password", payload->getPassword());
	}
	if (!payload->getReason().empty()) {
		mucElement.setAttribute("reason", payload->getReason());
	}
	if (!payload->getThread().empty()) {
		mucElement.setAttribute("thread", payload->getThread());
	}
	if (payload->getIsImpromptu()) {
		mucElement.addNode(boost::make_shared<XMLElement>("impromptu", "http://swift.im/impromptu"));
	}
	return mucElement.serialize();
}


}
