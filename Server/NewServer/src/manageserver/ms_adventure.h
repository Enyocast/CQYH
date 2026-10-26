#ifndef _MS_ADVENTURE_H_
#define _MS_ADVENTURE_H_

struct ADVENTURE_DATA;
struct MS_ONLINE_ROLE_DATA;

class CMSAdventure
{
public:
    CMSAdventure();
    ~CMSAdventure();

    BOOL Init(void);
    BOOL UnInit(void);
    BOOL MainLoop(void);
    static CMSAdventure& GetInstance(void) {return ms_Instance;}

    void CheckTrigger(MS_ONLINE_ROLE_DATA* pOnlineRole, INT32 nAdventureID, INT32 nVarID, INT32 nMaxCount, INT32 nChance);

private:
    static CMSAdventure ms_Instance;

    typedef std::list<const ADVENTURE_DATA*> ADVENTURE_DATA_LIST;
    ADVENTURE_DATA_LIST m_ServerTimeList;
};

#endif