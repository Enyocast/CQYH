#include "EnginePrivate.h"

namespace physx {
namespace apex {
	class NxApexAsset;
	class NxApexActor;
}}

#include "EngineApexFieldSamplerClasses.h"


IMPLEMENT_CLASS(UApexShape);

IMPLEMENT_CLASS(UApexShapeBox);

void* UApexShapeBox::CreateApexShape()
{
	return NULL;
}


IMPLEMENT_CLASS(UApexShapeCapsule);

void* UApexShapeCapsule::CreateApexShape()
{
	return NULL;
}


IMPLEMENT_CLASS(UApexShapeSphere);

void* UApexShapeSphere::CreateApexShape()
{
	return NULL;
}
