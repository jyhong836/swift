/*
 * Copyright (c) 2013 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/Override.h>
#include <Swiften/Base/API.h>
#include <Swiften/FileTransfer/FileTransferError.h>
#include <Swiften/Base/boost_bsignals.h>

namespace Swift {
	class SWIFTEN_API TransportSession {
		public:
			virtual ~TransportSession();

			virtual void start() = 0;
			virtual void stop() = 0;

			boost::signal<void (size_t)> onBytesSent;
			boost::signal<void (boost::optional<FileTransferError>)> onFinished;
	};
}
