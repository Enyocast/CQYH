# baselib - translated from baselib.vcxproj (Release|x64 / Debug|x64 settings).
# The source list is explicit on purpose; add new files here.

add_library(baselib STATIC
    asm.cpp
    btnod_test.cpp
    btnod.cpp
    censored_word_list.cpp
    checkdata.cpp
    circle_list.cpp
    data_manager.cpp
    db_init.cpp
    dir.cpp
    dump.cpp
    free_stack.cpp
    hash.cpp
    ifile.cpp
    linux_compatible.cpp
    log.cpp
    lua_script.cpp
    math_ex.cpp
    md5.cpp
    mutex.cpp
    pak_loader.cpp
    process_option.cpp
    profile.cpp
    report.cpp
    rsa_sign.cpp
    script_mgr.cpp
    script/tolua_check_data.cpp
    script/tolua_common.cpp
    script/tolua_tl_config.cpp
    share_mem_io.cpp
    share_mem.cpp
    simple_timer.cpp
    sql_mgr.cpp
    sql_stmt.cpp
    statis_info.cpp
    stdafx.cpp
    string_ex_test.cpp
    string_ex.cpp
    tabfile_test.cpp
    tabfile.cpp
    thread.cpp
    time_ex.cpp
    tl_config.cpp
    trie_test.cpp
    trie.cpp
    utf8.cpp
    weight_rand.cpp
)

cqyh_target_defaults(baselib)
cqyh_use_pch(baselib ${CMAKE_CURRENT_SOURCE_DIR})
cqyh_use_async_exceptions(baselib)

target_include_directories(baselib PRIVATE
    ${CQYH_SERVER_DIR}/NewServer/inc
    ${CQYH_SERVER_DIR}/NewServer/inc/baselib
    ${CQYH_SERVER_DIR}/NewServer/3rd/lua/src
    ${CQYH_SERVER_DIR}/NewServer/3rd/toluapp/include
    ${CQYH_SERVER_DIR}/NewServer/3rd/zlib
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/Common/fusion/inc
)
# MASM source (a MASM item in baselib.vcxproj): the _ReplaceThreadProc thunk used by dump.cpp
if(MSVC)
    target_sources(baselib PRIVATE code.asm)
endif()


# Propagate the matching C API headers and runtime to users of baselib.
target_link_libraries(baselib PUBLIC cqyh::mysql)
