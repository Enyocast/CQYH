class SeqAct_ResetBenchmarkFPSCalc extends SequenceAction
	native;

event Activated()
{	
}


cpptext
{
	virtual void Activated();
}


DefaultProperties
{
	ObjName="Reset Benchmark FPS Calc"
	ObjCategory="MMO Benchmark"

	InputLinks.Empty
	InputLinks(0)=(LinkDesc="In")

	OutputLinks.Empty
	OutputLinks(0)=(LinkDesc="Out")

	VariableLinks.Empty
}

