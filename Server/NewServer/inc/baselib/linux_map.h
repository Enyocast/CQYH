#ifndef _LINUX_MAP_H_
#define _LINUX_MAP_H_

#pragma pack(push, 1)
template<class N>
struct LM_MAP_NODE
{
	N               ID;
	union
	{
		LM_MAP_NODE*	pNext;
#if defined(WIN64) | defined(LINUX64)
		UINT64			uColor;
#else
		UINT32			uColor;
#endif
	};
	LM_MAP_NODE*	pLeft;
	LM_MAP_NODE*	pRight;
};
#pragma  pack(pop)

template<class N>
BOOL LM_Insert(LM_MAP_NODE<N>* pDataNode, LM_MAP_NODE<N>** ppRootNode);
template<class N>
void LM_Erase(LM_MAP_NODE<N>* pDataNode, LM_MAP_NODE<N>** ppRootNode);

template<class N>
LM_MAP_NODE<N>* LM_Search(N ID, LM_MAP_NODE<N>* pRootNode);

template<class N>
LM_MAP_NODE<N>* LM_First(LM_MAP_NODE<N>* pRootNode);
template<class N>
LM_MAP_NODE<N>* LM_Last(LM_MAP_NODE<N>* pRootNode);
template<class N>
LM_MAP_NODE<N>* LM_Next(LM_MAP_NODE<N>* pDataNode);
template<class N>
LM_MAP_NODE<N>* LM_Prev(LM_MAP_NODE<N>* pDataNode);

#include "linux_map_inl.h"

#endif	// _LINUX_MAP_H_
