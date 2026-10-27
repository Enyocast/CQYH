# Matching schema and data exports

These two files are split from the populated variant of the supplied archive.

1. Import `cqyh_name_mysql26_10_schema_only.sql` to create the database, tables, and procedures. This contains DROP TABLE statements: use a fresh database.
2. Select that database and import `cqyh_name_mysql26_10_data_only.sql` once to load its 1,120 rows. It contains INSERT statements with UTF-8 connection setup and a transaction; it creates or drops no database, table, or procedure. It includes the version seed row.

Command-line import (prompts for your password):

```bat
mysql -h localhost -u root -p --default-character-set=utf8mb4 < cqyh_name_mysql26_10_schema_only.sql
mysql -h localhost -u root -p --default-character-set=utf8mb4 cqyh_name < cqyh_name_mysql26_10_data_only.sql
```

The original raw schema has different user columns and mail field lengths. Use this matching schema with this data file. The data-only file requires empty matching tables and does not select a database itself. Use a client that stops on errors, without --force.

## Source and SQL changes

This matching pair derives from `../cqyh_name-Data Included.sql`, via the modernized export. The separate custom-server raw schema in the parent directory is an independent variant.

- Use utf8mb4 text and InnoDB DYNAMIC rows; retain the login log table's explicit latin1 encoding and the original binary data.
- Remove integer display widths; map invalid zero DeleteTime defaults and five zero-date INSERT values to NULL.
- Add a non-unique username lookup index and a primary key on version.id.
- Make update_0 bootstrap idempotent. The data file supplies the original version `all = 8`.
- Validate identifiers and table compatibility in move_data; reject self-moves. Make move_group transactional and include auction_deposit and group_ms.
- Make clear_table skip absent log tables or partitions.

The schema file contains tables and four stored procedures, with no top-level seed INSERTs. The data file contains all 1,120 rows, including the version seed, with no CREATE, DROP, ALTER, TRUNCATE, or USE statements. Stored-procedure bodies in the schema still contain their operational INSERT statements.

## Application compatibility

The game server must treat NULL DeleteTime as not deleted and write NULL instead of a zero date. Connector mapping of TINYINT fields should be checked after removing display widths. User-column differences and mail lengths between the original variants remain meaningful.

The sample accounts and legacy plaintext password fields are preserved from the original populated export. These are sample game data; no local MySQL connection credentials are included.

See [TEST_RESULTS.md](TEST_RESULTS.md) for the live SQL validation and its limits. This is a fresh-install export, not an in-place migration.
