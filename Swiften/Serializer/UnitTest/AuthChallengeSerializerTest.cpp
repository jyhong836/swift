/*
 * Copyright (c) 2010 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "Swiften/Serializer/AuthChallengeSerializer.h"
#include "Swiften/Elements/AuthChallenge.h"

using namespace Swift;

class AuthChallengeSerializerTest : public CppUnit::TestFixture {
		CPPUNIT_TEST_SUITE(AuthChallengeSerializerTest);
		CPPUNIT_TEST(testSerialize);
		CPPUNIT_TEST(testSerialize_NoMessage);
		CPPUNIT_TEST(testSerialize_EmptyMessage);
		CPPUNIT_TEST_SUITE_END();

	public:
		void testSerialize() {
			AuthChallengeSerializer testling;
			boost::shared_ptr<AuthChallenge> authChallenge(new AuthChallenge());
			authChallenge->setValue("foo");

			CPPUNIT_ASSERT_EQUAL(String(
				"<challenge xmlns=\"urn:ietf:params:xml:ns:xmpp-sasl\">"
					"Zm9v"
				"</challenge>"), testling.serialize(authChallenge));
		}

		void testSerialize_NoMessage() {
			AuthChallengeSerializer testling;
			boost::shared_ptr<AuthChallenge> authChallenge(new AuthChallenge());

			CPPUNIT_ASSERT_EQUAL(String(
				"<challenge xmlns=\"urn:ietf:params:xml:ns:xmpp-sasl\">"
				"</challenge>"), testling.serialize(authChallenge));
		}

		void testSerialize_EmptyMessage() {
			AuthChallengeSerializer testling;
			boost::shared_ptr<AuthChallenge> authChallenge(new AuthChallenge());
			authChallenge->setValue(ByteArray());

			CPPUNIT_ASSERT_EQUAL(String(
				"<challenge xmlns=\"urn:ietf:params:xml:ns:xmpp-sasl\">"
					"="
				"</challenge>"), testling.serialize(authChallenge));
		}
};

CPPUNIT_TEST_SUITE_REGISTRATION(AuthChallengeSerializerTest);