# Exercise the production role writers against an explicitly selected test instance.
add_executable(test_mysql_roles test_mysql_roles.cpp
    ../../src/dbserver/db/db_create_role.cpp
    ../../src/dbserver/db/db_update_role_delete_time.cpp)
cqyh_target_defaults(test_mysql_roles EXECUTABLE)
get_target_property(_dbserver_includes dbserver INCLUDE_DIRECTORIES)
target_include_directories(test_mysql_roles PRIVATE ${_dbserver_includes})
target_compile_definitions(test_mysql_roles PRIVATE WIN32_LEAN_AND_MEAN _CRT_SECURE_NO_WARNINGS)
target_link_libraries(test_mysql_roles PRIVATE
    baselib cqyh::mysql cqyh::zlib cqyh::lua cqyh::sol2 fusion cqyh::syslibs)
cqyh_copy_runtime_dlls(test_mysql_roles)
add_test(NAME mysql_roles COMMAND test_mysql_roles)
set_tests_properties(mysql_roles PROPERTIES SKIP_RETURN_CODE 77 TIMEOUT 30)
