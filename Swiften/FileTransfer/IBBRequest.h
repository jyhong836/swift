/*
 * Copyright (c) 2010-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Queries/GenericRequest.h>
#include <Swiften/Elements/IBB.h>


namespace Swift {
	class SWIFTEN_API IBBRequest : public GenericRequest<IBB> {
		public:
			typedef boost::shared_ptr<IBBRequest> ref;

			static ref create(const JID& from, const JID& to, boost::shared_ptr<IBB> payload, IQRouter* router) {
				return ref(new IBBRequest(from, to, payload, router));
			}

		private:
			IBBRequest(const JID& from, const JID& to, boost::shared_ptr<IBB> payload, IQRouter* router) : GenericRequest<IBB>(IQ::Set, from, to, payload, router) {
			}
	};
}
