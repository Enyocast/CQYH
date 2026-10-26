/** @file context.h
	@brief Substance cooker context structure and related functions definitions
	@author Christophe Soum - Allegorithmic (christophe.soum@allegorithmic.com)
	@note This file is part of the Substance cooker headers
	@date 20090212
	@copyright Allegorithmic. All rights reserved.

	Defines the SubstanceContext structure. Initialized from platform specific
	informations. This structure is necessary to create Substance cooker handles.
	The context can be used to fill in cooking options/parameters 
	and function callbacks. 
	
	Summary of functions defined in this file:
	
	Context creation and deletion:
	  - substanceCookerContextInit
	  - substanceCookerContextRelease

	Options setting:
	  - substanceCookerContextSetOption 
	 
	Callback setting:
	  - substanceCookerContextSetCallback
*/

#ifndef _SUBSTANCE_COOKER_CONTEXT_H
#define _SUBSTANCE_COOKER_CONTEXT_H


/** Cooking options definitions */
#include "options.h"

/** Callback signature definitions */
#include "callbacks.h"

/** Version related definitions */
#include "version.h"

/** Platform dependent definitions */
#include "platformdep.h"

/** Error codes list */
#include "errors.h"



/** @brief Substance cooker context structure pre-declaration.

	Must be initialized using the substanceCookerContextInit function and 
	released using the substanceCookerContextRelease function. */
struct SubstanceCookerContext_;

/** @brief Substance cooker handle structure pre-declaration (C/C++ compatible). */
typedef struct SubstanceCookerContext_ SubstanceCookerContext;



/** @brief Substance cooker context initialization
	@param[out] substanceCookerContext Pointer to the Substance Cooker context 
		to initialize.
	@param substanceCookerApiVersion The value of this parameter should be 
		SUBSTANCE_COOKER_API_VERSION. Ensure that the header files against 
		which an application is compiled match the version of the cooker 
		dynamic libraries.
	@pre The context must be previously un-initialized or released.
	@post The context is now valid (if no error occurred).
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerContextInit(
	SubstanceCookerContext** substanceCookerContext,
	unsigned int substanceCookerApiVersion);

/** @brief Substance cooker context release
	@param substanceCookerContext Pointer to the Substance context to release.
	@pre The context must be previously initialized and every handle that uses
	this context must be previously released.
	@post This context is not valid any more (it can be re-initialized).
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerContextRelease(
	SubstanceCookerContext* substanceCookerContext);


	
/** @brief Set cooking option/parameters
	@param substanceCookerContext Pointer to the context to set the option.
	@param optionType Type of the option to set. See the 
		SubstanceCookerOptionEnum enumeration in options.h.
	@param value Option value (union).
	@pre The context must be previously initialized.
	@pre The value must have the required option type.
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerContextSetOption(
	SubstanceCookerContext* substanceCookerContext,
	SubstanceCookerOptionEnum optionType,
	SubstanceCookerOptionValue value);
	

/** @brief Set Substance cooker context callback
	@param substanceCookerContext Pointer to the Substance context to set the 
		callback for.
	@param callbackType Type of the callback to set. See the 
		SubstanceCookerCallbackEnum enumeration in callback.h.
	@param callbackPtr Pointer to the callback function to set.
	@pre The context must be previously initialized.
	@pre The callback function signature and callback type must match
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerContextSetCallback(
	SubstanceCookerContext* substanceCookerContext,
	SubstanceCookerCallbackEnum callbackType,
	void *callbackPtr);
	
	
#endif /* ifndef _SUBSTANCE_COOKER_CONTEXT_H */
