
#pragma once

#include "lua.h"
#include "Luau/Compiler.h"

namespace ls {
    lua_State* newState();
    void doFile(lua_State* L, std::string path, Luau::CompileOptions copts);
    void doString(lua_State* L, std::string src, Luau::CompileOptions copts);
}