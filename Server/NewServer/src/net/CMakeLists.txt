# net - translated from net.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_library(net STATIC
    ../../../Common/message/external_message_size.cpp
    intranet.cpp
    net.cpp
    packet_allocator.cpp
    script/tolua_common.cpp
    script/tolua_external_message.cpp
    script/tolua_internal_message.cpp
    share_mem_net.cpp
    simple_net.cpp
    stdafx.cpp
)

cqyh_target_defaults(net)
cqyh_use_pch(net ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(net PRIVATE
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/NewServer/3rd/lua/src
    ${CQYH_SERVER_DIR}/NewServer/3rd/toluapp/include
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/Common/message
)

# asio transport (netAsio). It must not use the project's precompiled stdafx.h: that header defines
# _HAS_EXCEPTIONS=0 and includes <windows.h> before the socket headers, neither of which asio can live with.
target_sources(net PRIVATE asio_net.cpp)
set_source_files_properties(asio_net.cpp PROPERTIES
    SKIP_PRECOMPILE_HEADERS ON
    COMPILE_DEFINITIONS NOMINMAX)
target_link_libraries(net PUBLIC asio::asio)


