/*
 * Copyright (c) 2010-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Serializer/GenericPayloadSerializer.h>
#include <Swiften/Elements/Command.h>

namespace Swift {
	class SWIFTEN_API CommandSerializer : public GenericPayloadSerializer<Command> {
		public:
			CommandSerializer();

			virtual std::string serializePayload(boost::shared_ptr<Command>)  const;

		private:
			std::string actionToString(Command::Action action) const;
	};
}
