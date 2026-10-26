#ifndef _MAPIMGTILES_H_
#define _MAPIMGTILES_H_

#include "MMOUtil.h"

#define MAP_SNAPSHOT_COORDINATE_STEP 1024

const FLOAT SIN_MAP = 0;//0.70710678118654752440084436210485;//sin45
const FLOAT COS_MAP = 1;//0.70710678118654752440084436210485;//cos45

enum MapTilesType
{
	E_MINIMAP_TILES,
	E_WORLDMAP_TILES,
	E_PATHMAP_TILES
};

class MMOMapImgTiles
{
public:
	static MMOMapImgTiles* GetMapImgTiles( MapTilesType mType );
	static void RegtMapImgTiles( MapTilesType mType, MMOMapImgTiles* tiles );

	//MMOMapImgTiles(){
	//	_TileUiRowMax = 0;
	//	_TileUiColMax = 0;
	//	_ShowTile = NULL;
	//}
	MMOMapImgTiles( UINT16 rowMax, UINT16 colMax );
	virtual ~MMOMapImgTiles();
public:
	bool isReady(){ 
		return _IsInitialized == TRUE;// && mapRfrncObj[1] != NULL;
	}

	bool LoadUiTile( TArray<UGFxObject*>titles, FString texLoaderName );
	void Initialize( UMMOGFXPlayer *OwnerPlayer, FString mapName, FVector pos3D,
					UINT uTileW, UINT uTileH, INT tileImgXMax, INT tileImgYMax,
					FVector2D region3Dto2D, FVector2D region2dOffsetInMap, FVector2D afterTurnedOffsetInMap, float fScale );
	void SetTilesGap( FLOAT fGap ){ _TilesGap = fGap; }
	void InitTilesFitImgTilesNums();
	//
	//void JustifyMapTilesToOrigin( FVector2D pos2DInMap );
	void TilesGoAroundByPosInTile( FVector2D pos2DInMap, bool hasBound = false );
	void UpdateTilesFitsView( FVector2D viewCenterPosInMap, UINT viewWidth, UINT viewHeight );
	void OnlyUpdateTilesPosition( FVector2D viewCenterPosInMap );
	FVector2D TilesKeepNotExceedBoundAround( FVector2D pos2DInMap, UINT halfW, UINT halfH );
	FVector2D KeepTilesNotExceed( UINT halfW, UINT halfH );
	void TileTheMap();

	FVector2D MMOMapImgTiles::GetOriginOffset(){
		return _MainTilePos;
	}
	//FVector2D PosInUiByScaledUiCenter( FVector pos3DNeedCovert, FVector2D pos2DCenter );
	FVector2D Map2DPosByWorld3DPos( FVector pos3D );
	FVector World3DPosByScaledMap2DPos( FVector2D pos2D );
	FVector World3DPosByMap2DPos( FVector2D pos2D );
	FVector2D Map2DOffsetFromWorld3DPos( FVector pos3D, FVector pos3DFrom );
	FVector2D ScaledMap2DOffsetFromWorld3DPos( FVector pos3D, FVector pos3DFrom ){
		return Map2DOffsetFromWorld3DPos( pos3D, pos3DFrom ) * _ZoomFactor;
	}

public:
	//
	UMMOGFXPlayer *_GfxPlayer;
	FString _TexName;
	//AMMOGameObject* mapRfrncObj[2];
	//
	FVector2D _Map3Dto2D;
	FVector2D _MapOffset;
	FVector2D _MapOffset2;
	float _ZoomFactor;

	struct UITile{
		UGFxObject *_UiObj;//this value mast be exit(defined in unrealscript)
		INT _ImgIdxX;
		INT _ImgIdxY;
		UINT _ImgLoderIdx;
		UINT _IsChanged;
		UITile()
		{
			_UiObj = 0;
			_ImgIdxX = 0;//0x80000001;
			_ImgIdxY = 0;//0x80000001;
			_ImgLoderIdx = 0;
			_IsChanged = 0;
		}
		virtual ~UITile()
		{
		}
		UITile( const UITile& Other )
		{
			*this = Other;
		}
		UITile& operator=( const UITile& Other )
		{
			if( this != &Other )
			{
				_UiObj = Other._UiObj;
				_ImgIdxX = Other._ImgIdxX;
				_ImgIdxY = Other._ImgIdxY;
				_ImgLoderIdx = Other._ImgLoderIdx;
				_IsChanged = Other._IsChanged;
			}
			return *this;
		}
	};

private:
	void ResetAllTiles();
	void Right2Left();
	void Left2Right();
	void Bottom2Top();
	void Top2Bottom();

private:
	typedef std::map<MapTilesType, MMOMapImgTiles*, M_UE3_STL_ALLOC_MAP(MapTilesType, MMOMapImgTiles*) > MapImgTilesMap;
	static MapImgTilesMap _MapImgTile;

private:
	UINT16 _TileUiRowMax;
	UINT16 _TileUiColMax;
	INT _TileImgRowNum;
	INT _TileImgColNum;
	//
	//UITile _ShowTile[_TileUiRowMax][_TileUiColMax];
	FString _texLoaderName;
	UITile **_ShowTile;
	UITile *_InterTempTile;
	FVector2D _MapTileSize;
	//FVector2D mapSize;
	////
	//FVector2D map3DBox;
	//FVector2D map2DBox;
	//
	//FVector2D displayOffset;

private:
	UBOOL _IsInitialized;
	FIntPoint _LastTileIdx;
	UBOOL _IsLastOnLeft;
	UBOOL _IsLastOnTop;
	//
	UINT16 _RowIdx;
	UINT16 _ColIdx;
	FVector2D _MainTilePos;
	FIntPoint _MapTileImgIdx;
	FLOAT _TilesGap;
};

#endif