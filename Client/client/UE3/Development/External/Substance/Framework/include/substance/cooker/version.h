/** @file version.h
	@brief Substance cooker current version accessor function
	@author Christophe Soum - Allegorithmic (christophe.soum@allegorithmic.com)
	@note This file is part of the Substance cooker headers
	@date 20090212
	@copyright Allegorithmic. All rights reserved.

	Defines the SubstanceCookerVersion structure. Filled using the
	substanceCookerGetCurrentVersion function.
*/

#ifndef _SUBSTANCE_COOKER_VERSION_H
#define _SUBSTANCE_COOKER_VERSION_H


/** Platform dependent definitions */
#include "platformdep.h"

/** @brief Version of the header of the Substance Cooker API */
#define SUBSTANCE_COOKER_API_VERSION 0x00020000


/** @brief Substance cooker current version description

	Filled using the substanceCookerGetCurrentVersion function declared 
	just below. */
typedef struct
{
	/** @brief Current cooker version: major */
	unsigned int versionMajor;
	
	/** @brief Current cooker version: minor */
	unsigned int versionMinor;
	
	/** @brief Current cooker version: patch */
	unsigned int versionPatch;
	
	/** @brief Current cooker stage (Release, alpha, beta, RC, etc.) */
	const char* currentStage;
	
	/** @brief Substance cooker build date (Mmm dd yyyy) */
	const char* buildDate;
	
	/** @brief Substance cooker sources revision */
	unsigned int sourcesRevision;

} SubstanceCookerVersion;


/** @brief Get the current substance cooker version
	@param[out] version Pointer to the version struct to fill. */
SUBSTANCE_EXPORT void substanceCookerGetCurrentVersion(
	SubstanceCookerVersion* version);


#endif /* ifndef _SUBSTANCE_COOKER_VERSION_H */
