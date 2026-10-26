#ifndef _OA_STATICLOGIN_MGR_H_
#define _OA_STATICLOGIN_MGR_H_

#include "wininet.h"

struct stAuthContext;
class CUser;

class COAStaticLoginMgr
{
public:
	COAStaticLoginMgr();
	~COAStaticLoginMgr();

	BOOL Init(VOID);
	BOOL UnInit(VOID);
	static COAStaticLoginMgr& GetInstance(VOID);

	BOOL DoLogin(CUser* poUser);
private:
	BOOL _ProcessUrlAndGetSession(CUser* poUser, const char* pcszURL);

private:
	static COAStaticLoginMgr ms_Instance;
    HINTERNET m_hSession;
};

#endif  // _OA_STATICLOGIN_MGR_H_
