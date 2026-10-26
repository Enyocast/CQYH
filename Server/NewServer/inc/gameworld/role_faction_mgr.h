#ifndef _ROLE_FRACTION_H_
#define _ROLE_FRACTION_H_

#include "role_def.h"

class CRoleFactionMgr
{
public:
    CRoleFactionMgr();
    ~CRoleFactionMgr();

    BOOL Init(void);
    BOOL UnInit(void);
    static CRoleFactionMgr& GetInstance(void);

    INT32 GetRelation(INT32 nFaction1, INT32 nFaction2);

private:
    static CRoleFactionMgr ms_Instance;
    INT32   m_nFactionRelation[MAX_ROLE_FRACTION_ID][MAX_ROLE_FRACTION_ID];
};

#endif  // _ROLE_FRACTION_H_