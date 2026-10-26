#include "..\stdafx.h"


IMPLEMENT_CLASS(USeqAct_ResetBenchmarkFPSCalc)
IMPLEMENT_CLASS(USeqAct_CheckBenchmarkFlags)

void USeqAct_ResetBenchmarkFPSCalc::Activated()
{
	ResetBenchMarkFPS();
	Super::Activated();
}

void USeqAct_CheckBenchmarkFlags::Activated()
{	
	debugf(TEXT("----CheckBenchmarkFlags::Activated GIsMMOBenchmarking:%d GLoopMMOBenchmark:%d GQuitMMOBenchmarkOnComplete:%d"),
		GIsMMOBenchmarking, GLoopMMOBenchmark, GQuitMMOBenchmarkOnComplete);

	if(GIsMMOBenchmarking)
	{
		if(GLoopMMOBenchmark)
		{
			MMO::ActiveKismetRemoteEvent(TEXT("LoopMMOBenchmark"));
		}

		if(GQuitMMOBenchmarkOnComplete)
		{
			MMO::ActiveKismetRemoteEvent(TEXT("QuitMMOBenchmarkOnComplete"));
		}
	}
	Super::Activated();
}

