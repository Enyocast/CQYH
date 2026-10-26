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

/**
    The test checks that for different ranges of random numbers (from 0 to 
    [MinThread, MaxThread]) generated with different seeds the probability 
    of each number in the range deviates from the ideal random distribution
    by no more than AcceptableDeviation percent.
**/

#include "harness_inject_scheduler.h"

#define HARNESS_DEFAULT_MIN_THREADS 2
#define HARNESS_DEFAULT_MAX_THREADS 32

#define TEST_TOTAL_SEQUENCE 0

#include "harness.h"
#include "tbb/atomic.h"

//! Coefficient defining tolerable deviation from ideal random distribution
const double AcceptableDeviation = 2.1;
//! Tolerable probability of failure to achieve tolerable distribution
const double AcceptableProbabilityOfOutliers = 1e-6;
//! Coefficient defining the length of random numbers series used to estimate the distribution
/** Number of random values generated per each range element. I.e. the larger is 
    the range, the longer is the series of random values. **/
const uintptr_t SeriesBaseLen = 100;
//! Number of random numbers series to generate
const uintptr_t NumSeries = 100;
//! Number of random number generation series with different seeds
const uintptr_t NumSeeds = 100;

tbb::atomic<uintptr_t> NumHighOutliers;
tbb::atomic<uintptr_t> NumLowOutliers;

inline void CheckProbability ( double probability, double expectedProbability, int index, int numIndices ) {
    double lowerBound = expectedProbability / AcceptableDeviation,
           upperBound = expectedProbability * AcceptableDeviation;
    if ( probability < lowerBound ) {
        if ( !NumLowOutliers )
            REMARK( "Warning: Probability %.3f of hitting index %d among %d elements is out of acceptable range (%.3f - %.3f)\n",
                    probability, index, numIndices, lowerBound, upperBound );
        ++NumLowOutliers;
    }
    else if ( probability > upperBound ) {
        if ( !NumHighOutliers )
            REMARK( "Warning: Probability %.3f of hitting index %d among %d elements is out of acceptable range (%.3f - %.3f)\n",
                    probability, index, numIndices, lowerBound, upperBound );
        ++NumHighOutliers;
    }
}

struct CheckDistributionBody {
    void operator() ( int id ) const {
        uintptr_t randomRange = id + MinThread;
        uintptr_t *curHits = new uintptr_t[randomRange]
#if TEST_TOTAL_SEQUENCE
                , *totalHits = new uintptr_t[randomRange]
#endif
        ;
        double expectedProbability = 1./randomRange;
        // Loop through different seeds
        for ( uintptr_t i = 0; i < NumSeeds; ++i ) {
            // Seed value is selected in two ways, the first of which mimics 
            // the one used by the TBB task scheduler
            void* seed = i % 2 ? (char*)&curHits + i * 16 : (void*)(i * 8);
            tbb::internal::FastRandom random( (unsigned)(uintptr_t)seed );
            memset( curHits, 0, randomRange * sizeof(uintptr_t) );
#if TEST_TOTAL_SEQUENCE
            memset( totalHits, 0, randomRange * sizeof(uintptr_t) );
#endif
            const uintptr_t seriesLen = randomRange * SeriesBaseLen,
                            experimentLen = NumSeries * seriesLen;
            uintptr_t *curSeries = new uintptr_t[seriesLen],  // circular buffer
                       randsGenerated = 0;
            // Initialize statistics
            while ( randsGenerated < seriesLen ) {
                uintptr_t idx = random.get() % randomRange;
                ++curHits[idx];
#if TEST_TOTAL_SEQUENCE
                ++totalHits[idx];
#endif
                curSeries[randsGenerated++] = idx;
            }
            while ( randsGenerated < experimentLen ) {
                for ( uintptr_t j = 0; j < randomRange; ++j ) {
                    CheckProbability( double(curHits[j])/seriesLen, expectedProbability, j, randomRange );
#if TEST_TOTAL_SEQUENCE
                    CheckProbability( double(totalHits[j])/randsGenerated, expectedProbability, j, randomRange );
#endif
                }
                --curHits[curSeries[randsGenerated % seriesLen]];
                int idx = random.get() % randomRange;
                ++curHits[idx];
#if TEST_TOTAL_SEQUENCE
                ++totalHits[idx];
#endif
                curSeries[randsGenerated++ % seriesLen] = idx;
            }
            delete [] curSeries;
        }
        delete [] curHits;
#if TEST_TOTAL_SEQUENCE
        delete [] totalHits;
#endif
    }
};

#include "tbb/tbb_thread.h"

int TestMain () {
    ASSERT( AcceptableDeviation < 100, NULL );
    MinThread = max(MinThread, 2);
    MaxThread = max(MinThread, MaxThread);
    double NumChecks = double(NumSeeds) * (MaxThread - MinThread + 1) * (MaxThread + MinThread) / 2.0 * (SeriesBaseLen * NumSeries - SeriesBaseLen);
    REMARK( "Number of distribution quality checks %g\n", NumChecks );
    NumLowOutliers = NumHighOutliers = 0;
    // Parallelism is used in this test only to speed up the long serial checks
    // Essentially it is a loop over random number ranges
    // Ideally tbb::parallel_for could be used to parallelize the outermost loop 
    // in CheckDistributionBody, but it is not used to avoid unit test contamination.
    int P = tbb::tbb_thread::hardware_concurrency();
    while ( MinThread <= MaxThread ) {
        NativeParallelFor( min(P, MaxThread - MinThread + 1), CheckDistributionBody() );
        MinThread += P;
    }
    double observedProbabilityOfOutliers = (NumLowOutliers + NumHighOutliers) / NumChecks;
    if ( observedProbabilityOfOutliers > AcceptableProbabilityOfOutliers ) {
        if ( NumLowOutliers )
            REPORT( "Warning: %d cases of too low probability of a given number detected\n", (int)NumLowOutliers );
        if ( NumHighOutliers )
            REPORT( "Warning: %d cases of too high probability of a given number detected\n", (int)NumHighOutliers );
        ASSERT( observedProbabilityOfOutliers <= AcceptableProbabilityOfOutliers, NULL );
    }
    return Harness::Done;
}
