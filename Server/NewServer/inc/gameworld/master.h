/********************************************************************
	created:	7:3:2013   17:44
	file:		master.h
	author:		Allan Tao
	
	purpose:	
*********************************************************************/

#ifndef _H_GS_MASTER_H_
#define _H_GS_MASTER_H_

#include "master_def.h"
#include "message_handler.h"

class CRole;

struct TEACHER_REWARD
{
	UINT32			dwRoleID;
	INT32			nExp;
	INT32			nMasterExp;
};

class CMaster
{
public:
    CMaster();
    ~CMaster();

public:
    BOOL    Init(UINT32 dwSelfID);
    BOOL    Clear();

    BOOL    OnLoadByGS_v_1(const char* pcData, UINT32 dwSize);
    BOOL    SaveByGS(char* pData, UINT32& rdwSize);

    BOOL    Onload(UINT32 dwTeacherID, INT32 nCount, UINT32 *pStudentID);

    BOOL    DelTeacher(UINT32 dwTeacherID);
    BOOL    DelStudent(UINT32 dwStudentID);
    void    AddTeacher(UINT32 dwTeacherID);
    void    AddStudent(UINT32 dwStudentID);

    UINT32  GetTwitterCD()      { return m_dwTwitterCD; }
    void    SetTwitterCD(UINT32 dwCD)   { m_dwTwitterCD = dwCD; }
    void    SetCD(UINT32 dwCD);
    UINT32  GetCD()        { return m_dwCD; }

	UINT32  GetStudentByIndex(INT32 nIndex);
	inline INT32  GetStudentCount();
	
	INT32   GetState()                  { return m_nState; }
    void    SetState(INT32 nState);

	inline BOOL	  IsTeacher();	
    inline BOOL   IsStudent();
	inline UINT32 GetTeacherID();

    inline BOOL IsMyTeacher(UINT32 dwTeacherID);
	inline BOOL	IsMyStudent(UINT32 dwRoleID);

    BOOL    IsStudentFull();

    inline void     SetTwitter(BOOL bTwitter);
    inline BOOL     GetTwitter();

	inline void AddTeacherRewardExp(UINT32 dwStudentRoleID, INT32 nRewardExp);
	inline INT32 GetTeacherRewardExp(UINT32 dwStudentRoleID);
	inline void SetTeacherRewardExp(UINT32 dwStudentRoleID, INT32 nRewardExp);

	inline void AddMasterExp(UINT32 dwStudentRoleID, INT32 nMasterExp);
	inline INT32 GetMasterExp(UINT32 dwStudentRoleID);
	inline void SetMasterExp(UINT32 dwStudentRoleID, INT32 nRewardExp);

	inline const TEACHER_REWARD* GetTeacherRewardList(void);
	inline void ClearTeacherReward(UINT32 dwStudentRoleID);

	inline void AddStudentRewardExp(INT32 nRewardExp);
	inline INT32 GetStudentRewardExp(void);
	inline void SetStudentRewardExp(INT32 nRewardExp);
	inline void ClearStudentRewardExp(void);

	inline INT32 GetStudentRewardMasterID();
	inline void SetStudentRewardMasterID(UINT32 dwRoleID);

	// lua
    BOOL    LuaSyncMasterExpToMS(CRole *poRole);

#ifdef _ROBOT
    BOOL    MainLoop();

    void    SetTwitterRole(UINT32 dwRoleID);
    UINT32  GetTwitterRole();
    BOOL    AsimovLoadTeacher(UINT32 dwTeacherID, UINT8 nTeacherLevel);
    BOOL    AsimovLoadStudent(UINT32 dwStudentID, UINT8 byStudentLevel, UINT8 byCZ);
    BOOL    AsimovClearRecruitList();
    BOOL    AsimovLoadRecuritList(UINT32 dwTeacherID);
    BOOL    AsimovClearSoloList();
    BOOL    AsimovLoadSoloList(UINT32 dwSoloID);

    INT32   AsimovGetRecruitNum();
    UINT32  AsimovGetRecruitRoleByIndex(INT32 nIndex);

    INT32   AsimovGetSoloNum();
    UINT32  AsimovGetSoloRoleByIndex(INT32 nIndex);

    INT32   AsimovGetSendListNum();
    UINT32  AsimovGetSendRoleIDByIndex(INT32 nIndex);

    INT32   AsimovGetRecvNum();
    UINT32  AsimovGetRecvRoleIDByIndex(INT32 nIndex);

    BOOL    AsimovIsSendListFull();
    BOOL    AsimovIsInSendAppList(UINT32 dwRoleID);
    BOOL    AsimovAddSendAppList(UINT32 dwRoleID);
    BOOL    AsimovDelSendAppList(UINT32 dwRoleID);
    BOOL    AsimovClearSendAppList();

    BOOL    AsimovIsRecvListFull();
    BOOL    AsimovIsInRecvAppList(UINT32 dwRoleID);
    BOOL    AsimovAddRecvAppList(UINT32 dwRoleID);
    BOOL    AsimovDelRecvAppList(UINT32 dwRoleID);
    BOOL    AsimovClearRecvAppList();

    BOOL    AsimovUpdateCZLevel(UINT32 dwRoleID, INT32 nCZCount);
    UINT32  AsimovGetCZLevel(UINT32 dwRoleID);
    BOOL    AsimovCanCZStudent(UINT32 dwRoleID);
    BOOL    AsimovUpdateLevel(UINT32 dwRoleID, INT32 nLevel);

    BOOL    AsimovSetGraduateRoleID(UINT32 dwRoleID);
    UINT32  AsimovGetGraduateRoleID();

#endif // _ROBOT


protected:
    BOOL            m_bTwitter;
    UINT32          m_dwTwitterCD;
    UINT32          m_dwCD;
    UINT32          m_dwSelfID;
    UINT32          m_dwTeacherID;
    INT32           m_nStudentNum;
    UINT32          m_arrStudentID[MAX_STUDENT_NUM];

    INT32           m_nState;

	TEACHER_REWARD	m_TeacherReward[MAX_STUDENT_NUM];
    UINT32          m_dwStudentRewardTeacherID;
	INT32			m_nStudentRewardExp;

#ifdef _ROBOT
    INT32           m_dwTwitterTimer;
    UINT32          m_dwTwitterRole;

    INT32           m_nTeacherLevel;
    INT32           m_nStudentCZ[MAX_STUDENT_NUM];
    INT32           m_nStudentLevel[MAX_STUDENT_NUM];

    INT32           m_nRecruitNum;
    UINT32          m_dwRecruitList[SEND_MASTER_INFO_NUM];

    INT32           m_nSoloNum;
    UINT32          m_dwSoloList[SEND_SOLO_INFO_NUM];

    INT32           m_nSendAppNum;
    UINT32          m_dwSendAppList[MAX_MASTER_SEND_APP_NUM];

    INT32           m_nRecvAppNum;
    UINT32          m_dwRecvAppList[MAX_MASTER_RECV_APP_NUM];

    UINT32          m_dwGraduateRoleID;
#endif



};

inline BOOL CMaster::IsTeacher()
{
	return m_nState == MASTER_TEACHER;
}

inline BOOL CMaster::IsStudent()
{
    return m_nState == MASTER_STUDENT;
}

inline INT32 CMaster::GetStudentCount()
{
	return m_nStudentNum;
}

inline UINT32 CMaster::GetTeacherID()
{
	return m_dwTeacherID;
}

inline BOOL CMaster::IsMyTeacher(UINT32 dwTeacherID)
{
    PROCESS_ERROR(m_dwTeacherID != 0);
    PROCESS_ERROR(m_dwTeacherID == dwTeacherID);

    return TRUE;
Exit0:
    return FALSE;
}

inline BOOL	CMaster::IsMyStudent(UINT32 dwRoleID)
{
	for (INT32 nIndex = 0; nIndex < m_nStudentNum; nIndex++)
	{
		if (m_arrStudentID[nIndex] == dwRoleID)
			return TRUE;
	}

	return FALSE;
}

inline void CMaster::SetTwitter(BOOL bTwitter)
{
    m_bTwitter = bTwitter;

#ifndef _ROBOT
    if (IsTeacher())
        CCliMessageHandler::GetInstance().DoMSMasterTwitter(m_dwSelfID, m_bTwitter);
#endif
}

inline BOOL CMaster::GetTwitter()
{
    return m_bTwitter;
}

inline void CMaster::AddTeacherRewardExp(UINT32 dwStudentRoleID, INT32 nRewardExp)
{
	INT32 nEmptyIndex = -1;

	for (INT32 nIndex = 0; nIndex < MAX_STUDENT_NUM; nIndex++)
	{
		if (m_TeacherReward[nIndex].dwRoleID == 0)
		{
			nEmptyIndex = nIndex;
		}
		else if (m_TeacherReward[nIndex].dwRoleID == dwStudentRoleID)
		{
			m_TeacherReward[nIndex].nExp += nRewardExp;
			return;
		}
	}

	LOG_CHECK_ERROR(nEmptyIndex != -1);
	if (nEmptyIndex != -1)
	{
		m_TeacherReward[nEmptyIndex].dwRoleID = dwStudentRoleID;
		m_TeacherReward[nEmptyIndex].nExp = nRewardExp;
	}

	return;
}

inline INT32 CMaster::GetTeacherRewardExp(UINT32 dwStudentRoleID)
{
	for (INT32 nIndex = 0; nIndex < MAX_STUDENT_NUM; nIndex++)
	{
		if (m_TeacherReward[nIndex].dwRoleID == dwStudentRoleID)
		{
			return m_TeacherReward[nIndex].nExp;
		}
	}

	return 0;
}

inline void CMaster::SetTeacherRewardExp(UINT32 dwStudentRoleID, INT32 nRewardExp)
{
	for (INT32 nIndex = 0; nIndex < MAX_STUDENT_NUM; nIndex++)
	{
		if (m_TeacherReward[nIndex].dwRoleID == dwStudentRoleID)
		{
			m_TeacherReward[nIndex].nExp = nRewardExp;
			return;
		}
	}

	LOG_CHECK_ERROR(FALSE);

	return;
}

inline const TEACHER_REWARD* CMaster::GetTeacherRewardList(void)
{
	return m_TeacherReward;
}

inline void CMaster::ClearTeacherReward(UINT32 dwStudentRoleID)
{
	for (INT32 nIndex = 0; nIndex < MAX_STUDENT_NUM; nIndex++)
	{
		if (m_TeacherReward[nIndex].dwRoleID == dwStudentRoleID)
		{
			m_TeacherReward[nIndex].dwRoleID = 0;
			m_TeacherReward[nIndex].nExp = 0;;
			m_TeacherReward[nIndex].nMasterExp = 0;
			break;
		}
	}

	return;
}

inline void CMaster::AddStudentRewardExp(INT32 nRewardExp)
{
	m_nStudentRewardExp += nRewardExp;
}

inline INT32 CMaster::GetStudentRewardMasterID()
{
    return m_dwStudentRewardTeacherID;
}

inline void CMaster::SetStudentRewardMasterID(UINT32 dwRoleID)
{
    m_dwStudentRewardTeacherID = dwRoleID;
}

inline INT32 CMaster::GetStudentRewardExp(void)
{
	return m_nStudentRewardExp;
}

inline void CMaster::SetStudentRewardExp(INT32 nRewardExp)
{
	m_nStudentRewardExp = nRewardExp;
}

inline void CMaster::ClearStudentRewardExp(void)
{
    m_dwStudentRewardTeacherID = 0;
	m_nStudentRewardExp = 0;
}

inline void CMaster::AddMasterExp(UINT32 dwStudentRoleID, INT32 nMasterExp)
{
	INT32 nEmptyIndex = -1;

	for (INT32 nIndex = 0; nIndex < MAX_STUDENT_NUM; nIndex++)
	{
		if (m_TeacherReward[nIndex].dwRoleID == 0)
		{
			nEmptyIndex = nIndex;
		}
		else if (m_TeacherReward[nIndex].dwRoleID == dwStudentRoleID)
		{
			m_TeacherReward[nIndex].nMasterExp += nMasterExp;
			return;
		}
	}

	LOG_CHECK_ERROR(nEmptyIndex != -1);
	if (nEmptyIndex != -1)
	{
		m_TeacherReward[nEmptyIndex].dwRoleID = dwStudentRoleID;
		m_TeacherReward[nEmptyIndex].nMasterExp = nMasterExp;
	}

	return;
}

inline INT32 CMaster::GetMasterExp(UINT32 dwStudentRoleID)
{
	for (INT32 nIndex = 0; nIndex < MAX_STUDENT_NUM; nIndex++)
	{
		if (m_TeacherReward[nIndex].dwRoleID == dwStudentRoleID)
		{
			return m_TeacherReward[nIndex].nExp;
		}
	}

	return 0;
}

inline void CMaster::SetMasterExp(UINT32 dwStudentRoleID, INT32 nRewardExp)
{
	for (INT32 nIndex = 0; nIndex < MAX_STUDENT_NUM; nIndex++)
	{
		if (m_TeacherReward[nIndex].dwRoleID == dwStudentRoleID)
		{
			m_TeacherReward[nIndex].nExp = nRewardExp;
			return;
		}
	}

	LOG_CHECK_ERROR(FALSE);

	return;
}

#endif //_H_GS_MASTER_H_




