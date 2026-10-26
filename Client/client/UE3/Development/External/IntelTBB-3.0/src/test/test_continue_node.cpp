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
#define TBB_PREVIEW_GRAPH 1
#include "tbb/graph.h"

#define N 100
#define T 10

struct counting_receiver : public tbb::receiver<tbb::continue_msg> {

    typedef tbb::continue_msg input_type;
    typedef tbb::sender<tbb::continue_msg> predecessor_type;

    tbb::atomic< int > my_count;

    counting_receiver() { my_count = 0; }    

    bool try_put( input_type ) { 
        ++my_count; 
        return true;  
    }

};

#if !__TBB_LAMBDAS_PRESENT
class native_body : tbb::internal::no_assign {
    tbb::continue_node &my_node;

public:

     native_body( tbb::continue_node &n ) : my_node(n) {}
     void operator()( int ) const { 
         my_node.try_put( tbb::continue_msg() ); 
     } 
};
#endif

// Tests
//  
// Test that the node fires after receiving N messages from multiple senders
// Test that the node resets and can be reused
// Test that a successor added after triggering is NOT immediately signalled
// 
int test_parallel_puts() {
    tbb::graph g;
    tbb::continue_node n(g);
    counting_receiver r;
    counting_receiver r2;

    n.register_successor(r);

    for (int i = 0; i < N; ++i) 
        n.register_predecessor( n ); // this is a trick since the predecessor doesn't matter

    for (int t = 0; t < T; ++t)
#if __TBB_LAMBDAS_PRESENT
        NativeParallelFor( N, [&](int) { n.try_put( tbb::continue_msg() ); } );
#else
        NativeParallelFor( N, native_body(n) );
#endif

    g.wait_for_all();
    ASSERT( r.my_count == T, NULL ); 


    n.register_successor(r2);
    ASSERT( r2.my_count == 0, NULL );
    return 0; 
}

//
// Tests
//  
// Test that the node fires after receiving N messages from a single sender
// Test that the node resets and can be reused
// Test that a successor added after triggering is NOT immediately signalled
// 
int test_serial_puts() {
    tbb::graph g;
    tbb::continue_node n(g);
    counting_receiver r;
    counting_receiver r2;

    n.register_successor(r);

    for (int i = 0; i < N; ++i) 
        n.register_predecessor( n ); // this is a trick since the predecessor doesn't matter

    for (int t = 0; t < T; ++t)
        for (int i = 0; i < N; ++i)
            n.try_put( tbb::continue_msg() );

    g.wait_for_all();
    ASSERT( r.my_count == T, NULL ); 

    n.register_successor(r2);
    ASSERT( r2.my_count == 0, NULL );
    return 0; 
}

int TestMain() { 
   test_serial_puts();
   test_parallel_puts();
   return Harness::Done;
}

