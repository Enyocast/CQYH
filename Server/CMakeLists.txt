cmake_minimum_required(VERSION 3.25)

project(CQYHServer LANGUAGES C CXX)

if(MSVC)
    enable_language(ASM_MASM)   # baselib/code.asm
endif()

# Root of the server tree (this directory); the sub-projects refer to everything relative to it.
set(CQYH_SERVER_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)   # solution folders (the tools go into "Tools")

include(CQYH)
include(ThirdParty)
include(Sol2)
include(Asio)

# Static libraries
add_subdirectory(Common/fusion)
add_subdirectory(NewServer/src/baselib)
add_subdirectory(NewServer/src/net)
add_subdirectory(NewServer/src/gameworld)

# Servers
foreach(server
        gateserver loginserver balanceserver dbserver datalogserver
        gameserver manageserver gmserver mgateserver mobileserver gen_msg)
    add_subdirectory(NewServer/src/${server})
endforeach()

# Tools (Visual Studio solution folder "Tools")
option(CQYH_BUILD_TOOLS "Build the command line / GUI tools in NewServer/tools" ON)
if(CQYH_BUILD_TOOLS)
    add_subdirectory(NewServer/tools)
endif()

# Tests
option(CQYH_BUILD_TESTS "Build the test programs (ctest)" ON)
if(CQYH_BUILD_TESTS)
    enable_testing()
    add_subdirectory(NewServer/test/zlib)
    add_subdirectory(NewServer/test/asio_net)
    add_subdirectory(NewServer/test/lua_bindings)
    if(WIN32)
        add_subdirectory(NewServer/test/mysql)
    endif()
endif()

# nameserver is not part of the Visual Studio solution (universe.sln) and does not compile as it stands
# (nameserver.h uses std::map/std::set<std::string> without including <string>), so it is opt-in.
option(CQYH_BUILD_NAMESERVER "Build nameserver (not in universe.sln; currently does not compile)" OFF)
if(CQYH_BUILD_NAMESERVER)
    add_subdirectory(NewServer/src/nameserver)
endif()
