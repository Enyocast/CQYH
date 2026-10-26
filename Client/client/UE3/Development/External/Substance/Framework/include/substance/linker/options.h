/** @file options.h
	@brief Substance linker options definitions. 
	@author Christophe Soum - Allegorithmic (christophe.soum@allegorithmic.com)
	@note This file is part of the Substance linker headers
	@date 20100408
	@copyright Allegorithmic. All rights reserved. 
	
	Returned by all Substance linker functions. */

#ifndef _SUBSTANCE_LINKER_OPTIONS_H
#define _SUBSTANCE_LINKER_OPTIONS_H


/** Basic type defines */
#include <stddef.h>


/** @brief Substance linker error codes enumeration */
typedef enum
{
	Substance_Linker_Option_INVALID      = 0,  /**< Unknown option, do not use */
	
	/** @brief Linking optimizations level: unsigned integer option
		Combination of SubstanceLinkerOptionOpt flags. Default is 
		Substance_Linker_Opt_Full. */
	Substance_Linker_Option_Optimizations,
	
	/** @brief Maximum size of compositing nodes: unsigned integer option
		Maximum width and height of all compositing nodes and outputs
		generated during link.
		The default value is dependant to the targeted engine. */
	Substance_Linker_Option_SizeLimit,
	
	/** @brief Global tweaks handling: unsigned integer option
		Combination of SubstanceLinkerOptionGlobal flags. Default is 
		Substance_Linker_Global_FuseAll. */
	Substance_Linker_Option_GlobalTweaks,
	
	/* etc. */
	
	Substance_Linker_Option_Internal_Count
	
} SubstanceLinkerOptionEnum;


/** @brief Linking optimizations flags 
	Used by Substance_Linker_Option_Optimizations option. */
typedef enum
{
	/** @brief No optimizations, fastest linking process */
	Substance_Linker_Opt_None                  = 0x0,   
	
	/** @brief Combination of all available optimizations
		Best performance and memory footprint, slowest linking process */
	Substance_Linker_Opt_Full                  = 0xFF,
	
	/** @brief Merge data redundancies (reduce binary size)
		Only usefull when several assemblies are linked together.
		Included in Substance_Linker_Opt_Full. */
	Substance_Linker_Opt_MergeData             = 0x01,
	
	/** @brief Merge graph redundancies inter assemblies (best performance)
		Only usefull when several assemblies are linked together.
		Included in Substance_Linker_Opt_Full. */
	Substance_Linker_Opt_MergeGraph            = 0x02
	
} SubstanceLinkerOptionOpt;


/** @brief Linking global tweaks handling flags
	Used by Substance_Linker_Option_GlobalTweaks option. */
typedef enum
{
	/** @brief 'Time' and 'Normal Format' tweaks are not implicitely fused 
		It cause UID collisions if assemblies w/ 'Time' and/or 'Normal Format' 
		defined are pushed twice or more. */
	Substance_Linker_Global_FuseNone           = 0x0,
	
	/** @brief 'Time' and 'Normal Format' global tweaks are implicitely fused */
	Substance_Linker_Global_FuseAll            = 0xFF,   
	
	/** @brief 'Time' ($time) global tweak is implicitely fused */
	Substance_Linker_Global_FuseTime           = 0x01,
	
	/** @brief 'Normal Format' ($normalformat) tweak is implicitely fused */
	Substance_Linker_Global_FuseNormalFormat   = 0x02
	
} SubstanceLinkerOptionGlobal;


/** @brief Union used to set option (substanceLinkerContextSetOption) */
typedef union 
{
	int integer;                /**< For integer type options */
	unsigned int uinteger;      /**< For unsigned integer type options */
	float fp;                   /**< For floating point type options */
	const wchar_t* ustring;     /**< For UNICODE string type options */

} SubstanceLinkerOptionValue;

#endif /* ifndef _SUBSTANCE_LINKER_OPTIONS_H */
