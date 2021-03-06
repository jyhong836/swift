/*
 * Copyright (c) 2011 Tobias Markmann
 * Licensed under the simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

/*
 * Copyright (c) 2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */


#pragma once

#include <boost/shared_ptr.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Disco/DiscoServiceWalker.h>
#include <Swiften/Network/HostAddressPort.h>
#include <Swiften/Elements/S5BProxyRequest.h>

namespace Swift {

class JID;
class IQRouter;

/*
 * This class is designed to find possible SOCKS5 bytestream proxies which are used for peer-to-peer data transfers in
 * restrictive environments.
 */
class SWIFTEN_API SOCKS5BytestreamProxyFinder {
	public:
		SOCKS5BytestreamProxyFinder(const JID& service, IQRouter *iqRouter);
		~SOCKS5BytestreamProxyFinder();

		void start();
		void stop();

		boost::signal<void(boost::shared_ptr<S5BProxyRequest>)> onProxyFound;

	private:
		void sendBytestreamQuery(const JID&);

		void handleServiceFound(const JID&, boost::shared_ptr<DiscoInfo>);
		void handleProxyResponse(boost::shared_ptr<S5BProxyRequest>, ErrorPayload::ref);
	private:
		JID service;
		IQRouter* iqRouter;
		boost::shared_ptr<DiscoServiceWalker> serviceWalker;
		std::vector<boost::shared_ptr<GenericRequest<S5BProxyRequest> > > requests;
	};

}
