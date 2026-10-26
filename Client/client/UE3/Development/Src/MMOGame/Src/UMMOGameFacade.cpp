//#include "MMOGameClasses.h"

static UMMOGameFacade* g_Singleton = 0;

UMMOGameFacade::UMMOGameFacade()
{
	check(g_Singleton == 0);
	g_Singleton = this;
}
//------------------------------------------------------------------------
UMMOGameFacade* UMMOGameFacade::GetSingleton()
{
	check(g_Singleton != 0);
	return g_Singleton;
}
//------------------------------------------------------------------------
UMMOGameFacade* UMMOGameFacade::GetGameFacade()
{
	check(g_Singleton != 0);
	return g_Singleton;
}