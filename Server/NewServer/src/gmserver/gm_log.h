/********************************************************************
	created:	4:3:2014   14:28
	file:		gm_log.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_GM_LOG_H_
#define _H_GM_LOG_H_


enum GM_LOG_FILE_ENUM
{
    glfNone     = 0,

    glfBegin,
    glfGM   = glfBegin,
    glfItemLog,
    glfMoneyLog,

    glfNum,
};


class CGMLog
{
protected:
    CGMLog();
    ~CGMLog();

    static CGMLog   m_Instance;
    

public:
    static CGMLog  &GetInstance();

    BOOL Init();
    BOOL UnInit();

    BOOL WriteLog(const char *pcszUserName, const char *pcszCmdStr, const char *format, ...);

    BOOL WriteLogWithTime(UINT32 dwTime, const char *pcszName, const char *pcszCmdStr, const char *format, ...);

    BOOL WriteLogData(INT32 nFileType, const char *pcszBuffer);

    BOOL CheckFile(INT32 eLogFileEnum);
private:
#define MAX_LOG_LENGTH (2048)

    char		m_LogContent[glfNum][MAX_LOG_LENGTH];
    FILE*       m_pFile[glfNum];
    UINT32      m_dwCreateFileTime[glfNum];
    INT32       m_nTimeZone;
};






#endif //_H_GM_LOG_H_




