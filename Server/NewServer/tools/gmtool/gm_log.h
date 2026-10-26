/********************************************************************
	created:	1:3:2014   11:05
	file:		gm_log.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/


#ifndef _H_GM_LOG_H_
#define _H_GM_LOG_H_



class CGMLog
{
protected:
    CGMLog();
    ~CGMLog();

    static CGMLog   m_Instance;


public:
    static CGMLog &GetInstance();

    BOOL Init();
    BOOL UnInit();


    BOOL Log(const char *pcszLog, ...);





private:







};














#endif //_H_GM_LOG_H_






