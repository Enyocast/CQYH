# gmserver - translated from gmserver.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(gmserver
    ../../../Common/message/external_message_size.cpp
    ../dbserver/db/db_load_role.cpp
    ../dbserver/db/db_save_role.cpp
    cmd_mgr_logic.cpp
    cmd_mgr.cpp
    db_mgr_cb.cpp
    db_mgr.cpp
    gm_db_operation.cpp
    gm_log.cpp
    gm_query_thread.cpp
    gm_role_mgr.cpp
    gm_script_func.cpp
    gm_session_mgr.cpp
    gm_sql_stmt_list.cpp
    gmserver.cpp
    kernel.cpp
    ld_listener.cpp
    message_handler.cpp
    message_notifier.cpp
    ms_mgr.cpp
    order_mgr.cpp
    permission_mgr.cpp
    prep_stmt.cpp
    script/tolua_common.cpp
    script/tolua_enum_str.cpp
    script/tolua_gm_def.cpp
    stdafx.cpp
    tl_user.cpp
    user_manager.cpp
)

cqyh_target_defaults(gmserver EXECUTABLE)
cqyh_use_pch(gmserver ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(gmserver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/Common/fusion/inc
    ${CQYH_SERVER_DIR}/Common/message
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/gm
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/NewServer/inc/gameworld
    ${CQYH_SERVER_DIR}/NewServer/3rd/toluapp/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/lua/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/zlib
    ${CQYH_SERVER_DIR}/NewServer/3rd/mysql-5.1.65/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/gpk/Include
)
target_compile_definitions(gmserver PRIVATE
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_DEPRECATE
)
target_link_libraries(gmserver PRIVATE
    gameworld
    baselib
    cqyh::lua
    cqyh::toluapp
    cqyh::zlib
    cqyh::mysql
    cqyh::gpk
    fusion
    net
    cqyh::syslibs
)
cqyh_server_output(gmserver gmserver64)

