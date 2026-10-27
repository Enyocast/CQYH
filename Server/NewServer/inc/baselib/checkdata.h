#ifndef _CHECK_DATA_H_
#define _CHECK_DATA_H_


#include <string>
#include <map>

using namespace std;
class CTabFile;

class CCheckData
{
public:

	CCheckData();
	virtual ~CCheckData();

	INT32 Init(BOOL bIsProgrammer);
	INT32 UnInit();
	static CCheckData& GetInstance(void);

	BOOL Check(const char* pPath, const char* pcszFolderName);
	CTabFile* GetDataByName(const char* pName); 

	INT32 GetTabRowCount(CTabFile* pTab);
	INT32 GetTabColCount(CTabFile* pTab);

	INT32 GetNumber(CTabFile* pTab, char* pCol, INT32 nRow);
	char* GetString(CTabFile* pTab, char* pCol, INT32 nRow);

	const char* GetColName(CTabFile* pTab, INT32 nColID);

	void PrintInfo(char* pInfo);
	void PrintWrn(char* pWrn);

private:

	BOOL _Load(const char* pPath);
	BOOL _UnLoad();
	BOOL _RegisterName2TabConfig(const char* pPath, CTabFile* pTabConfig);

	static CCheckData ms_Instance;

	typedef map<string, CTabFile*> MapConfig;
	typedef MapConfig::iterator IterMapConfig;

	MapConfig m_MapConfig;
	char chString[512];
	BOOL m_bIsProgrammer;
};

#endif // _CHECK_DATA_H_