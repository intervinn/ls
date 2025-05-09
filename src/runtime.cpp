
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>

#include "luacode.h"
#include "lualib.h"
#include "lua.h"

#include "io.hpp"

#include "runtime.hpp"

namespace ls {
    lua_State* newState() {
        auto L = luaL_newstate(); 
        luaL_openlibs(L);

        lua_pushcfunction(L, LPrint, "print");
        lua_setglobal(L, "print");

        return L;
    }

    void doFile(lua_State* L, std::string path, Luau::CompileOptions copts) {
        std::ifstream file(path);
        if (!file.is_open()) {
            return;
        }
    
        std::stringstream src_stream;
        src_stream << file.rdbuf();
        std::string src = src_stream.str();
        file.close();
    
        doString(L, src, copts);
    }

    void doString(lua_State* L, std::string src, Luau::CompileOptions copts) {
        auto bytecode = Luau::compile(src, copts);

        if (luau_load(L, "main", bytecode.c_str(), bytecode.size(), 0) != 0) {
            lua_pop(L, 1);
            throw std::runtime_error(lua_tostring(L, -1));
        }

        if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
            lua_pop(L, 1);
            throw std::runtime_error(lua_tostring(L, -1));
        }
    }
}