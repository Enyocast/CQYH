#include "stdafx.h"
#include "aura.h"

CAura::CAura(void)
{
	m_Data.m_nID = 0;
	memset(m_Data.m_nAttrTable, 0, sizeof(m_Data.m_nAttrTable));
}

CAura::~CAura(void)
{

}

void CAura::SetAttr(INT32 eAttrType, INT32 nVal)
{
	LOG_PROCESS_ERROR(eAttrType > aatInvalid && eAttrType < aatTotal);

	m_Data.m_nAttrTable[eAttrType] = nVal;
Exit0:
	return;
}

CAura* CAura::MakeCopy(void)
{
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CAuraTemplate::CAuraTemplate(void)
{

}

void CAuraTemplate::SetAttr(INT32 eAttrType, INT32 nVal)
{

}

CAura* CAuraTemplate::MakeCopy(void)
{
	CAuraEntryCopy* cp = new CAuraEntryCopy();
	CopyTo(cp);

	return cp;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CAuraEntryCopy::CAuraEntryCopy(void)
{

}

CAura* CAuraEntryCopy::MakeCopy(void)
{
	return this;
}
