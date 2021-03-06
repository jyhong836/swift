/*
 * Copyright (c) 2010-2015 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <Swiften/Base/API.h>
#include <Swiften/Base/SafeByteArray.h>

namespace Swift {
	class SWIFTEN_API CertificateWithKey {
		public:
			typedef boost::shared_ptr<CertificateWithKey> ref;
			CertificateWithKey() {}

			virtual ~CertificateWithKey() {}

			virtual bool isNull() const = 0;

	};
}
