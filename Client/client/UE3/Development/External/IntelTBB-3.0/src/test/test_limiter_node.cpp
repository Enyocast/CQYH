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
#include "tbb/atomic.h"
#include "tbb/task_scheduler_init.h"

const int L = 10;
const int N = 1000;

template< typename T >
struct serial_receiver : public tbb::receiver<T> {
   T next_value;

   serial_receiver() : next_value(T(0)) {}

   /* override */ bool try_put( T v ) {
       ASSERT( next_value++  == v, NULL );
       return true;
   }
};

template< typename T >
struct parallel_receiver : public tbb::receiver<T> {

   tbb::atomic<int> my_count;

   parallel_receiver() { my_count = 0; }

   /* override */ bool try_put( T ) {
       ++my_count;
       return true;
   }
};

template< typename T >
struct empty_sender : public tbb::sender<T> {
        /* override */ bool register_successor( tbb::receiver<T> & ) { return false; }
        /* override */ bool remove_successor( tbb::receiver<T> & ) { return false; }
};


template< typename T >
struct put_body : NoAssign {

    tbb::limiter_node<T> &my_lim;
    tbb::atomic<int> &my_accept_count;

    put_body( tbb::limiter_node<T> &lim, tbb::atomic<int> &accept_count ) : 
        my_lim(lim), my_accept_count(accept_count) {}

    void operator()( int ) const {
        for ( int i = 0; i < L; ++i ) {
            bool msg = my_lim.try_put( T(i) );
            if ( msg == true )
               ++my_accept_count; 
        }
    }
};

template< typename T >
struct put_dec_body : NoAssign {

    tbb::limiter_node<T> &my_lim;
    tbb::atomic<int> &my_accept_count;

    put_dec_body( tbb::limiter_node<T> &lim, tbb::atomic<int> &accept_count ) : 
        my_lim(lim), my_accept_count(accept_count) {}

    void operator()( int ) const {
        int local_accept_count = 0;
        while ( local_accept_count < N ) {
            bool msg = my_lim.try_put( T(local_accept_count) );
            if ( msg == true ) {
                ++local_accept_count;
                ++my_accept_count;
                my_lim.decrement.try_put( tbb::continue_msg() );
            } 
        }
    }

};

//
// Tests
//
// limiter only forwards below the limit, multiple parallel senders / single receiver
// mutiple parallel senders that put to decrement at each accept, limiter accepts new messages
// 
// 
template< typename T >
int test_parallel(int num_threads) {
 
   // test puts with no decrements
   for ( int i = 0; i < L; ++i ) {
       tbb::graph g;
       tbb::limiter_node< T > lim(g, i);
       parallel_receiver<T> r;
       tbb::atomic<int> accept_count;
       accept_count = 0;
       lim.register_successor( r );
       // test puts with no decrements
       NativeParallelFor( num_threads, put_body<T>(lim, accept_count) );
       g.wait_for_all();
       int c = accept_count;
       ASSERT( c == i, NULL );
   }

   // test puts with decrements
   for ( int i = 1; i < L; ++i ) {
       tbb::graph g;
       tbb::limiter_node< T > lim(g, i);
       parallel_receiver<T> r;
       empty_sender< tbb::continue_msg > s;
       tbb::atomic<int> accept_count;
       accept_count = 0;
       lim.register_successor( r );
       lim.decrement.register_predecessor( s );
       // test puts with no decrements
       NativeParallelFor( num_threads, put_dec_body<T>(lim, accept_count) );
       int c = accept_count;
       ASSERT( c == N*num_threads, NULL );
       ASSERT( r.my_count == N*num_threads, NULL );
   }

   return 0;
}

//
// Tests
//
// limiter only forwards below the limit, single sender / single receiver
// at reject, a put to decrement, will cause next message to be accepted
// 
template< typename T >
int test_serial() {
 
   // test puts with no decrements
   for ( int i = 0; i < L; ++i ) {
       tbb::graph g;
       tbb::limiter_node< T > lim(g, i);
       serial_receiver<T> r;
       lim.register_successor( r );
       for ( int j = 0; j < L; ++j ) {
           bool msg = lim.try_put( T(j) );
           ASSERT( ( j < i && msg == true ) || ( j >= i && msg == false ), NULL );
       }
       g.wait_for_all();
   }

   // test puts with decrements
   for ( int i = 1; i < L; ++i ) {
       tbb::graph g;
       tbb::limiter_node< T > lim(g, i);
       serial_receiver<T> r;
       empty_sender< tbb::continue_msg > s;
       lim.register_successor( r );
       lim.decrement.register_predecessor( s );
       for ( int j = 0; j < N; ++j ) {
           bool msg = lim.try_put( T(j) );
           ASSERT( ( j < i && msg == true ) || ( j >= i && msg == false ), NULL );
           if ( msg == false ) {
               lim.decrement.try_put( tbb::continue_msg() );
               msg = lim.try_put( T(j) );
               ASSERT( msg == true, NULL );
           }
       }
   }
   return 0;
}

int TestMain() { 
    for (int i = 1; i <= 8; ++i) {
        tbb::task_scheduler_init init(i);
        test_serial<int>();
        test_parallel<int>(i);
    }
   return Harness::Done;
}
