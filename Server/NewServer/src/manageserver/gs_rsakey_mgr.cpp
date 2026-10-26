#include "stdafx.h"
#include "gs_rsakey_mgr.h"
#include "rsa_sign.h"

CRSAKeyMgr CRSAKeyMgr::ms_Instance;

CRSAKeyMgr::CRSAKeyMgr()
{
	m_pKey = NULL;
}

CRSAKeyMgr::~CRSAKeyMgr()
{
	UnInit();
}

BOOL CRSAKeyMgr::Init(void)
{
	//m_pKey = RSA_GenetateKey();
	//LOG_PROCESS_ERROR(m_pKey);

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CRSAKeyMgr::UnInit(void)
{
	//RSA_FreeKey(m_pKey);

    return TRUE;
}