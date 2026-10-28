# Vendored sol2 v3.3.1. No download is needed to build the Lua bindings.
set(_sol2_root "${CQYH_SERVER_DIR}/NewServer/3rd/sol2")
if(NOT EXISTS "${_sol2_root}/include/sol/sol.hpp")
    message(FATAL_ERROR "sol/sol.hpp not found under ${_sol2_root}/include")
endif()
add_library(cqyh_sol2 INTERFACE)
add_library(cqyh::sol2 ALIAS cqyh_sol2)
target_include_directories(cqyh_sol2 SYSTEM INTERFACE "${_sol2_root}/include")
target_include_directories(cqyh_sol2 INTERFACE
    "${CQYH_SERVER_DIR}/NewServer/inc/baselib"
    "${CQYH_SERVER_DIR}/NewServer/3rd/lua/include")
target_compile_features(cqyh_sol2 INTERFACE cxx_std_17)
if(MSVC)
    target_compile_options(cqyh_sol2 INTERFACE /bigobj)
endif()
target_link_libraries(cqyh_sol2 INTERFACE cqyh::lua)
