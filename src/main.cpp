
#include "Luau/Compiler.h"
#include "lua.h"
#include "luaconf.h"
#include "lualib.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int Lfizzbuzz(lua_State* L) {
    std::string n = luaL_checkstring(L, 1);
    if (n == "fizz") {
        lua_pushstring(L, "buzz");
    } else if (n == "buzz") {
        lua_pushstring(L, "fizz");
    } else {
        lua_pushstring(L, "what");
    }

    return 1;
}

int main() {
    auto L = luaL_newstate(); 
    luaL_openlibs(L);
    lua_pushcfunction(L, Lfizzbuzz, "fizzbuzz");
    lua_setglobal(L, "buzz");

    Luau::CompileOptions copts = {};
    copts.optimizationLevel = 2;
    copts.debugLevel = 2;
    copts.typeInfoLevel = 1;
    copts.coverageLevel = 0;

    std::ifstream i;
    std::string line;
    std::string src = "";
    i.open("example/main.luau");
    while (i) {
        std::getline(i, src);
        src += line;
    }
    i.close();

    lua_checkstack(L, LUA_MINSTACK);
    auto bytecode = Luau::compile(src, copts);
    auto result = luau_load(L, "woo", bytecode.c_str(), bytecode.size(), 0);
    
    std::cout << "res: " << result << std::endl;
    if (result == 0) {
        int n = lua_gettop(L);
        if (n) {
             lua_pcall(L, 0, LUA_MULTRET, 0);
        }
    }
}