/****************************************************************************************
 
   Copyright (C) 2011 Autodesk, Inc.
   All rights reserved.
 
   Use of this software is subject to the terms of the Autodesk license agreement
   provided at the time of installation or download, or which otherwise accompanies
   this software in either electronic or hard copy form.
 
****************************************************************************************/

//! \file fbxconnectionpoint.h
#ifndef _FBXSDK_CORE_CONNECTION_POINT_H_
#define _FBXSDK_CORE_CONNECTION_POINT_H_

#include <fbxsdk/fbxsdk_def.h>

#include <fbxsdk/core/base/fbxarray.h>
#include <fbxsdk/core/base/fbxmemory.h>
//#include <fbxsdk/core/fbxpropertydef.h>

#include <fbxsdk/fbxsdk_nsbegin.h>

class FBXSDK_DLL FbxConnection
{
public:
	enum Type
	{ 
		eNone = 0,
		// System or user
		eSystem = 1 << 0,
		eUser = 1 << 1,
		eSystemOrUser = eUser | eSystem,
		// Type of Link
		eReference = 1 << 2,
		eContains = 1 << 3,
		eData = 1 << 4,
		eLinkType = eReference | eContains | eData,
		eDefault = eUser | eReference,
		eUnidirectional = 1 << 7
	};
};

class FbxConnectionPointFilter;

class FBXSDK_DLL FbxConnectionPoint
{
public:
	enum Direction
	{ 
		eDirSrc = 1 << 0,	// Contains sources
		eDirDst = 1 << 1,	// Contains destinations
		eDirUni = 1 << 2,	// Connection is not 2 ways
		eDirBoth = eDirSrc | eDirDst,
		eDirMask = eDirSrc | eDirDst | eDirUni
	};

	enum Type
	{
		eStandard = 0,
		eSubConnection = 1 << 3,		// Connect is a sub Connect of another
		eTypeMask = eSubConnection
	}; 

	enum Attribute
	{
		eDefault = 0,
		eCache = 1 << 4,			
		eAttributeMask = eCache
	}; 

	enum AllocFlag
	{
		eNotAllocated = 0,
		eAllocated = 1 << 5,
		eAllocFlagMask = eAllocated
	};

	enum CleanedFlag
	{
		eNotCleaned = 0,
		eCleaned = 1 << 6,
		eCleanedFlagMask = eCleaned
	};

	// --------------------------------------------
	// Actions
	// --------------------------------------------
	enum Event
	{
		eSrcConnectRequest,
		eDstConnectRequest,

		eSrcConnect,
		eDstConnect,
		eSrcConnected,
		eDstConnected,

		eSrcDisconnect,
		eDstDisconnect,
		eSrcDisconnected,
		eDstDisconnected, //do not destroy Connect on disconnected

		eSrcReplaceBegin,
		eSrcReplaceEnd,
		eDstReplaceBegin,
		eDstReplaceEnd,

		eSrcReorder,
		eSrcReordered
	};

	class ConnectionList
	{
	public:
		ConnectionList();
		~ConnectionList();

		void Clear();

		// Src
		void InsertSrcAt(int pIndex, FbxConnectionPoint* pConnect, FbxConnection::Type pType);
		void AddSrc(FbxConnectionPoint* pConnect, FbxConnection::Type pType);
		void RemoveSrcAt(int pIndex);
		int FindSrc(FbxConnectionPoint* pConnect) const;
		int GetSrcCount() const; 
		FbxConnectionPoint* GetSrc(int pIndex) const;
		FbxConnection::Type GetSrcType(int pIndex) const;

		// Dst
		void InsertDstAt(int pIndex, FbxConnectionPoint* pConnect, FbxConnection::Type pType);
		void AddDst(FbxConnectionPoint* pConnect, FbxConnection::Type pType);
		void RemoveDstAt(int pIndex);
		int FindDst(FbxConnectionPoint* pConnect) const;
		int GetDstCount() const;
		FbxConnectionPoint* GetDst(int pIndex) const;
		FbxConnection::Type GetDstType(int pIndex) const;

	protected:
		FbxArray<FbxConnectionPoint*>	mList;
		FbxArray<char>					mType;
		int								mSrcCount, mDstCount;
	};

	// Constructor/Destructor	
	FbxConnectionPoint(void* pData=0);
	virtual ~FbxConnectionPoint();

	void SetFilter(FbxConnectionPointFilter* pConnectFilter, Type pType=eStandard);
	void InternalClear();

	//! Clear the ConnectList without any regards to what is connected
	void WipeConnectionList();
	void Destroy();
	void SubConnectRemoveAll();

	inline FbxConnectionPoint* GetSubOwnerConnect(){ return GetConnectType()==eSubConnection ? mOwner : NULL; }
	inline FbxConnectionPointFilter* GetFilter(){ return mFilter; }

	virtual bool		IsInReplace(FbxConnectionPoint* p1, FbxConnectionPoint* p2);

	inline void			SetConnectType(Type pType){ mFlags = (mFlags & ~eTypeMask) | pType; }
	inline Type			GetConnectType(){ return Type(mFlags & eTypeMask); }
	inline void			SetDirection(int pDirections){ mFlags = (mFlags & ~eDirMask) | pDirections; }
	inline Direction	GetDirection(){ return Direction(mFlags & eDirMask); }
	inline void			SetAttribute(int pAttributes){ mFlags = (mFlags & ~eAttributeMask) | pAttributes; }
	inline Attribute	GetAttribute(){ return Attribute(mFlags & eAttributeMask); }
	inline void			SetAllocatedFlag(bool pBool){ mFlags = ( pBool ) ? mFlags | eAllocated : mFlags & ~eAllocFlagMask; }
	inline bool			GetAllocatedFlag(){ return ( mFlags & eAllocFlagMask ) ? true : false; }
	inline void			SetCleanedFlag(bool pBool){ mFlags = ( pBool ) ? mFlags | eCleaned : mFlags & ~eCleanedFlagMask; }
	inline bool			GetCleanedFlag(){ return ( mFlags & eCleanedFlagMask ) ? true : false; }		

	bool				IsValidSrc(FbxConnectionPoint* pConnect);
	bool				IsValidDst(FbxConnectionPoint* pConnect);
	bool				IsValidSrcConnection(FbxConnectionPoint* pConnect,FbxConnection::Type pConnectionType);
	bool				IsValidDstConnection(FbxConnectionPoint* pConnect,FbxConnection::Type pConnectionType);
	bool				RequestValidSrcConnection(FbxConnectionPoint* pConnect,FbxConnection::Type pConnectionType );
	bool				RequestValidDstConnection(FbxConnectionPoint* pConnect,FbxConnection::Type pConnectionType );

	// Connection services
	bool			ConnectSrc			(FbxConnectionPoint* pSrc,FbxConnection::Type pConnectionType = FbxConnection::eNone );
	bool			ConnectDst			(FbxConnectionPoint* pDst,FbxConnection::Type pConnectionType = FbxConnection::eNone );
	bool			ConnectSrcAt		(int pDst_SrcIndex, FbxConnectionPoint* pSrc, FbxConnection::Type pConnectionType = FbxConnection::eNone );
	bool			ConnectDstAt		(int pSrc_DstIndex, FbxConnectionPoint* pDst, FbxConnection::Type pConnectionType = FbxConnection::eNone );
	static bool		ConnectConnect		(FbxConnectionPoint* pSrc,FbxConnectionPoint* pDst,FbxConnection::Type pConnectionType );
	static bool		ConnectAt			(FbxConnectionPoint* pSrc,int pSrc_DstIndex,FbxConnectionPoint* pDst,int pDst_SrcIndex,FbxConnection::Type pConnectionType  );

	bool			DisconnectDst		(FbxConnectionPoint* pSrc);
	bool			DisconnectSrc		(FbxConnectionPoint* pSrc);
	void			DisconnectAllSrc	();
	void			DisconnectAllDst	();
	static bool		DisconnectConnect	(FbxConnectionPoint* pSrc,FbxConnectionPoint* pDst);
	bool			DisconnectDstAt		(int pIndex);
	bool			DisconnectSrcAt		(int pIndex);

	bool			ReplaceInDst		(FbxConnectionPoint* pDstOld,FbxConnectionPoint* pDstNew, int pIndexInNew);
	bool			ReplaceInSrc		(FbxConnectionPoint* pSrcOld,FbxConnectionPoint* pSrcNew, int pIndexInNew);
	bool			ReplaceDstAt		(int pIndex,FbxConnectionPoint* pDst);
	bool			ReplaceSrcAt		(int pIndex,FbxConnectionPoint* pSrc);
	bool			SwapSrc				(int pIndexA,int pIndexB);

	/** Change the position of a source Connect.
	* \param pIndex	Position of the Connect to move.
	* \param pAtIndex	Position where to move the Connect.
	* \return			\c True if the Connect was moved.
	* \remarks After the move, the Connect will be precisely at position pAtIndex.
	*/
	bool MoveSrcAt(int pIndex, int pAtIndex);

	/** Change the position of a source Connect.
	* \param pSrc		Connect to move.
	* \param pAtSrc	Connect at which position to move.
	* \return			\c True if the Connect was moved.
	* \remarks After the move, the Connect will be precisely at the position where pAtSrc was before the move.
	*/
	bool MoveSrcAt(FbxConnectionPoint* pSrc, FbxConnectionPoint* pAtSrc);

	// Access services
	bool IsConnectedSrc(FbxConnectionPoint*);
	bool IsConnectedDst(FbxConnectionPoint*);
	inline bool IsConnected(FbxConnectionPoint* pConnect) { return IsConnectedSrc(pConnect) || IsConnectedDst(pConnect); }

	inline int					GetSrcCount() const { return mConnectionList.GetSrcCount(); }
	inline FbxConnectionPoint*	GetSrc(int pIndex) const { return mConnectionList.GetSrc(pIndex);}
	inline FbxConnection::Type	GetSrcType(int pIndex) const { return mConnectionList.GetSrcType(pIndex);}
	inline int					GetDstCount() const { return mConnectionList.GetDstCount(); }
	inline FbxConnectionPoint*	GetDst(int pIndex) const { return mConnectionList.GetDst(pIndex);}
	inline FbxConnection::Type	GetDstType(int pIndex) const { return mConnectionList.GetDstType(pIndex);}

	inline int					FindSrc(FbxConnectionPoint* pConnect){ return mConnectionList.FindSrc(pConnect); }
	inline int					FindDst(FbxConnectionPoint* pConnect){ return mConnectionList.FindDst(pConnect); }

	// Filtered versions	
	inline int					GetSrcCount(FbxConnectionPointFilter* pFilter){ return (pFilter) ? SubConnectGetOrCreate(pFilter)->GetSrcCount() : GetSrcCount(); }
	inline FbxConnectionPoint*	GetSrc(int pIndex,FbxConnectionPointFilter* pFilter){ return (pFilter) ? SubConnectGetOrCreate(pFilter)->GetSrc(pIndex) : GetSrc(pIndex); }
	inline FbxConnection::Type	GetSrcType(int pIndex,FbxConnectionPointFilter* pFilter){ return (pFilter) ? SubConnectGetOrCreate(pFilter)->GetSrcType(pIndex) : GetSrcType(pIndex); }
	inline int					GetDstCount(FbxConnectionPointFilter* pFilter){ return (pFilter) ? SubConnectGetOrCreate(pFilter)->GetDstCount() : GetDstCount(); }
	inline FbxConnectionPoint*	GetDst(int pIndex,FbxConnectionPointFilter* pFilter){ return (pFilter) ? SubConnectGetOrCreate(pFilter)->GetDst(pIndex): GetDst(pIndex); }
	inline FbxConnection::Type	GetDstType(int pIndex,FbxConnectionPointFilter* pFilter){ return (pFilter) ? SubConnectGetOrCreate(pFilter)->GetDstType(pIndex) : GetDstType(pIndex); }

	void* GetData(){ return mData; }

protected:
	void SubConnectAdd(FbxConnectionPoint* pConnect);
	void SubConnectRemove(FbxConnectionPoint* pConnect);
	FbxConnectionPoint* SubConnectFind(FbxConnectionPointFilter* pFilter);
	FbxConnectionPoint* SubConnectGetOrCreate(FbxConnectionPointFilter* pFilter);
	void SubConnectFill(FbxConnectionPoint*	pConnect);

	// Connections
	virtual	bool ConnectNotify(Event pAction,FbxConnectionPoint* pThis,int pIndex,FbxConnectionPoint* pConnect = NULL,FbxConnection::Type pConnectionType=FbxConnection::eNone,FbxConnectionPoint* pNewConnect=NULL );
	virtual void ConnectCleanUp(FbxConnectionPoint* pThis); //Call after disconnected

	int FindSrcIndexFromOwnerConnectIndex(FbxConnectionPoint* pOwner,int pOwnerIndex);	
	int FindDstIndexFromOwnerConnectIndex(FbxConnectionPoint* pOwner,int pOwnerIndex);

	/** Change the position of a source Connect.
	* \param pIndex		Position of the Connect to move.
	* \param pBeforeIndex	Position before which to move the Connect.
	* \return				\c True if the Connect was moved.
	* \remarks If you want to move to the last position, specify a pBeforeIndex equal to the SrcCount.
	*/
	bool InternalMoveSrcBefore( int pIndex, int pBeforeIndex );

	// Internal Access
private:	
	inline void InsertSrcAt(int pIndex,FbxConnectionPoint* pConnect,FbxConnection::Type pConnectionType){ mConnectionList.InsertSrcAt(pIndex,pConnect,pConnectionType); }
	inline void InsertDstAt(int pIndex,FbxConnectionPoint* pConnect,FbxConnection::Type pConnectionType){ mConnectionList.InsertDstAt(pIndex,pConnect,pConnectionType); }
	inline void RemoveSrcAt(int pIndex){ mConnectionList.RemoveSrcAt(pIndex); }
	inline void RemoveDstAt(int pIndex){ mConnectionList.RemoveDstAt(pIndex); }    	

	static bool InternalConnectBefore (FbxConnectionPoint* pSrc,FbxConnectionPoint* pSrc_BeforeDst,FbxConnectionPoint* pDst,FbxConnectionPoint* pDst_BeforeSrc,FbxConnection::Type pConnectionType );
	static bool UserConnectBefore (FbxConnectionPoint* pSrc,FbxConnectionPoint* pSrc_BeforeDst,FbxConnectionPoint* pDst,FbxConnectionPoint* pDst_BeforeSrc,FbxConnection::Type pConnectionType );
	static bool EmitReplaceNotify(FbxConnectionPoint* pDstOwner, FbxConnectionPoint* pSrcOwner, FbxConnectionPoint* pDst, FbxConnectionPoint* pSrc, Event pConnectAction, FbxConnectionPoint* pNew);

	// Owner ship management	
	virtual bool SetOwnerConnect(FbxConnectionPoint* pConnect);
	inline FbxConnectionPoint* GetOwnerConnect(){ return mOwner;  }
	bool ConnectOwnedConnect(FbxConnectionPoint* pConnect);
	bool DisconnectOwnedConnect(FbxConnectionPoint* pConnect);

	//Connection Data
	void*							mData;
	int								mFlags;
	FbxConnectionPoint*				mOwner;
	ConnectionList					mConnectionList;

	//SubConnection Data
	FbxArray<FbxConnectionPoint*>	mSubConnectList;
	FbxArray<FbxConnectionPoint*>	mSubConnectCreatedList;		
	FbxConnectionPointFilter*		mFilter;
};

/** Class to manage ConnectFilter.
  * \nosubgrouping
  */
class FBXSDK_DLL FbxConnectionPointFilter
{
public: 
	/**
	  * \name Constructor and Destructor
	  */
	//@{
		//! Constructor
		FbxConnectionPointFilter(){}

		//! Destructor
		virtual ~FbxConnectionPointFilter();
	//@}

	/**
	  * \name ConnectFilter management
	  */
	//@{
		//! Return reference ConnectionPoint filter.
		virtual FbxConnectionPointFilter* Ref();

		//! Cancel reference
		virtual void Unref();

		//! Get unique filter ID
		virtual FbxInt GetUniqueId() const { return 0; }

		/** Judge if the given Connection Point is valid
		  * \param pConnect The given Connection Point.
		  * \return \c True if valid, \c false if not valid.
		  */
		virtual bool IsValid(FbxConnectionPoint* pConnect) const;

		/** Judge if the given Connection Point is a valid connection
		  * \param pConnect The given Connection Point.
		  * \param pType Connection type.
		  * \return \c True if valid, \c false if not valid.
		  */
		virtual bool IsValidConnection(FbxConnectionPoint* pConnect, FbxConnection::Type pType) const;

		/** Judge if it is equal with the given  ConnectionPoint filter.
		  * \param pConnectFilter The given  ConnectionPoint filter.
		  * \return \c True if equal, \c false if unequal.
		  */
		virtual bool IsEqual(FbxConnectionPointFilter* pConnectFilter) const;
	//@}
};

#include <fbxsdk/fbxsdk_nsend.h>

#endif /* _FBXSDK_CORE_CONNECTION_POINT_H_ */
