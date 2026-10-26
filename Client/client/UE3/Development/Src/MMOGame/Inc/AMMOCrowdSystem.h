#ifndef _AMMOCROWDSYSTEM_H_
#define _AMMOCROWDSYSTEM_H_

virtual void PostLoad();

template <class T, class conT>
void TagNeighbors(const T& entity, conT& ContainerOfEntities, double radius)
{
	//iterate through all entities checking for range
// 	for (typename conT::iterator curEntity = ContainerOfEntities.begin();
// 		curEntity != ContainerOfEntities.end();
// 		++curEntity)

	for(INT i = 0; i < ContainerOfEntities.Num(); ++i)
	{
		T curEntity = ContainerOfEntities(i);
		if(curEntity)
		{
			//first clear any current tag
			curEntity->UnTag();

			FVector to = curEntity->GetLocation() - entity->GetLocation();

			//the bounding radius of the other is taken into account by adding it 
			//to the range
			double range = radius + curEntity->GetBRadius();

			//if entity within range, tag for further consideration. (working in
			//distance-squared space to avoid sqrts)
			if ( (curEntity != entity) && (to.SizeSquared() < range * range))
			{
				curEntity->Tag();
			}
		}

	}//next entity
}

void  TagVehiclesWithinViewRange(UMMOCrowdInstance* inst, FLOAT range)
{
	TagNeighbors(inst, CrowdInstanceData, range);
}

virtual void TickSpecial( FLOAT DeltaSeconds );
virtual void PostEditChangeProperty( struct FPropertyChangedEvent& PropertyChangedEvent);

class UMMOCrowdInstance* GetInstanceByID(INT instId);

#endif