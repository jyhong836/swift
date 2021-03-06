/*
 * Copyright (c) 2014 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Sluift/ElementConvertors/StatusShowConvertor.h>

#include <lua.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <Sluift/Lua/Check.h>
#include <Sluift/Lua/Exception.h>

using namespace Swift;

StatusShowConvertor::StatusShowConvertor() : GenericLuaElementConvertor<StatusShow>("show") {
}

StatusShowConvertor::~StatusShowConvertor() {
}

boost::shared_ptr<StatusShow> StatusShowConvertor::doConvertFromLua(lua_State* L) {
	boost::shared_ptr<StatusShow> result = boost::make_shared<StatusShow>();
	lua_getfield(L, -1, "type");
	if (lua_isstring(L, -1)) {
		result->setType(convertStatusShowTypeFromString(lua_tostring(L, -1)));
	}
	lua_pop(L, 1);
	return result;
}

void StatusShowConvertor::doConvertToLua(lua_State* L, boost::shared_ptr<StatusShow> payload) {
	lua_createtable(L, 0, 0);
	const std::string show = convertStatusShowTypeToString(payload->getType());
	if (!show.empty()) {
		lua_pushstring(L, show.c_str());
		lua_setfield(L, -2, "type");
	}
}

std::string StatusShowConvertor::convertStatusShowTypeToString(const StatusShow::Type &show) {
	switch (show) {
		case StatusShow::Online: return "online";
		case StatusShow::FFC: return "ffc";
		case StatusShow::Away: return "away";
		case StatusShow::XA: return "xa";
		case StatusShow::DND: return "dnd";
		case StatusShow::None: return "";
	}
	assert(false);
	return "";
}

StatusShow::Type StatusShowConvertor::convertStatusShowTypeFromString(const std::string& show) {
	if (show == "online") {
		return StatusShow::Online;
	}
	else if (show == "ffc") {
		return StatusShow::FFC;
	}
	else if (show == "away") {
		return StatusShow::Away;
	}
	else if (show == "xa") {
		return StatusShow::XA;
	}
	else if (show == "dnd") {
		return StatusShow::DND;
	}
	else {
		throw Lua::Exception("Illegal status show: '" + show + "'");
	}
}
