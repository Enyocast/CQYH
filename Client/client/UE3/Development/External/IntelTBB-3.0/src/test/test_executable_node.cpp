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

#include "harness_graph.h"

#include "tbb/task_scheduler_init.h"
#include "tbb/spin_mutex.h"

tbb::spin_mutex global_mutex;

#define N 1000
#define MAX_NODES 4
#define C 8 

struct empty_no_assign : private NoAssign { 
   empty_no_assign() {}
   empty_no_assign( int ) {}
   operator int() { return 0; }
};

template< typename InputType >
struct parallel_puts : private NoAssign {

    tbb::receiver< InputType > * const my_exe_node;

    parallel_puts( tbb::receiver< InputType > &exe_node ) : my_exe_node(&exe_node) {}

    void operator()( int ) const  {
        for ( int i = 0; i < N; ++i ) {
            // the nodes will accept all puts
            ASSERT( my_exe_node->try_put( InputType() ) == true, NULL );
        }
    }

};

template< typename OutputType, typename Body >
void continue_nodes( Body body ) {

    for (int p = 1; p < 2*MaxThread; ++p) {
        tbb::graph g;
        tbb::executable_node< OutputType > exe_node( g, body );
        for (size_t i = 0; i < N; ++i) {
           exe_node.register_predecessor( *reinterpret_cast< tbb::sender< tbb::continue_msg > * >(&exe_node) );
        }

        for (size_t num_receivers = 1; num_receivers <= MAX_NODES; ++num_receivers ) { 
            harness_counting_receiver<OutputType> *receivers = new harness_counting_receiver<OutputType>[num_receivers];
            harness_graph_executor<tbb::continue_msg, OutputType>::execute_count = 0;

            for (size_t r = 0; r < num_receivers; ++r ) {
                ASSERT( exe_node.register_successor( receivers[r] ), NULL );
            }

            NativeParallelFor( p, parallel_puts<tbb::continue_msg>(exe_node) );
            g.wait_for_all(); 

            // 2) the nodes will receive puts from multiple predecessors simultaneously,
            size_t ec = harness_graph_executor<tbb::continue_msg, OutputType>::execute_count;
            ASSERT( (int)ec == p, NULL ); 
            for (size_t r = 0; r < num_receivers; ++r ) {
                size_t c = receivers[r].my_count;
                // 3) the nodes will send to multiple successors.
                ASSERT( (int)c == p, NULL );
            }
        }
    }
}

template< typename OutputType >
void run_continue_nodes() {
    harness_graph_executor< tbb::continue_msg, OutputType>::max_executors = 0;
    #if __TBB_LAMBDAS_PRESENT
    continue_nodes<OutputType>( []( tbb::continue_msg i ) -> OutputType { return harness_graph_executor<tbb::continue_msg, OutputType>::func(i); } );
    #endif
    continue_nodes<OutputType>( &harness_graph_executor<tbb::continue_msg, OutputType>::func );
    continue_nodes<OutputType>( typename harness_graph_executor<tbb::continue_msg, OutputType>::functor() );
}

//! Tests limited concurrency cases for nodes that accept data messages
void test_concurrency(int num_threads) {
    tbb::task_scheduler_init init(num_threads);
    run_continue_nodes<tbb::continue_msg>();
    run_continue_nodes<int>();
    run_continue_nodes<empty_no_assign>();
}

int TestMain() { 
    if( MinThread<1 ) {
        REPORT("number of threads must be positive\n");
        exit(1);
    }
    for( int p=MinThread; p<=MaxThread; ++p ) {
       test_concurrency(p);
   }
   return Harness::Done;
}

