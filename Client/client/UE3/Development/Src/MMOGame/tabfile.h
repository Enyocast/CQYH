#ifndef _TAB_FILE_H_
#define _TAB_FILE_H_

#include "MMOUtil.h"

#include <string>
#include <map>

/************************************************************************/
/* The strings output from this class are always UTF-8 format!!!		*/
/************************************************************************/

class CTabFile
{
public:
	CTabFile();
	~CTabFile();

	bool Init(const TCHAR* pcszFileName);
	bool UnInit(void);

	int GetRowCount(void);
	int GetColCount(void);

	const TCHAR* GetData(int nCol, int nRow) const;
	const TCHAR* GetData(const TCHAR* pcszColName, int nRow) const;
	int GetKeyColIdx(const TCHAR* pcszColName) const;

private:
	TCHAR*			m_pData;
	size_t			m_uSize;
	int			m_nRowCount;
	int			m_nColCount;
	int*			m_pOffsetTable;
		
	typedef std::map<FString, int, ComparFString, STLAllocator< std::pair<FString, int>, UE3STLAllocatorPolicy> > MAP_NAME_2_COL;

	//typedef std::map<std::string, int, std::less<std::string> > MAP_NAME_2_COL;
	MAP_NAME_2_COL	m_mapName2Col;
};

#endif	// _TAB_FILE_H_
