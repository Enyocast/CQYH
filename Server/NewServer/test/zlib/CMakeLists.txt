# Upstream's API regression suite, linked to the same library as the server.
add_executable(test_zlib_upstream ../../3rd/zlib/test/example.c)
target_link_libraries(test_zlib_upstream PRIVATE cqyh::zlib)
target_compile_definitions(test_zlib_upstream PRIVATE ZLIB_BUILD)
if(MSVC)
    target_compile_definitions(test_zlib_upstream PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
add_test(NAME zlib_upstream COMMAND test_zlib_upstream)
set_tests_properties(zlib_upstream PROPERTIES TIMEOUT 30)

add_executable(test_zlib_compatibility test_zlib_compatibility.c)
target_link_libraries(test_zlib_compatibility PRIVATE cqyh::zlib)
add_test(NAME zlib_compatibility COMMAND test_zlib_compatibility)
set_tests_properties(zlib_compatibility PROPERTIES TIMEOUT 30)
