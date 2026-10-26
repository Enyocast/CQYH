# Legend Eternal (CQYH) – Source Code

The 2016 Shanda Games *Legend Eternal* (传奇永恒 / CQYH) source code: the Unreal Engine 3 client and the server, split into `Client` and `Server`.

> **The client assets are not in this repository.** The game content and prebuilt binaries (about 64 GB) are too large for GitHub and are hosted separately. See [Client assets](#client-assets-required-to-build-and-run-the-client) below.

## Client assets (required to build and run the client)

This repository contains the client **source code only**. The game assets and prebuilt binaries the client needs are in a single archive:

**[`Client Assets.7z`](https://mirfiles.co.uk/resources/mir2/users/Jev/Legend%20Eternal/Organised/Client%20Assets.7z)**, hosted in the [Organised files folder](https://mirfiles.co.uk/resources/mir2/users/Jev/Legend%20Eternal/Organised/).

It contains the cooked game content (`.upk`, `.udk`, `.pak`, `.bik` videos, the `CookedPC` and `Content` folders), prebuilt third-party libraries (for example the Scaleform GFx `.lib` files), executables and DLLs, compiled UnrealScript packages (`.u`), the Mac binaries and the QA build tools.

**How to use it:**

1. Download `Client Assets.7z` and extract it with [7-Zip](https://www.7-zip.org/).
2. Extract it **into the `Client` folder of this repository**, so the folders merge: the archive uses the same relative paths as the repository (`client\UE3\MMOGame\CookedPC\...`, `client\UE3\Development\External\...` and so on).
3. There is nothing to configure: the extracted files are already ignored by `Client/.gitignore` (see the "Client assets" block at the end of that file), so git will not pick them up.

Without the assets you can read and edit the source, but you cannot build or run the client.

The same folder also hosts the other files from this release: packaged client builds, packaged server builds, tool installers and `Documentation.7z` (setup and compile notes, database files, design documents).

## Repository layout

`Client` and `Server` are independent: neither needs the other to compile. Both compile against the shared `Common` folder, so each one carries its own copy.

**`*GitIgnored*`** marks files and folders that come from [`Client Assets.7z`](#client-assets-required-to-build-and-run-the-client) (63.65 GB, 29,650 files). They sit in the normal places in the tree so everything builds, but `Client/.gitignore` stops git from committing them. `(partly GitIgnored)` means the folder itself is committed and only the prebuilt files inside it are ignored.

```text
Client/
├── client/                              The UE3-based game client
│   ├── UE3/
│   │   ├── Development/                 (partly GitIgnored)
│   │   │   ├── Src/                     C++ and UnrealScript source (UE3.sln, MMOGame.sln)
│   │   │   ├── External/                Bundled third-party libraries
│   │   │   │                            *GitIgnored*: prebuilt .lib/.dll files (Scaleform GFx, 4.5 GB)
│   │   │   ├── Tools/                   UnrealBuildTool and engine tools
│   │   │   ├── Flash/                   Flash / Scaleform UI source (*GitIgnored*: .swf/.fla)
│   │   │   └── Documentation/           *GitIgnored*: UnrealEngine3.chm (over 100 MB)
│   │   ├── Engine/                      Config, shaders, localization
│   │   │   └── Content/                 *GitIgnored*: engine content packages (.upk)
│   │   ├── MMOGame/                     Game config and localization
│   │   │   ├── CookedPC/                *GitIgnored*: cooked game packages (10.6 GB)
│   │   │   ├── Content/                 *GitIgnored*: game content (33.6 GB)
│   │   │   ├── Movies/                  *GitIgnored*: .bik videos (2.6 GB)
│   │   │   ├── Flash/                   *GitIgnored*: UI .swf/.fla files (1.5 GB)
│   │   │   └── Script*/                 *GitIgnored*: compiled UnrealScript packages (.u)
│   │   ├── Binaries/, BinariesRelease/  (partly GitIgnored) runtime support files
│   │   │   ├── Win32/, Win64/           *GitIgnored*: prebuilt .exe/.dll files
│   │   │   └── Mac/                     *GitIgnored*: Mac binaries
│   │   ├── Install/                     *GitIgnored*: redistributable installers (.exe/.cab)
│   │   └── Launcher*/, SDO/             Launcher and SDO login (*GitIgnored*: .exe/.dll)
│   ├── DevTools/                        DevLauncher, ReplayView
│   ├── PatchTools/                      FixClient, FileUpdate
│   ├── OtherTools/                      dump_analyze (crash dump analyser)
│   ├── PackageTool/                     Packaging scripts (*GitIgnored*: bundled .exe/.dll)
│   ├── ClientBuildServer/               Cook and packaging scripts (*GitIgnored*: bundled .exe/.dll)
│   └── SDOTest/, AODBenchmarkLaunch/    Small test and benchmark projects
├── Common/                              Shared protocol and data definitions (define, message, fusion)
├── _AutoBuild/                          Build-server scripts and packaging toolchain
│   ├── aod_pack/                        (partly GitIgnored) toolchain; bundled .exe/.dll are *GitIgnored*
│   └── edition/_CQ_S1/client_qa_build/  *GitIgnored*: UE3 dev/editor binaries (1.3 GB)
├── DevLauncher.exe                      *GitIgnored*: prebuilt tools
├── dump_analyze.exe                     *GitIgnored*
└── MsgBox.exe                           *GitIgnored*

Server/
├── NewServer/
│   ├── src/                   Server source (universe.sln): gameserver, gateserver, loginserver,
│   │                          dbserver, gmserver, manageserver, nameserver, balanceserver, ...
│   ├── bin/                   Runtime layout: commonconfig (game scripts and data tables),
│   │                          start/stop scripts, configs
│   ├── 3rd/                   Third-party libraries (MySQL, Lua, tolua++, zlib, oasdk, ...)
│   ├── inc/, lib/             Shared headers and libraries
│   ├── tools/                 gmtool, maintaintool, guardserver, certserver and other tools
│   ├── test/                  Test projects
│   └── build/                 Linux Makefile
├── Common/                    Shared protocol and data definitions (newest version)
└── Common1/                   Alternative "new protocol" variant (not used by the build)
```

### Things to know

- **Keep the folder layout.** Project files reach `Common` with paths such as `..\..\..\Common`, so `client` / `NewServer` and `Common` must stay side by side inside `Client` and `Server`.
- **Two `Common` copies.** `Client/Common` and `Server/Common` are separate; a change in one does not carry to the other.
- **Compiled server executables are not included.** Packaged server builds are in the [Organised folder](https://mirfiles.co.uk/resources/mir2/users/Jev/Legend%20Eternal/Organised/) under `Server Builds`.
- **Two things need `Client` and `Server` side by side.** The server tool `gen_msg` writes `ServerEnum.uc` and `MMOBT*.ini` into the client folder, and the client cook scripts in `ClientBuildServer` copy `NewServer\bin\commonconfig`. They do not work with the two apart.

### Dependencies

Visual Studio and the DirectX SDK come from Microsoft. Everything else is hosted in the [Organised files folder](https://mirfiles.co.uk/resources/mir2/users/Jev/Legend%20Eternal/Organised/):

| Needed for | Dependency | Download |
|---|---|---|
| Server build | Visual Studio 2013 | Microsoft (not hosted) |
| Client build | Visual Studio 2010 + Service Pack 1, DirectX SDK (June 2010) | Microsoft (not hosted) |
| Database | MySQL 5.5.62 (64-bit MSI) – the original notes also mention 5.1 | [`MySQL Install.7z`](https://mirfiles.co.uk/resources/mir2/users/Jev/Legend%20Eternal/Organised/MySQL%20Install.7z) |
| Database tool | Navicat for MySQL 12.1 (64-bit) | [`Navicat Install.7z`](https://mirfiles.co.uk/resources/mir2/users/Jev/Legend%20Eternal/Organised/Navicat%20Install.7z) |
| Client troubleshooting | DirectX repair tool (blank-screen and DirectX errors on old clients) | [`DirectX 4.2 Repair Tool.7z`](https://mirfiles.co.uk/resources/mir2/users/Jev/Legend%20Eternal/Organised/DirectX%204.2%20Repair%20Tool.7z) |
| Dev environment | Python 2.7.8, Perforce P4V, XAMPP 1.8.3 | [`Dev Tools Install.7z`](https://mirfiles.co.uk/resources/mir2/users/Jev/Legend%20Eternal/Organised/Dev%20Tools%20Install.7z) |
| Setup and compile notes | Build, database and runtime guides, SQL files, design documents | [`Documentation.7z`](https://mirfiles.co.uk/resources/mir2/users/Jev/Legend%20Eternal/Organised/Documentation.7z) |

- **MySQL:** official installers are also available from the [MySQL archive](https://downloads.mysql.com/archives/community/) (5.5.62 Windows MSI and ZIP).
- **Navicat** is commercial software and needs a valid licence; the official version is on the [Navicat website](https://www.navicat.com/en/products#navicat). Any MySQL client works if you prefer another.
- **Legacy client problems:** if the DirectX SDK installer fails, uninstall the Microsoft Visual C++ redistributables (2005 to 2022), reinstall the SDK, then run the DirectX repair tool. The details are in `Documentation.7z`.
- Packaged client builds, packaged server builds and the rest of the release are in the same folder.
---
## 🔗 Quick Links

### Project Resources
- 🌐 [Legend Eternal Database](https://eternalmir.co.uk/) - by [DontReallyMind](https://www.lomcn.net/forum/members/dontreallymind.4351/)
- <img src="https://cdn.prod.website-files.com/6257adef93867e50d84d30e2/66e3d80db9971f10a9757c99_Symbol.svg" alt="Discord" width="20"/> [Discord](https://discord.gg/KahjsD7fhn)

### Official Resources

- 🌐 [Shanda Games - Legend Eternal Website](https://cq.web.sdo.com/)

### LOMCN Community

- 💬 [Development Section](https://www.lomcn.net/forum/forums/mir-3d-emulation.812/)
- 📚 [Tutorials](https://www.lomcn.net/forum/forums/mir-3d-tutorials.852/)
- 📦 [Releases](https://www.lomcn.net/forum/forums/mir-3d-releases.853/)
- 🐞 [Bug Reports](https://www.lomcn.net/forum/forums/mir-3d-bug-reports.813/)
- 🛠️ [Updates](https://www.lomcn.net/forum/forums/mir-3d-updates.814/)
- 📖 [Wiki](https://www.lomcn.net/wiki/index.php/Mir3DEmu/)

---

## 🙏 Special Thanks

- [DontReallyMind](https://www.lomcn.net/forum/members/dontreallymind.4351/)
- [CraZyEriK](https://www.lomcn.net/forum/members/crazyerik.9944/)
- [Armifer (ElAmO)](https://www.lomcn.net/forum/members/elamo.10165/)
- [Damian (CodePwr)](https://www.lomcn.net/forum/members/damian.1126/)
- [Jev](https://www.lomcn.net/forum/members/jev.29880/)
- [mir2pion](https://www.lomcn.net/forum/members/mir2pion.19657/)
- [Xander](https://www.lomcn.net/forum/members/xander.2473/)
- [Chriz](https://www.lomcn.net/forum/members/chriz.86/)

---

<h2 align="center">
  <img src="https://www.lomcn.net/forum/styles/uix/images/logo2024_100.png" width="32">
  Other Projects
</h2>

<table align="center" width="100%">

  <tr>
    <td width="48" align="center" valign="top">
      <a href="https://github.com/JevLOMCN/mir1/">
        <img src="https://raw.githubusercontent.com/JevLOMCN/mir4/main/Tools/icons/mir1.png" width="32" height="32">
      </a>
    </td>
    <td>
      <b>Mir 1</b> •
      <a href="https://github.com/JevLOMCN/mir1/">Project</a> •
      <a href="https://github.com/Suprcode/Carbon.Database">Database</a><br>
      Remake of ActozSoft's 1997 <i>The Legend Of Mir 1</i>
    </td>
  </tr>

  <tr>
    <td width="48" align="center" valign="top">
      <a href="https://github.com/Suprcode/Crystal">
        <img src="https://raw.githubusercontent.com/JevLOMCN/mir4/main/Tools/icons/mir2.png" width="32" height="32">
      </a>
    </td>
    <td>
      <b>Mir 2</b> •
      <a href="https://github.com/Suprcode/Crystal">Project</a> •
      <a href="https://github.com/Suprcode/Crystal.Database">Database</a> •
      <a href="https://github.com/Suprcode/Crystal.MapEditor">Map Editor</a><br>
      Remake of ActozSoft / Wemade Entertainment's 1999 <i>The Legend Of Mir 2</i>
    </td>
  </tr>

  <tr>
    <td width="48" align="center" valign="top">
      <a href="https://github.com/Suprcode/Zircon">
        <img src="https://raw.githubusercontent.com/JevLOMCN/mir4/main/Tools/icons/mir3.png" width="32" height="32">
      </a>
    </td>
    <td>
      <b>Mir 3</b> •
      <a href="https://github.com/Suprcode/Zircon">Project</a> •
      <a href="https://mirfiles.com/resources/mir3/zircon/Database.7z">Database</a> •
      <a href="https://www.lomcn.net/forum/threads/map-editor.109317/">Map Editor</a><br>
      Remake of Wemade Entertainment's 2003 <i>The Legend Of Mir 3</i>
    </td>
  </tr>

  <tr>
    <td width="48" align="center" valign="top">
      <a href="https://www.lomcn.net/forum/forums/woool-development-project-onyx.857/">
        <img src="https://raw.githubusercontent.com/JevLOMCN/mir4/main/Tools/icons/woool.png" width="32" height="32">
      </a>
    </td>
    <td>
      <b>WoOOL</b> •
      <a href="https://www.lomcn.net/forum/forums/woool-development-project-onyx.857/">Project</a> •
      <a href="https://www.lomcn.net/forum/threads/nmp-viewer-editor.114580">Map Editor</a><br>
      Remake of Shanda Games' (Shengqu Games) 2003 <i>The World Of Legend</i>
    </td>
  </tr>

  <tr>
    <td width="48" align="center" valign="top">
      <a href="https://github.com/mir-ethernity/mir-eternal">
        <img src="https://raw.githubusercontent.com/JevLOMCN/mir4/main/Tools/icons/mir3d.png" width="32" height="32">
      </a>
    </td>
    <td>
      <b>Mir 3D</b> •
      <a href="https://github.com/mir-ethernity/mir-eternal">Moon Spirit</a> •
      <a href="https://github.com/JevLOMCN/Eternal-Legend">Holy Cow</a> •
      <a href="https://github.com/JevLOMCN/CQYH">Official</a><br>
      Remake of Shanda Games' 2016 <i>Legend Eternal</i>
    </td>
  </tr>

  <tr>
    <td width="48" align="center" valign="top">
      <a href="https://github.com/JevLOMCN/mir4">
        <img src="https://raw.githubusercontent.com/JevLOMCN/mir4/main/Tools/icons/mir4.png" width="32" height="32">
      </a>
    </td>
    <td>
      <b>Mir 4</b> •
      <a href="https://github.com/JevLOMCN/mir4">Project</a><br>
      Remake of Wemade Entertainment's 2021 <i>Mir 4</i>
    </td>
  </tr>

  <tr>
    <td width="48" align="center" valign="top">
      <a href="https://mirfiles.co.uk/resources/mir2/users/Jev/Mir%205/Leaks/">
        <img src="https://raw.githubusercontent.com/JevLOMCN/mir4/main/Tools/icons/mir5.png" width="32" height="32">
      </a>
    </td>
    <td>
      <b>Mir 5</b> •
      <a href="https://github.com/JevLOMCN/mir5-private">Project</a> •
      <a href="https://mirfiles.co.uk/resources/mir2/users/Jev/Mir%205/Leaks/">Leaked Files</a> •
      <a href="https://mirfiles.co.uk/resources/mir2/users/Jev/Mir%205/Leaks/Mir5%20Alpha%202.mkv">Gameplay Video (24m)</a><br>
      A massive 2TB development leak from the currently unreleased Mir 5. Includes server/client builds, internal documentation, and a 24-minute video showing <a href="https://github.com/JevLOMCN">Jev</a> connecting a leaked client to Wemade's official development server—since removed from YouTube with two copyright strikes. Preserved for historical and research purposes.
    </td>
  </tr>

</table>
