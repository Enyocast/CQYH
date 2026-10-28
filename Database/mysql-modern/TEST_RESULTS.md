# Live MySQL validation

Tested 27 October 2026 on MySQL 9.7.1 at localhost:3306.

SQL mode: ONLY_FULL_GROUP_BY, STRICT_TRANS_TABLES, NO_ZERO_IN_DATE, NO_ZERO_DATE, ERROR_FOR_DIVISION_BY_ZERO, NO_ENGINE_SUBSTITUTION. No global settings were changed.

## Split import

- Schema-only imported successfully into a fresh isolated database: 22 empty InnoDB/DYNAMIC tables and 4 stored procedures.
- Data-only then imported successfully: 1,120 rows across those tables, including 5 users, 3 roles, 27 rankings, 1,080 variables, and version all=8.
- Every table's exact row count and CHECKSUM TABLE EXTENDED result matched the successful combined populated import.
- Only the schema script's two database identifiers were redirected for isolation. The data-only script was executed without changes in the selected test database.

## Procedure validation on the matching combined export

- Calling update_0 twice preserved the single version row at 8.
- move_data rejected self-moves, absent destination tables, and incompatible column definitions.
- move_group transferred the selected group successfully. Forcing a duplicate key in its final table rolled back all earlier source deletions and destination inserts.
- After restoring transferred rows, all table checksums matched their pre-transfer values.
- clear_table completed safely with its referenced partitioned log tables absent.
- The independent raw variant also passed import and procedure tests; fixtures exercised auction_deposit and group_ms transfers.

Existing databases were untouched. Tests used uniquely named databases; temporary destination databases and synthetic fixtures were removed.

## Server C API upgrade validation, 28 October 2026

- Built all default CMake server targets on Windows x64 with MSVC v143 in Debug and Release, using the bundled MySQL 26.10.0 headers, import library and shared runtime.
- The production role create/delete/restore writers passed the `mysql_roles` regression test in both configurations against an isolated MySQL 26.10.0 instance with strict SQL mode. Creation and restoration stored NULL DeleteTime; deletion round-tripped its Unix timestamp.
- The existing `asio_net` test passed in Debug and Release with localhost networking available.
- Imported the matching schema and data into an isolated MySQL 26.10.0 database: schema version 8 and three populated roles were preserved.
- All 98 active management and GM SQL statements prepared against that schema after removing application binding annotations. Arena statements now quote the reserved Rank column. This checks syntax and column compatibility, not execution of every statement.
- The bundled Linux x64 shared client and its private OpenSSL libraries were taken from the matching upstream archive; Linux execution was not tested on this Windows host.

The local installed database service was not upgraded. The tests used a separate instance and data directory.

## Limits

Full game sessions, concurrent operations, other MySQL versions, and truncation of actual populated log partitions were not tested. The CMake server build now supports NULL DeleteTime; the role writer regression above covers its creation and restoration behavior.
