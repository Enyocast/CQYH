#ifndef _MMONAVIGATIONMANAGER_H_
#define _MMONAVIGATIONMANAGER_H_

#include "MMOSingleton.h"
#include "GraphUtil/SparseGraph.h"
#include "GraphUtil/GraphAlgorithms.h"
#include <list>
#include <map>
#include "MMOGameEvent.h"
#include "MMOUtil.h"

// 路标的显示隐藏规则仿照斗战神做法:
// 角色到路标的向量与路标指向的夹角(点积: >=0: 夹角小于等于90度，<0:夹角大于90度)来判断角色当前位置是否在当前路标的前方还是后方，前方隐藏，后方显示；
// 同时为了避免U型路线导致的后面的路标还没靠近就消失(因为这些路标在角色的后方)，所以限定角色能够影响路标的最大距离为1024(1024 * 1024 = 1048576)，经验值，差不多一屏
#define PATH_POINT_PLAYER_DIST_SQUARED_MAX 1048576
// 路点更新间隔
#define PATH_POINT_UPDATE_TIME			   0.5f
// 路点消失时间
#define PATH_EFFECT_DISAPPEAR_TIME         0.5f
// 路点波动周期
#define PATH_EFFECT_WAVE_TIME              4.0f

enum
{
	INVALID_MAP_ID = -1,
	MAX_PATH_EFFECT_NUM = 20,
};

// 导航算法
enum NaviMode
{
	NM_DIJKSTRA = 0,		// DIJKSTRA
	NM_ASTAR,				// ASTAR
	NM_ASTARCOST			// ASTAR BY COST
};

// 导航节点
class NaviNode
{  
public:
	NaviNode() : _Index(invalid_node_index), _MapId(INVALID_MAP_ID)
	{}
	NaviNode(INT index) : _Index(index), _MapId(INVALID_MAP_ID)
	{}

	virtual ~NaviNode()
	{}

	INT Index() const { return _Index; }
	void SetIndex(INT index) { _Index = index; }

	INT MapId() const { return _MapId; }
	void SetMapId(INT mapId) { _MapId = mapId; }

protected:
	INT _Index;
	INT _MapId;
};   

// 导航链接
class NaviLink
{
public:
	NaviLink(INT from, INT to, double cost) : _Cost(cost), _From(from), _To(to) 
	{}
	NaviLink(INT from, INT to) : _Cost(1.0), _From(from), _To(to) 
	{}
	NaviLink() : _Cost(1.0), _From(INVALID_MAP_ID), _To(INVALID_MAP_ID) 
	{}

	virtual ~NaviLink() {}

	INT From() const { return _From; }
	void SetFrom(INT mapId){ _From = mapId; }

	INT To() const { return _To; }
	void SetTo(INT mapId) { _To = mapId; }

	double Cost() const { return _Cost; }
	void SetCost(double cost) { _Cost = cost; }

protected:
	INT _From;
	INT _To;
	double _Cost;
};

typedef SparseGraph<NaviNode, NaviLink> NaviGraph;
typedef std::map<INT, class NaviNode, M_UE3_STL_ALLOC_MAP(INT, class NaviNode)> NaviNodeMap;	//MapId->Index

typedef std::list<NaviNode, M_UE3_STL_ALLOC(NaviNode)> NaviNodeList;
typedef std::list<NaviLink, M_UE3_STL_ALLOC(NaviLink)> NaviLinkList;

// 导航类型
enum NaviType
{
	NT_NULL = 0,
	NT_NAV_POINT,					// 导航点
	NT_NPC,							// 导航NPC
	NT_POINT,						// 任意坐标点
	NT_DOODAD,						// DOODAD
};

// 导航事件
struct MMOGameEvent_Navigation : public MMOGameEvent
{
public:
	enum NaviEventType
	{
		NET_NULL = 0,
		NET_BEGIN,				// 开始导航
		NET_END,				// 结束导航
		NET_ENTER_SCENE			// 跨地图
	};

	MMOGameEvent_Navigation()
	{
		_EventType = NET_NULL;
	}

	virtual EGameEvent GetEventType() const { return GameEvent_Navigation; }

public:
	NaviEventType _EventType;
};

struct NaviInfo
{
	NaviType Type;
	FString PointName;
	INT MapId;
	INT NpcId;
	INT DoodadId;
	FVector Point;
	UBOOL NeedMove;

	NaviInfo() : Type(NT_NULL), 
		PointName(TEXT("")), 
		MapId(INVALID_MAP_ID), 
		NpcId(0), 
		Point(0.0, 0.0, 0.0), 
		DoodadId(0), 
		NeedMove(FALSE)
	{}
};

struct PathPointInfo
{
	FVector Pos;
	UBOOL NeedDisappear;
	FLOAT DisappearTime;

	PathPointInfo() : Pos(0.0, 0.0, 0.0), NeedDisappear(FALSE), DisappearTime(0.0)
	{}
};

class MMONavigationManager : public SingletonMeyers<MMONavigationManager>, public INativeGameEventHandler
{
public:
	MMONavigationManager();
	virtual ~MMONavigationManager();

	void Init();
	void Shutdown();
	void Clear();
	void Update(FLOAT deltaTime);
	virtual void OnNativeGameEvent(struct MMOGameEvent* evt);

	void StopNavigate(UBOOL stopMove = TRUE);

	// 找到并且向对应的teleport移动
	UBOOL FindAndMoveToTeleport(INT from, INT to, INT npcId = 0, UBOOL needMove = FALSE);

	void EnterScene();

	UBOOL IsNavigating(){ return _IsNavigating; }

	void InitPathEffect();
	void ShutdownPathEffect();
	void ClearPathEffect();

	

protected:
	UBOOL _Navigate(INT mapId, const FString& pointName, UBOOL needMove);
	UBOOL _NavigateDoodad(INT mapId, const FString& pointName, INT doodadId, UBOOL needMove);
	UBOOL _Navigate(INT mapId, INT npcId, UBOOL needMove);
	UBOOL _Navigate(INT mapId, FVector point, UBOOL needMove);

protected:
	void _AddNaviNode(INT mapId);
	void _AddNaviLink(INT from, INT to, double cost);
	INT _GetNaviNodeMapId(INT index);

	void _SearchByDijkstra(INT from, INT to, std::list<INT>& list);
	void _SearchByAStar(INT from, INT to, std::list<INT>& list);
	void _SearchByAStarCost(INT from, INT to, std::list<INT>& list);

	UBOOL _GenNaviNodeList(INT from, INT to);
	INT _GetNextMapId(INT curIndex);

	void _StopNavigate();
	void _BeginNavigate();

	// 路点特效
	void _FiltPathPoint(FVector& pos);
	void _GeneratePathPoint();
	void _UpdatePathPoint(FLOAT deltaTime);
	void _DrawPathEffect(FLOAT deltaTime);


	

	// CQ版本，客户端寻路依然是导航网格，某些可行走格子，导航网格是不可达的，对于不可达的坐标点，这里做适当偏移
	UBOOL _GeneratePath(const FVector& srcPoint, const FVector& dstPoint, UBOOL withOffset = FALSE);
public:
	UBOOL Navigate(INT mapId, INT npcId, UBOOL needMove);										// 用于NPC寻路
	UBOOL Navigate(INT mapId, const FString& pointName, UBOOL needMove);						// 用于导航点寻
	UBOOL NavigateDoodad(INT mapId, const FString& pointName, INT doodadId, UBOOL needMove);	// 用于doodad寻路
	UBOOL Navigate(INT mapId, FVector point, UBOOL needMove);									// 用于任意坐标点寻路

protected:
	NaviMode _NaviMode;
	NaviGraph* _NaviGraph;
	NaviNodeMap _NaviNodeMap;

	NaviNodeList _NaviNodeList;
	NaviLinkList _NaviLinkList;

	NaviInfo _NaviInfo;
	UBOOL _IsNavigating;

	TArray<PathPointInfo> _PathPointList;
	TArray<AMMONavitationEmitter*> _PathEffectList;
	FLOAT _PathPointProgress;
	FLOAT _PathEffectProgress;
};

#endif