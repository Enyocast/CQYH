#ifndef _WEIGHT_RAND_H_
#define _WEIGHT_RAND_H_

#define MAX_WEIGHT	(256)

class CWeightRand
{
public:
    CWeightRand();
    ~CWeightRand();

    BOOL Add(INT32 nID, INT32 nWeight);
    INT32 Rand(void) const;
	INT32 GetTotalWeight(void) const;

private:
    INT32   m_nRandTable[MAX_WEIGHT];
    INT32   m_nTotalWeight;
};

#endif  // _WEIGHT_RAND_H_