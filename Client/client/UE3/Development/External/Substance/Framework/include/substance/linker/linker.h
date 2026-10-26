/** @file linker.h
	@brief Header for the Substance linker API. Manages the linking process.
	@author Christophe Soum - Allegorithmic (christophe.soum@allegorithmic.com)
	@note This file is part of the Substance linker headers
	@date 20100406
	@copyright Allegorithmic. All rights reserved.

	Linking HOWTO:
	  - 1. Initialize a SubstanceLinkerContext with linking options and
		   target platform engine id.
	  - 2. Create a SubstanceLinkerHandle from the SubstanceLinkerContext.
	  - 3. Select the SBS assemblies to link.
	  - 4. Launch the linking process and grab the generated Substance binaries
		   at the end of link.
	  - 6. Release the handle.
	  - 7. Release the context.
*/

/** @mainpage Substance - Linker API Documentation

	@section intro_sec Introduction

	The Substance Linker API allows the linking of assemblies produced by
	the Substance cooker tools. Linked results are meant to be used by a specific
	Substance Engine (same version and chosen platform).

	@section start_sec Getting started with Substance Linker
 
	The include entry point is linker.h header. 
	It contains also a linking generation HOWTO.
	
	The most important header file is handle.h one. It contains Substance Linker
	handle structure and related functions definitions. This handle is used to 
	select assemblies to link, launch the link process and grab resulting 
	binaries.
 */


#ifndef _SUBSTANCE_LINKER_LINKER_H
#define _SUBSTANCE_LINKER_LINKER_H

/** Handle structure and related functions definitions */
#include "handle.h"

/** Engine IDs enumeration header */
#include <substance/engineid.h>

#endif /* ifndef _SUBSTANCE_LINKER_LINKER_H */
