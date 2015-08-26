/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <iostream>
#include <boost/optional.hpp>

#include <Swiften/Parser/PresenceParser.h>

namespace Swift {

PresenceParser::PresenceParser(PayloadParserFactoryCollection* factories) : 
		GenericStanzaParser<Presence>(factories) {
}

void PresenceParser::handleStanzaAttributes(const AttributeMap& attributes) {
	boost::optional<std::string> type = attributes.getAttributeValue("type");
	if (type) {
		if (*type == "unavailable") {
			getStanzaGeneric()->setType(Presence::Unavailable);
		}
		else if (*type == "probe") {
			getStanzaGeneric()->setType(Presence::Probe);
		}
		else if (*type == "subscribe") {
			getStanzaGeneric()->setType(Presence::Subscribe);
		}
		else if (*type == "subscribed") {
			getStanzaGeneric()->setType(Presence::Subscribed);
		}
		else if (*type == "unsubscribe") {
			getStanzaGeneric()->setType(Presence::Unsubscribe);
		}
		else if (*type == "unsubscribed") {
			getStanzaGeneric()->setType(Presence::Unsubscribed);
		}
		else if (*type == "error") {
			getStanzaGeneric()->setType(Presence::Error);
		}
		#ifdef SWIFTEN_INVISIBLE_PRESENCE
			else if (*type == "invisible") {
				getStanzaGeneric()->setType(Presence::Invisible);
			}
			else if (*type == "visible") {
				getStanzaGeneric()->setType(Presence::Visible);
			}
		#endif // SWIFTEN_INVISIBLE_PRESENCE
		else {
			std::cerr << "Unknown Presence type: " << *type << std::endl;
			getStanzaGeneric()->setType(Presence::Available);
		}
	}
	else {
		getStanzaGeneric()->setType(Presence::Available);
	}
}

}
