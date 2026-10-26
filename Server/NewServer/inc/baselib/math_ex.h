#ifndef _MATH_EX_H_
#define _MATH_EX_H_

#include <math.h>

#define MAX_SQUARE				(65536)
#define MAX_CLIENT_DIRECTION_COUNT  (65536)
#define MAX_DIRECTION_COUNT		(1024 * 8)
#define MAX_DIRECTION_DISTANCE	(1024)
#define MAX_RANK_SCORE_VALUE	(3200)
#define LUCK_LIMIT	(9)

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

struct MATH_TABLE
{
    INT32   nDirectionTable[MAX_DIRECTION_DISTANCE * 2][MAX_DIRECTION_DISTANCE * 2];
    INT32   nSinTable[MAX_DIRECTION_COUNT];
    INT32   nCosTable[MAX_DIRECTION_COUNT];
    INT32   nSinSquareTable[MAX_DIRECTION_COUNT / 4];
    UINT16  wSqrtTable[MAX_SQUARE];
    INT32	nAdjacentX[DT_DIRECTION_8_COUNT];
    INT32	nAdjacentY[DT_DIRECTION_8_COUNT];
    INT32	nAdjList[DT_DIRECTION_8_COUNT][6];
};

extern MATH_TABLE  g_MathTable;

#define PI		(3.1415927)

inline INT64 g_GetDistance2D(INT64 llSrcX, INT64 llSrcY, INT64 llDestX, INT64 llDestY)
{
    return (llSrcX - llDestX) * (llSrcX - llDestX) + (llSrcY - llDestY) * (llSrcY - llDestY);
}

inline INT64 g_GetDistance3D(INT64 llSrcX, INT64 llSrcY, INT64 llSrcZ, INT64 llDestX, INT64 llDestY, INT64 llDestZ)
{
    return (llSrcX - llDestX) * (llSrcX - llDestX) + (llSrcY - llDestY) * (llSrcY - llDestY) +
        (llSrcZ - llDestZ) * (llSrcZ - llDestZ);
}

extern INT32 g_nAdjacentX[DT_DIRECTION_8_COUNT];
extern INT32 g_nAdjacentY[DT_DIRECTION_8_COUNT];
extern INT32 g_nAdjList[DT_DIRECTION_8_COUNT][6];

inline INT32 g_GetDirection(INT64 llSrcX, INT64 llSrcY, INT64 llDestX, INT64 llDestY)
{
    INT64 llDistanceX = llDestX - llSrcX;
    INT64 llDistanceY = llDestY - llSrcY;

    while (llDistanceX >= MAX_DIRECTION_DISTANCE ||
        llDistanceX < -MAX_DIRECTION_DISTANCE ||
        llDistanceY >= MAX_DIRECTION_DISTANCE ||
        llDistanceY < -MAX_DIRECTION_DISTANCE)
    {
        llDistanceX /= 2;
        llDistanceY /= 2;
    }

    return g_MathTable.nDirectionTable[llDistanceX + MAX_DIRECTION_DISTANCE][llDistanceY + MAX_DIRECTION_DISTANCE];
}

inline INT32 NormalizeDirection(INT32 nDirection)
{
    return (nDirection + MAX_DIRECTION_COUNT) % MAX_DIRECTION_COUNT;
}

inline INT32 ConvertToDir8(INT32 nDirection)
{
    return ((nDirection + (MAX_DIRECTION_COUNT / 16)) / (MAX_DIRECTION_COUNT / 8)) % 8;
}

inline INT32 NormalizeDirection8(INT32 nDirection)
{
    return (nDirection + 8) % 8;
}

template <typename T>
inline T g_Abs(T Value)
{
    return Value < 0 ? -Value : Value;
}

inline INT32 OffsetDirection8(INT32 nDirection1, INT32 nDirection2)
{
    INT32 nDirection8 = NormalizeDirection8(g_Abs(nDirection1 - nDirection2));

    return nDirection8 < 4 ? nDirection8 : 8 - nDirection8;
}

inline INT32 g_GetMirDirection8(INT32 nSrcGridX, INT32 nSrcGridY, INT32 nDstGridX, INT32 nDstGridY)
{
    INT32 nFlagX = 0, nFlagY = 0;

    if (nSrcGridX < nDstGridX)
        nFlagX = 1;
    else if (nSrcGridX == nDstGridX)
        nFlagX = 0;
    else
        nFlagX = -1;

    if (g_Abs(nSrcGridY - nDstGridY) > 2 && (nDstGridX - 1) <= nSrcGridX && (nDstGridX + 1) >= nSrcGridX)
        nFlagX = 0;

    if (nSrcGridY < nDstGridY)
        nFlagY = 1;
    else if (nSrcGridY == nDstGridY)
        nFlagY = 0;
    else
        nFlagY = -1;

    if (g_Abs(nSrcGridX - nDstGridX) > 2 && (nDstGridY - 1) < nSrcGridY && (nDstGridY + 1) >= nSrcGridY)
        nFlagY = 0;

    if (nFlagX == 0)
    {
        if (nFlagY >= 0)
            return DT_SOUTH;
        else
            return DT_NORTH;
    }
    else if (nFlagY == 0)
    {
        if (nFlagX >= 0)
            return DT_EAST;
        else
            return DT_WEST;
    }
    else
    {
        if (nFlagX >= 0)
        {
            if (nFlagY >= 0)
                return DT_SOUTH_EAST;
            else
                return DT_NORTH_EAST;
        }
        else
        {
            if (nFlagY >= 0)
                return DT_SOUTH_WEST;
            else
                return DT_NORTH_WEST;
        }
    }

    return DT_EAST;
}


#define SIN_COS_NUMBER	(16384)

inline INT64 g_Sin(INT32 nDirection)
{
    return (INT64)g_MathTable.nSinTable[nDirection % MAX_DIRECTION_COUNT];
}

inline INT64 g_Cos(INT32 nDirection)
{
    return (INT64)g_MathTable.nCosTable[nDirection % MAX_DIRECTION_COUNT];
}

INT32 g_GetAngle(INT32 nSinSquare);

inline UINT16 g_Sqrt(UINT16 wNumber)
{
    return g_MathTable.wSqrtTable[wNumber];
}

class CFlagBits
{
public:
    CFlagBits(void)
    {
        m_dwFlag = 0;
    }

    inline BOOL CheckFlag(UINT32 eBit);
    inline void SetFlag(UINT32 eBit);
    inline void ClearFlag(UINT32 eBit);
    inline void ResetFlag(void);
    inline BOOL FlagIncludeBits(UINT32 dwMask);
    inline BOOL FlagNotIncludeBits(UINT32 dwMask);
    inline UINT32 GetFlag(void);

private:
    UINT32 m_dwFlag;
};

inline BOOL CFlagBits::CheckFlag(UINT32 eBit)
{
    return (m_dwFlag & (1 << eBit)) > 0;
}

inline void CFlagBits::SetFlag(UINT32 eBit)
{
    m_dwFlag |= (1 << eBit);
}

inline void CFlagBits::ClearFlag(UINT32 eBit)
{
    m_dwFlag &= ~(1 << eBit);
}

inline void CFlagBits::ResetFlag(void)
{
    m_dwFlag = 0;
}

inline BOOL CFlagBits::FlagIncludeBits(UINT32 dwMask)
{
    return (m_dwFlag > 0 && (m_dwFlag & dwMask) == dwMask) || (m_dwFlag == 0 && dwMask == 0);
}

inline BOOL CFlagBits::FlagNotIncludeBits(UINT32 dwMask)
{
    return (m_dwFlag & dwMask) == 0;
}

inline UINT32 CFlagBits::GetFlag(void)
{
    return m_dwFlag;
}

extern UINT32 g_dwRandSeed;
inline UINT32 g_Random(UINT32 dwRange)
{
    PROCESS_ERROR(dwRange > 0);

    g_dwRandSeed = (UINT32)(g_dwRandSeed * 0x08088405) + 1;

    return (UINT32)((g_dwRandSeed * (UINT64)dwRange) >> 32);
Exit0:
    return 0;
}

inline UINT32 g_Random(UINT32 dwMin, UINT32 dwMax)
{
    PROCESS_ERROR(dwMin < dwMax);

    return dwMin + g_Random(dwMax - dwMin);
Exit0:
    return dwMin;
}

inline UINT32 g_RandomEx(INT32 nCount, INT32 nRate)
{
    UINT32 dwResult = 0;
    for (INT32 nIndex = 0; nIndex < nCount; nIndex++)
    {
        if (g_Random(nRate) == 0)
            dwResult++;
        else
            break;
    }
    return dwResult;
}

template <typename T>
inline T g_Max(const T Left, const T Right)
{
    return Left >= Right ? Left : Right;
}

template <typename T>
inline T g_Min(const T& Left, const T& Right)
{
    return Left < Right ? Left : Right;
}

inline BOOL g_PointInCube(INT32 px, INT32 py, INT32 pz, INT32 ltx, INT32 lty, INT32 ltz, INT32 rbx, INT32 rby, INT32 rbz)
{
    if (px >= ltx && px <= rbx && py >= lty && py <= rby && pz >= ltz && pz <= rbz)
        return TRUE;
    return FALSE;
}

// 四舍六入五成双
inline INT32 round_div(INT32 dividend, INT32 divisor)
{
    INT32 quotient = dividend / divisor;
    INT32 remainder = dividend % divisor;
    if (remainder * 2 < divisor)
        return quotient;
    else if (remainder * 2 > divisor)
        return quotient + 1;
    else
        return (quotient + 1) & (~1);
}

inline INT32 LuckGo(INT32 nInput, INT32 nLuck, INT32 nParamE)
{
    INT32 nOutput = nInput;
    INT32 nLuckRand1 = g_Random(0, LUCK_LIMIT + 1 - g_Min(nLuck, LUCK_LIMIT));
    INT32 nLuckRand2 = g_Random(0, LUCK_LIMIT + 1 - g_Max(-nLuck, 0));

    if (nLuck == 0)
    {
        nOutput += g_Random(0, nParamE + 1);
    }
    else if (nLuck > 0)
    {
        if (nLuckRand1 == 0)
            nOutput += g_Random(0, nParamE + 1);
        else
            nOutput += nParamE;
    }
    else
    {
        if (nLuckRand2 != 0)
            nOutput += g_Random(0, nParamE + 1);
    }

    return nOutput;
}

#define SHIFTPOS (47)

inline BOOL SimpleEncrypt(char*& szBuff, INT32 nBuffLen)
{
    for (INT32 i = 0; i < nBuffLen; ++i)
    {
        LOG_PROCESS_ERROR(szBuff[i] >= ' ' && szBuff[i] <= '~'); //[32, 126]
        szBuff[i] = (szBuff[i] - ' ' + SHIFTPOS) % ('~' - ' ' + 1) + ' ';
    }
    return TRUE;
Exit0:
    return FALSE;
}

inline BOOL SimpleDecrypt(char*& szBuff, INT32 nBuffLen)
{
    for (INT32 i = 0; i < nBuffLen; ++i)
    {
        LOG_PROCESS_ERROR(szBuff[i] >= ' ' && szBuff[i] <= '~'); //[32, 126]
        szBuff[i] = (szBuff[i] - ' ' - SHIFTPOS) % ('~' - ' ' + 1) + ' ';
    }
    return TRUE;
Exit0:
    return FALSE;
}

BOOL InitMathEx(const char* pcData);
BOOL UnInitMathEx(void);

#endif	// _MATH_EX_H_
