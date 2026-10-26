#ifndef _FUSION_H_
#define _FUSION_H_

#ifdef FUSION_LIB_EXPORT
    #define FUSION_API  extern
#else  
    #ifdef FUSION_DLL_EXPORT
        #define FUSION_API __declspec(dllexport)
    #else
        #define FUSION_API __declspec(dllimport)
    #endif  // FUSION_DLL_EXPORT
#endif  // FUSION_LIB_EXPORT


#endif // _FUSION_H_