/** 
  * @note This file is part of Air UE3 integration
  * @date 2012-03-05
  * @copyright Allegorithmic. All rights reserved. 
  */

#ifndef ATC_API_CONF_H
#define ATC_API_CONF_H

#if USE_ATC_API==1
	#define ATC_API_CONV __declspec(dllimport)
#else
	#define ATC_API_CONV __declspec(dllexport)
#endif

#endif // ATC_API_CONF_H
