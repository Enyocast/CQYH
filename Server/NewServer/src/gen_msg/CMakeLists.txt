# gen_msg - translated from gen_msg.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(gen_msg
    gen_msg.cpp
    script/tolua_common.cpp
    script/tolua_enum_module.cpp
    script/tolua_external_message.cpp
    stdafx.cpp
)

cqyh_target_defaults(gen_msg EXECUTABLE)
cqyh_use_pch(gen_msg ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(gen_msg PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CQYH_SERVER_DIR}/Common/fusion/inc
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/Common/message
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/NewServer/3rd/lua/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/toluapp/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/zlib
)
target_link_libraries(gen_msg PRIVATE
    baselib
    cqyh::lua
    cqyh::toluapp
    cqyh::zlib
    fusion
    cqyh::syslibs
)
cqyh_server_output(gen_msg gen_msg)

