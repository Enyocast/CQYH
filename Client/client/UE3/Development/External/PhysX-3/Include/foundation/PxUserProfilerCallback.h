// This code contains NVIDIA Confidential Information and is disclosed to you 
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and 
// any modifications thereto. Any use, reproduction, disclosure, or 
// distribution of this software and related documentation without an express 
// license agreement from NVIDIA Corporation is strictly prohibited.
// 
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2012 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  
#ifndef PX_FOUNDATION_PX_USER_PROFILER_CALLBACK_H
#define PX_FOUNDATION_PX_USER_PROFILER_CALLBACK_H

/** \addtogroup foundation
@{
*/

#include "foundation/PxSimpleTypes.h"
// This indicates the version number of the API.  Any time the API is changed
// This version number must be bumped! 
#define PX_USER_PROFILER_CALLBACK_VERSION 102
// Uncomment to completely disable all instrumented profiling
//#ifndef PX_DISABLE_USER_PROFILER_CALLBACK
//#define PX_DISABLE_USER_PROFILER_CALLBACK
//#endif
//#endif

#ifndef PX_DISABLE_USER_PROFILER_CALLBACK

namespace PVD
{
	class PvdBinding;
};

namespace PX_USER_PROFILER_CALLBACK
{

/**
\brief User defined interface class.  Used to embed profiling instrumentation, memory tracking, object persistence, and message logging.

<b>Threading:</b> The implementation of this class must be thread safe.
*/
class PxUserProfilerCallback
{
public:

	/**
	\brief The layout format for the memory report.
	*/
	enum MemoryReportFormat
	{
		MRF_SIMPLE_HTML,       // just a very simple HTML document containing the tables.
		MRF_CSV,               // Saves the Tables out as comma seperated value text
		MRF_TEXT,              // Saves the tables out in human readable text format.
		MRF_TEXT_EXTENDED,     // Saves the tables out in human readable text format, but uses the MS-DOS style extended ASCII character set for the borders.
	};
	/**
	\brief This enumeration determines which underlying profiling SDK to use
	*/
	enum Type
	{
		PT_NONE,				// no profiling, just memory tracking.
		PT_TELEMETRY,			// use Telemetry from Rad Game Tools
		PT_DEJA_INSIGHT,		// use DejaInsight from DejaTools
		PT_PVD,					// uses PVD from NVIDIA
		PT_NSIGHT,				// Use Parallel Insight from NVIDIA
		PT_USER_API,			// The underlying profiling implentation is a custom version written by the developer.
	};

	/**
	\brief This Descriptor controls how the profiler will be initialized.
	*/
	class Desc
	{
	public:
		Desc(void)
		{
			init();
		}
		Type		type;						// Which 3rd party profiler to connect to.
		size_t		version;					// The version number of the PxUserProfilerCallback API
		bool		profilerActive;				// whether or not the profiler should be active on startup.
		bool		useMemTracker;				// whether or not full memory tracking is active.
		bool		logEveryAllocation;			// whether or not to log every single memory allocation.  WARNING! Do not use this unless you are absolutely sure!
		bool		logEveryFrame;				// whether or not to log a per frame memory status.  
		bool		verifySingleThreaded;		// Set to true of you expect all allocations within a single context to be in the same thread.  Will generate a warning if it fails.
		bool		createProfilerContext;		// Whether or not the DLL should create the profiler context.  Otherwise, it must be passed in either by the descriptor or later.
		void		*telemetryContext;			// Optional user provided telemetry context.  IF null and 'createProfilerContext' is true, then one will be created.
		PVD::PvdBinding *pvdBinding;			// Optional user provided PvdBinding interface.  If null and 'createProfilerContext' is true, then one will be created.
		void init(void)
		{
			version = PX_USER_PROFILER_CALLBACK_VERSION;
			type = PT_NONE;						// By default connect to no third party profiler and simply enable the memory tracking features of the DLL.
			profilerActive = true;				// By default start up with the profiler active.
			useMemTracker = true;				// by default DO use the memory tracker; which can report memory leaks and generate an HTML report of memory usage in all contexts.
			logEveryFrame = false;				// by default do *not* generate a per frame memory summary.
			logEveryAllocation = false;			// by default do *not* log every single memory allocation.
			verifySingleThreaded = false;		// by default assume multi-threaded memory allocation pattern
			createProfilerContext = true;		// by default the DLL will create the profiling context for the application.
			telemetryContext = NULL;			// by default no application provided telemtry context.
			pvdBinding = NULL;					// by default no application provided PVD context.
		}
	};
	/**
	\brief This enumeration determines what type of CUDA event data is being transferred.
	*/
	enum CUDAProfileEventType
	{
		CUDA_WARP_PROFILE_EVENT = 1,
	};
	/**
	\brief This data structure describes the contents of a single CUDA event.
	*/
	struct CUDAWarpProfileEvent
	{
		physx::PxU16 block;
		physx::PxU8  warp;
		physx::PxU8  mpId;
		physx::PxU8  hwWarpId;
		physx::PxU8  userDataCfg;
		physx::PxU16 eventId;
		physx::PxU32 startTime;
		physx::PxU32 endTime;
	};
	/**
	\brief This enumeration determines how a graphics data plot should be displayed.
	*/
	enum PlotType
	{
		PT_FLOAT = 0,
		PT_MEMORY = 1,
		PT_HEX = 2,
		PT_INTEGER = 3,
		PT_PERCENTAGE_COMPUTED = 4,
		PT_PERCENTAGE_DIRECT = 5,
		PT_TIME = 6,
		PT_TIME_MS = 7,
		PT_LAST
	};
	/**
	\brief This enumeration determines how a profile message will be highlighted
	*/
	enum MessageChannelType
	{
		MCT_LOG			= 0x0001,
		MCT_WARNING		= 0x0002,
		MCT_ERROR		= 0x0004,
		MCT_EXCLAMATION	= 0x1000,
		MCT_NOTE		= 0x2000,
		MCT_QUESTION	= 0x3000,
	};

	/**
	\brief This enumeration indicates the type of memory allocation that is being performed.
	*/
	enum MemoryType
	{
		MT_NEW,						// Captured new operator
		MT_NEW_ARRAY,				// Captured new array operator
		MT_MALLOC,					// Standard heap allocation
		MT_FREE,					// Standard heap free
		MT_DELETE,					// Captured delete operator
		MT_DELETE_ARRAY,			// Captured array delete
		MT_GLOBAL_NEW,				// Allocation via Global new
		MT_GLOBAL_NEW_ARRAY,		// Allocation via global new array
		MT_GLOBAL_DELETE,			// Deallocation via global delete
		MT_GLOBAL_DELETE_ARRAY,		// Deallocation via global delete array
	};

	/**
	\brief This data structure is used to return the current state of a particular block of allocated memory.
	*/
	struct TrackInfo
	{
		const void		*mMemory;		// Address of memory
		MemoryType		 mType;			// Type of allocation
		size_t			mSize;			// Size of the memory allocation
		const char		*mContext;		// The context of the memory allocation.
		const char		*mClassName;	// The class or type name of this allocation.
		const char		*mFileName;		// Source code file name where this allocation occured
		physx::PxU32	 mLineNo;		// Source code line number where this allocation occured
		size_t			mAllocCount; 	// Indicates which time this allocation occured at this particular source file and line number.
	};

	/**
	\brief Returns the current state of an allocated block of memory.  If it returns false, this address was not currently being tracked..
	*/
	virtual bool trackInfo(const void *mem,TrackInfo &info) = 0;

	/**
	\brief This method is used to register an allocated piece of memory.
	*/
	virtual void trackAlloc(void *mem,		// The address of the memory that was allocated.
		size_t size,						// The size of the block of memory.
		MemoryType type,					// How this block of memory was allocated (malloc/free new/delete array new/array delete, or fall through to the global new/delete allocator)
		const char *context,				// The context in which this block of memory was allocated.  Typically used to indicate the source of the memory allocation (PhysX, APEX, User Interface, etc.)
		const char *className,				// The descriptive ASCII name of this block of memory.  Typically corresponds to the class name if from a new operator.
		const char *fileName,				// The source code file name where this allocation was performed.
		physx::PxU32 lineno) = 0;			// The source code line number where this allocation was performed.

	/**
	\brief This method is used to register a reallocation event.
	*/
	virtual void trackRealloc(void *oldMem,		// The old address of the piece of memory being reallocated.
		void *newMem,							// The new address for this memory block.
		size_t newSize,							// The new size of the memory block.
		const char *context,					// The context of this memory allocation.
		const char *className,					// The descriptive ASCII name of this block of memory.  Typically corresponds to the class name if from a new operator.
		const char *fileName,					// The source code file name where the reallocation is being performed.
		physx::PxU32 lineno) = 0;				// The source code line number where this reallocation was performed.

	/**
	\brief This method is used to register a memory de-allocation event.
	*/
	virtual void trackFree(void *mem,			// The address of the piece of memory being deallocated.
		MemoryType type,						// The type of deallocation event (free, delete, array delete, etc.)
		const char *context,					// The context of the memory deallocation; must match the same context as when it was previously allocated.
		const char *fileName,					// The source code file name where the deallocation event occurred.
		physx::PxU32 lineno) = 0;				// The source code line number where the deallocation event occurred.

	/**
	\brief This method is used to validate a free memory request.  If there is an error, this method will return a clear ASCII description of how the error occurred.
	*/
	virtual const char * trackValidateFree(void *mem,	// The address of the block of memory to be freed
		MemoryType type,								//  The type of deallocation event (free, delete, array delete, etc.)
		const char *context,							// The context of the memory deallocation; must match the same context as when it was previously allocated.
		const char *fileName,							// The source code file name where the deallocation event occurred.
		physx::PxU32 lineno) = 0;								// The source code line number where the deallocation event occurred.

	/**
	\brief This method is used to record a statistic value.
	*/
	virtual void profileStat(const char *statName,		// The descriptive name of this statistic
							physx::PxU64 context,		// The context of this statistic. Data is presented 'in context' by PVD.  This parameter is ignored by other profiler tools.
							physx::PxI64 statValue,		// Up to a 16 bit signed integer value for the statistic.
							const char *fileName,		// The source code file name where this statistic event was generated.
							physx::PxU32 lineno) = 0;	// The source code line number where this statistic event was generated.

	/**
	\brief This method is used to mark the beginning of a CPU based profiling event.  Assumes the matching 'end event' is in the same thread.
	*/
	virtual void profileBegin(const char *event,			// The name of the event.
							physx::PxU64 context,			// The context of the event (only used by PVD)
							const char *fileName,			// The source code file name where the event was started.
							physx::PxU32 lineno) = 0;		// The source code line number where the event was started.

	/**
	\brief This method is used to mark the beginning of a CPU based profiling event. This version supports the strange use-case where the end event might not occur in the same thread.   This is a feature supported by PVD but no other profiler.
	*/
	virtual void profileBegin(const char *event,		// The name of the event
							physx::PxU64 context,		// The context of the event (only used by PVD)
							physx::PxU32 threadId,		// The thread id where the event began.
							const char *fileName,		// The source code file name where the event was started.
							physx::PxU32 lineno) = 0;	// The source code line number where the event was started.

	/**
	\brief This method is used to mark the end of an timed event.
	*/
	virtual void profileEnd(const char *event,				// The name of the event which is being ended.  This is *not* needed by any profiler other than PVD.
							physx::PxU64 context) = 0;		// The context of the event which is being ended; matches the context of the begin event.  PVD only.

	/**
	\brief This method is used to mark the end of an timed event where the end of the event is not necessarily in the same thread as the beginning event.  Only supported on PVD.
	*/
	virtual void profileEnd(const char *event,			// The name of the event which is being ended.  This is *not* needed by any profiler other than PVD.
							physx::PxU64 context,		// The context of the event which is being ended; matches the context of the begin event.  PVD only.
							physx::PxU32 threadId) = 0;	// The thread id corresponding to the begin event.  This method does not necessarily have to be executed in the same thread that the begin event occured in.  PVD only.

	/**
	\brief Records a log message.
	*/
	virtual void profileMessageChannel(MessageChannelType messageType,	// How to highlight this log message (error, warning, log, etc.)
									const char *channel,				// The 'channel' this message is for.  In Telemetry this can use a path like semantic for hierarchical message logging.  Example: "Simulate/Particles"
									const char *message,...) = 0;		// The 'printf' style specification for the message, followed by varargs

	/**
	\brief Denotes what 'section' the application is in. Typically used for designating phases of an application.  Examples: 'Level Loading', 'Shutting Down', etc.
	*/
	virtual void profileSectionName(const char *fmt,...) = 0; // The 'printf' style specification for the section name, followed by varargs

	/**
	\brief This method is used to indicate when a 'frame' has been processed.  Execute this method exactly once per frame.
	*/
	virtual void profileFrame(void) = 0;

	/**
	\brief This method is used to generate a report, on disk, of the current state of all memory allocations.  Returns true if a report was generated (i.e. leaks on exit)
	*/
	virtual bool memoryReport(MemoryReportFormat format,		// The format to output the report in.
							const char *reportName,				// The name of the file on disk to save.
							bool reportAllLeaks) = 0;			// Whether or not to output every single memory leak.  *WARNING* Only enable this if you know you wish to identify a specific limited number of memory leaks. 

	/**
	\brief This method is used to generate a memory usage report in memory.  If it returns NULL then no active memory blocks are registered. (i.e. no leaks on application exit.
	*/
	virtual const void * memoryReport(MemoryReportFormat format,	// The format to output the report in.
									const char *reportName,			// The name of the report.
									bool reportAllLeaks,			// Whether or not to output every single memory leak.  *WARNING* Only enable this if you know you wish to identify a specific limited number of memory leaks. 
									physx::PxU32 &reportSize) = 0;	// The size of the output report.

	/**
	\brief Releases the memory allocated for a previous memory report.
	*/
	virtual void		releaseMemoryReport(const void *reportData) = 0;


	/**
	\brief Indicate that an object has been constructed (DejaInsight feature only)
	*/
	virtual void	objectInit(void *mem,					// Address of the object.
								const char *object,			// The name of the object.
								const char *fileName,		// The source code file name where the object was constructed.
								physx::PxU32 lineno) = 0;	// The source code line number where the object was constructed.

	/**
	\brief Indicate that an object has been destroyed (DejaInsight feature only)
	*/
	virtual void	objectKill(void *mem,					// The address of the object being destroyed
								const char *fileName,		// The source code file name where the object was destoryed
								physx::PxU32 lineno) = 0;	// The source code line number where the object was destroyed

	/**
	\brief Indicate that an array of objects has been constructed (DejaInsight feature only)
	*/
	virtual void	objectInitArray(void *mem,				// The address of the array of objects.
									size_t objectSize,		// The size of each individual object.
									size_t objectCount,		// The number of objects in the array.
									const char *object,		// The name of the object.
									const char *fileName,	// The source code file name where the array of objects was created.
									physx::PxU32 lineno) = 0;	// The source code line number where the array of objects was created.

	/**
	\brief Indicate that an array of objects has been destroyed (DejaInsight feature only.)
	*/
	virtual void	objectKillArray(void *mem,
									const char *fileName,
									physx::PxU32 lineno) = 0;

	/**
	\brief Processes a buffer of CUDA data events.  PVD only.
	*/
	virtual void profileCUDABuffer(physx::PxF32 elapsedTimeInMilliseconds,
		const physx::PxU8 *data,
		physx::PxU32 dataSize,
		CUDAProfileEventType type) = 0;

	/**
	\brief Enables or disables the profiler from tracking data.  Does not affect memory tracking; only profiling events.
	*/
	virtual void setProfilerActive(bool state) = 0; 

	/**
	\brief Reports whether or not the profiler is currently active.
	*/
	virtual bool getProfilerActive(void) const = 0;	

	/**
	\brief Releases this PxUserProfilerCallback interface
	*/
	virtual void release(void) = 0;

	/**
	\brief Processes a single data point to be plotted by the profiler. 
	*/
	virtual void	profilePlot(PlotType type,				// How to display/format the data.
								physx::PxF32 value,			// The data value to plot.
								const char *name) = 0;		// The name of the data item.

	/**
	\brief Processes a single data point to be plotted by the profiler. 
	*/
	virtual void	profilePlot(PlotType type,				// How to display/format the data.
								physx::PxF64 value,			// The data value to plot.
								const char *name) = 0;		// The name of the data item.

	/**
	\brief Processes a single data point to be plotted by the profiler. 
	*/
	virtual void	profilePlot(PlotType type,				// How to display/format the data.
								physx::PxU64 value,			// The data value to plot.
								const char *name) = 0;		// The name of the data item.

	/**
	\brief Processes a single data point to be plotted by the profiler. 
	*/
	virtual void	profilePlot(PlotType type,				// How to display/format the data.
								physx::PxI64 value,			// The data value to plot.
								const char *name) = 0;		// The name of the data item.

		/**
	\brief Processes a single data point to be plotted by the profiler. 
	*/
	virtual void	profilePlot(PlotType type,				// How to display/format the data.
								physx::PxU32 value,			// The data value to plot.
								const char *name) = 0;		// The name of the data item.

	/**
	\brief Processes a single data point to be plotted by the profiler. 
	*/
	virtual void	profilePlot(PlotType type,				// How to display/format the data.
								physx::PxI32 value,			// The data value to plot.
								const char *name) = 0;		// The name of the data item.


	/**
	\brief Sets the handle/pointer to the current 3rd party profiler SDK
	*/
	virtual void	setProfilerHandle(Type type,void *context) = 0;

	/**
	\brief Retrieves the handle to the 3rd party profiler SDK
	*/
	virtual void	*getProfilerHandle(void) = 0;

	/**
	\brief Reports the 'Type' of 3rd party profiler SDK being used.
	*/
	virtual Type	getProfilerType(void) = 0;

	virtual ~PxUserProfilerCallback() {}

};

extern PxUserProfilerCallback *gPxUserProfilerCallback;

}; // end of USER_PROFILER_ANAYLZER namespace


class PxUserProfilerCallbackProfileEvent
{
public:
	PxUserProfilerCallbackProfileEvent(const char *name,physx::PxU64 context,const char *fileName,physx::PxU32 lineno)
	{
		mEventName = name;
		mContext = context;
		PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileBegin(name,context,fileName,lineno);
	}

	PxUserProfilerCallbackProfileEvent(physx::PxI32 dataItem,const char *name,physx::PxU64 context,const char *fileName,physx::PxU32 lineno)
	{
		mEventName = name;
		mContext = context;
		PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileBegin(name,context,fileName,lineno);
		PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileStat(name,context,dataItem,fileName,lineno);
	}


	~PxUserProfilerCallbackProfileEvent(void)
	{
		PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileEnd(mEventName,mContext);
	}
private:
	const char		*mEventName;
	physx::PxU64	mContext;
};


#define PX_USER_PROFILER_PLOT PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profilePlot
#define PX_USER_PROFILER_MESSAGE_CHANNEL PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileMessageChannel
#define PX_USER_PROFILER_PERF_SCOPE(name) PxUserProfilerCallbackProfileEvent _pe(name,0,__FILE__,__LINE__)
#define PX_USER_PROFILER_PERF_DSCOPE(name,data) PxUserProfilerCallbackProfileEvent _pe(data,name,0,__FILE__,__LINE__)
#define PX_USER_PROFILER_PERF_SCOPE_CONTEXT(name,context) PxUserProfilerCallbackProfileEvent _pe(name,context,__FILE__,__LINE__)
#define PX_USER_PROFILER_FRAME() PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileFrame();
#define PX_USER_PROFILER_SECTION_NAME(x) PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileSectionName(x);
#define PX_USER_PROFILER_CALLBACK_RELEASE() if ( PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback ) { PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->release(); PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback = NULL; }
#define PX_USER_PROFILER_MEMORY_REPORT(x,y,z) PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->memoryReport(x,y,z)

#define PX_USER_PROFILER_STAT(x,y) PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileStat()
#define PX_USER_PROFILER_START_EVENT(x,y) PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileBegin(x,y,__FILE__,__LINE__)
#define PX_USER_PROFILER_STOP_EVENT(x,y) PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileEnd(x,y)

#define PX_USER_PROFILER_START_EVENT_THREADID(x,y,z) PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileBegin(x,y,z,__FILE__,__LINE__)
#define PX_USER_PROFILER_STOP_EVENT_THREADID(x,y,z) PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->profileEnd(x,y,z)

#define PX_USER_PROFILER_RELEASE if ( PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback ) { PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback->release(); PX_USER_PROFILER_CALLBACK::gPxUserProfilerCallback = NULL; };

#else

#define PX_USER_PROFILER_PLOT
#define PX_USER_PROFILER_MESSAGE_CHANNEL
#define PX_USER_PROFILER_PERF_SCOPE(name)
#define PX_USER_PROFILER_PERF_DSCOPE(name,data)
#define PX_USER_PROFILER_PERF_SCOPE_CONTEXT(name,context)
#define PX_USER_PROFILER_FRAME()
#define PX_USER_PROFILER_SECTION_NAME(x)
#define PX_USER_PROFILER_CALLBACK_RELEASE()
#define PX_USER_PROFILER_MEMORY_REPORT(x,y,z)

#define PX_USER_PROFILER_STAT(x,y)
#define PX_USER_PROFILER_START_EVENT(x,y)
#define PX_USER_PROFILER_STOP_EVENT(x,y)

#define PX_USER_PROFILER_START_EVENT_THREADID(x,y,z)
#define PX_USER_PROFILER_STOP_EVENT_THREADID(x,y,z)

#define PX_USER_PROFILER_RELEASE

namespace PX_USER_PROFILER_CALLBACK
{
	class PxUserProfilerCallback
	{
	public:
	/**
	\brief The layout format for the memory report.
	*/
	enum MemoryReportFormat
	{
		MRF_SIMPLE_HTML,       // just a very simple HTML document containing the tables.
		MRF_CSV,               // Saves the Tables out as comma seperated value text
		MRF_TEXT,              // Saves the tables out in human readable text format.
		MRF_TEXT_EXTENDED,     // Saves the tables out in human readable text format, but uses the MS-DOS style extended ASCII character set for the borders.
	};
	/**
	\brief This enumeration determines which underlying profiling SDK to use
	*/
	enum Type
	{
		PT_NONE,				// no profiling, just memory tracking.
		PT_TELEMETRY,			// use Telemetry from Rad Game Tools
		PT_DEJA_INSIGHT,		// use DejaInsight from DejaTools
		PT_PVD,					// uses PVD from NVIDIA
		PT_NSIGHT,				// Use Parallel Insight from NVIDIA
		PT_USER_API,			// The underlying profiling implentation is a custom version written by the developer.
	};
	/**
	\brief This enumeration determines how a graphics data plot should be displayed.
	*/
	enum PlotType
	{
		PT_FLOAT = 0,
		PT_MEMORY = 1,
		PT_HEX = 2,
		PT_INTEGER = 3,
		PT_PERCENTAGE_COMPUTED = 4,
		PT_PERCENTAGE_DIRECT = 5,
		PT_TIME = 6,
		PT_TIME_MS = 7,
		PT_LAST
	};
	/**
	\brief This enumeration determines how a profile message will be highlighted
	*/
	enum MessageChannelType
	{
		MCT_LOG			= 0x0001,
		MCT_WARNING		= 0x0002,
		MCT_ERROR		= 0x0004,
		MCT_EXCLAMATION	= 0x1000,
		MCT_NOTE		= 0x2000,
		MCT_QUESTION	= 0x3000,
	};

	};


};

#endif // end if disable profiler

/** @} */

#endif // PX_FOUNDATION_PX_USER_PROFILER_CALLBACK_H
