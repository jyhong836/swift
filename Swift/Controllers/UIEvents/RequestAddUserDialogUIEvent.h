/*
 * Copyright (c) 2010-2012 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include "Swift/Controllers/UIEvents/UIEvent.h"
#include <string>
#include <Swiften/JID/JID.h>


namespace Swift {
	class RequestAddUserDialogUIEvent : public UIEvent {

		public:
			RequestAddUserDialogUIEvent(const JID& predefinedJID, const std::string& predefinedName) : preJID_(predefinedJID), preName_(predefinedName) {}
			RequestAddUserDialogUIEvent() : preJID_(), preName_() {}

			const JID& getPredefinedJID() const { return preJID_; }
			const std::string& getPredefinedName() const { return preName_; }

		private:
			JID preJID_;
			std::string preName_;

	};
}
