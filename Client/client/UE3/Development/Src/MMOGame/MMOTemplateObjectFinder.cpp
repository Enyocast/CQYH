#include "stdafx.h"
#include "MMOTemplateObjectFinder.h"
#include "MMOFacade.h"
#include "DoodadManager.h"
#include "MMODropManager.h"
#include "MmoSkillManager.h"

UMMOAbility* TemplateObjectFinder_Ability::FindTemplateObject( INT templatID )
{
	if(templatID == 0)
	{
		return NULL;
	}

	return MMOSkillManager::getSingleton().FindAbilityTemplate(templatID);
}


UDoodad* TemplateObjectFinder_Doodad::FindTemplateObject( INT templatID )
{
	if(templatID == 0)
	{
		return NULL;
	}
	return DoodadManager::getSingleton().FindDoodadTemplate(templatID);
}

UItem* TemplateObjectFinder_Item::FindTemplateObject( INT templatID )
{
	if(templatID == 0)
	{
		return NULL;
	}

	return MMOFacade::getSingleton().FindItemTemplate(templatID);
}

// UDropGroup* TemplateObjectFinder_DropGroup::FindTemplateObject( INT templatID )
// {
// 	if(templatID == 0)
// 	{
// 		return NULL;
// 	}
// 
// 	return (UDropGroup*)MMODropGroupDataManager::getSingleton().FindData(templatID);
// }


UNPCTemplate* TemplateObjectFinder_NPCTemplate::FindTemplateObject( INT templatID )
{
	return MMOFacade::getSingleton().FindNPCTemplate(templatID);
}
