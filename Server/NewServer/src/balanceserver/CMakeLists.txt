# balanceserver - translated from balanceserver.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(balanceserver
    balanceserver.cpp
    bs_session_mgr.cpp
    external_message_handler.cpp
    internal_message_handler.cpp
    stdafx.cpp
)

cqyh_target_defaults(balanceserver EXECUTABLE)
cqyh_use_pch(balanceserver ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(balanceserver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/Common/message
    ${CQYH_SERVER_DIR}/Common/fusion/inc
)
target_compile_definitions(balanceserver PRIVATE
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_DEPRECATE
)
target_link_libraries(balanceserver PRIVATE
    baselib
    net
    cqyh::lua
    cqyh::toluapp
    cqyh::zlib
    fusion
    cqyh::syslibs
)
cqyh_server_output(balanceserver balanceserver64)

