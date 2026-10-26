/*
    Copyright 2005-2011 Intel Corporation.  All Rights Reserved.

    The source code contained or described herein and all documents related
    to the source code ("Material") are owned by Intel Corporation or its
    suppliers or licensors.  Title to the Material remains with Intel
    Corporation or its suppliers and licensors.  The Material is protected
    by worldwide copyright laws and treaty provisions.  No part of the
    Material may be used, copied, reproduced, modified, published, uploaded,
    posted, transmitted, distributed, or disclosed in any way without
    Intel's prior express written permission.

    No license under any patent, copyright, trade secret or other
    intellectual property right is granted to or conferred upon you by
    disclosure or delivery of the Materials, either expressly, by
    implication, inducement, estoppel or otherwise.  Any license under such
    intellectual property rights must be express and approved by Intel in
    writing.
*/

#include "harness.h"
#include "tbb/task.h"
#include "tbb/task_scheduler_init.h"

const int NumRepeats = 200;
const int MaxNumThreads = 16;
static volatile bool Finished[MaxNumThreads] = {};

static volatile bool CanStart;

//! Custom user task interface
class ITask {
public: 
	virtual ~ITask() {} 
	virtual void Execute() = 0;
	virtual void Release() { delete this; }
};

class TestTask : public ITask {
	volatile bool *m_pDone;
public:
    TestTask ( volatile bool *pDone ) : m_pDone(pDone) {}

	/* override */ void Execute() {
		*m_pDone = true;
	}
};

class CarrierTask : public tbb::task {
	ITask* m_pTask;
public:
    CarrierTask(ITask* pTask) : m_pTask(pTask) {}

	/*override*/ task* execute() {
		m_pTask->Execute();
		m_pTask->Release();
		return NULL;
	}
};

class SpawnerTask : public ITask {
	ITask* m_taskToSpawn;
public:
	SpawnerTask(ITask* job) : m_taskToSpawn(job) {}

	void Execute() {
		while ( !CanStart )
		    __TBB_Yield();
		tbb::task::enqueue( *new( tbb::task::allocate_root() ) CarrierTask(m_taskToSpawn) );
	}
};

class EnqueuerBody {
public:
    void operator() ( int id ) const {
	    tbb::task_scheduler_init init(tbb::task_scheduler_init::default_num_threads() + 1);

	    SpawnerTask* pTask = new SpawnerTask( new TestTask(Finished + id) );
	    tbb::task::enqueue( *new( tbb::task::allocate_root() ) CarrierTask(pTask) );
    }
};

//! Regression test for a bug that caused premature arena destruction
void TestCascadedEnqueue () {
	tbb::task_scheduler_init init(tbb::task_scheduler_init::default_num_threads() + 1);

    int minNumThreads = min(tbb::task_scheduler_init::default_num_threads(), MaxNumThreads) / 2;
	int maxNumThreads = min(tbb::task_scheduler_init::default_num_threads() * 2, MaxNumThreads);

	for ( int numThreads = minNumThreads; numThreads <= maxNumThreads; ++numThreads ) {
		for ( int i = 0; i < NumRepeats; ++i ) {
			CanStart = false;
            __TBB_Yield();
			NativeParallelFor( numThreads, EnqueuerBody() );
			CanStart = true;
            int j = 0;
			while ( j < numThreads ) {
                if ( Finished[j] )
                    ++j;
                else
    				__TBB_Yield();
			}
            for ( j = 0; j < numThreads; ++j )
                Finished[j] = false;
            REMARK("%02d threads; Iteration %03d\r", numThreads, i);
		}
	}
    REMARK( "                                 \r" );
}

class DummyTask : public tbb::task {
public:
    task *execute() {
        Harness::Sleep(1);
        return NULL;
    }
};

class SharedRootBody {
    tbb::task *my_root;
public:
	SharedRootBody ( tbb::task *root ) : my_root(root) {}

	void operator() ( int ) const {
	    tbb::task::enqueue( *new( tbb::task::allocate_additional_child_of(*my_root) ) DummyTask );
	}
};

//! Test for enqueuing children of the same root from different master threads
void TestSharedRoot () { 
    for ( int p = MinThread; p <= MaxThread; ++p ) {
        tbb::task_scheduler_init init(p);
    	tbb::task *root =  new ( tbb::task::allocate_root() ) tbb::empty_task; 
    	root->set_ref_count(1);
        for( int n = MinThread; n <= MaxThread; ++n )
            NativeParallelFor( n, SharedRootBody(root) );
    	root->wait_for_all();
        tbb::task::destroy(*root);
    } 
}


int TestMain () {
    TestCascadedEnqueue();
    TestSharedRoot();
    return Harness::Done;
}
