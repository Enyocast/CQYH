# Build the bundled Lua 5.1 runtime with the same toolchain and CRT as the server.
# The historical DLLs depend on Visual C++ 2013 runtimes, including its Debug CRT.
set(_lua_src "${CQYH_SERVER_DIR}/NewServer/3rd/lua/src")
add_library(cqyh_lua STATIC
    ${_lua_src}/lapi.c ${_lua_src}/lauxlib.c ${_lua_src}/lbaselib.c
    ${_lua_src}/lcode.c ${_lua_src}/ldblib.c ${_lua_src}/ldebug.c
    ${_lua_src}/ldo.c ${_lua_src}/ldump.c ${_lua_src}/lfunc.c
    ${_lua_src}/lgc.c ${_lua_src}/linit.c ${_lua_src}/liolib.c
    ${_lua_src}/llex.c ${_lua_src}/lmathlib.c ${_lua_src}/lmem.c
    ${_lua_src}/loadlib.c ${_lua_src}/lobject.c ${_lua_src}/lopcodes.c
    ${_lua_src}/loslib.c ${_lua_src}/lparser.c ${_lua_src}/lstate.c
    ${_lua_src}/lstring.c ${_lua_src}/lstrlib.c ${_lua_src}/ltable.c
    ${_lua_src}/ltablib.c ${_lua_src}/ltm.c ${_lua_src}/lundump.c
    ${_lua_src}/lvm.c ${_lua_src}/lzio.c)
add_library(cqyh::lua ALIAS cqyh_lua)
target_include_directories(cqyh_lua PUBLIC "${_lua_src}")
if(MSVC)
    target_compile_definitions(cqyh_lua PRIVATE _CRT_SECURE_NO_WARNINGS)
elseif(UNIX)
    target_compile_definitions(cqyh_lua PRIVATE LUA_USE_LINUX)
    target_link_libraries(cqyh_lua PUBLIC ${CMAKE_DL_LIBS} m)
endif()
