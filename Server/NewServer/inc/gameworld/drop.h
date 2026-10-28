#ifndef _DROP_H_
#define _DROP_H_

#include "scene_object.h"
#include <list>

struct Item;
class CRole;

struct DropContent
{
    struct DropMoney
    {
        INT32 moneytype;
        INT32 count;
    };

    enum
    {
        DROP_INVALID,
        DROP_ITEM,
        DROP_MONEY
    };

    UINT8 m_type;
    union
    {
        Item* m_item;
        DropMoney m_money;
    };
};

class CDrop : public CSceneObject
{
public:
    CDrop();
    virtual ~CDrop();

    enum DropState
    {
        DS_INVALID,
        DS_PROTECT, // 保护期，有拾取权的角色可拾取
        DS_PUBLIC,  // 保护期结束，任何人都可以拾取
        DS_PLAYER   // 玩家丢弃，任何人都可以拾取
    };

    BOOL Init(UINT32 dwObjID, const DropContent& content, DropState drop_state);
    BOOL UnInit(void);
    BOOL MainLoop();
    virtual INT32 GetObjType();
    void AddOwner(UINT32 dwRoleID);
    BOOL IsOwner(UINT32 dwRoleID) const;
	UINT32 PopOwner();

    INT32 OnPickUp(CRole* pRole);
    void DestroyContent();

    DropContent m_content;

private:
    DropState m_state;
    INT64 m_state_frame;    //是哪一帧进入当前状态的
    void _SetState(DropState estate, INT64 frame = 0);

    std::set<UINT32> m_owners;
	typedef std::set<UINT32>::iterator iterowner;
};


#endif // _DROP_H_