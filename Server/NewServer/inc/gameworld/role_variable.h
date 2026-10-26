#ifndef _ROLE_VARIABLE_H_
#define _ROLE_VARIABLE_H_

#define MAX_ROLE_VAR_COUNT  (1024)

class CRoleVariable
{
public:
    CRoleVariable();
    ~CRoleVariable();

    BOOL Init(void);
    BOOL UnInit(void);

    BOOL Load(const char* pData, UINT32 dwSize);
    BOOL Save(char* pData, UINT32& rdwSize);

    void SetValue(INT32 nIndex, INT32 nValue);
    INT32 GetValue(INT32 nIndex);

private:
    INT32   m_nVarList[MAX_ROLE_VAR_COUNT];
};

#endif  // _ROLE_VARIABLE_H_