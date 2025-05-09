#include <iostream>
#include "lualib.h"
#include "io.hpp"

#define LS_INDENT(rep) std::string("   ", rep)

namespace ls {
    void LPrintString(lua_State* L, int idx, std::ostream& out, int indent = 0) {
        out << LS_INDENT(indent) << luaL_checkstring(L, idx);
    }

    void LPrintNumber(lua_State* L, int idx, std::ostream& out, int indent = 0) {
        out << LS_INDENT(indent) << luaL_checknumber(L, idx);
    }

    bool LIsInline(lua_State* L, int idx) {

        int nums = 0;
        int len = 0;

        lua_pushnil(L);
        while (lua_next(L, idx)) {
            if (lua_type(L, -2) == LUA_TNUMBER) {
                nums++;
            }
            len++;
            lua_pop(L, 1);
        }
        return nums == len || len < 4;
    }

    void LPrintTable(lua_State* L, int idx, std::ostream& out, int indent = 0) {
        lua_pushvalue(L, idx);
        lua_pushnil(L);

        out << LS_INDENT(indent) << "{";

        bool nline = LIsInline(L, idx);

        int len = 0;
        while (lua_next(L, -2)) {
            if (len != 0) {
                out << ",";
            }

            if (!nline) {
                out << std::endl;
            }

            if (!nline) {
                out << LS_INDENT(indent+1);
            }

            LPrintValue(L, -2, out, 0);
            out << " = ";
            LPrintValue(L, -1, out, 0);
            
            len++;
            lua_pop(L, 1);
        }

        if (!nline) {
            out << std::endl;
        }

        out << LS_INDENT(indent) << "}";
    }

    void LPrintValue(lua_State* L, int idx, std::ostream& out, int indent) {
        if (lua_isnumber(L, idx)) {
            LPrintNumber(L, idx, out, indent);
            return;
        }

        if (lua_isstring(L, idx)) {
            LPrintString(L, idx, out, indent);
            return;
        }

        if (lua_istable(L, idx)) {
            LPrintTable(L, idx, out, indent);
            return;
        }
    }

    int LPrint(lua_State* L) {
        int nargs = lua_gettop(L);
        for (int i = 1; i <= nargs; i++) {
            LPrintValue(L, i, std::cout, 0);
        }
        std::cout << std::endl;
        return 0;
    }
}