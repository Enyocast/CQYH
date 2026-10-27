# gateserver - translated from gateserver.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(gateserver
    external_message_handler.cpp
    gateserver.cpp
    gt_session_mgr.cpp
    internal_message_handler.cpp
    stdafx.cpp
)

cqyh_target_defaults(gateserver EXECUTABLE)
cqyh_use_pch(gateserver ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(gateserver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/Common/message
    ${CQYH_SERVER_DIR}/Common/fusion/inc
    ${CQYH_SERVER_DIR}/NewServer/3rd/zlib
)
target_compile_definitions(gateserver PRIVATE
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_DEPRECATE
    $<$<CONFIG:Debug>:_LOG_MESSAGE>
)
target_link_libraries(gateserver PRIVATE
    baselib
    net
    cqyh::lua
    cqyh::toluapp
    cqyh::zlib
    fusion
    cqyh::syslibs
)
cqyh_server_output(gateserver gateserver64)

