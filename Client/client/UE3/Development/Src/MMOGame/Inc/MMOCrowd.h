#ifndef _MMOCROWD_H_
#define _MMOCROWD_H_

//the radius of the constraining circle for the wander behavior
const double WanderRad    = 1.2;
//distance the wander circle is projected in front of the agent
const double WanderDist   = 2.0;
//the maximum amount of displacement along the circle each frame
const double WanderJitterPerSec = 80.0;

//used in path following
const double WaypointSeekDist   = 20;                                          

inline FLOAT RandFloat()      { return (FLOAT)appRand() / (RAND_MAX + 1.0); }
inline FLOAT RandomClamped()    {return RandFloat() - RandFloat();}

#endif