# loginserver - translated from loginserver.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(loginserver
    login_server.cpp
    ls_message_handler.cpp
    ls_session_mgr.cpp
    oa_auth_mgr.cpp
    stdafx.cpp
)

cqyh_target_defaults(loginserver EXECUTABLE)
cqyh_use_pch(loginserver ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(loginserver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/Common/fusion/inc
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/NewServer/3rd/sdobase/include
)
target_compile_definitions(loginserver PRIVATE
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_DEPRECATE
)
target_link_libraries(loginserver PRIVATE
    net
    cqyh::lua
    cqyh::toluapp
    cqyh::sdobase
    cqyh::zlib
    fusion
    baselib
    cqyh::syslibs
)
cqyh_server_output(loginserver loginserver64)

