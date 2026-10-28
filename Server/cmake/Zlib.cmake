# Build the vendored zlib with the server's compiler and runtime on every platform.
set(_zlib_src "${CQYH_SERVER_DIR}/NewServer/3rd/zlib")
add_library(cqyh_zlib STATIC
    ${_zlib_src}/adler32.c
    ${_zlib_src}/compress.c
    ${_zlib_src}/crc32.c
    ${_zlib_src}/deflate.c
    ${_zlib_src}/gzclose.c
    ${_zlib_src}/gzlib.c
    ${_zlib_src}/gzread.c
    ${_zlib_src}/gzwrite.c
    ${_zlib_src}/infback.c
    ${_zlib_src}/inffast.c
    ${_zlib_src}/inflate.c
    ${_zlib_src}/inftrees.c
    ${_zlib_src}/trees.c
    ${_zlib_src}/uncompr.c
    ${_zlib_src}/zutil.c)
add_library(cqyh::zlib ALIAS cqyh_zlib)

target_include_directories(cqyh_zlib PUBLIC "${_zlib_src}")
target_compile_definitions(cqyh_zlib PRIVATE ZLIB_BUILD)
set_target_properties(cqyh_zlib PROPERTIES DEBUG_POSTFIX _d)

include(CheckIncludeFile)
include(CheckFunctionExists)
check_include_file(unistd.h CQYH_ZLIB_HAVE_UNISTD_H)
check_include_file(stdarg.h CQYH_ZLIB_HAVE_STDARG_H)
check_function_exists(fseeko CQYH_ZLIB_HAVE_FSEEKO)
if(CQYH_ZLIB_HAVE_UNISTD_H)
    target_compile_definitions(cqyh_zlib PRIVATE HAVE_UNISTD_H)
endif()
if(CQYH_ZLIB_HAVE_STDARG_H)
    target_compile_definitions(cqyh_zlib PRIVATE HAVE_STDARG_H)
endif()
if(NOT CQYH_ZLIB_HAVE_FSEEKO)
    target_compile_definitions(cqyh_zlib PRIVATE NO_FSEEKO)
endif()
if(MSVC)
    target_compile_definitions(cqyh_zlib PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
