#include "stdafx.h"
#include "db/db_create_role.h"
#include "db/db_update_role_delete_time.h"
#include <cstdio>
#include <cstdlib>

// Only an explicitly selected port enables this test. Never use the normal game database.
// The test account needs CREATE/DROP DATABASE privileges on cqyh_mysql_test_*.
struct TestDatabase
{
    MYSQL* connection = mysql_init(nullptr);
    std::string name;
    ~TestDatabase()
    {
        if (!connection) return;
        if (!name.empty())
            mysql_query(connection, ("DROP DATABASE `" + name + "`").c_str());
        mysql_close(connection);
    }
};

struct RoleWriters
{
    CDBCreateRole create;
    CDBUpdateRoleDeleteTime update;
    ~RoleWriters() { update.UnInit(); create.UnInit(); }
};

static bool scalarEquals(MYSQL* connection, const char* query, const char* expected)
{
    if (mysql_query(connection, query)) return false;
    MYSQL_RES* result = mysql_store_result(connection);
    if (!result) return false;
    MYSQL_ROW row = mysql_fetch_row(result);
    bool matches = row && row[0] && std::string(row[0]) == expected;
    mysql_free_result(result);
    return matches;
}

#define REQUIRE(condition) do { if (!(condition)) { \
    std::fprintf(stderr, "Failed: %s (%s)\n", #condition, \
        db.connection ? mysql_error(db.connection) : "mysql_init failed"); \
    return 1; } } while (0)

int main()
{
    const char* port = std::getenv("CQYH_TEST_MYSQL_PORT");
    if (!port)
    {
        std::puts("Set CQYH_TEST_MYSQL_PORT to run the MySQL role integration test.");
        return 77;
    }
    const char* host = std::getenv("CQYH_TEST_MYSQL_HOST");
    const char* user = std::getenv("CQYH_TEST_MYSQL_USER");
    const char* password = std::getenv("CQYH_TEST_MYSQL_PASSWORD");
    char* end = nullptr;
    unsigned long portNumber = std::strtoul(port, &end, 10);
    if (!*port || *end || portNumber == 0 || portNumber > 65535)
    {
        std::fputs("CQYH_TEST_MYSQL_PORT must be between 1 and 65535.\n", stderr);
        return 1;
    }
    TestDatabase db;
    REQUIRE(db.connection);
    REQUIRE(mysql_real_connect(db.connection, host ? host : "127.0.0.1",
        user ? user : "root", password ? password : "", nullptr,
        static_cast<unsigned int>(portNumber), nullptr, 0));
    REQUIRE(mysql_get_client_version() >= 261000);
    REQUIRE(mysql_get_server_version(db.connection) >= 261000);
    REQUIRE(mysql_set_character_set(db.connection, "utf8mb4") == 0);
    REQUIRE(mysql_query(db.connection, "SET SESSION sql_mode = 'STRICT_TRANS_TABLES,NO_ZERO_DATE,NO_ZERO_IN_DATE,NO_ENGINE_SUBSTITUTION'") == 0);
    std::string name = "cqyh_mysql_test_" + std::to_string(mysql_thread_id(db.connection));
    REQUIRE(mysql_query(db.connection, ("CREATE DATABASE `" + name + "` CHARACTER SET utf8mb4").c_str()) == 0);
    db.name = name;
    REQUIRE(mysql_select_db(db.connection, name.c_str()) == 0);
    REQUIRE(mysql_query(db.connection,
        "CREATE TABLE role (GroupID TINYINT UNSIGNED NOT NULL, RoleID INT UNSIGNED PRIMARY KEY, "
        "RoleName VARCHAR(24) NOT NULL, UserName VARCHAR(64) NOT NULL, CreateTime DATETIME NOT NULL, "
        "DeleteTime DATETIME NULL DEFAULT NULL, LoginTime DATETIME NOT NULL, RoleDeleted TINYINT NOT NULL, "
        "BaseData BLOB NOT NULL, RoleData BLOB NOT NULL) ENGINE=InnoDB") == 0);
    RoleWriters writers;
    REQUIRE(writers.create.Init(db.connection));
    REQUIRE(writers.update.Init(db.connection));
    char roleName[] = "mysql_test";
    char userName[] = "mysql_test_user";
    char baseData[] = "base";
    char roleData[] = "role";
    REQUIRE(writers.create.DoCreateRole(1, 42, roleName, userName,
        baseData, sizeof(baseData), roleData, sizeof(roleData)));
    REQUIRE(scalarEquals(db.connection, "SELECT DeleteTime IS NULL FROM role WHERE RoleID=42", "1"));
    writers.update.m_dwRoleID = 42;
    writers.update.m_dwDeleteTime = 1700000000;
    REQUIRE(writers.update.DoUpdate());
    REQUIRE(scalarEquals(db.connection, "SELECT UNIX_TIMESTAMP(DeleteTime) FROM role WHERE RoleID=42", "1700000000"));
    writers.update.m_dwDeleteTime = 0;
    REQUIRE(writers.update.DoUpdate());
    REQUIRE(scalarEquals(db.connection, "SELECT DeleteTime IS NULL FROM role WHERE RoleID=42", "1"));
    std::printf("MySQL client %s / server %s: create, delete and restore passed under strict SQL mode.\n",
        mysql_get_client_info(), mysql_get_server_info(db.connection));
    return 0;
}
