# mgateserver - translated from mgateserver.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(mgateserver
    mg_external_message_handler.cpp
    mg_internal_message_handler.cpp
    mg_session_mgr.cpp
    mgateserver.cpp
    stdafx.cpp
)

cqyh_target_defaults(mgateserver EXECUTABLE)
cqyh_use_pch(mgateserver ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(mgateserver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/Common/message
    ${CQYH_SERVER_DIR}/Common/fusion/inc
)
target_link_libraries(mgateserver PRIVATE
    baselib
    cqyh::net
    cqyh::lua
    cqyh::sol2
    cqyh::zlib
    fusion
    cqyh::syslibs
)
cqyh_server_output(mgateserver mgateserver64)

