add_executable(test_lua_bindings test_lua_bindings.cpp
    ../../src/baselib/script/sol_tl_config.cpp)
target_include_directories(test_lua_bindings PRIVATE ../../src/baselib ../../inc)
target_compile_definitions(test_lua_bindings PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
cqyh_target_defaults(test_lua_bindings)
target_link_libraries(test_lua_bindings PRIVATE cqyh::sol2)
if(MSVC)
    target_compile_options(test_lua_bindings PRIVATE /GR)
endif()
add_test(NAME lua_bindings COMMAND test_lua_bindings)

add_executable(test_lua_protocol_bindings test_lua_protocol_bindings.cpp)
cqyh_target_defaults(test_lua_protocol_bindings)
target_include_directories(test_lua_protocol_bindings PRIVATE ../../inc
    ${CQYH_SERVER_DIR}/Common/message ${CQYH_SERVER_DIR}/Common/define)
target_compile_definitions(test_lua_protocol_bindings PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_link_libraries(test_lua_protocol_bindings PRIVATE cqyh::net cqyh::sol2)
add_test(NAME lua_protocol_bindings COMMAND test_lua_protocol_bindings)

add_executable(test_lua_fusion_bindings test_lua_fusion_bindings.cpp)
cqyh_target_defaults(test_lua_fusion_bindings)
target_include_directories(test_lua_fusion_bindings PRIVATE
    ${CQYH_SERVER_DIR}/Common/define
    ${CQYH_SERVER_DIR}/Common/fusion/inc
    ${CQYH_SERVER_DIR}/Common/fusion/src)
target_compile_definitions(test_lua_fusion_bindings PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_link_libraries(test_lua_fusion_bindings PRIVATE fusion cqyh::sol2)
add_test(NAME lua_fusion_bindings COMMAND test_lua_fusion_bindings)

add_executable(test_lua_enum_string_bindings
    test_lua_enum_string_bindings.cpp
    ../../src/gmserver/script/sol_enum_str.cpp
    ../../src/gmserver/script/bindings/definitions/item_bindings.cpp
    ../../src/gmserver/script/bindings/definitions/error_bindings.cpp)
cqyh_target_defaults(test_lua_enum_string_bindings)
target_include_directories(test_lua_enum_string_bindings PRIVATE
    ${CQYH_SERVER_DIR}/Common/fusion/src)
target_compile_definitions(test_lua_enum_string_bindings PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_link_libraries(test_lua_enum_string_bindings PRIVATE cqyh::sol2)
add_test(NAME lua_enum_string_bindings COMMAND test_lua_enum_string_bindings)
