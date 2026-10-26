#ifndef _NAV_DEF_H_
#define _NAV_DEF_H_

#define SCENE_NAV_FILE_EXT_NAME     "nav"
#define SCENE_NAV_FILE_TAG          'navi'
#define SCENE_NAV_FILE_VERSION      (4)
#define MAX_EDGE_PER_POLY			(32)

#ifdef WIN32
    #pragma warning(disable:4200)
#endif  //WIN32

struct NAV_VERTEX_DATA
{
	int						nX;
	int						nY;
	int						nZ;
};

struct SCENE_NAV_HEADER
{
	unsigned int			dwTag;
	unsigned int            dwVersion;
	unsigned short			wVertexCount;
	unsigned short			wEdgeCount;
	NAV_VERTEX_DATA			VertexData[0];
};

struct NAV_EDGE_DATA
{
	unsigned short			wLeftPoint;
	unsigned short			wRightPoint;
	unsigned short			wPairEdge;
	unsigned short			wStartEdge;
	unsigned short			wLinkEdge[MAX_EDGE_PER_POLY - 1];
	unsigned short			wLinkCost[MAX_EDGE_PER_POLY - 1];
};

#endif	// _NAV_DEF_H_