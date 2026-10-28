#include "stdafx.h"
#include "sol_bindings.h"
#include "stdlib.h"
#include "spell.h"
#include "spell_book.h"
#include "../../../inc/gameworld/spell_set.h"

int sol_spell_book_open(lua_State* L)
{
    sol::state_view lua(L);
    sol::table globals = lua.globals();
    auto type1 = cqyh::lua::usertype<ISpellBook>(L, globals, "ISpellBook", "ISpellBook");
    type1.set_function("BeginSpellSet", [](ISpellBook* self) -> decltype(auto) { self->BeginSpellSet(); });
    type1.set_function("NextSpellSet", [](ISpellBook* self) -> decltype(auto) { return self->NextSpellSet(); });
    type1.set_function("GetSpellSet", [](ISpellBook* self, signed int nSpellID) -> decltype(auto) { return self->GetSpellSet(nSpellID); });
    return 1;
}
