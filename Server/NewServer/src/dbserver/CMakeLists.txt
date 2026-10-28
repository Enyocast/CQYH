# dbserver - translated from dbserver.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_executable(dbserver
    db_message_handler.cpp
    db_session_mgr.cpp
    db/db_create_role.cpp
    db/db_delete_role.cpp
    db/db_list_role.cpp
    db/db_load_role.cpp
    db/db_save_role.cpp
    db/db_update_role_delete_time.cpp
    dbserver.cpp
    logic/db_worker_thread.cpp
    logic/dbrole_mgr.cpp
    logic/dbrole.cpp
    logic/dbuser_mgr.cpp
    logic/dbuser.cpp
    logic/mem_mgr.cpp
    stdafx.cpp
)

cqyh_target_defaults(dbserver EXECUTABLE)
cqyh_use_pch(dbserver ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(dbserver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CQYH_SERVER_DIR}/Common/fusion/inc
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/net
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/3rd/zlib
)
target_compile_definitions(dbserver PRIVATE
    _CRT_SECURE_NO_WARNINGS
    WIN32_LEAN_AND_MEAN
)
target_link_libraries(dbserver PRIVATE
    cqyh::mysql
    baselib
    net
    cqyh::lua
    cqyh::toluapp
    cqyh::zlib
    fusion
    cqyh::syslibs
)
cqyh_server_output(dbserver dbserver64)

