#ifndef _BLOCK_HANDLER_H__
#define _BLOCK_HANDLER_H__

//class CScene;
//class CSceneObject;
//struct GRID_DATA;
//struct ZONE_DATA;
//struct GRID_INSTANCE_DATA;
//
//class CBlockHandler
//{
//public:
//	CBlockHandler(void);
//	virtual ~CBlockHandler(void);
//
//	BOOL Init(CSceneObject* poSceneObj);
//	void UnInit(void);
//
//	BOOL EnableBlock(CSceneObject* poSceneObj, INT32 eBlockType, INT32 eBlockShape, INT32 nBlockParam);
//    void DisableBlock(CSceneObject* poSceneObj);
//
//	inline INT32 GetBlockType(void);
//
//protected:
//    BOOL _LineBlockMark(CScene* poScene, INT64 llSrcX, INT64 llSrcY, INT64 llSrcZ, INT64 llDstX, INT64 llDstY, INT64 llDstZ);
//    BOOL _SquareBlockMark(CScene* poScene, INT64 llCenterX, INT64 llCenterY, INT64 llCenterZ, INT64 llWidth);
//	BOOL _ProcessGridBlock(CScene* poScene, INT64 llX, INT64 llY, INT64 llZ);
//
//private:
//	INT32 m_eBlockType;
//	INT32 m_eBlockShape;
//
//	typedef std::list<GRID_INSTANCE_DATA*> TGridList;
//	TGridList			m_BlockGridList;
//};
//
//
//inline INT32 CBlockHandler::GetBlockType(void)
//{
//	return m_eBlockType;
//}

#endif // block_handler_h__

