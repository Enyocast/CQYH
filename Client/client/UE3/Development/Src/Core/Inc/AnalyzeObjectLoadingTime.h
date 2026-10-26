#ifndef _ANALYZE_OBJECT_LOADING_TIME_H_
#define _ANALYZE_OBJECT_LOADING_TIME_H_

#include <map>
#include <vector>
using namespace std;


class ObjectLoadingTimeAnalyzer
{
	struct Node
	{
		DOUBLE Time;
		INT Num;
		Node(){Time = 0;Num = 0;}
		Node(DOUBLE InTime, INT InNum){Time = InTime; Num = InNum;}
	};

	map<const UClass*, Node> ClassLoadingTimes;

public:
	void AddObjectLoadingTime(const UClass* InNewObject, DOUBLE InTime)
	{
		map<const UClass*, Node>::iterator pos = ClassLoadingTimes.find(InNewObject);
		if (pos == ClassLoadingTimes.end())
		{
			Node newNode(InTime, 1);
			ClassLoadingTimes.insert(make_pair(InNewObject, newNode));
		}
		else
		{
			pos->second.Time += InTime;
			pos->second.Num++;
		}
	}

	void Clear()
	{
		ClassLoadingTimes.clear();
	}

	void DumpResultToLog()
	{
		debugf(TEXT("Start Dump LoadingTime Result To Log!"));
		for (map<const UClass*, Node>::iterator pos = ClassLoadingTimes.begin(); pos != ClassLoadingTimes.end(); ++pos)
		{
			debugf(TEXT("%s,Loading Time=,%lf,  Num=%d"), *(pos->first->GetName()), pos->second.Time, pos->second.Num);
		}
		debugf(TEXT("End Dump LoadingTime Result To Log!"));
	}
};

#endif