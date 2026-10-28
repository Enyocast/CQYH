# Server zlib

This directory vendors the unmodified core sources and headers of **zlib 1.3.2** (17 February 2026),
plus upstream's `test/example.c`, `LICENSE`, `README` and `ChangeLog`.

Source: <https://zlib.net/zlib-1.3.2.tar.gz>

SHA-256: `bb329a0a2cd0274d05519d61c667c062e06990d72e125ee2dfa8de64f0119d16`

The server's `cmake/Zlib.cmake` compiles all 15 core C files into `cqyh::zlib` using the current
compiler and runtime, on both Windows and Linux. The public include path points here, so headers
and library always match. The old zlib 1.2.7 prebuilt libraries have been removed.
The upstream build scripts and optional contrib packages are not vendored.

The server's test suite includes the upstream API example and a compatibility regression test for
zlib 1.2.7 compressed data, used by database blobs, packs and network payloads.

## Separate legacy tools

The remaining standalone tool projects still reference `lib/win64/zlib[_d].lib` (or `lib/win32`).
Build the retained `zlib.vcxproj` with Visual Studio 2022's v143 toolset before linking those tools:

```powershell
msbuild zlib.vcxproj /p:Configuration=Debug /p:Platform=x64
msbuild zlib.vcxproj /p:Configuration=Release /p:Platform=x64
```

Use `Win32` for 32-bit tools. These generated libraries and intermediate files are ignored by Git.
The legacy project has been updated for 1.3.2 and includes the complete core API.
The CMake server build does not consume these files.
