#ifndef _H_MS_CHAT_H_
#define _H_MS_CHAT_H_

class  CMSChatMgr
{
public:
	CMSChatMgr();
	~CMSChatMgr();

	BOOL    Init(const char* pcszScriptName);
	BOOL    Uninit();
	static CMSChatMgr &GetInstance();

	INT32	Say(UINT32 dwSourceRoleID, UINT32 dwTargetRoleID, INT32 nShowLocation, const char* pText, INT32 nGroupID);

private:
	static CMSChatMgr  ms_Instance;
};
#endif // _H_MS_CHAT_H_
