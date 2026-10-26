
#include "stdafx.h"
#include "MMOGameClasses.h"

IMPLEMENT_CLASS(AMeshMarker)

void AMeshMarker::Show()
{
	SetHidden(FALSE);
}

void AMeshMarker::Hide()
{
	SetHidden(TRUE);
}