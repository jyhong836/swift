/*
 * Copyright (c) 2013 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include <Swiften/Base/Override.h>
#include <Swiften/Base/API.h>
#include <Swiften/Elements/PubSubError.h>
#include <Swiften/Parser/GenericPayloadParser.h>
#include <Swiften/Parser/EnumParser.h>

namespace Swift {
	class PayloadParserFactoryCollection;
	class PayloadParser;

	class SWIFTEN_API PubSubErrorParser : public GenericPayloadParser<PubSubError> {
		public:
			PubSubErrorParser();
			virtual ~PubSubErrorParser();

			virtual void handleStartElement(const std::string& element, const std::string&, const AttributeMap& attributes) SWIFTEN_OVERRIDE;
			virtual void handleEndElement(const std::string& element, const std::string&) SWIFTEN_OVERRIDE;
			virtual void handleCharacterData(const std::string& data) SWIFTEN_OVERRIDE;

		private:
			int level;
			EnumParser<PubSubError::Type> typeParser;
			EnumParser<PubSubError::UnsupportedFeatureType> unsupportedTypeParser;
	};
}
