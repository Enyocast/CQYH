
#pragma once

#if !SHIPPING_PC_GAME

enum EShowHistogramStyle
{
	ESHS_Composed,
	ESHS_Separeted,
	ESHS_All
};

extern UINT GShowHistogramStyle;

#define HISTOGRAM_LEVEL (256)

struct FHistogram
{
	UINT Value[HISTOGRAM_LEVEL];
};

enum EHistogramType
{
	EHT_LUMINANCE,
	EHT_R,
	EHT_G,
	EHT_B,
	EHT_NUM
};

extern FHistogram GHistogram[ EHT_NUM ];

void UpdateHistogram( FViewport* Viewport, EShowFlags ShowFlag );

UINT GetMaxHistogramValue();

void DrawHistogram(class FCanvas* Canvas, EShowFlags ShowFlag);

#endif