#ifndef _IDIALOGOPTIONACTION_H_
#define _IDIALOGOPTIONACTION_H_

//------------------------------------------------------------------------
// IDialogOptionAction
//------------------------------------------------------------------------
class IDialogOptionAction
{
public:

	//virtual FString GetKeyword() const = 0;
	virtual FString GetDisplayText() const = 0;
	virtual void Parse(const FString& DisplayText, struct ParseContext* ctx,const FString* pParameters) = 0;
	virtual FString GetTypeName() const = 0;
	virtual void Execute() = 0;
};


#endif