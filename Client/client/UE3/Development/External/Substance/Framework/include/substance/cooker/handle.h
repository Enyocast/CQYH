/** @file handle.h
	@brief Substance cooker handle structure and related functions definitions
	@author Christophe Soum - Allegorithmic (christophe.soum@allegorithmic.com)
	@note This file is part of the Substance cooker headers
	@date 20090212
	@copyright Allegorithmic. All rights reserved.

	Defines the SubstanceCookerHandle structure.
	Initialized from a SubstanceCookerContext.
	This handle is used to select packages to cook, launch the cooking process 
	and grab resulting assemblies.<BR>

	Summary of functions defined in this file:

	Handle creation and deletion:
	  - substanceCookerHandleInit
	  - substanceCookerHandleRelease

	Packages list management:
	  - substanceCookerHandlePushPackageFileA
	  - substanceCookerHandlePushPackageFileW
	  - substanceCookerHandlePushPackageMemory

	Includes directories:
	  - substanceCookerHandlePushIncludeDirA
	  - substanceCookerHandlePushIncludeDirW
	  - substanceCookerHandlePushIncludeDirDefault

	Create dependent assembly:
	  - substanceCookerHandlePushDependencyA
	  - substanceCookerHandlePushDependencyW
	  - substanceCookerHandlePushDependencyMemory
	  
	Extra data:
	  - substanceCookerHandlePushExtraData
	  
	Cooking process start:
	  - substanceCookerHandleCook

	Grab Results:
	  - substanceCookerHandleGetAssembly
	  - substanceCookerHandleGetIODesc


	Typical call sequence for Substance handle:
	  - 1. substanceCookerHandleInit
	  - 2. substanceCookerHandlePushPackage...
	  - 3. substanceCookerHandlePushIncludeDirDefault
	  - 4. substanceCookerHandleCook (launch the cooking process)
	  - 5. substanceCookerHandleGetAssembly (grab the result assembly)
	  - 6. substanceCookerHandleGetIODesc (grab the I/O bindings)
	  - 7. substanceCookerHandleRelease (close the handle)
*/


#ifndef _SUBSTANCE_COOKER_HANDLE_H
#define _SUBSTANCE_COOKER_HANDLE_H


/** Context structure and related functions definitions */
#include "context.h"

/** Extra data enumeration header */
#include "../extradata.h"



/** @brief Substance cooker handle structure pre-declaration.

	Must be initialized using the substanceCookerHandleInit function and
	released using the substanceCookerHandleRelease function. */
struct SubstanceCookerHandle_;

/** @brief Substance cooker handle structure pre-declaration (C/C++ compatible).
*/
typedef struct SubstanceCookerHandle_ SubstanceCookerHandle;



/** @brief Substance cooker handle initialization from context
	@param[out] substanceCookerHandle Pointer to the Substance Cooker handle to
		initialize.
	@param substanceCookerContext Pointer to the Substance Cooker context used
		for the cooking of substance data.
	@pre The handle must be previously un-initialized or released.
	@pre The context must be valid (correctly initialized) and remain valid
		during the handle lifetime.
	@post The handle is now valid (if no errors occurred).
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandleInit(
	SubstanceCookerHandle** substanceCookerHandle,
	SubstanceCookerContext* substanceCookerContext);

/** @brief Substance cooker handle release
	@param substanceCookerHandle Pointer to the Substance handle to release.
	@pre The handle must be already initialized and there must be no cooking
		processes currently running.
	@post This handle is not valid any more (it can be re-initialized).
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandleRelease(
	SubstanceCookerHandle* substanceCookerHandle);




/** @brief Add a package FILE to cook, ASCII filepath version
	@param substanceCookerHandle Pointer to the Substance handle.
	@param filepath Filepath of the package to cook, ASCII null-terminated str.
	@pre The handle must be previously initialized.
	@return Returns 0 if succeeded, an error code otherwise.

	A call to this function adds a package to cook. All outputs of all graphs in
	this package (except disabled graphes) are added to the output results list.

	At least one of the substanceCookerHandlePushPackage... function must be
	called before cooking (substanceCookerHandleCook) */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushPackageFileA(
	SubstanceCookerHandle* substanceCookerHandle,
	const char* filepath);

/** @brief Add a package FILE to cook, UNICODE filepath version
	@param substanceCookerHandle Pointer to the Substance handle.
	@param filepath Filepath of the package to cook, UNICODE null-terminated
		string.
	@pre The handle must be previously initialized.
	@return Returns 0 if succeeded, an error code otherwise.

	A call to this function adds a package to cook. All outputs of all graphs in
	this package (except disabled graphes) are added to the output results list.

	At least one of the substanceCookerHandlePushPackage... function must be
	called before cooking (substanceCookerHandleCook) */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushPackageFileW(
	SubstanceCookerHandle* substanceCookerHandle,
	const wchar_t* filepath);

/** @brief Add a package IN MEMORY to cook
	@param substanceCookerHandle Pointer to the Substance handle.
	@param packageData ASCII null-terminated str. that contains the package data
	@pre The handle must be previously initialized.
	@return Returns 0 if succeeded, an error code otherwise.

	A call to this function adds a package to cook. All outputs of all graphs in
	this package (except disabled graphes) are added to the output results list.

	At least one of the substanceCookerHandlePushPackage... function must be
	called before cooking (substanceCookerHandleCook) */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushPackageMemory(
	SubstanceCookerHandle* substanceCookerHandle,
	const char* packageData);
	
	
/** @brief Add a POST FILTER package, ASCII filepath version
	@param substanceCookerHandle Pointer to the Substance handle.
	@param filepath Filepath of the package, ASCII null-terminated str.
	@pre The handle must be previously initialized.
	@return Returns 0 if succeeded, an error code otherwise.

	A call to this function adds a package to cook. The graphs of this package
	w/ exactly one image input and one output are used as post filter of all
	results outputs. Both grayscale and color graphs can be defined.

	Must be pushed before packages to apply post filter. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushPostFilterFileA(
	SubstanceCookerHandle* substanceCookerHandle,
	const char* filepath);
	
/** @brief Add a POST FILTER package, UNICODE filepath version
	@param substanceCookerHandle Pointer to the Substance handle.
	@param filepath Filepath of the package, UNICODE null-terminated string.
	@pre The handle must be previously initialized.
	@return Returns 0 if succeeded, an error code otherwise.

	A call to this function adds a package to cook. The graphs of this package
	w/ exactly one image input and one output are used as post filter of all
	results outputs. Both grayscale and color graphs can be defined.

	Must be pushed before packages to apply post filter. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushPostFilterFileW(
	SubstanceCookerHandle* substanceCookerHandle,
	const wchar_t* filepath);


/** @brief Add an include path (ASCII), used to retrieve shared sbs files.
	@param substanceCookerHandle Pointer to the Substance handle.
	@param filepath Filepath of the include directory to add.
		ASCII null terminating string.
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushIncludeDirA(
	SubstanceCookerHandle* substanceCookerHandle,
	const char* filepath);

/** @brief Add a include path (UNICODE), used to retrieve shared sbs files.
	@param substanceCookerHandle Pointer to the Substance handle.
	@param filepath Filepath of the include directory to add.
		UNICODE null terminating string.
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushIncludeDirW(
	SubstanceCookerHandle* substanceCookerHandle,
	const wchar_t* filepath);

/** @brief Add the default include path, used to retrieve shared sbs files.
	@param substanceCookerHandle Pointer to the Substance handle.
	@param[out] defaultFilepath Returns the pointer on the default path found.
		Can be NULL if the default path information is not required.
	@return Returns 0 if succeeded, an error code otherwise.

	The default Substance Editor include dir path is read from the registry.
	Substance Editor must be installed. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushIncludeDirDefault(
	SubstanceCookerHandle* substanceCookerHandle,
	const wchar_t** defaultFilepath);

	
	
/** @brief Add a dependency to an existing assembly (ASCII filepath).
	@param substanceCookerHandle Pointer to the Substance handle.
	@param filepath Filepath of the assembly to create dependency on.
		ASCII null terminating string.
	@return Returns 0 if succeeded, an error code otherwise. 
	
	The result assembly will use any shared content of this assembly. */	
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushDependencyA(
	SubstanceCookerHandle* substanceCookerHandle,
	const char* filepath);

/** @brief Add a dependency to an existing assembly (UNICODE filepath).
	@param substanceCookerHandle Pointer to the Substance handle.
	@param filepath Filepath of the assembly to create dependency on.
		UNICODE null terminating string.
	@return Returns 0 if succeeded, an error code otherwise. 
	
	The result assembly will use any shared content of this assembly. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushDependencyW(
	SubstanceCookerHandle* substanceCookerHandle,
	const wchar_t* filepath);

/** @brief Add a dependency to an existing assembly (in memory).
	@param substanceCookerHandle Pointer to the Substance handle.
	@param assemblyData Pointer on buffer that contains the assembly data.
	@param assemblySize Size of the buffer (debug purposes only).
	@return Returns 0 if succeeded, an error code otherwise. 
	
	The result assembly will use any shared content of this assembly. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushDependencyMemory(
	SubstanceCookerHandle* substanceCookerHandle,
	const char* assemblyData,
	size_t assemblySize);
	
	
	
/** @brief Add user extra data in generated assembly.
	@param substanceCookerHandle Pointer to the Substance handle.
	@param extraUID Unique identifier of this user extra data. Used to retrieve
		this extra data into the generated assembly. User UIDs must be greater
		or equal to Substance_ExtraData_User (../extradata.h): 
		lower values are reserved. 
		Each extraUID must be unique for one assembly. 
	@param extraData Pointer on buffer that contains the user extra data.
	@param extraSize Size of the extra data buffer.
	@return Returns 0 if succeeded, an error code otherwise. 

	Extra data can be extracted from assemblies by Linker functions. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandlePushExtraData(
	SubstanceCookerHandle* substanceCookerHandle,
	unsigned int extraUID,
	const void* extraData,
	size_t extraSize);
	
	
	
/** @brief Launch the cooking process, process the pushed packages
	@param substanceCookerHandle Pointer to the Substance handle to cook.
	@pre The handle must be previously initialized, at least one package must
		be pushed.
	@post The packages, extra data and depedency lists are resetted if 
		cooking succeed.
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandleCook(
	SubstanceCookerHandle* substanceCookerHandle);

	

/** @brief Grab cooking result: A Substance assembly
	@param substanceCookerHandle Pointer to the Substance handle to grab the
		assembly result from.
	@param[out] resultData Sets the pointer on the binary string result.
		Set to NULL if failed. Remains valid during the handle lifetime and
		until the next cooking on the same handle.
	@param[out] resultSize Sets the data size of the binary string result.
		Set to 0 if failed.
	@pre The handle must be previously initialized and valid.
	@pre substanceCookerHandleCook must be called before.
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandleGetAssembly(
	SubstanceCookerHandle* substanceCookerHandle,
	const unsigned char** resultData,
	size_t* resultSize);

/** @brief Get the Input/Output bindings description (XML formatted)
	@param substanceCookerHandle Pointer to the Substance handle to grab
		bindings results from.
	@param[out] resultBindings Sets the pointer on the ASCII null terminated str
		bindings result. Set to NULL if failed.
		Remains valid during the handle lifetime and until the next cooking on
		the same handle.
	@pre The handle must be previously initialized and valid.
	@pre substanceCookerHandleCook must be called beforehands.
	@return Returns 0 if succeeded, an error code otherwise.

	The formats are described in the cooker documentation.
	
	Input/Output bindings description format is controlled by 
	Substance_Cooker_Option_IO option (see options.h). */
SUBSTANCE_EXPORT unsigned int substanceCookerHandleGetIODesc(
	SubstanceCookerHandle* substanceCookerHandle,
	const char** resultBindings);
	
/** @brief Grab an archive (SBSAR format): contains the assembly and I/O desc
	@param substanceCookerHandle Pointer to the Substance handle to grab the
		archive result from.
	@param basename Basename of assembly into the archive. UNICODE
		null-terminated string. Can be NULL: in this case, use the filename 
		added by the first substanceCookerHandlePushPackageFile... call.
	@param[out] archiveData Sets the pointer on the archive buffer result.
		Set to NULL if failed. Remains valid during the handle lifetime and
		until the next cooking on the same handle.
	@param[out] archiveSize Sets the data size of the archive result.
		Set to 0 if failed.
	@pre The handle must be previously initialized and valid.
	@pre substanceCookerHandleCook must be called before.
	@return Returns 0 if succeeded, an error code otherwise. */
SUBSTANCE_EXPORT unsigned int substanceCookerHandleGetArchive(
	SubstanceCookerHandle* substanceCookerHandle,
	const wchar_t* basename,
	const unsigned char** archiveData,
	size_t* archiveSize);


#endif /* ifndef _SUBSTANCE_COOKER_HANDLE_H */
