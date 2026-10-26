/** @file options.h
	@brief Substance cooker options definitions. 
	@author Christophe Soum - Allegorithmic (christophe.soum@allegorithmic.com)
	@note This file is part of the Substance cooker headers
	@date 20100412
	@copyright Allegorithmic. All rights reserved. 
	
	Returned by all Substance cooker functions. */

#ifndef _SUBSTANCE_COOKER_OPTIONS_H
#define _SUBSTANCE_COOKER_OPTIONS_H


/** Basic type defines */
#include <stddef.h>


/** @brief Substance cooker error codes enumeration */
typedef enum
{
	Substance_Cooker_Option_INVALID      = 0,  /**< Unknown option, do not use */
	
	/** @brief Cooking optimizations level: unsigned integer option
		Combination of SubstanceCookerOptionOpt flags. Default is 
		Substance_Cooker_Opt_Full. */
	Substance_Cooker_Option_Optimizations,
	
	/** @brief Maximum size of compositing nodes: unsigned integer option
		Maximum width and height of all compositing nodes and outputs
		generated during cook.
		The default value is fixed at linking time. */
	Substance_Cooker_Option_SizeLimit,
	
	/** @brief I/O Desc generation format: unsigned integer option
		One of SubstanceCookerOptionIO enum. Default is 
		Substance_Cooker_IO_Full.

		Controls Input/Output bindings description format (full/linear): see 
		substanceCookerHandleGetIODesc for further information. */
	Substance_Cooker_Option_IO,
	
	/** @brief Set graph base inputs as dynamic option: unsigned integer option
		Combination of one or several SubstanceCookerOptionDynamic enums. 
		Default is Substance_Cooker_Dynamic_None.

		Controls if base inputs (Output size, Random seed and Pixel Size) common 
		of all Substance graphs are dynamic or not. When dynamic, they are 
		controlled by tweaks named respectively $outputsize (Integer2: log2 
		width and height), $randomseed (Integer) and $pixelsize (Float2). */
	Substance_Cooker_Option_Dynamic,
	
	/* etc. */
	
	Substance_Cooker_Option_Internal_Use,
	Substance_Cooker_Option_Internal_Count
	
} SubstanceCookerOptionEnum;


/** @brief Cooking optimizations flags 
	Used by Substance_Cooker_Option_Optimizations option. */
typedef enum
{
	/** @brief No optimizations, fastest cooking process */
	Substance_Cooker_Opt_None                  = 0x0,   
	
	/** @brief Combination of all available optimizations
		Best performance and memory footprint, slowest cooking process */
	Substance_Cooker_Opt_Full                  = 0xFF,
	
	/** @brief Merge data redundancies (reduce binary size)
		Included in Substance_Cooker_Opt_Full. */
	Substance_Cooker_Opt_MergeData             = 0x01,
	
	/** @brief Merge graph redundancies inter assemblies (best performance)
		Included in Substance_Cooker_Opt_Full. */
	Substance_Cooker_Opt_MergeGraph            = 0x02,
	
	/** @brief Search for best compute order (memory footprint reduction)
		Included in Substance_Cooker_Opt_Full. */
	Substance_Cooker_Opt_Reordering            = 0x04,
	
	/** @brief Compute assembly CRC
		Not really an optimization, but can be disabled to speed up the cooking
		process.
		Included in Substance_Cooker_Opt_Full. */
	Substance_Cooker_Opt_CRC                   = 0x80,
	
} SubstanceCookerOptionOpt;


/** @brief I/O Desc generation option flags
	Used by Substance_Cooker_Option_IO option.
	See substanceCookerHandleGetIODesc for further information. */
typedef enum
{
	/** @brief Default format: full description sorted by graph (default) */
	Substance_Cooker_IO_Full                  = 0x0,   
	
	/** @brief Linear format: compact description w\ GUI and graph info. */
	Substance_Cooker_IO_Linear                = 0x1,
	
} SubstanceCookerOptionIO;


/** @brief Graph base inputs as dynamic option flags
	Used by Substance_Cooker_Option_Dynamic option. Can be combined. */
typedef enum
{
	/** @brief Default flag: none as dynamic (default) */
	Substance_Cooker_Dynamic_None                  = 0x0,   
	
	/** @brief Dynamic output size 
		$outputsize tweak is added for each cooked graph. */
	Substance_Cooker_Dynamic_OutputSize            = 0x1,

	/** @brief Dynamic random seed
		$randomseed tweak is added for each cooked graph. */
	Substance_Cooker_Dynamic_RandomSeed            = 0x2,

	/** @brief Dynamic pixel size
		$pixelsize tweak is added for each cooked graph. */
	Substance_Cooker_Dynamic_PixelSize             = 0x4,

	/** @brief All dynamics (output size, random seed and pixel size) */
	Substance_Cooker_Dynamic_All            = 0xFF,
	
} SubstanceCookerOptionDynamic;


/** @brief Union used to set option (substanceCookerContextSetOption) */
typedef union 
{
	int integer;                /**< For integer type options */
	unsigned int uinteger;      /**< For unsigned integer type options */
	float fp;                   /**< For floating point type options */
	const wchar_t* ustring;     /**< For UNICODE string type options */

} SubstanceCookerOptionValue;


#endif /* ifndef _SUBSTANCE_COOKER_OPTIONS_H */
