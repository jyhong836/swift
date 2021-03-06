/*
 * Copyright (c) 2010-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Queries/GenericRequest.h>
#include <Swiften/Elements/VCard.h>

namespace Swift {
	class SWIFTEN_API GetVCardRequest : public GenericRequest<VCard> {
		public:
			typedef boost::shared_ptr<GetVCardRequest> ref;

			static ref create(const JID& jid, IQRouter* router) {
				return ref(new GetVCardRequest(jid, router));
			}

		private:
			GetVCardRequest(const JID& jid, IQRouter* router) : GenericRequest<VCard>(IQ::Get, jid, boost::shared_ptr<Payload>(new VCard()), router) {
			}
	};
}
