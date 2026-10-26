#include "UnrealEd.h"
#include "EnginePrivate.h"

#include "tinyxml.h"

#include "../../Engine/Inc/EngineClasses.h"
#include "../../Engine/Inc/EngineMeshClasses.h"
#include "../../Engine/Inc/EngineAnimClasses.h"
#include "../../Engine/Inc/EngineAIClasses.h"
#include "../../GameFramework/Inc/GameFrameworkClasses.h"
#include "../../MMOGame/Inc/MMOGameClasses.h"


class ExportArchetypeUtils
{
public:
	static UBOOL ShouldSerializeValue( QWORD PropertyFlags);
	static UBOOL ExportToXML(const TCHAR* Str);
	static void ExportOjbectToXML(UObject* AbilityObj, TiXmlElement* e = NULL);
	static void PropertyToXML(BYTE*Data, UProperty* Property, TiXmlElement* e);
	static void ConvertAbilityData();
	static UBOOL ConvertAbilityComponent(UAbilityComponent* InComponent);
};