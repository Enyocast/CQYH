#include "stdafx.h"
#include "math_ex.h"

#include <math.h>
#include <time.h>

#if defined(__linux__)
    #include <fpu_control.h>
#endif

INT32 g_nAdjacentX[DT_DIRECTION_8_COUNT] = { 0 };
INT32 g_nAdjacentY[DT_DIRECTION_8_COUNT] = { 0 };
INT32 g_nAdjList[DT_DIRECTION_8_COUNT][6] = { 0 };

MATH_TABLE  g_MathTable;

UINT32 g_dwRandSeed = 0;

BOOL InitMathEx(const char* pcData)
{
#if defined(__linux__)
    fpu_control_t cw; 
    _FPU_GETCW(cw); 
    cw &= ~_FPU_EXTENDED; 
    cw |= _FPU_DOUBLE; 
    _FPU_SETCW(cw); 
#endif  // __linux__

	g_dwRandSeed = time(NULL);

	if (pcData)
	{
		memcpy(&g_MathTable, pcData, sizeof(g_MathTable));
	}

    for (INT32 nY = -MAX_DIRECTION_DISTANCE; nY < MAX_DIRECTION_DISTANCE; nY++)
    {
        for (INT32 nX = -MAX_DIRECTION_DISTANCE; nX < MAX_DIRECTION_DISTANCE; nX++)
        {
            if (nX == 0 && nY == 0)
                g_MathTable.nDirectionTable[nX + MAX_DIRECTION_DISTANCE][nY + MAX_DIRECTION_DISTANCE] = 0;
            else if (nX >= 0 && nY >= 0)
            {
                g_MathTable.nDirectionTable[nX + MAX_DIRECTION_DISTANCE][nY + MAX_DIRECTION_DISTANCE] = 
                    (INT32)floor(MAX_DIRECTION_COUNT * atan((double)nY / nX) / (PI * 2) + 0.5f);
            }
            else if (nX < 0 && nY > 0)
            {
                g_MathTable.nDirectionTable[nX + MAX_DIRECTION_DISTANCE][nY + MAX_DIRECTION_DISTANCE] = 
                    (INT32)floor(MAX_DIRECTION_COUNT * atan((double)nY / nX) / (PI * 2) + MAX_DIRECTION_COUNT / 2 + 0.5f);
            }
            else if (nX < 0 && nY <= 0)
            {
                g_MathTable.nDirectionTable[nX + MAX_DIRECTION_DISTANCE][nY + MAX_DIRECTION_DISTANCE] = 
                    (INT32)floor(MAX_DIRECTION_COUNT * atan((double)nY / nX) / (PI * 2) + MAX_DIRECTION_COUNT / 2 + 0.5f);
            }
            else if (nX >= 0 && nY < 0)
            {
                g_MathTable.nDirectionTable[nX + MAX_DIRECTION_DISTANCE][nY + MAX_DIRECTION_DISTANCE] = 
                    (INT32)floor(MAX_DIRECTION_COUNT * atan((double)nY / nX) / (PI * 2) + MAX_DIRECTION_COUNT + 0.5f);
            }
        }
    }

	if (pcData)
	{
		memcpy((void*)g_nAdjacentX, g_MathTable.nAdjacentX, sizeof(g_nAdjacentX));
		memcpy((void*)g_nAdjacentY, g_MathTable.nAdjacentY, sizeof(g_nAdjacentY));
		memcpy((void*)g_nAdjList, g_MathTable.nAdjList, sizeof(g_nAdjList));
	}

	return TRUE;
}

BOOL UnInitMathEx(void)
{
	return TRUE;
}

INT32 s_SearchTable(INT32 v, INT32* head, INT32* p, INT32 count)
{
	if(count == 0)
		return -1;

	if(v >= *p && v < *(p+1))
	{
		if(v - *p <= *(p+1) - v)
			return (INT32)(p - head);
		else if(v - *p > *(p+1) - v)
			return (INT32)(p - head + 1);
	}

	if(v < *(p+count/2))
		return s_SearchTable(v, head, p, count/2);
	else
		return s_SearchTable(v, head, p + count/2, count/2);

	return -1;
}

INT32 g_GetAngle(INT32 nSinSquare)
{
	if (nSinSquare < g_MathTable.nSinSquareTable[0] || 
        nSinSquare > g_MathTable.nSinSquareTable[sizeof(g_MathTable.nSinSquareTable)/sizeof(g_MathTable.nSinSquareTable[0]) - 1])
		return -1;

	return s_SearchTable(nSinSquare, g_MathTable.nSinSquareTable, g_MathTable.nSinSquareTable, sizeof(g_MathTable.nSinSquareTable)/sizeof(g_MathTable.nSinSquareTable[0]));
}
