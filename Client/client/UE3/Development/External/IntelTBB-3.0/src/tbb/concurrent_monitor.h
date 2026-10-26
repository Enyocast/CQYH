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

#ifndef __TBB_concurrent_monitor_H
#define __TBB_concurrent_monitor_H

#include "tbb/tbb_stddef.h"
#include "tbb/atomic.h"
#include "tbb/spin_mutex.h"
#include "semaphore.h"

namespace tbb {
namespace internal {

//! Circular doubly-linked list with sentinel
/** head.next points to the front and  head.prev points to the back */
class circular_doubly_linked_list_with_sentinel : no_copy {
public:  
    struct node_t {
        node_t* next;  
        node_t* prev;  
        node_t() : next(NULL), prev(NULL) {}
    };

    // ctor
    circular_doubly_linked_list_with_sentinel() {clear();}
    // dtor
    ~circular_doubly_linked_list_with_sentinel() {__TBB_ASSERT( head.next==&head && head.prev==&head, "the list is not empty" );}
    
    inline size_t  size() const {return count;}
    inline bool    empty()  const {return size()==0;}
    inline node_t* front()  const {return head.next;}
    inline node_t* last()   const {return head.prev;}
    inline node_t* begin()  const {return front();}
    inline const node_t* end() const {return &head;}

    //! add to the back of the list
    inline void add( node_t* n ) {
        count = count + 1;
        n->prev = head.prev;  
        n->next = &head;  
        head.prev->next = n;  
        head.prev = n;
    }
  
    //! remove node 'n' from the 'this' list
    inline void remove( node_t& n ) {
        count = count - 1;
        n.prev->next = n.next;
        n.next->prev = n.prev;
    }  

    //! move all elements to 'lst' and initiallize the 'this' list
    inline void flush_to( circular_doubly_linked_list_with_sentinel& lst ) {
        if( count>0 ) {  
            lst.count = count;
            lst.head.next = head.next;  
            lst.head.prev = head.prev;
            head.next->prev = &lst.head;
            head.prev->next = &lst.head;
            clear();
        }
    }
  
#if !TBB_USE_DEBUG
private:  
#endif
    atomic<size_t> count;
    node_t head;
    void clear() {count = 0; head.next = &head; head.prev = &head;}
};

typedef circular_doubly_linked_list_with_sentinel waitset_t;
typedef circular_doubly_linked_list_with_sentinel dllist_t;
typedef circular_doubly_linked_list_with_sentinel::node_t waitset_node_t;

class concurrent_monitor;

//! concurrent_monitor
/** fine-grained concurrent_monitor implementation */
class concurrent_monitor : no_copy {
public:
    /** per-thread descriptor for concurrent_monitor */
    class thread_context : waitset_node_t, no_copy {
        friend class concurrent_monitor;
    public:
        thread_context() : spurious(false), context(NULL) {epoch = 0; in_waitset = false;}
        ~thread_context() { if( spurious ) sema.P(); }
    private:
        semaphore   sema;
        tbb::atomic<unsigned> epoch;
        tbb::atomic<bool>     in_waitset;
        bool         spurious;
        void*        context;
    };

    //! ctor
    concurrent_monitor() {epoch = 0;}

    //! prepare wait by inserting 'thr' into the wailt queue
    void prepare_wait( thread_context& thr, void* ctx = 0 );

    //! Commit wait if even count has not changed; otherwise, cancel wait.
    /** Returns true of commited; false if canceled. */
    inline bool commit_wait( thread_context& thr ) {
        bool do_it = thr.epoch==epoch;
        // this check is just an optimization
        if( do_it ) {
            thr.sema.P();
            __TBB_ASSERT( !thr.in_waitset, "still in the queue?" );
        } else {
            cancel_wait( thr );
        }
        return do_it;
    }
    //! Cancel the wait. Removes the thread from the wait queue if not removed yet.
    void cancel_wait( thread_context& thr );

    //! Notify one thread about the event
    void notify_one() {atomic_fence(); notify_one_relaxed();}
 
    //! Notify one thread about the event. Relaxed version.
    void notify_one_relaxed();

    //! Notify all waiting threads of the event
    void notify_all() {atomic_fence(); notify_all_relaxed();}
 
    //! Notify all waiting threads of the event; Relaxed version
    void notify_all_relaxed();

    //! Notify waiting threads of the event that satisfies the given predicate
    template<typename P> void notify( const P& predicate ) {atomic_fence(); notify_relaxed( predicate );}
 
    //! Notify waiting threads of the event that satisfies the given predicate; Relaxed version
    template<typename P> void notify_relaxed( const P& predicate );

private:
    tbb::spin_mutex mutex_ec;
    waitset_t       waitset_ec;
    tbb::atomic<unsigned> epoch;
    thread_context* to_thread_context( waitset_node_t* n ) { return static_cast<thread_context*>(n); }
};

template<typename P> 
void concurrent_monitor::notify_relaxed( const P& predicate ) {
        if( waitset_ec.size()==0 )
            return;
        dllist_t temp;
        waitset_node_t* nxt;
        const waitset_node_t* end = waitset_ec.end();
        {
            tbb::spin_mutex::scoped_lock l( mutex_ec );
            epoch = epoch + 1;
            for( waitset_node_t* n=waitset_ec.last(); n!=end; n=nxt ) {
                nxt = n->prev;
                thread_context* thr = to_thread_context( n );
                if( predicate( thr->context ) ) {
                    waitset_ec.remove( *n );
                    thr->in_waitset = false;
                    temp.add( n );
                }
            }
        }
    
        end = temp.end();
        for( waitset_node_t* n=temp.front(); n!=end; n=nxt ) {
            nxt = n->next;
            to_thread_context(n)->sema.V();
        }
#if TBB_USE_DEBUG
        temp.clear();
#endif
}

} // namespace internal
} // namespace tbb

#endif /* __TBB_concurrent_monitor_H */
