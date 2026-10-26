/** @file cooker.h
	@brief Header for the Substance cooker API. Manages the cooking process.
	@author Christophe Soum - Allegorithmic (christophe.soum@allegorithmic.com)
	@note This file is part of the Substance cooker headers
	@date 20090212
	@copyright Allegorithmic. All rights reserved.

	Cooking HOWTO:
	  - 1. Initialize a SubstanceCookerContext.
	  - 2. Create a SubstanceCookerHandle from the SubstanceCookerContext .
	  - 3. Set up the cooking parameters, select the SBS packages to cook, fill
	  in the desired function callbacks.
	  - 4. Launch the cooking process.
	  - 5. Grab the generated Substance assemblies at the end of cook.
	  - 6. Release the handle.
	  - 7. Release the context.
*/

/** @mainpage Substance - Cooker API Documentation

	@section intro_sec Introduction

	The Substance Cooker API allows the cooking of packages produced by
	the Substance authoring tools. Cooked results (assemblies) are meant to be
	used by Substance Linker. 

	@section start_sec Getting started with Substance Cooker
 
	The include entry point is cooker.h header. 
	It contains also a cooking generation HOWTO.
	
	The most important header file is handle.h one. It contains Substance Cooker
	handle structure and related functions definitions. This handle is used to 
	select packages to cook, launch the cook process and grab resulting 
	assemblies.

 */


#ifndef _SUBSTANCE_COOKER_COOKER_H
#define _SUBSTANCE_COOKER_COOKER_H

/** Handle structure and related functions definitions */
#include "handle.h"


#endif /* ifndef _SUBSTANCE_COOKER_COOKER_H */
