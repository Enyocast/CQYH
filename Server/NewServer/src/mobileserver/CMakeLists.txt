# mobileserver - translated from mobileserver.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(mobileserver
    mm_message_handler.cpp
    mm_session_mgr.cpp
    mobileserver.cpp
    stdafx.cpp
)

cqyh_target_defaults(mobileserver EXECUTABLE)
cqyh_use_pch(mobileserver ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(mobileserver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/Common/message
    ${CQYH_SERVER_DIR}/Common/fusion/inc
)
target_link_libraries(mobileserver PRIVATE
    baselib
    cqyh::net
    cqyh::lua
    cqyh::sol2
    cqyh::zlib
    fusion
    cqyh::syslibs
)
cqyh_server_output(mobileserver mobileserver64)

