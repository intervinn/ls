
#pragma once
#include <sstream>

#include "lua.h"

namespace ls {
    void LPrintValue(lua_State* L, int idx, std::ostream& out, int indent = 0);
    int LPrint(lua_State* L);
}