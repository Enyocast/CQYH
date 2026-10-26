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

// Header that sets HAVE_m128 if we have type __m128

#if (__SSE__||_M_IX86) && !defined(__sun)
#include <xmmintrin.h>
#define HAVE_m128 1

//! Class for testing safety of using __m128
/** Uses circuitous logic forces compiler to put __m128 objects on stack while
    executing various methods, and thus tempt it to use aligned loads and stores
    on the stack. */
//  Do not create file-scope objects of the class, because MinGW (as of May 2010)
//  did not always provide proper stack alignment in destructors of such objects.
class ClassWithSSE {
    static const int n = 16;
    __m128 field[n];
    void init( int start );
public:
    ClassWithSSE() {init(-n);} 
    ClassWithSSE( int i ) {init(i);}
    void operator=( const ClassWithSSE& src ) {
        __m128 stack[n];
        for( int i=0; i<n; ++i )
            stack[i^5] = src.field[i];
        for( int i=0; i<n; ++i )
            field[i^5] = stack[i];
    }
    ~ClassWithSSE() {init(-2*n);}
    friend bool operator==( const ClassWithSSE& x, const ClassWithSSE& y ) {
        for( int i=0; i<4*n; ++i )
            if( ((const float*)x.field)[i]!=((const float*)y.field)[i] )
                return false;
        return true;
    }
    friend bool operator!=( const ClassWithSSE& x, const ClassWithSSE& y ) {
        return !(x==y);
    }
};

void ClassWithSSE::init( int start ) {
    __m128 stack[n];
    for( int i=0; i<n; ++i ) {
        // Declaring value as a one-element array instead of a scalar quites 
        // gratuitous warnings about possible use of "value" before it was set.
        __m128 value[1];
        for( int j=0; j<4; ++j )
            ((float*)value)[j] = float(n*start+4*i+j);
        stack[i^5] = value[0];
    }
    for( int i=0; i<n; ++i )
        field[i^5] = stack[i];
}

#endif /* __SSE__||_M_IX86 */
