#include "linux_map.h"
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "sdtype.h"
#include "sqlite3db.h"
#include "sdloggerimpl.h"

typedef std::string tstring;

#include "tab_config.h"
// #include "luascriptrunner.h"

#define CASE_PASS printf("Testcase [%s] pass.\n", __func__)

// SGDP::CSDLoggerImpl

BOOL basic_test()
{
    LM_MAP_NODE * root = NULL;
    LM_MAP_NODE stub_root;
    stub_root.dwID = 1000;

    assert(LM_Insert(&stub_root, &root));
    assert(root->dwID == 1000);

    LM_Erase(&stub_root, &root);
    assert(root == NULL);

    CASE_PASS;
    return TRUE;
}

BOOL test_insert()
{
    LM_MAP_NODE * root = NULL;
    LM_MAP_NODE stub_root;
    stub_root.dwID = 0;

    assert(LM_Insert(&stub_root, &root));
    assert(root->dwID == 0);

    LM_MAP_NODE node1;
    node1.dwID = 0xffffffff;
    assert(LM_Insert(&node1, &root));

    LM_Erase(&stub_root, &root);
    assert(root == &node1);

    CASE_PASS;
    return TRUE;
}

BOOL test_dup_insert()
{
    LM_MAP_NODE * root = NULL;
    LM_MAP_NODE stub_root;
    stub_root.dwID = 1000;
    assert(LM_Insert(&stub_root, &root));

    LM_MAP_NODE node1;
    node1.dwID = stub_root.dwID;
    assert(!LM_Insert(&node1, &root));

    CASE_PASS;
    return TRUE;
}

BOOL test_search()
{
    LM_MAP_NODE * root = NULL;
    LM_MAP_NODE stub_root;
    stub_root.dwID = 1000;

    LM_Insert(&stub_root, &root);
    assert(root->dwID == 1000);

    LM_MAP_NODE node1;
    LM_MAP_NODE node2;
    LM_MAP_NODE node3;
    LM_MAP_NODE node4;
    LM_MAP_NODE node5;
    LM_MAP_NODE node6;
    LM_MAP_NODE node7;

    node1.dwID = 1001;
    node2.dwID = 1002;
    node3.dwID = 1003;
    node4.dwID = 1004;
    node5.dwID = 1005;
    node6.dwID = 1006;
    node7.dwID = 1007;

    assert(LM_Insert(&node1, &root));
    assert(LM_Insert(&node2, &root));
    assert(LM_Insert(&node3, &root));
    assert(LM_Insert(&node4, &root));
    assert(LM_Insert(&node5, &root));
    assert(LM_Insert(&node6, &root));
    assert(LM_Insert(&node7, &root));

    assert(LM_Search(node7.dwID, root) == &node7);
    assert(LM_Search(node6.dwID, root) == &node6);
    assert(LM_Search(node5.dwID, root) == &node5);
    assert(LM_Search(node4.dwID, root) == &node4);
    assert(LM_Search(node3.dwID, root) == &node3);
    assert(LM_Search(node2.dwID, root) == &node2);
    assert(LM_Search(node1.dwID, root) == &node1);

    LM_Erase(&node2, &root);
    assert(LM_Search(node2.dwID, root) == NULL);

    CASE_PASS;
    return TRUE;
}

void simple_perf()
{
    UINT32 cnt = 65535;
    LM_MAP_NODE * nodes = (LM_MAP_NODE *) malloc(sizeof(LM_MAP_NODE) * cnt);

    LM_MAP_NODE * root = NULL;
    LM_MAP_NODE stub_root;
    stub_root.dwID = 65536;

    LM_Insert(&stub_root, &root);
    assert(root->dwID == 65536);

    clock_t t1 = clock();
    clock_t t2;
    UINT32 idx = 0;
    for (idx = 0; idx < cnt; ++idx)
    {
        nodes[idx].dwID = idx + 1;
        LM_Insert(&nodes[idx], &root);
    }

    t2 = clock();
    printf("%ld %ld Insert %d spend %f ms.\n", t1, t2, cnt, (t2 - t1) / 1000.0);

    for (idx = 0; idx < cnt; ++idx)
    {
        LM_Search(nodes[idx].dwID, root);
    }

    printf("%ld Search %d spend %f ms.\n", t2, cnt, (clock() - t2) / 1000.0);

    free(nodes);
    nodes = NULL;

    CASE_PASS;
}

static TCHAR * path_template = (TCHAR *) "./setting/test_%s_file%s";
static TCHAR * read_path_template = (TCHAR *) "test_%s_file";

void print_configdata(int row, int col, CTabConfig * p)
{
    TCHAR cval[32];
    for (int i = 0; i < row; ++i)
    {
        TCHAR key[20] = "A";
        for (int j = 0; j < col; ++j)
        {
            key[0] = 'A' + j;
            assert(p->ReadData(key, i, cval, sizeof(cval)));
            printf("%s\t", cval);
        }
        printf("\n");
    }
    printf("\n");
}

void do_config_test(CTabConfig & tconfig, CTabConfig & tconfig2, CTabConfig & tconfig3)
{
    assert(tconfig.GetColCount() == 5);
    assert(tconfig.GetRowCount() == 3);
    assert(tconfig2.GetColCount() == 5);
    assert(tconfig2.GetRowCount() == 3);
    assert(tconfig3.GetColCount() == 5);
    assert(tconfig3.GetRowCount() == 3);

    print_configdata(3, 5, &tconfig);
    print_configdata(3, 5, &tconfig2);
    print_configdata(3, 5, &tconfig3);

    INT32 val;
    assert(tconfig.ReadData("A", 0, val) > 0);
    assert(val == 1);

    assert(tconfig2.ReadData("C", 0, val) > 0);
    assert(val == 3);

    assert(tconfig3.ReadData("D", 1, val) > 0);
    assert(val == 9);

    assert(tconfig.ReadData("D", 0, val) > 0);
    assert(val == 4000);

    // Failure test.
    assert(!tconfig3.ReadData("X", 0, val));
    assert(!tconfig3.ReadData("D", 100, val));
    assert(!tconfig3.ReadData("F", 1, val));
    assert(!tconfig3.ReadData("AB", 0, val));

    TCHAR cval[32];
    assert(tconfig.ReadData("C", 2, cval, sizeof(cval)));
    assert(cval != NULL);
    assert(cval[0] == 'c');

    assert(tconfig2.ReadData("A", 0, cval, sizeof(cval)));
    assert(cval != NULL);
    assert(strcmp(cval, "JUMP") == 0);

    assert(tconfig3.ReadData("D", 0, cval, sizeof(cval)));
    assert(cval != NULL);
    assert(strcmp(cval, "oh my god") == 0);
}

void test_tab_config()
{
    TCHAR tab_path[200];
    TCHAR tab_path2[200];
    TCHAR tab_path3[200];
    TCHAR read_path[200];
    TCHAR read_path2[200];
    TCHAR read_path3[200];
    sprintf(tab_path, path_template, "tab", ".tab");
    sprintf(tab_path2, path_template, "tab2", ".tab");
    sprintf(tab_path3, path_template, "tab3", ".tab");
    sprintf(read_path, read_path_template, "tab");
    sprintf(read_path2, read_path_template, "tab2");
    sprintf(read_path3, read_path_template, "tab3");

    FILE * f = fopen(tab_path, "w");
    FILE * f2 = fopen(tab_path2, "w");
    FILE * f3 = fopen(tab_path3, "w");
    assert(f != NULL);
    CHAR p[] =
            "A\tB\tC\tD\tE\n1\t2\t3\t4000\t5\n6\t7\t8\t9\t10\na\tb\tc\tdd\te\n";
    CHAR
            p2[] =
                    "A\tB\tC\tD\tE\n\"JUMP\"\t2\t3\t4000\t5\r\n6\t7\t8\t9\t10\r\na\tb\tc\tdd\te\r\n";
    CHAR p3[] =
            "A\tB\tC\tD\tE\n1\t2\t3\t\"oh my god\"\t5\n6\t7\t8\t9\t10\r\na\tb\tc\tdd\te\n";
    fwrite(p, strlen(p), sizeof(CHAR), f);
    fwrite(p2, strlen(p2), sizeof(CHAR), f2);
    fwrite(p3, strlen(p3), sizeof(CHAR), f3);
    fclose(f);
    fclose(f2);
    fclose(f3);

    CTabConfig tconfig, tconfig2, tconfig3;
    assert(tconfig.Init(read_path) > 0);
    assert(tconfig2.Init(read_path2) > 0);
    assert(tconfig3.Init(read_path3) > 0);

    do_config_test(tconfig, tconfig2, tconfig3);

    tconfig.UnInit();
    tconfig2.UnInit();
    tconfig3.UnInit();

    CASE_PASS;
}

void test_sqlite_config()
{
    TCHAR read_path[200];
    TCHAR read_path2[200];
    TCHAR read_path3[200];
    sprintf(read_path, read_path_template, "sqlite");
    sprintf(read_path2, read_path_template, "sqlite2");
    sprintf(read_path3, read_path_template, "sqlite3");

    CTabConfig tconfig, tconfig2, tconfig3;
    assert(tconfig.Init(read_path) > 0);
    assert(tconfig2.Init(read_path2) > 0);
    assert(tconfig3.Init(read_path3) > 0);

    do_config_test(tconfig, tconfig2, tconfig3);

    tconfig.UnInit();
    tconfig2.UnInit();
    tconfig3.UnInit();

    CASE_PASS;
}

/*
 void test_lua_caller()
 {
 CLuaScriptRunner::Instance()->Init();
 CLuaScriptRunner::Instance()->CallScript("hi", "hi", 0, 0, NULL);
 CLuaScriptRunner::Instance()->UnInit();
 CASE_PASS;
 }
 */

#include "sdcsvfile.h"
int main()
{
    if (FALSE == SGDP::CSDLoggerImpl::Init("./test_config.xml"))
    {
        return FALSE;
    }

    basic_test();
    test_insert();
    test_search();
    test_dup_insert();

    simple_perf();

    test_tab_config();
    test_sqlite_config();

    //test_lua_caller();

    return 0;
}
