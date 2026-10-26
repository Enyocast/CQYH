/****************************************************************************************
 
   Copyright (C) 2011 Autodesk, Inc.
   All rights reserved.
 
   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

//! \file fbxstream.h
#ifndef _FBXSDK_CORE_STREAM_H_
#define _FBXSDK_CORE_STREAM_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

/** Generic base class for streamable data.
  */
class FBXSDK_DLL FbxStream
{
public:
	/** \enum State
	  * - \e eClosed	indicate a closed stream  
	  * - \e eOpen		indicate an opened stream  
	  * - \e eEmpty		indicate an empty stream
	  */
	enum State {eClosed, eOpen, eEmpty};

	//! Default constructor.
	FbxStream() {};

	//! Destructor
	virtual ~FbxStream() {};

	/** Query the current state of the stream.
	  */
	virtual State GetState() = 0;

	/** Open the stream.
	  * \return True if successful.
	  */
	virtual bool Open() = 0;

	/** Close the stream.
	  * \return True if successful.
	  */
	virtual bool Close() = 0;

	/** Empties the internal data of the stream.
	  * \return True if successful.
	  */
	virtual bool Flush() = 0;

	/** Writes a memory block.
	  * \param pData Pointer to the memory block to write.
	  * \param pSize Size (in bytes) of the memory block to write.
	  * \return The number of bytes written in the stream.
	  */
	virtual int Write(const void* /*pData*/, int /*pSize*/) = 0;

	/** Read bytes from the stream and store them in the memory block.
	  * \param pData Pointer to the memory block where the read bytes are stored.
	  * \param pSize Number of bytes read from the stream.
	  * \return The actual number of bytes successfully read from the stream.
	  */
	virtual int Read(void* /*pData*/, int /*pSize*/) const = 0;

///////////////////////////////////////////////////////////////////////////////
//
//  WARNING!
//
//	Anything beyond these lines may not be documented accurately and is 
// 	subject to change without notice.
//
///////////////////////////////////////////////////////////////////////////////
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	int Write(const char* pData, int pSize){ return Write((void*)pData, pSize); }
	int Write(const int* pData, int pSize){ return Write((void*)pData, pSize); }
	int Read(char* pData, int pSize) const { return Read((void*)pData, pSize); }
	int Read(int* pData, int pSize) const { return Read((void*)pData, pSize); }
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_CORE_STREAM_H_ */
