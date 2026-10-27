# Pre-built third-party libraries that live in NewServer/3rd (there is no source for them in the repo).
#
# Windows : lib/win64 import/static libs (+ the DLLs that go with the import libs)
# Linux   : lib/linux64 static libs where the repo has them; zlib comes from the system.
# A missing Linux library only fails when something links against it.

set(_3rd "${CQYH_SERVER_DIR}/NewServer/3rd")

# Debug/Release selection for imported libs; RelWithDebInfo/MinSizeRel use the Release one.
function(_cqyh_imported name kind)
    cmake_parse_arguments(A "" "RELEASE;DEBUG;DLL_RELEASE;DLL_DEBUG" "" ${ARGN})
    add_library(cqyh::${name} ${kind} IMPORTED GLOBAL)
    set_target_properties(cqyh::${name} PROPERTIES
        IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
        MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE
        MAP_IMPORTED_CONFIG_MINSIZEREL RELEASE)
    if(kind STREQUAL "SHARED")
        set_target_properties(cqyh::${name} PROPERTIES
            IMPORTED_IMPLIB_RELEASE   "${A_RELEASE}"
            IMPORTED_IMPLIB_DEBUG     "${A_DEBUG}"
            IMPORTED_LOCATION_RELEASE "${A_DLL_RELEASE}"
            IMPORTED_LOCATION_DEBUG   "${A_DLL_DEBUG}")
    else()
        set_target_properties(cqyh::${name} PROPERTIES
            IMPORTED_LOCATION_RELEASE "${A_RELEASE}"
            IMPORTED_LOCATION_DEBUG   "${A_DEBUG}")
    endif()
endfunction()

if(WIN32)
    _cqyh_imported(lua SHARED
        RELEASE "${_3rd}/lua/lib/win64/lua64.lib"   DLL_RELEASE "${_3rd}/lua/lib/win64/lua64.dll"
        DEBUG   "${_3rd}/lua/lib/win64/lua64_d.lib" DLL_DEBUG   "${_3rd}/lua/lib/win64/lua64_d.dll")

    _cqyh_imported(toluapp STATIC
        RELEASE "${_3rd}/toluapp/lib/win64/toluapp.lib"
        DEBUG   "${_3rd}/toluapp/lib/win64/toluapp_d.lib")

    _cqyh_imported(zlib STATIC
        RELEASE "${_3rd}/zlib/lib/win64/zlib.lib"
        DEBUG   "${_3rd}/zlib/lib/win64/zlib_d.lib")

    _cqyh_imported(mysql SHARED
        RELEASE "${_3rd}/mysql-5.1.65/lib/win64/libmysql64.lib"   DLL_RELEASE "${_3rd}/mysql-5.1.65/lib/win64/libmysql64.dll"
        DEBUG   "${_3rd}/mysql-5.1.65/lib/win64/libmysql64_d.lib" DLL_DEBUG   "${_3rd}/mysql-5.1.65/lib/win64/libmysql64_d.dll")

    # GPK: only a Debug redistributable DLL is shipped; used for both configurations.
    _cqyh_imported(gpk SHARED
        RELEASE "${_3rd}/gpk/Lib/GPKitSvr64.lib" DLL_RELEASE "${_3rd}/gpk/Redist/Debug/Server/64-bit/GPKitSvr64.dll"
        DEBUG   "${_3rd}/gpk/Lib/GPKitSvr64.lib" DLL_DEBUG   "${_3rd}/gpk/Redist/Debug/Server/64-bit/GPKitSvr64.dll")

    # Import libs whose DLLs are not in the repo: link only (the DLLs are expected next to the executable).
    _cqyh_imported(sdobase UNKNOWN
        RELEASE "${_3rd}/sdobase/lib/SdoBaseDLL.lib"
        DEBUG   "${_3rd}/sdobase/lib/SdoBaseDLL.lib")
    _cqyh_imported(fcm UNKNOWN
        RELEASE "${_3rd}/fcm/lib/fcmsdk_X64.lib"
        DEBUG   "${_3rd}/fcm/lib/fcmsdk_X64.lib")

    # Windows system libraries every server needs.
    add_library(cqyh_syslibs INTERFACE)
    target_link_libraries(cqyh_syslibs INTERFACE ws2_32 iphlpapi winmm dbghelp psapi)
    add_library(cqyh::syslibs ALIAS cqyh_syslibs)
else()
    find_package(ZLIB)
    add_library(cqyh_syslibs INTERFACE)
    target_link_libraries(cqyh_syslibs INTERFACE pthread dl rt)
    add_library(cqyh::syslibs ALIAS cqyh_syslibs)

    _cqyh_imported(lua STATIC
        RELEASE "${_3rd}/lua/lib/linux64/liblua.a"
        DEBUG   "${_3rd}/lua/lib/linux64/liblua.a")
    _cqyh_imported(toluapp STATIC
        RELEASE "${_3rd}/toluapp/lib/linux64/libtolua++.a"
        DEBUG   "${_3rd}/toluapp/lib/linux64/libtolua++.a")
    _cqyh_imported(mysql STATIC
        RELEASE "${_3rd}/mysql-5.1.65/lib/linux64/libmysqlclient.a"
        DEBUG   "${_3rd}/mysql-5.1.65/lib/linux64/libmysqlclient.a")
    _cqyh_imported(gpk STATIC
        RELEASE "${_3rd}/gpk/Redist/Debug/Server/64-Centos. 6.x/libGPKitSvr.a"
        DEBUG   "${_3rd}/gpk/Redist/Debug/Server/64-Centos. 6.x/libGPKitSvr.a")

    add_library(cqyh::zlib INTERFACE IMPORTED GLOBAL)
    if(ZLIB_FOUND)
        target_link_libraries(cqyh::zlib INTERFACE ZLIB::ZLIB)
    endif()
    # sdobase / fcm are Windows-only SDKs (the Linux build of manageserver/loginserver never used them)
    add_library(cqyh::sdobase INTERFACE IMPORTED GLOBAL)
    add_library(cqyh::fcm INTERFACE IMPORTED GLOBAL)
endif()
