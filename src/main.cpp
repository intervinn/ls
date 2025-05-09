
#include "Luau/Compiler.h"
#include "lua.h"
#include "luaconf.h"
#include "lualib.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "runtime.hpp"

int main() {
    auto L = ls::newState();

    Luau::CompileOptions copts{};

    try {
        ls::doFile(L, "example/main.luau", copts);
    } catch (Luau::CompileError& err) {
        std::cout << "compile error: " << err.what() << std::endl;
    } catch (std::runtime_error& err) {
        std::cout << "runtime error:" << err.what() << std::endl;
    } catch (std::exception& err) {
        std::cout << "exception: " << err.what() << std::endl;
    }

    lua_close(L);
    return 0;
}