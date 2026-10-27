# datalogserver - translated from datalogserver.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(datalogserver
    datalogscript.cpp
    datalogserver.cpp
    db/dl_sql_stmt_list.cpp
    dl_message_handler.cpp
    dl_message_notifier.cpp
    dl_session_mgr.cpp
    logdata.cpp
    script/tolua_common.cpp
    script/tolua_enum_str.cpp
    stdafx.cpp
)

cqyh_target_defaults(datalogserver EXECUTABLE)
cqyh_use_pch(datalogserver ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(datalogserver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/Common/message
    ${CQYH_SERVER_DIR}/Common/fusion/inc
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/NewServer/inc/gameworld
    ${CQYH_SERVER_DIR}/NewServer/3rd/lua/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/toluapp/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/gpk/Include
    ${CQYH_SERVER_DIR}/NewServer/3rd/mysql-5.1.65/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/zlib
)
target_compile_definitions(datalogserver PRIVATE
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_DEPRECATE
)
target_link_libraries(datalogserver PRIVATE
    gameworld
    net
    cqyh::lua
    cqyh::toluapp
    cqyh::mysql
    baselib
    cqyh::zlib
    cqyh::gpk
    fusion
    cqyh::syslibs
)
cqyh_server_output(datalogserver datalogserver64)

