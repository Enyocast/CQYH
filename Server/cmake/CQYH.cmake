# Shared helpers for the server build.

set(CQYH_CXX_STANDARD 23 CACHE STRING "C++ standard used for all server targets (14, 17, 20 or 23)")
set_property(CACHE CQYH_CXX_STANDARD PROPERTY STRINGS 14 17 20 23)

option(CQYH_OUTPUT_TO_BIN
       "Write server executables to NewServer/bin/<server>/ (where the Visual Studio projects put them and where the configs/scripts are found)"
       ON)

# ---------------------------------------------------------------------------------------------------------------------
# Defaults every server target gets. EXECUTABLE adds the _d debug suffix the old projects used (gateserver64_d.exe).
function(cqyh_target_defaults tgt)
    cmake_parse_arguments(A "EXECUTABLE" "" "" ${ARGN})

    set_target_properties(${tgt} PROPERTIES
        CXX_STANDARD ${CQYH_CXX_STANDARD}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        DEBUG_POSTFIX _d)

    if(WIN32)
        # The code keys its platform #ifs on WIN32 / WIN64 (and the compiler's own macros), so provide both, as the
        # old project files did. _MBCS = "Use Multi-Byte Character Set".
        target_compile_definitions(${tgt} PRIVATE WIN32 WIN64 _MBCS)
    elseif(UNIX)
        target_compile_options(${tgt} PRIVATE -m64 -ggdb3 -Wall)
    endif()

    if(MSVC)
        # Same switches as the old projects: no buffer security checks (/GS-), no RTTI (/GR-).
        # (The old Release projects also asked for /GL + /LTCG; that cannot work with the pre-built zlib/toluapp
        # libraries, which carry intermediate code from an older compiler, so it is not used here.)
        # /std:c++latest turns on /permissive- (strict conformance). The code base relies on non-conforming but
        # long-accepted MSVC behaviour (goto Exit0 jumping over initializations, ...), so switch it back off.
        target_compile_options(${tgt} PRIVATE
            /permissive
            /GS- /GR-
            /MP
            # Sources are GBK-encoded (Chinese comments/strings, no BOM). Pin the code pages so the result does not
            # depend on the Windows system language.
            /source-charset:gbk /execution-charset:gbk)
    endif()
endfunction()

# Every project uses a precompiled "stdafx.h" (the VS projects built it from stdafx.cpp with /Yc and used it with /Yu).
# The directory goes on the include path as well so sources in other directories that say #include "stdafx.h" find it.
function(cqyh_use_pch tgt dir)
    target_include_directories(${tgt} PRIVATE "${dir}")
    # <stdafx.h>, not a full path: CMake writes the PCH wrapper header as UTF-8, and a path containing non-ASCII
    # characters would be misread under /source-charset:gbk.
    target_precompile_headers(${tgt} PRIVATE <stdafx.h>)
endfunction()

# The legacy code was written for /EHa (SEH + C++ exceptions) in baselib.
function(cqyh_use_async_exceptions tgt)
    if(MSVC)
        target_compile_options(${tgt} PRIVATE /EHa)
    endif()
endfunction()

# Output location + name for a server executable, and the runtime DLLs of imported shared libraries.
function(cqyh_server_output tgt out_name)
    set_target_properties(${tgt} PROPERTIES OUTPUT_NAME ${out_name})
    if(CQYH_OUTPUT_TO_BIN)
        set(dir "${CQYH_SERVER_DIR}/NewServer/bin/${tgt}")
        set_target_properties(${tgt} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${dir}")
        foreach(cfg DEBUG RELEASE RELWITHDEBINFO MINSIZEREL)
            set_target_properties(${tgt} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${cfg} "${dir}")
        endforeach()
    endif()
    if(WIN32)
        add_custom_command(TARGET ${tgt} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:${tgt}> $<TARGET_FILE_DIR:${tgt}>
            COMMAND_EXPAND_LISTS)
    endif()
endfunction()
