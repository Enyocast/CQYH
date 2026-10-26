#ifndef _GS_RSAKEY_MGR_H_
#define _GS_RSAKEY_MGR_H_

typedef struct rsa_st RSA;

class CRSAKeyMgr
{
public:
	CRSAKeyMgr();
	virtual ~CRSAKeyMgr();

	inline static CRSAKeyMgr& GetInstance(void);
	inline RSA*   GetRSAKey();

	BOOL Init(void);
	BOOL UnInit(void);

private:
	static CRSAKeyMgr   ms_Instance;
	RSA*				m_pKey;
};


inline CRSAKeyMgr& CRSAKeyMgr::GetInstance(void)
{
	return ms_Instance;
}

inline RSA* CRSAKeyMgr::GetRSAKey()
{
	return m_pKey;
}

#endif  // _GS_RSAKEY_MGR_H_