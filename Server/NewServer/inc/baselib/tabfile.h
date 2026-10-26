#ifndef _TAB_FILE_H_
#define _TAB_FILE_H_

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

	BOOL Init(const char* pcszFileName, INT32 nSkipLine);
	BOOL UnInit(void);

	INT32 GetRowCount(void);
	INT32 GetColCount(void);
    const char* GetColName(INT32 nCol);

    BOOL ReadData(INT32 nCol, INT32 nRow, INT32& rnValue);
	BOOL ReadData(const char* pcszColName, int nRow, INT32& rnValue);
    BOOL ReadData(INT32 nCol, INT32 nRow, char* pszValue, INT32 nSize);
    BOOL ReadData(const char* pcszColName, int nRow, char* pszValue, INT32 nSize);

    UINT32 GetCRC(void);

private:
    const char* GetData(INT32 nCol, INT32 nRow);
    const char* GetData(const char* pcszColName, INT32 nRow);

private:
	char*			m_pData;
	size_t			m_uSize;
	INT32           m_nSkipLine;
	INT32			m_nRowCount;
	INT32			m_nColCount;
	INT32*			m_pOffsetTable;
    UINT32          m_dwCRC32;

	typedef std::map<std::string, int, std::less<std::string> > MAP_NAME_2_COL;
	MAP_NAME_2_COL	m_mapName2Col;
};

#endif	// _TAB_FILE_H_
