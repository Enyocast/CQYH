#ifndef _COOLDOWN_H_
#define _COOLDOWN_H_

class CCoolDown
{
public:
	CCoolDown(void);

	void Init(void);
	void UnInit(void);

	BOOL Add(INT32 nKey, INT32 nInterval);
    void Reset(INT32 nKey);
	void ResetAll(void);
	BOOL CheckReady(INT32 nKey);
    INT32 GetRemainFrm(INT32 nKey);
	BOOL ChangeRemainFrm(INT32 nKey, INT32 nValue);

    void Enable(BOOL bEnabled);
	BOOL IsDisabled(void);

	void Begin(void);
	BOOL Next(INT32& nKey, UINT32& dwTimeupFrm);

private:
	typedef std::map<INT32, INT32> TCoolDownMap;
	TCoolDownMap m_CoolDownMap;
	TCoolDownMap::iterator m_CoolDownItr;

    BOOL        m_bDisabled;
};

#endif // _cooldown_h__
