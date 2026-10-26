#pragma once

#if SHIPPING_PC_GAME
#	define M_DEBUG_HUD_NAME 0
#	define M_DEBUG_HUD_NAME_MOVE 0
#	define M_DEBUG_CAMERA_MOVE 0
#else
#	define M_DEBUG_HUD_NAME 0
#	define M_DEBUG_HUD_NAME_MOVE 0
#	define M_DEBUG_CAMERA_MOVE 0
#endif

#if M_DEBUG_HUD_NAME
#	define logTickOrderf debugf
#else
#	define logTickOrderf(...)
#endif


enum ETickOrder
{
	ETO_StopTick,
	ETO_AfterCameraTick,
	ETO_BeforeCameraUpdate,
	ETO_AfterCameraUpdate,

	ETO_BeforeGfxTick,
	ETO_AfterGfxTick,

	ETO_BeforeRenderingTick,
	ETO_AfterRenderingTick,

	ETO_AfterEngineTick,

	ETO_BeforeViewportTick,
	ETO_AfterViewportTick,

	ETO_BeforeCanvasRenderingTick,

	ETO_BeforeRenderUITick,
	ETO_AfterDrawHUDPostGfxTick,
};

extern bool g_updateMainPlayerHudName;

extern ETickOrder g_tickOrder;
extern void _OnMMOTick(FLOAT DeltaSeconds);

#if M_DEBUG_HUD_NAME_MOVE
extern INT g_hudMoveSpeed;
#endif
