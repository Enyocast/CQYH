#ifndef _ADVENTURE_H_
#define _ADVENTURE_H_

class CScene;
class CRole;
class CNpc;
class CDoodad;
struct ADVENTURE_DATA;

class CAdventure
{
public:
    CAdventure();
    ~CAdventure();

    BOOL Init(void);
    BOOL UnInit(void);
    static CAdventure& GetInstance(void) {return ms_Instance;}

    void OnMainLoop(CRole* poRole);
    void OnKillNpc(CRole* poRole, CNpc* poNpc);
    void OnDestoryDoodad(CRole* poRole, CDoodad* poDoodad);
    void OnRefineEquip(CRole* poRole);
    void OnAddSoul(CRole* poRole);
    void OnRandomizeEquip(CRole* poRole);

    void TriggerReward(const ADVENTURE_DATA* pAdventureData, CRole* poRole);
    void SpawnNpcAtPoint(INT32 nServerGroup, const ADVENTURE_DATA* pAdventureData);
    void SpawnDoodadAtPoint(INT32 nServerGroup, const ADVENTURE_DATA* pAdventureData);

private:
    inline BOOL _CheckTrigger(const ADVENTURE_DATA* pAdventureData, CRole* poRole, INT32 nMaxCount, INT32 nChance);

    struct CTraverseSceneSpawnNpc
    {
        const ADVENTURE_DATA* pAdventureData;
        INT32 nServerGroup;
        BOOL operator()(UINT64 qwSceneKey, CScene* poScene);
    }                   m_TraverseSceneSpawnNpc;

    struct CTraverseSceneSpawnDoodad
    {
        const ADVENTURE_DATA* pAdventureData;
        INT32 nServerGroup;
        BOOL operator()(UINT64 qwSceneKey, CScene* poScene);
    }                   m_TraverseSceneSpawnDoodad;

private:
    static CAdventure   ms_Instance;

    typedef std::list<const ADVENTURE_DATA*> ADVENTURE_DATA_LIST;
    ADVENTURE_DATA_LIST m_OnlineTimeList;
    ADVENTURE_DATA_LIST m_RefindEquipList;
    ADVENTURE_DATA_LIST m_AddSoulList;
    ADVENTURE_DATA_LIST m_RandomizeEquipList;
};

#endif  // _ADVENTURE_H_