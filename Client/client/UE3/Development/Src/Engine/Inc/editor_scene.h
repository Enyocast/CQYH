#ifndef _EDITOR_SCENE_
#define _EDITOR_SCENE_

//#if !SHIPPING_PC_GAME

#include "string_def.h"
#include "scene_def.h"

struct GRID_DATA;
struct ZONE_DATA;
struct NAV_VERTEX_DATA;
struct NAV_EDGE_DATA;


enum DIRECTION_8_TYPE
{
	DT_EAST,
	DT_SOUTH_EAST,
	DT_SOUTH,
	DT_SOUTH_WEST,
	DT_WEST,
	DT_NORTH_WEST,
	DT_NORTH,
	DT_NORTH_EAST,

	DT_DIRECTION_8_COUNT
};

extern INT32 g_nAdjacentX[DT_DIRECTION_8_COUNT];
extern INT32 g_nAdjacentY[DT_DIRECTION_8_COUNT];
extern bool g_bUseX[DT_DIRECTION_8_COUNT];

typedef ZONE_DATA* ZONE_DATA_TYPE[MAX_ZONE_PER_SCENE][MAX_ZONE_PER_SCENE];

class CEditorScene
{
public:
	CEditorScene();
	CEditorScene(const TCHAR* pStrPathConfigName);
	~CEditorScene();

	bool Init(const TCHAR* pcszName);
	bool UnInit(void);

	bool Load(void);
	bool Save(void);

	GRID_DATA* GetGroundGrid(int nX, int nY);
	GRID_DATA* GetGrid(int nX, int nY, int nZ);
	GRID_DATA* CreateGrid(int nX, int nY, int nLowZ, int nHighZ);
	GRID_DATA* GetGridByIndex(int nX, int nY, int Index);

	inline ZONE_DATA* GetZone(int nZoneX, int nZoneY);
	inline ZONE_DATA_TYPE& GetZoneData(void);
	bool Preprocess(void);
	bool ProcessNavData(unsigned char* data, const int dataSize);
    bool SetVolumeScript(INT32 nVolumeID, const char* pcszScript);
	bool SetMaxVolumeTriggerCount(INT32 nVolumeID, INT32 nMaxTriggerCount);


	bool IsModified(void) {return m_bModified;}
	void SetModified(void) { m_bModified = TRUE;}

#if !SHIPPING_PC_GAME
	void CheckForError();
#endif

	const GRID_DATA* _GetLowerGrid(INT64 llX, INT64 llY, INT64 llZ);
	inline unsigned short _GetEdge(NAV_VERTEX_DATA* VertexData, int nVertexCount, NAV_EDGE_DATA* EdgeData, int nEdgeCount, int nX, int nY, int nZ, BOOL& rbOutOfPoly);
	inline bool _CheckPos(__int64 nX, __int64 nY, NAV_VERTEX_DATA* pLeftPoint, NAV_VERTEX_DATA* pRightPoint);


protected:
	bool LoadPhxFromFile(const TCHAR* pPhxFilePath);

protected:
	TCHAR		m_szSceneName[PATH_LEN];
	FString     m_strPathConfigName;
    char        m_szVolumeScript[MAX_VOLUME_COUNT][MAX_EMBEDDED_SCRIPT_LEN];
	int			m_nMaxTriggerCount[MAX_VOLUME_COUNT];
	ZONE_DATA*	m_ZoneData[MAX_ZONE_PER_SCENE][MAX_ZONE_PER_SCENE];
	int			m_nGridTotal;
	int			m_nZoneTotal;
	bool		m_bModified;

};

//#endif // !SHIPPING_PC_GAME

inline ZONE_DATA* CEditorScene::GetZone(int nZoneX, int nZoneY)
{
	if (nZoneX < 0 || nZoneX >= MAX_ZONE_PER_SCENE ||
		nZoneY < 0 || nZoneY >= MAX_ZONE_PER_SCENE)
	{
		return NULL;
	}

	return m_ZoneData[nZoneX][nZoneY];
}

inline ZONE_DATA_TYPE& CEditorScene::GetZoneData(void)
{
	return m_ZoneData;
}


inline void ConvertCoordC2S(float& x, float& y, float& z)
{
	const float k = 0.7071068f;
	x *= POINT_PER_CM; 
	y *= POINT_PER_CM; 
	z *= POINT_PER_CM; 
	float xx = x;
	float yy = y;
	x = xx * k - yy * k + MAX_SCENE_WIDTH / 2;
	y = xx * k + yy * k;
}

inline void ConvertCoordC2S(FVector& v)
{
	ConvertCoordC2S(v.X, v.Y, v.Z);
}

inline void ConvertXYToServer(float& x, float& y)
{
	const float k = 0.7071068f;
	float xx = x;
	float yy = y;
	x = xx * k - yy * k + (MAX_SCENE_WIDTH / POINT_PER_CM) / 2;
	y = xx * k + yy * k;
}

inline void ConvertCoordS2C(float& x, float& y, float& z)
{
	const float k = 0.7071068f;
	float xx = x - MAX_SCENE_WIDTH / 2;
	float yy = y;
	x = xx * k + yy * k;
	y = -xx * k + yy * k;
	x /= POINT_PER_CM;
	y /= POINT_PER_CM;
	z /= POINT_PER_CM;
}

inline void ConvertXYToClient(float& x, float& y)
{
	const float k = 0.7071068f;
	float xx = x - (MAX_SCENE_WIDTH / POINT_PER_CM) / 2;
	float yy = y;
	x = xx * k + yy * k;
	y = -xx * k + yy * k;
}

inline void ConvertCoordS2C(FVector& v)
{
	ConvertCoordS2C(v.X, v.Y, v.Z);
}

inline void ConvertCoordN2C(FVector& Pos)
{
	Pos = Pos * 4 * POINT_PER_CM;
	ConvertCoordS2C(Pos);
}

inline void ConvertCoordC2N(FVector& Pos)
{
	ConvertCoordC2S(Pos);
	Pos = Pos / (POINT_PER_CM * 4);
}

inline void ConvertBoxToServer(FBox& box)
{
	FBox temp = box;
	float x, y;

	box.Min.X = temp.Min.X;
	y = temp.Max.Y;
	ConvertXYToServer(box.Min.X, y);

	x = temp.Min.X;
	box.Min.Y = temp.Min.Y;
	ConvertXYToServer(x, box.Min.Y);

	box.Min.Z = temp.Min.Z;

	box.Max.X = temp.Max.X;
	y = temp.Min.Y;
	ConvertXYToServer(box.Max.X, y);

	x = temp.Max.X;
	box.Max.Y = temp.Max.Y;
	ConvertXYToServer(x, box.Max.Y);

	box.Max.Z = temp.Max.Z;
}

inline FLOAT ConvertToClientTime(INT ServerFrames)
{
	return FLOAT(ServerFrames) / FLOAT(GAME_FPS);
}

inline INT ConvertToServerDegree(INT Yaw)
{
	Yaw = (Yaw & 0xFFFF) >> 3;
	Yaw = (Yaw + 1024) % 8192;
	return Yaw;
}

inline INT ConvertToClientDegree(INT ServerYaw)
{
	ServerYaw = (ServerYaw + 1024 * 7) % 8192;
	return ServerYaw<<3;
}

#endif	// _EDITOR_SCENE_
