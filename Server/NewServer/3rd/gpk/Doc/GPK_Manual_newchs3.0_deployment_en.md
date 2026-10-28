# GPK deployment instructions from the Chinese SDK manual

This is a translation of section 6 on page 13 of `GPK_Manual_newchs3.0.pdf`. The separately supplied English manual has different wording for the update-server directory; consult the SDK package and its maintainers to resolve the difference.

## 6.1 Update server

Upload all files from the `GPK` directory to the update server.

## 6.2 Game server

1. Copy `GPKitSvr.dlll` (release) or `GPKitSvrD.dll` (debug) to the server program directory. The triple `l` in the release filename is as printed in the Chinese manual; verify the actual SDK filename.
2. Create a dynamic-code directory on the server, such as `DynCodeBin`. Its name may be customized but must match the path passed to the SDK. Create server and client subdirectories, such as `Server` and `Client`, for the two sides of each dynamic-code pair. The files have a `.bin` extension, for example `01.bin` and `02.bin`. Each server file must have a client file with the same name; these matching files form a pair but have different contents. The anti-cheat team supplies them. The manual refers to `Client0` in one sentence although the example directory is `Client`; verify the intended path. A prepared `DynCodeBin` directory and files are supplied under `Redist\Server` and may be copied into the server directory.

## 6.3 Game client

1. Copy the `gpk` subdirectory and its contents from `Redist\Client` in the SDK into the game client directory. The next phrase in the original omits the name of another file to copy; its example shows the resulting client directory containing both a `gpk` directory and `GPKitClt.dll`.
2. Start protection through the GPK SDK interface, as described in section 4 of the manual.

## 6.4 Debugging

GPK has anti-debugging functionality that prevents breaking into an integrated game under a debugger. The manual recommends controlling GPK-related code on both client and server with a macro, and disabling that code in debug builds.
