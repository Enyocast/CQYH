/** @file callbacks.h
	@brief Substance callbacks signatures and related defines
	@author Christophe Soum - Allegorithmic (christophe.soum@allegorithmic.com)
	@note This file is part of the Substance cooker headers
	@date 20090212
	@copyright Allegorithmic. All rights reserved.

	Defines callback function signatures used by handle and context structures.
*/

#ifndef _SUBSTANCE_COOKER_CALLBACKS_H
#define _SUBSTANCE_COOKER_CALLBACKS_H

/** Handle structure and related functions definitions pre-declaration */
struct SubstanceCookerHandle_;

/** Platform dependent definitions */
#include "platformdep.h"


/** @brief Callback types enumeration

	This enumeration is used to name callbacks in the Substance cooker context
	structure.*/
typedef enum
{
	Substance_Cooker_Callback_Progress,
	Substance_Cooker_Callback_Error,
	Substance_Cooker_Callback_MemoryDependency,
	/* etc. */

	Substance_Cooker_Callback_Internal_Count

} SubstanceCookerCallbackEnum;


/** @brief Steps (progression) enumeration

	This enumeration is used by the cooker to returns progression.
	Ordered. */
typedef enum
{
	Substance_Cooker_Step_Loading,
	Substance_Cooker_Step_Init,
	Substance_Cooker_Step_FrontEnd,
	Substance_Cooker_Step_Flattening,
	Substance_Cooker_Step_BackEnd,
	Substance_Cooker_Step_Writing,

	Substance_Cooker_Step_Internal_Count

} SubstanceCookerStepEnum;



/* Begin of the EXTERNC block (if necessary) */
#ifdef __cplusplus
SUBSTANCE_EXTERNC {
#endif /* ifdef __cplusplus */


/** @typedef void SubstanceCookerCallbackProgress
	@brief Type of the progress callback function

	@code void (*)(
		SubstanceCookerHandle* handle,
		SubstanceCookerStepEnum step) @endcode

	The 'handle' parameter is the Substance handle that calls this callback
	func.<BR>
	The 'step' parameter contains the current progression. */
typedef void (SUBSTANCE_CALLBACK *SubstanceCookerCallbackProgress)(
	struct SubstanceCookerHandle_ *handle,
	SubstanceCookerStepEnum step);

	
/** @typedef void SubstanceCookerCallbackError
	@brief Type of the error message callback function

	@code void (*)(
		SubstanceCookerHandle* handle,
		unsigned int severity,
		const char* msg) @endcode

	The 'handle' parameter is the Substance handle that calls this callback
	func.<BR>
	The 'severity' parameter describe the error severity 
	(0: warning, 1: error, 2: critical error).<BR>
	The 'msg' parameter contains the error message string. */
typedef void (SUBSTANCE_CALLBACK *SubstanceCookerCallbackError)(
	struct SubstanceCookerHandle_ *handle,
	unsigned int severity,
	const char* msg);
	
	
/** @typedef void SubstanceCookerCallbackMemoryDependency
	@brief Type of the dependency required callback function

	@code void (*)(
		SubstanceCookerHandle* handle,
		const wchar_t* packageFilepath) @endcode
		
	This callback is called each time the cooker requires an new package
	dependency used by a package pushed with 
	substanceCookerHandlePushPackageMemory function.

	The 'handle' parameter is the Substance handle that calls this callback
	function.<BR>
	The 'packageFilepath' parameter contains the filepath of the required
	package. It's an UNICODE null-terminated string.
	Must return the required package content (ASCII null terminated string) or 
	NULL if not found (interrupts the cooking process). */
typedef unsigned char* (SUBSTANCE_CALLBACK *SubstanceCookerCallbackMemoryDependency)(
	struct SubstanceCookerHandle_* handle,
	const wchar_t* packageFilepath);
	
	
#ifdef __cplusplus
};
/* End of the EXTERNC block (if necessary) */
#endif /* ifdef __cplusplus */

#endif /* ifndef _SUBSTANCE_COOKER_CALLBACKS_H */
