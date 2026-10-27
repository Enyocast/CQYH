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
ctest --preset vs2022-debug                (runs the asio transport test)
```

Executables are written to `NewServer/bin/<server>/<server>64[_d].exe`, where the configs and scripts are, exactly as
the old projects did. Pass `-DCQYH_OUTPUT_TO_BIN=OFF` to keep them in the build directory instead.

## Things worth knowing

* asio (standalone, header only) is downloaded on the first configure and pinned by hash (`cmake/Asio.cmake`). To
  build offline point `-DCQYH_ASIO_SOURCE_DIR=<asio checkout>` at an existing copy.
* `-DCQYH_CXX_STANDARD=14|17|20|23` selects the language standard (default 23). The legacy code needs MSVC's
  `/permissive` mode; that is set in `cmake/CQYH.cmake`.
* The source lists in the `CMakeLists.txt` files are explicit. A new `.cpp` has to be added there.
* `nameserver` is not built by default (`-DCQYH_BUILD_NAMESERVER=ON`): it was never in the old solution and does not
  compile (`nameserver.h` uses `std::string` without including it).
* Not migrated: `NewServer/src/asimov` (Qt robot client), `bteditor`, `gameworld/script/script.vcxproj` (the Lua
  bytecode compiler step) and everything under `NewServer/tools` still have their own project files.
* The source files are GBK encoded (Chinese comments). Edit them with a tool that keeps the bytes as they are.

## Networking

The client facing side (`gateserver`, `balanceserver`, `mgateserver`) uses the asio transport in
`NewServer/src/net/asio_net.cpp` (`netAsio`), which replaced the winsock IOCP and epoll implementations.
Server-to-server traffic still goes through `netIntranet` / `netSimple` (shared memory + a `select()` based reactor).
`NewServer/test/asio_net` is an integration test of the transport.

