#ifndef __MMO_TEST_CASE__
#define __MMO_TEST_CASE__

#ifdef _DEBUG

class ITestCase
{
public:

	virtual bool Run() = 0;
	virtual const FString& GetName() const = 0;
};

INT ProcTestCaseExcept( LPEXCEPTION_POINTERS ExceptionInfo, ITestCase* testCase );



void TestCaseLoader(ITestCase* testCase);




#define M_TEST_CASE(className) {className className##Inst; className##Inst.SetName(TEXT(#className)); TestCaseLoader(&className##Inst);}

class AbstractTestCase : public ITestCase
{
protected:
	FString _name;

public:

	AbstractTestCase();
	virtual ~AbstractTestCase();
	virtual const FString& GetName() const;
	void SetName(const FString& name);
};


void RunTestCase();

#endif

#endif
