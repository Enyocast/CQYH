#ifndef _ENUM_STRING_H_
#define _ENUM_STRING_H_


#include <string>
#include "lua_script.h"



class CEnumString
{
public:
	CEnumString();
	~CEnumString();

	BOOL Init(void);
	BOOL UnInit(void);

	static CEnumString& GetInstance(void);

	std::string GetEnumString(const char *pcszEnumName, INT32 nEnumKeyValue);

private:
	static CEnumString         ms_Instance;

	CLuaScript                 m_LuaScript;
};



#endif  // _ENUM_STRING_H_