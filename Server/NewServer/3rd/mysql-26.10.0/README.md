# MySQL 26.10.0 C API

Unmodified Oracle Community client binaries, public headers, and required OpenSSL runtimes.
Both Debug and Release use the same shared library. The original upstream `README`, Windows `LICENSE`,
and `LICENSE-Linux` accompany these files.

| Platform | Bundled files |
| --- | --- |
| Windows x64 | `lib/win64/libmysql.lib`, `libmysql.dll`, `libssl-3-x64.dll`, `libcrypto-3-x64.dll` |
| Linux x64, glibc 2.28+ | `lib/linux64/libmysqlclient.so.24`, OpenSSL libraries in `lib/linux64/private` |

The Linux file is the upstream `libmysqlclient.so.24.2.0`, stored under its SONAME to avoid requiring
symlink creation on Windows checkouts. Its upstream relative runtime search paths are preserved.
Headers come from the Windows package and support both platforms.

Packages retrieved on 28 October 2026:

- [Windows x64 ZIP](https://cdn.mysql.com/Downloads/MySQL-26.10/mysql-26.10.0-winx64.zip)
  SHA-256: `4ef425963d11675d865528f5970e2b3766a48363694d0a588969fcce6ce54dd9`
  MD5 matched Oracle's download page: `11d70a5011b7760508e98b3a2fe5db3f`.
- [Linux x64 minimal archive](https://cdn.mysql.com/Downloads/MySQL-26.10/mysql-26.10.0-linux-glibc2.28-x86_64-minimal.tar.xz)
  SHA-256: `292e196560614eb5966e5034aaa949dbd4dd69870d67f090186023e35d0e835d`

Server programs, tools, static client libraries and debug symbols are omitted.
