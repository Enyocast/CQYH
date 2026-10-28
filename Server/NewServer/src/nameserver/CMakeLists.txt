# nameserver - translated from nameserver.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(nameserver
    nameserver.cpp
    ns_message_handler.cpp
    stdafx.cpp
)

cqyh_target_defaults(nameserver EXECUTABLE)
cqyh_use_pch(nameserver ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(nameserver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/Common/message
    ${CQYH_SERVER_DIR}/Common/fusion/inc
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/NewServer/inc/gameworld
    ${CQYH_SERVER_DIR}/NewServer/3rd/lua/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/gpk/Include
    ${CQYH_SERVER_DIR}/NewServer/3rd/zlib
)
target_compile_definitions(nameserver PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_DEPRECATE
)
target_link_libraries(nameserver PRIVATE
    baselib
    cqyh::lua
    cqyh::toluapp
    net
    cqyh::zlib
    cqyh::gpk
    fusion
    cqyh::mysql
    cqyh::syslibs
)
cqyh_server_output(nameserver nameserver64)

