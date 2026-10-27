# gameserver - translated from gameserver.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(gameserver
    ../../../Common/message/external_message_size.cpp
    gameserver.cpp
    gs_message_handler.cpp
    gs_session_mgr.cpp
    message_notifier.cpp
    stdafx.cpp
)

cqyh_target_defaults(gameserver EXECUTABLE)
cqyh_use_pch(gameserver ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(gameserver PRIVATE
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
target_compile_definitions(gameserver PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_DEPRECATE
)
target_link_libraries(gameserver PRIVATE
    gameworld
    baselib
    cqyh::lua
    cqyh::toluapp
    net
    cqyh::zlib
    cqyh::gpk
    fusion
    cqyh::syslibs
)
cqyh_server_output(gameserver gameserver64)

