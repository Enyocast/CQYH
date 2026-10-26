/********************************************************************
	created:	19:11:2013   19:17
	file:		ms_guild_member.h
	author:		Allan Tao
	
	purpose:	guild member class
*********************************************************************/

#ifndef _H_MS_GUILD_MEMBER_H_
#define _H_MS_GUILD_MEMBER_H_



class CMsGuildMember
{
public:
    CMsGuildMember();
    ~CMsGuildMember();

    BOOL Init(UINT32 dwGuildID, UINT32 dwRoleID, UINT8 byPosition, UINT8 byFlag, INT32 nSalary, INT32 dwDrawSalaryTime, INT32 nPow);
    BOOL UnInit();

    inline  UINT32  GetGuildID();
    inline  UINT32  GetRoleID();

    inline  UINT8   GetPosition();
    BOOL SetPosition(UINT8 byPosition, BOOL isNtf = TRUE);

    inline  UINT8   GetFlag();
    BOOL SetFlag(UINT8 byFlag);
    

    inline  INT32   GetSalary();
    BOOL    AddSalary(INT32 nSalary, BOOL isSave = TRUE);
    BOOL    SubSalary(INT32 nSalary, BOOL isSave = TRUE);

    inline  UINT32  GetDrawSalaryTime();
    BOOL    SetDrawSalaryTime(UINT32 dwTime);

    // pow
    void  SetPow(INT32 nRolePow)     { m_nPow = nRolePow; }
    INT32 GetPow()          { return m_nPow; }
    BOOL  SavePow();

protected:
    BOOL    _Save();



private:
    UINT32      m_dwGuildID;
    UINT32      m_dwRoleID;
    UINT8       m_byPosition;
    UINT8       m_byGuildFlag;        // GUILD_FLAG_FIELD
    INT32       m_nSalary;
    UINT32      m_dwDrawSalaryTime;

    INT32       m_nPow;
};


inline UINT32 CMsGuildMember::GetGuildID()
{
    return m_dwGuildID;
}

inline UINT32 CMsGuildMember::GetRoleID()
{
    return m_dwRoleID;
}

inline UINT8 CMsGuildMember::GetPosition()
{
    return m_byPosition;
}

inline UINT8 CMsGuildMember::GetFlag()
{
    return m_byGuildFlag;
}

inline INT32 CMsGuildMember::GetSalary()
{
    return  m_nSalary;
}

inline UINT32 CMsGuildMember::GetDrawSalaryTime()
{
    return m_dwDrawSalaryTime;
}




#endif //_H_MS_GUILD_MEMBER_H_





