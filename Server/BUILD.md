# Building the server

One build system: CMake (3.25+, the copy bundled with Visual Studio 2022 is fine). C++23, x64.
The old makefiles and Visual Studio project files are gone; Visual Studio and the command line both use the
`CMakeLists.txt` files in this tree.

## Visual Studio 2022

* **Open the folder** (`File > Open > Folder...` on `Server`). VS reads `CMakePresets.json`; pick the `vs2022` preset
  and a Debug/Release configuration, then `Build > Build All`. or
* **Generate a solution**: `cmake --preset vs2022` creates `build/vs2022/CQYHServer.sln`. Open that, build as usual.

## Command line

```
cmake --preset vs2022
cmake --build --preset vs2022-debug        (or vs2022-release)
ctest --preset vs2022-debug                (runs transport, Lua bindings and optional MySQL tests)
```

Executables are written to `NewServer/bin/<server>/<server>64[_d].exe`, where the configs and scripts are, exactly as
the old projects did. Pass `-DCQYH_OUTPUT_TO_BIN=OFF` to keep them in the build directory instead.

## Things worth knowing

* asio (standalone, header only) is downloaded on the first configure and pinned by hash (`cmake/Asio.cmake`). To
  build offline point `-DCQYH_ASIO_SOURCE_DIR=<asio checkout>` at an existing copy.
* sol2 v3.3.1 is vendored in `NewServer/3rd/sol2` alongside the other third-party libraries. The build uses these
  local headers directly; it does not download sol2. Lua 5.1 is compiled from the bundled `3rd/lua/src` sources
  with the server's toolchain, so the old Lua DLLs and their Visual C++ 2013 Debug runtime are unnecessary.
* zlib 1.3.2 is vendored in `NewServer/3rd/zlib` and compiled as the static `cqyh::zlib` library on Windows
  and Linux. No system zlib or prebuilt zlib library is needed. See its `README.md` for provenance and the
  separate legacy tool build. `ctest -R zlib --output-on-failure` runs the upstream API tests and verifies
  compatibility with compressed data produced by the former zlib 1.2.7.
* `-DCQYH_CXX_STANDARD=17|20|23` selects the language standard (default 23). The legacy code needs MSVC's
  `/permissive` mode; that is set in `cmake/CQYH.cmake`.
* The source lists in the `CMakeLists.txt` files are explicit. A new `.cpp` has to be added there.
* `CQYH_MSVC_COMPILE_PROCESSES` limits compiler workers per MSBuild target (default 2). sol2 templates need
  substantial compiler memory; increase this only when the machine has enough memory for parallel targets too.
* `nameserver` is not built by default (`-DCQYH_BUILD_NAMESERVER=ON`): it was never in the old solution and does not
  compile (`nameserver.h` uses `std::string` without including it).
* Not migrated: `NewServer/src/asimov` (Qt robot client), `bteditor`, `gameworld/script/script.vcxproj` (the Lua
  bytecode compiler step) and everything under `NewServer/tools` still have their own project files.
* Source files use UTF-8. MSVC emits narrow string literals using GBK for compatibility with the legacy server.

## Lua bindings

The server uses typed sol2 registrations in C++. Fusion registrations live under
`Common/fusion/src/script/bindings`, grouped into `config`, `data`, `definitions` and `support` folders.
Feature files such as `config/game_world_bindings.cpp` and `data/quest_bindings.cpp` keep each type's members
together. The `script/sol_*.cpp` entry points assemble these shared registrations; `bindings/registration.h`
declares their internal functions. `Common1/fusion` follows the same layout for its alternative protocol variant.
The other server and tool binding directories follow the same feature-based layout. Packet registrations are
under `bindings/external` and `bindings/internal`, named by direction and feature, for example
`external_client_to_game_movement_bindings.cpp` and `internal_manage_to_database_bindings.cpp`.
Enum-string registrations are grouped by their declaring headers under `bindings/definitions`.
Numbered binding source files are no longer used.
Edit these C++ registrations directly; there is no binding generator or package specification to regenerate.
Existing `LoadPackage("name.pkg")` strings remain module identifiers for scripts.
The networking objects are archived as `net`, `net_lua_external` and `net_lua_internal` to stay below MSVC's
Debug archive size limit; CMake consumers link `cqyh::net` for the complete interface.

The shared policy in `NewServer/inc/baselib/sol_bindings.h` preserves zero-based C arrays, nested object references,
bounded string assignment and named objects passed through `CLuaScript::CallFunction`. `Cast(object, "CType")`
converts base pointers and packet pointers to registered script types. Existing scripts now use this function.
`ctest -R lua_bindings --output-on-failure` exercises these behaviors.

## MySQL

The CMake server build uses the Oracle MySQL **26.10.0 C API**, bundled in `NewServer/3rd/mysql-26.10.0`
and imported as `cqyh::mysql` SHARED in `cmake/ThirdParty.cmake`. Debug and Release use the same client library.
The Windows build copies `libmysql.dll`, `libssl-3-x64.dll` and `libcrypto-3-x64.dll` alongside each executable.
The Linux x64 shared client requires glibc 2.28+ and carries its OpenSSL libraries in `lib/linux64/private`.
See the dependency's `README.md` for upstream package URLs and checksums.
The old SDK remains in `NewServer/3rd` for the separate legacy tool projects.

Use the matching fresh-install schema and optional data in [Database/mysql-modern](../Database/mysql-modern/README.md).
The server now represents an unset `DeleteTime` as SQL NULL and converts it to zero in game data.
Existing databases need their zero deletion dates converted to NULL and those columns made nullable before
using this build. The archived SQL exports and `commonconfig/sql` bootstrap scripts target the old database;
they are not an upgrade path for populated databases. This change does not upgrade a local database service.

MySQL uses `caching_sha2_password` authentication; the modern client supports it without enabling the removed
`mysql_native_password` plugin. Rebuild the server executables before connecting to a modern database.

The Windows `mysql_roles` regression test runs the production role create/delete/restore writers under strict
SQL mode. It skips unless a test instance is explicitly selected. The account needs permission to create and
drop databases named `cqyh_mysql_test_*`; each run removes only its own database:

```powershell
$env:CQYH_TEST_MYSQL_PORT = "33360"
$env:CQYH_TEST_MYSQL_USER = "root"
# Optional: CQYH_TEST_MYSQL_HOST and CQYH_TEST_MYSQL_PASSWORD
ctest --preset vs2022-debug -R mysql_roles --output-on-failure
```

## Networking

The client facing side (`gateserver`, `balanceserver`, `mgateserver`) uses the asio transport in
`NewServer/src/net/asio_net.cpp` (`netAsio`), which replaced the winsock IOCP and epoll implementations.
Server-to-server traffic still goes through `netIntranet` / `netSimple` (shared memory + a `select()` based reactor).
`NewServer/test/asio_net` is an integration test of the transport.

