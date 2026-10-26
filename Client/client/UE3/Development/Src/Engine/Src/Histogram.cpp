
#include "EnginePrivate.h"
#include "Histogram.h"
#include "UnTemplate.h"

#if !SHIPPING_PC_GAME

FHistogram GHistogram[ EHT_NUM ];
UINT GShowHistogramStyle = 0;

#if 0
bool UpdateTestHistogram()
{
	for (register INT i = 0; i < EHT_NUM; ++i)
	{
		for (INT j = 0; j < HISTOGRAM_LEVEL; ++j)
		{
			GHistogram[i].Value[j] = RandRange(0, 255);
		}
	}
	return true;
}

static bool g_initHistogram = UpdateTestHistogram();
#endif

void UpdateHistogram( FViewport* Viewport, EShowFlags ShowFlag )
{
	if(!(ShowFlag & SHOW_Histogram))
	{
		return;
	}

	static INT cnt = 0;
	++cnt;

	if(cnt < 30)
	{
		return;
	}

	cnt = 0;

	TArray<FColor> srcImg;
	Viewport->ReadPixels(srcImg);
	memset(&GHistogram[0], 0, sizeof(FHistogram) * EHT_NUM);

	for (register INT i = 0; i < srcImg.Num(); ++i)
	{
		register BYTE r = srcImg(i).R;
		register BYTE g = srcImg(i).G;
		register BYTE b = srcImg(i).B;

		register UINT tmpLum = ((INT)r * 114 + (INT)g * 587 + (INT)b * 299) / 1000;
		register BYTE lum = (BYTE)tmpLum;

		++GHistogram[EHT_LUMINANCE].Value[lum];
		++GHistogram[EHT_R].Value[r];
		++GHistogram[EHT_G].Value[g];
		++GHistogram[EHT_B].Value[b];
	}
}

UINT GetMaxHistogramValue()
{
	UINT maxVal = 0;
	//UINT64 allCount = 0;
	for (INT i = 0; i < EHT_NUM; ++i)
	{
		for (INT j = 0; j < HISTOGRAM_LEVEL; ++j)
		{
			UINT val = GHistogram[i].Value[j];
			//allCount += val;

			if(val > maxVal)
			{
				maxVal = val;
			}
		}
	}

	//debugf(TEXT("Max Histogram val:%u all:%d"), maxVal, allCount);
	return maxVal;
}

void DrawHistogram(FCanvas* Canvas, EShowFlags ShowFlag)
{
	if(!(ShowFlag & SHOW_Histogram))
	{
		return;
	}

	static FLinearColor hisClrs[EHT_NUM] =
	{
		FLinearColor(1.0f, 1.0f, 1.0f, 0.5f),
		FLinearColor(1.0f, 0.0f, 0.0f, 0.5f),
		FLinearColor(0.0f, 1.0f, 0.0f, 0.5f),
		FLinearColor(0.0f, 0.0f, 1.0f, 0.5f)
	};

	static FLinearColor hisClrsComposed[EHT_NUM] =
	{
		FLinearColor(1.0f, 1.0f, 1.0f, 1.0f),
		FLinearColor(1.0f, 0.0f, 0.0f, 0.5f),
		FLinearColor(0.0f, 1.0f, 0.0f, 0.5f),
		FLinearColor(0.0f, 0.0f, 1.0f, 0.5f)
	};

	UINT maxHistogramVal = Clamp(GetMaxHistogramValue(), (UINT)1, (UINT)0xFFFFFFFF);
	const UINT C_DrawSizeWidth = 256;
	const UINT C_DrawSizeHeight = 100;

	const UINT C_DrawOrigX = 4;
	const UINT C_DrawOrigY = C_DrawSizeHeight + 4;

	FLOAT heightR = maxHistogramVal / C_DrawSizeHeight;

	INT drawY = C_DrawOrigY;

	if(GShowHistogramStyle == (UINT)ESHS_Composed || GShowHistogramStyle == (UINT)ESHS_All)
	{
		for (INT i = EHT_NUM - 1; i >= 0; --i)
		{
			for (INT j = 0; j < HISTOGRAM_LEVEL; ++j)
			{
				UINT val = GHistogram[i].Value[j];

				FVector2D startPt(C_DrawOrigX + j, drawY);
				FVector2D endPt(C_DrawOrigX + j, drawY - val / heightR);

				DrawLine2D(Canvas, startPt, endPt, hisClrsComposed[i]);
			}
		}

		drawY += C_DrawSizeHeight + 16;
	}

	if(GShowHistogramStyle == (UINT)ESHS_Separeted || GShowHistogramStyle == (UINT)ESHS_All)
	{
		for (INT i = 0; i < EHT_NUM; ++i)
		{
			for (INT j = 0; j < HISTOGRAM_LEVEL; ++j)
			{
				UINT val = GHistogram[i].Value[j];

				FVector2D startPt(C_DrawOrigX + j, drawY);
				FVector2D endPt(C_DrawOrigX + j, drawY - val / heightR);

				DrawLine2D(Canvas, startPt, endPt, hisClrs[i]);
			}

			drawY += C_DrawSizeHeight + 16;
		}
	}
}

#endif
