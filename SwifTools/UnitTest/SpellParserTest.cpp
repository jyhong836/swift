/*
 * Copyright (c) 2012 Vlad Voicu
 * Licensed under the Simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include <boost/algorithm/string.hpp>

#include <SwifTools/SpellParser.h>

using namespace Swift;

class SpellParserTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(SpellParserTest);
	CPPUNIT_TEST(testSimpleCheckFragment);
	CPPUNIT_TEST(testWWWCheckFragment);
	CPPUNIT_TEST_SUITE_END();
	public:
		SpellParserTest() {
			parser_ = new SpellParser();
		};
		void tearDown() {
			position_.clear();
		}
		void testSimpleCheckFragment() {
			parser_->check("fragment test", position_);
			int size = position_.size();
			CPPUNIT_ASSERT_EQUAL(2, size);
			CPPUNIT_ASSERT_EQUAL(0, boost::get<0>(position_.front()));
			CPPUNIT_ASSERT_EQUAL(8, boost::get<1>(position_.front()));
			CPPUNIT_ASSERT_EQUAL(9, boost::get<0>(position_.back()));
			CPPUNIT_ASSERT_EQUAL(13, boost::get<1>(position_.back()));
		}
		void testWWWCheckFragment() {
			parser_->check("www.link.com fragment test", position_);
			int size = position_.size();
			CPPUNIT_ASSERT_EQUAL(2, size);
			CPPUNIT_ASSERT_EQUAL(13, boost::get<0>(position_.front()));
			CPPUNIT_ASSERT_EQUAL(21, boost::get<1>(position_.front()));
			CPPUNIT_ASSERT_EQUAL(22, boost::get<0>(position_.back()));
			CPPUNIT_ASSERT_EQUAL(26, boost::get<1>(position_.back()));
		}
	private:
		SpellParser *parser_;
		PositionPairList position_;
};

CPPUNIT_TEST_SUITE_REGISTRATION(SpellParserTest);
