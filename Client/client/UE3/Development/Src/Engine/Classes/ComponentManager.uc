/*
 * Component Manager
 *  manage the components that not managed by the engine
 *  
 *  fangruyi@snda.com
 * 
 */
class ComponentManager extends Actor
	native;


// WindPointSource components
var array<WindPointSourceComponent> PoolWindPointSource;
var array<WindPointSourceComponent> ActiveWindPointSources;


native final function WindPointSourceComponent GetPooledWindPointSourceComponent(optional WindPointSourceComponent Template);

native final function ReturnToPool(ActorComponent InComponent);








defaultproperties
{
}
