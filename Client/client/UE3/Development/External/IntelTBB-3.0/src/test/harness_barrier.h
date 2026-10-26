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

#include "tbb/atomic.h"

#ifndef harness_barrier_H
#define harness_barrier_H

namespace Harness {

class SpinBarrier
{
    unsigned numThreads;
    tbb::atomic<unsigned> numThreadsFinished; /* threads reached barrier in this epoch */
    tbb::atomic<unsigned> epoch;   /* how many times this barrier used - XXX move to a separate cache line */

    struct DummyCallback {
        void operator() () const {}
    };

    SpinBarrier( const SpinBarrier& );    // no copy ctor
    void operator=( const SpinBarrier& ); // no assignment 
public:
    SpinBarrier( unsigned nthreads = 0 ) { initialize(nthreads); };

    void initialize( unsigned nthreads ) {
        numThreads = nthreads;
        numThreadsFinished = 0;
        epoch = 0;
    };

    // onOpenBarrierCallback is called by last thread arrived on a barrier
    template<typename Callback>
    bool wait(const Callback &onOpenBarrierCallback)
    { // return true if last thread
        unsigned myEpoch = epoch;
        int threadsLeft = numThreads - numThreadsFinished.fetch_and_increment() - 1;
        ASSERT(threadsLeft>=0, "Broken barrier");
        if (threadsLeft > 0) {
            /* not the last threading reaching barrier, wait until epoch changes & return 0 */
            tbb::internal::spin_wait_while_eq(epoch, myEpoch);
            return false;
        }
        /* No more threads left to enter, so I'm the last one reaching this epoch;
           reset the barrier, increment epoch, and return non-zero */
        onOpenBarrierCallback();
        numThreadsFinished = 0;
        epoch = myEpoch+1; /* wakes up threads waiting to exit this epoch */
        return true;
    }
    bool wait()
    {
        return wait(DummyCallback());
    }
};

}

#endif //harness_barrier_H
