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

#ifndef _TBB_observer_proxy_H
#define _TBB_observer_proxy_H

#if __TBB_SCHEDULER_OBSERVER

#include "tbb/task_scheduler_observer.h"

namespace tbb {
namespace internal {

class observer_proxy {
    friend class task_scheduler_observer_v3;
    //! Reference count used for garbage collection.
    /** 1 for reference from my task_scheduler_observer.
        1 for each my_local_last_observer_proxy that points to me. 
        No accounting for predecessor in the global list. 
        No accounting for global_last_observer_proxy that points to me. */
    atomic<int> gc_ref_count;
    //! Pointer to next task_scheduler_observer 
    /** Valid even when *this has been removed from the global list. */
    observer_proxy* next; 
    //! Pointer to previous task_scheduler_observer in global list.
    observer_proxy* prev; 
    //! Associated observer
    task_scheduler_observer* observer;
    //! Account for removing reference from p.  No effect if p is NULL.
    void remove_ref_slow();
    void remove_from_list(); 
    observer_proxy( task_scheduler_observer_v3& wo ); 
public:
    static observer_proxy* process_list( observer_proxy* local_last, bool is_worker, bool is_entry );
};

extern observer_proxy* global_last_observer_proxy;

} // namespace internal
} // namespace tbb

#endif /* __TBB_SCHEDULER_OBSERVER */

#endif /* _TBB_observer_proxy_H */
