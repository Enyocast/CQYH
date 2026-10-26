/** @file errors.h
	@brief Substance cooker error codes definitions. 
	@author Christophe Soum - Allegorithmic (christophe.soum@allegorithmic.com)
	@note This file is part of the Substance cooker headers
	@date 20090212
	@copyright Allegorithmic. All rights reserved. 
	
	Returned by all Substance cooker functions. */

#ifndef _SUBSTANCE_COOKER_ERRORS_H
#define _SUBSTANCE_COOKER_ERRORS_H


/** @brief Substance cooker error codes enumeration */
typedef enum
{
	Substance_Cooker_Error_None               = 0,  /**< No errors */
	Substance_Cooker_Error_InvalidContext     = 1,  /**< Context is not valid */
	Substance_Cooker_Error_InvalidHandle      = 2,  /**< Invalid handle used */
	Substance_Cooker_Error_InvalidParams      = 3,  /**< Invalid parameters */
	Substance_Cooker_Error_InternalError      = 4,  /**< Internal error */
	Substance_Cooker_Error_NYI                = 5,  /**< Not yet implemented */
	Substance_Cooker_Error_OpenPackage        = 6,  /**< Cannot open the package */
	Substance_Cooker_Error_DirNoExists        = 7,  /**< The directory do not exists*/
	Substance_Cooker_Error_NoPackagesToCook   = 8,  /**< The package list is empty */
	Substance_Cooker_Error_NoDefaultDir       = 9,  /**< Cannot include default dir */
	Substance_Cooker_Error_FrontEndFailed     = 10, /**< Error in front end */
	Substance_Cooker_Error_FlatteningFailed   = 11, /**< Error in flattening pass */
	Substance_Cooker_Error_BackEndFailed      = 12, /**< Error in back end */
	Substance_Cooker_Error_NotCooked          = 13, /**< No cook results available */
	Substance_Cooker_Error_APIVersionMismatch = 14, /**< Cooker DDL older than .h */
	Substance_Cooker_Error_OpenAssembly       = 15, /**< Cannot open the assembly */
	Substance_Cooker_Error_InvalidAssembly    = 16, /**< Invalid assembly format */
	Substance_Cooker_Error_ReservedUID        = 17, /**< Cannot use UID: reserved */
	Substance_Cooker_Error_NotUniqueUID       = 18, /**< UID already used */
	/* etc. */

	Substance_Cooker_Error_Internal_Count

} SubstanceCookerErrorCodes;

#endif /* ifndef _SUBSTANCE_COOKER_ERRORS_H */
