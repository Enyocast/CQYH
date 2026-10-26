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

//! Performs test on executable nodes with limited concurrency
/** Theses tests check:
    1) that the nodes will accepts puts up to the concurrency limit,
    2) the nodes do not exceed the concurrency limit even when run with more threads (this is checked in the harness_graph_executor), 
    3) the nodes will receive puts from multiple successors simultaneously,
    and 4) the nodes will send to multiple predecessors.
    There is no checking of the contents of the messages for corruption.
*/
     
template< typename InputType, typename OutputType, typename Body >
void concurrency_levels( size_t concurrency, Body body ) {

   for ( size_t lc = 1; lc <= concurrency; ++lc ) { 
   tbb::graph g;
   harness_graph_executor<InputType, OutputType, tbb::spin_mutex>::execute_count = 0;

   tbb::function_node< InputType, OutputType > exe_node( g, lc, body );

   for (size_t num_receivers = 1; num_receivers <= MAX_NODES; ++num_receivers ) {

        harness_counting_receiver<OutputType> *receivers = new harness_counting_receiver<OutputType>[num_receivers];

        for (size_t r = 0; r < num_receivers; ++r ) {
            ASSERT( exe_node.register_successor( receivers[r] ), NULL );
        }

        harness_counting_sender<InputType> *senders = NULL;

        for (size_t num_senders = 1; num_senders <= MAX_NODES; ++num_senders ) {
            {
                // lock m to prevent exe_node from finishing
                tbb::spin_mutex::scoped_lock l( harness_graph_executor< InputType, OutputType, tbb::spin_mutex >::mutex );

                // put to lc level, it will accept and then block at m
                for ( size_t c = 0 ; c < lc ; ++c ) {
                    ASSERT( exe_node.try_put( InputType() ) == true, NULL );
                }
                // it only accepts to lc level
                ASSERT( exe_node.try_put( InputType() ) == false, NULL );

                senders = new harness_counting_sender<InputType>[num_senders];
                for (size_t s = 0; s < num_senders; ++s ) {
                   // register a sender
                   senders[s].my_limit = N;
                   exe_node.register_predecessor( senders[s] );
                }

            } // release lock at end of scope, setting the exe node free to continue
            // wait for graph to settle down
            g.wait_for_all();

            // cofirm that each sender was requested from N times 
            for (size_t s = 0; s < num_senders; ++s ) {
                size_t n = senders[s].my_received;
                ASSERT( n == N, NULL ); 
                ASSERT( senders[s].my_receiver == &exe_node, NULL );
            }
            // cofirm that each receivers got N * num_senders + the initial lc puts
            for (size_t r = 0; r < num_receivers; ++r ) {
                size_t n = receivers[r].my_count;
                ASSERT( n == num_senders*N+lc, NULL );
                receivers[r].my_count = 0;
            }
            delete [] senders;
        }
        for (size_t r = 0; r < num_receivers; ++r ) {
            ASSERT( exe_node.remove_successor( receivers[r] ) == true, NULL );
        }
        ASSERT( exe_node.try_put( InputType() ) == true, NULL );
        g.wait_for_all();
        for (size_t r = 0; r < num_receivers; ++r ) {
            ASSERT( int(receivers[r].my_count) == 0, NULL );
        }
        delete [] receivers;
    }

    }
}

template< typename InputType, typename OutputType >
void run_concurrency_levels( int c ) {
    harness_graph_executor<InputType, OutputType, tbb::spin_mutex>::max_executors = c;
    #if __TBB_LAMBDAS_PRESENT
    concurrency_levels<InputType,OutputType>( c, []( InputType i ) -> OutputType { return harness_graph_executor<InputType, OutputType, tbb::spin_mutex>::func(i); } );
    #endif
    concurrency_levels<InputType,OutputType>( c, &harness_graph_executor<InputType, OutputType, tbb::spin_mutex>::func );
    concurrency_levels<InputType,OutputType>( c, typename harness_graph_executor<InputType, OutputType, tbb::spin_mutex>::functor() );
}


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

//! Performs test on executable nodes with unlimited concurrency
/** Theses tests check:
    1) that the nodes will accept all puts
    2) the nodes will receive puts from multiple predecessors simultaneously,
    and 3) the nodes will send to multiple successors.
    There is no checking of the contents of the messages for corruption.
*/

template< typename InputType, typename OutputType, typename Body >
void unlimited_concurrency( Body body ) {

    for (int p = 1; p < 2*MaxThread; ++p) {
        tbb::graph g;
        tbb::function_node< InputType, OutputType > exe_node( g, tbb::graph::unlimited, body );

        for (size_t num_receivers = 1; num_receivers <= MAX_NODES; ++num_receivers ) {

            harness_counting_receiver<OutputType> *receivers = new harness_counting_receiver<OutputType>[num_receivers];
            harness_graph_executor<InputType, OutputType>::execute_count = 0;

            for (size_t r = 0; r < num_receivers; ++r ) {
                ASSERT( exe_node.register_successor( receivers[r] ), NULL );
            }

            NativeParallelFor( p, parallel_puts<InputType>(exe_node) );
            g.wait_for_all(); 

            // 2) the nodes will receive puts from multiple predecessors simultaneously,
            size_t ec = harness_graph_executor<InputType, OutputType>::execute_count;
            ASSERT( (int)ec == p*N, NULL ); 
            for (size_t r = 0; r < num_receivers; ++r ) {
                size_t c = receivers[r].my_count;
                // 3) the nodes will send to multiple successors.
                ASSERT( (int)c == p*N, NULL );
            }
        }
    }
}

template< typename InputType, typename OutputType >
void run_unlimited_concurrency() {
    harness_graph_executor<InputType, OutputType>::max_executors = 0;
    #if __TBB_LAMBDAS_PRESENT
    unlimited_concurrency<InputType,OutputType>( []( InputType i ) -> OutputType { return harness_graph_executor<InputType, OutputType>::func(i); } );
    #endif
    unlimited_concurrency<InputType,OutputType>( &harness_graph_executor<InputType, OutputType>::func );
    unlimited_concurrency<InputType,OutputType>( typename harness_graph_executor<InputType, OutputType>::functor() );
}

//! Tests limited concurrency cases for nodes that accept data messages
void test_concurrency(int num_threads) {
    tbb::task_scheduler_init init(num_threads);
    run_concurrency_levels<int,int>(num_threads);
    run_concurrency_levels<int,tbb::continue_msg>(num_threads);
    run_unlimited_concurrency<int,int>();
    run_unlimited_concurrency<int,empty_no_assign>();
    run_unlimited_concurrency<empty_no_assign,int>();
    run_unlimited_concurrency<empty_no_assign,empty_no_assign>();
    run_unlimited_concurrency<int,tbb::continue_msg>();
    run_unlimited_concurrency<empty_no_assign,tbb::continue_msg>();
}

int TestMain() { 
    current_executors = 0;
    if( MinThread<1 ) {
        REPORT("number of threads must be positive\n");
        exit(1);
    }
    for( int p=MinThread; p<=MaxThread; ++p ) {
       test_concurrency(p);
   }
   return Harness::Done;
}

