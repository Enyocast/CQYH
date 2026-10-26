#include "stdafx.h"
#include "weight_rand.h"
#include "math_ex.h"

CWeightRand::CWeightRand()
{
    m_nTotalWeight = 0;
}

CWeightRand::~CWeightRand()
{

}

BOOL CWeightRand::Add(INT32 nID, INT32 nWeight)
{
    LOG_PROCESS_ERROR(m_nTotalWeight + nWeight < MAX_WEIGHT);

    for (INT32 nIndex = 0; nIndex < nWeight; nIndex++)
    {
        m_nRandTable[m_nTotalWeight + nIndex] = nID;
    }

	m_nTotalWeight += nWeight;

    return TRUE;
Exit0:
    return FALSE;
}

INT32 CWeightRand::Rand(void) const
{
    if (m_nTotalWeight > 0)
        return m_nRandTable[g_Random(m_nTotalWeight)];
    else
        return 0;
}

INT32 CWeightRand::GetTotalWeight(void) const 
{
	return m_nTotalWeight;
}
