#ifndef __MMOTEMPLATEOBJECTFINDER_H__
#define __MMOTEMPLATEOBJECTFINDER_H__

struct TemplateObjectFinder_Ability
{
	static UMMOAbility* FindTemplateObject(INT templatID);
};


struct TemplateObjectFinder_Doodad
{
	static UDoodad* FindTemplateObject(INT templatID);
};

struct TemplateObjectFinder_Item
{
	static UItem* FindTemplateObject(INT templatID);
};

// struct TemplateObjectFinder_DropGroup
// {
// 	static UDropGroup* FindTemplateObject( INT templatID );
// };

struct TemplateObjectFinder_NPCTemplate
{
	static UNPCTemplate* FindTemplateObject(INT templatID);
};

#endif