/*
 * Copyright (c) 2013 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>

#include <Sluift/GenericLuaElementConvertor.h>
#include <Swiften/Elements/PubSubRetract.h>

namespace Swift {
	class LuaElementConvertors;

	class PubSubRetractConvertor : public GenericLuaElementConvertor<PubSubRetract> {
		public:
			PubSubRetractConvertor(LuaElementConvertors* convertors);
			virtual ~PubSubRetractConvertor();

			virtual boost::shared_ptr<PubSubRetract> doConvertFromLua(lua_State*) SWIFTEN_OVERRIDE;
			virtual void doConvertToLua(lua_State*, boost::shared_ptr<PubSubRetract>) SWIFTEN_OVERRIDE;
			virtual boost::optional<Documentation> getDocumentation() const SWIFTEN_OVERRIDE;

		private:
			LuaElementConvertors* convertors;
	};
}
