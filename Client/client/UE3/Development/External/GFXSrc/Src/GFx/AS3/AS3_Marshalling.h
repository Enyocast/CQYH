/**************************************************************************

Filename    :   AS3_Marshalling.h
Content     :   
Created     :   Dec, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#ifndef INC_AS3_MARSHALLING_H
#define INC_AS3_MARSHALLING_H

namespace Scaleform { namespace GFx { namespace AS3
{

///////////////////////////////////////////////////////////////////////////
template <typename T>
struct Clean
{
    typedef T type;
};

template <typename T>
struct Clean<const T>
{
    typedef T type;
};

template <typename T>
struct Clean<T&>
{
    typedef T type;
};

template <typename T>
struct Clean<const T&>
{
    typedef T type;
};

///////////////////////////////////////////////////////////////////////////
template <typename T>
SF_INLINE
typename Clean<T>::type DefaultValue(StringManager&)
{
    return NULL;
}

template <>
SF_INLINE
void DefaultValue<void>(StringManager&)
{
}

template <>
SF_INLINE
bool DefaultValue<bool>(StringManager&)
{
    return false;
}
#if !defined(SF_CC_GNU) && !defined(SF_CC_SNC) && !defined(SF_OS_WII) && !defined(SF_CC_ARM) && !defined(SF_CC_GHS) && !defined(SF_CC_CLANG)
template <>
SF_INLINE
int DefaultValue<int>(StringManager&)
{
    return 0;
}
#endif
template <>
SF_INLINE
SInt32 DefaultValue<SInt32>(StringManager&)
{
    return 0;
}
#if !defined(SF_CC_GNU) && !defined(SF_CC_SNC) && !defined(SF_OS_WII) && !defined(SF_CC_ARM) && !defined(SF_CC_GHS) && !defined(SF_CC_CLANG)
template <>
SF_INLINE
unsigned int DefaultValue<unsigned int>(StringManager&)
{
    return 0;
}
#endif
template <>
SF_INLINE
UInt32 DefaultValue<UInt32>(StringManager&)
{
    return 0;
}

template <>
SF_INLINE
Value::Number DefaultValue<Value::Number>(StringManager&)
{
    return NumberUtil::NaN();
}
template <>
SF_INLINE
Value::Number DefaultValue<const Value::Number&>(StringManager&)
{
    return NumberUtil::NaN();
}

template <>
SF_INLINE
ASStringNode* DefaultValue<ASStringNode*>(StringManager& sm)
{
    return sm.GetEmptyStringNode();
}

// !!! Do not delete this !!!
template <>
SF_INLINE
String DefaultValue<String>(StringManager&)
{
    return String();
}
template <>
SF_INLINE
String DefaultValue<const String&>(StringManager&)
{
    return String();
}

template <>
SF_INLINE
ASString DefaultValue<ASString>(StringManager& sm)
{
    // No problem with RefCount.
    return sm.CreateEmptyString();
}
template <>
SF_INLINE
ASString DefaultValue<const ASString&>(StringManager& sm)
{
    // No problem with RefCount.
    return sm.CreateEmptyString();
}

template <>
SF_INLINE
Value DefaultValue<Value>(StringManager&)
{
    return Value::GetUndefined();
}
template <>
SF_INLINE
Value DefaultValue<const Value&>(StringManager&)
{
    return Value::GetUndefined();
}

template <>
SF_INLINE
AS3::Object* DefaultValue<AS3::Object*>(StringManager&)
{
    return NULL;
}

template <>
SF_INLINE
Instances::Function* DefaultValue<Instances::Function*>(StringManager&)
{
    return NULL;
}

///////////////////////////////////////////////////////////////////////////
namespace Impl
{

    // C - class
    // M - method id
    // N - arg number
    // T - arg type
    template <class C, int M, int N, typename T>
    SF_INLINE
    typename Clean<T>::type GetMethodDefArg(AS3::StringManager& sm)
    {
        return DefaultValue<T>(sm);
    }

}

///////////////////////////////////////////////////////////////////////////////
namespace Impl
{

    ///////////////////////////////////////////////////////////////////////////
    // Convert<FROM,TO> is a class specialization used to convert Value to
    // is component primitive types and back. This class is used to implement the
    // Convert() template function used for reading argument values Thunks.
    // Typically Value -> type conversions are used for reading arguments,
    // while type -> Value conversion is used for the return type.
    //
    // Specializations such as <Value, ASString>, <Value, unsigned> are defined for
    // each primitive type; furthermore, additional conversions are defined in each
    // each object implementation header, converting Value to Instances::ObjectType
    // through a static cast from Instances::Object.

    template <typename FROM, typename TO>
    class Convert
    {
    };

    template <>
    class Convert<Value, Value>
    {
    public:
        typedef Value TO;
        typedef Value FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            to.Assign(from);
        }
    };

    template <>
    class Convert<Value, String>
    {
    public:
        typedef String TO;
        typedef Value FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            StringBuffer buf;
            if (from.Convert2String(buf))
                to.AssignString(buf.ToCStr(), buf.GetSize());
        }
    };

    template <>
    class Convert<Value, ASString>
    {
    public:
        typedef ASString TO;
        typedef Value FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            from.Convert2String(to).DoNotCheck();
        }
    };

    template <>
    class Convert<Value, bool>
    {
    public:
        typedef bool TO;
        typedef Value FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            to = from.Convert2Boolean();
        }
    };

#if !defined(SF_CC_GNU) && !defined(SF_CC_SNC) && !defined(SF_CC_ARM) && !defined(SF_CC_GHS) && !defined(SF_CC_CLANG)
    template <>
    class Convert<Value, int>
    {
    public:
        typedef int TO;
        typedef Value FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            SInt32 v;
            if (from.Convert2Int32(v))
                to = v;
        }
    };
#endif

    template <>
    class Convert<Value, SInt32>
    {
    public:
        typedef SInt32 TO;
        typedef Value FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            from.Convert2Int32(to).DoNotCheck();
        }
    };

#if !defined(SF_CC_GNU) && !defined(SF_CC_SNC) && !defined(SF_CC_ARM) && !defined(SF_CC_GHS) && !defined(SF_CC_CLANG)
    template <>
    class Convert<Value, unsigned int>
    {
    public:
        typedef unsigned int TO;
        typedef Value FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            UInt32 v;
            if (from.Convert2UInt32(v))
                to = v;
        }
    };
#endif

    template <>
    class Convert<Value, UInt32>
    {
    public:
        typedef UInt32 TO;
        typedef Value FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            from.Convert2UInt32(to).DoNotCheck();
        }
    };

    template <>
    class Convert<Value, Value::Number>
    {
    public:
        typedef Value::Number TO;
        typedef Value FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            from.Convert2Number(to).DoNotCheck();
        }
    };

    template <class T>
    class Convert<Value, T>
    {
    public:
        typedef T TO;
        typedef Value FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            // This *if* statement is required only in case when REPORT_NOT_IMPLEMENTED
            // is not defined.
            if (from.IsUndefined())
                to = T();
            else
                to = (TO)(from.GetObject());
        }
    };

    template <typename FROM>
    class Convert<FROM, Value>
    {
    public:
        typedef Value TO;

    public:
        SF_INLINE
        Convert(TO& to, FROM from)
        {
            to.Assign(from);
        }
    };

    template <>
    class Convert<bool, Value>
    {
    public:
        typedef Value TO;
        typedef bool FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            to.SetBool(from);
        }
    };

    template <>
    class Convert<SInt32, Value>
    {
    public:
        typedef Value TO;
        typedef SInt32 FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            to.SetSInt32(from);
        }
    };

    template <>
    class Convert<UInt32, Value>
    {
    public:
        typedef Value TO;
        typedef UInt32 FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            to.SetUInt32(from);
        }
    };

    template <>
    class Convert<Value::Number, Value>
    {
    public:
        typedef Value TO;
        typedef Value::Number FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            to.SetNumber(from);
        }
    };

    template <>
    class Convert<ASString, Value>
    {
    public:
        typedef Value TO;
        typedef ASString FROM;

    public:
        SF_INLINE
        Convert(TO& to, const FROM& from)
        {
            to.Assign(from);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // Unsafe version of Convert.

    template <typename FROM, typename TO>
    class ConvertUnsafe
    {
    };

    template <>
    class ConvertUnsafe<Value, Value>
    {
    public:
        typedef Value TO;
        typedef Value FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            to.AssignUnsafe(from);
        }
    };

    template <>
    class ConvertUnsafe<Value, String>
    {
    public:
        typedef String TO;
        typedef Value FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            StringBuffer buf;
            if (from.Convert2String(buf))
                to.AssignString(buf.ToCStr(), buf.GetSize());
        }
    };

    template <>
    class ConvertUnsafe<Value, ASString>
    {
    public:
        typedef ASString TO;
        typedef Value FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            from.Convert2String(to).DoNotCheck();
        }
    };

    template <>
    class ConvertUnsafe<Value, bool>
    {
    public:
        typedef bool TO;
        typedef Value FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            to = from.Convert2Boolean();
        }
    };

#if !defined(SF_CC_GNU) && !defined(SF_CC_SNC) && !defined(SF_CC_ARM) && !defined(SF_CC_GHS) && !defined(SF_CC_CLANG)
    template <>
    class ConvertUnsafe<Value, int>
    {
    public:
        typedef int TO;
        typedef Value FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            SInt32 v;
            if (from.Convert2Int32(v))
                to = v;
        }
    };
#endif

    template <>
    class ConvertUnsafe<Value, SInt32>
    {
    public:
        typedef SInt32 TO;
        typedef Value FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            from.Convert2Int32(to).DoNotCheck();
        }
    };

#if !defined(SF_CC_GNU) && !defined(SF_CC_SNC) && !defined(SF_CC_ARM) && !defined(SF_CC_GHS) && !defined(SF_CC_CLANG)
    template <>
    class ConvertUnsafe<Value, unsigned int>
    {
    public:
        typedef unsigned int TO;
        typedef Value FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            UInt32 v;
            if (from.Convert2UInt32(v))
                to = v;
        }
    };
#endif

    template <>
    class ConvertUnsafe<Value, UInt32>
    {
    public:
        typedef UInt32 TO;
        typedef Value FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            from.Convert2UInt32(to).DoNotCheck();
        }
    };

    template <>
    class ConvertUnsafe<Value, Value::Number>
    {
    public:
        typedef Value::Number TO;
        typedef Value FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            from.Convert2Number(to).DoNotCheck();
        }
    };

    template <class T>
    class ConvertUnsafe<Value, T>
    {
    public:
        typedef T TO;
        typedef Value FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            // This *if* statement is required only in case when REPORT_NOT_IMPLEMENTED
            // is not defined.
            if (from.IsUndefined())
                to = T();
            else
                to = (TO)(from.GetObject());
        }
    };

    template <typename FROM>
    class ConvertUnsafe<FROM, Value>
    {
    public:
        typedef Value TO;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, FROM from)
        {
            to.AssignUnsafe(from);
        }
    };

    template <>
    class ConvertUnsafe<bool, Value>
    {
    public:
        typedef Value TO;
        typedef bool FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            to.SetBoolUnsafe(from);
        }
    };

    template <>
    class ConvertUnsafe<SInt32, Value>
    {
    public:
        typedef Value TO;
        typedef SInt32 FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            to.SetSInt32Unsafe(from);
        }
    };

    template <>
    class ConvertUnsafe<UInt32, Value>
    {
    public:
        typedef Value TO;
        typedef UInt32 FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            to.SetUInt32Unsafe(from);
        }
    };

    template <>
    class ConvertUnsafe<Value::Number, Value>
    {
    public:
        typedef Value TO;
        typedef Value::Number FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            to.SetNumberUnsafe(from);
        }
    };

    template <>
    class ConvertUnsafe<ASString, Value>
    {
    public:
        typedef Value TO;
        typedef ASString FROM;

    public:
        SF_INLINE
        ConvertUnsafe(TO& to, const FROM& from)
        {
            to.AssignUnsafe(from);
        }
    };

}

///////////////////////////////////////////////////////////////////////////
template <typename TO, typename FROM>
SF_INLINE
void Convert(TO& to, const FROM& from)
{
    Impl::Convert<FROM, TO>(to, from);
}

template <typename TO, typename FROM>
SF_INLINE
void ConvertUnsafe(TO& to, const FROM& from)
{
    Impl::ConvertUnsafe<FROM, TO>(to, from);
}

///////////////////////////////////////////////////////////////////////////
#if 0
template <typename TO>
SF_INLINE
void ConvertValue(Value& /*to*/, StringManager& /*sm*/)
{
}

template <>
SF_INLINE
void ConvertValue<bool>(Value& to, StringManager& /*sm*/)
{
    to.ToBooleanValue();
}

#if !defined(SF_CC_GNU) && !defined(SF_CC_SNC) && !defined(SF_CC_ARM) && !defined(SF_CC_GHS) && !defined(SF_CC_CLANG)
template <>
SF_INLINE
void ConvertValue<int>(Value& to, StringManager& /*sm*/)
{
    to.ToInt32Value().DoNotCheck();
}

template <>
SF_INLINE
void ConvertValue<unsigned int>(Value& to, StringManager& /*sm*/)
{
    to.ToUInt32Value().DoNotCheck();
}
#endif

template <>
SF_INLINE
void ConvertValue<SInt32>(Value& to, StringManager& /*sm*/)
{
    to.ToInt32Value().DoNotCheck();
}

template <>
SF_INLINE
void ConvertValue<UInt32>(Value& to, StringManager& /*sm*/)
{
    to.ToUInt32Value().DoNotCheck();
}

template <>
SF_INLINE
void ConvertValue<Value::Number>(Value& to, StringManager& /*sm*/)
{
    to.ToNumberValue().DoNotCheck();
}

template <>
SF_INLINE
void ConvertValue<ASString>(Value& to, StringManager& sm)
{
    to.ToStringValue(sm).DoNotCheck();
}
#endif

///////////////////////////////////////////////////////////////////////////
// RT stands for Result Type. It can be of type Value, which can hold multiple
// value types.
// If argument is not available, result won't be changed.
template <typename RT>
SF_INLINE
void ReadArg(unsigned n, RT& result, unsigned argc, const Value* argv)
{
    if (argc > n)
        AS3::Convert(result, argv[n]);
}

///////////////////////////////////////////////////////////////////////////

// ThunkFunk0-6 are thunk function generator classes.
// The actual implementation of static Func() is provided in VM.h; its
// implementation is resposible for reading the arguments from argv and
// calling the pointer-to-member.

template <typename T, size_t N, typename R>
struct ThunkFunc0
{
    typedef void (T::*TMethod)(R&);

    static void Func(const ThunkInfo& ti, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv);
    static const TMethod Method;
};

template <typename T, size_t N, typename R> 
const typename ThunkFunc0<T, N, R>::TMethod ThunkFunc0<T, N, R>::Method = NULL;

///////////////////////////////////////////////////////////////////////////
template <typename T, size_t N, typename R, typename A0>
struct ThunkFunc1
{
    typedef void (T::*TMethod)(R&, A0);

    static void Func(const ThunkInfo& ti, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv);
    static const TMethod Method;
};

template <typename T, size_t N, typename R, typename A0> 
const typename ThunkFunc1<T, N, R, A0>::TMethod ThunkFunc1<T, N, R, A0>::Method = NULL;

///////////////////////////////////////////////////////////////////////////
template <typename T, size_t N, typename R, typename A0, typename A1>
struct ThunkFunc2
{
    typedef void (T::*TMethod)(R&, A0, A1);

    static void Func(const ThunkInfo& ti, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv);
    static const TMethod Method;
};

template <typename T, size_t N, typename R, typename A0, typename A1> 
const typename ThunkFunc2<T, N, R, A0, A1>::TMethod ThunkFunc2<T, N, R, A0, A1>::Method = NULL;

// Specialization for variable-argument length function call.
template <typename T, size_t N>
struct ThunkFunc2<T, N, Value, unsigned, const Value*>
{
    typedef void (T::*TMethod)(Value&, unsigned, const Value*);

//     SF_INLINE
    static void Func(const ThunkInfo& /*ti*/, VM& /*vm*/, const Value& obj, Value& result, unsigned argc, const Value* argv)
    {
        T& _this = static_cast<T&>(*obj.GetObject());

        (_this.*Method)(result, argc, argv);
    }

    static const TMethod Method;
};

template <typename T, size_t N> 
const typename ThunkFunc2<T, N, Value, unsigned, const Value*>::TMethod ThunkFunc2<T, N, Value, unsigned, const Value*>::Method = NULL;

///////////////////////////////////////////////////////////////////////////
template <typename T, size_t N, typename R, typename A0, typename A1, typename A2>
struct ThunkFunc3
{
    typedef void (T::*TMethod)(R&, A0, A1, A2);

    static void Func(const ThunkInfo& ti, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv);
    static const TMethod Method;
};

template <typename T, size_t N, typename R, typename A0, typename A1, typename A2> 
const typename ThunkFunc3<T, N, R, A0, A1, A2>::TMethod
ThunkFunc3<T, N, R, A0, A1, A2>::Method = NULL;

///////////////////////////////////////////////////////////////////////////
template <typename T, size_t N, typename R, typename A0, typename A1, typename A2, typename A3>
struct ThunkFunc4
{
    typedef void (T::*TMethod)(R&, A0, A1, A2, A3);

    static void Func(const ThunkInfo& ti, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv);
    static const TMethod Method;
};

template <typename T, size_t N, typename R, typename A0, typename A1, typename A2, typename A3> 
const typename ThunkFunc4<T, N, R, A0, A1, A2, A3>::TMethod
ThunkFunc4<T, N, R, A0, A1, A2, A3>::Method = NULL;

///////////////////////////////////////////////////////////////////////////
template <typename T, size_t N, typename R, typename A0, typename A1, typename A2,
    typename A3, typename A4>
struct ThunkFunc5
{
    typedef void (T::*TMethod)(R&, A0, A1, A2, A3, A4);

    static void Func(const ThunkInfo& ti, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv);
    static const TMethod Method;
};

template <typename T, size_t N, typename R, typename A0, typename A1, typename A2,
typename A3, typename A4> 
const typename ThunkFunc5<T, N, R, A0, A1, A2, A3, A4>::TMethod
ThunkFunc5<T, N, R, A0, A1, A2, A3, A4>::Method = NULL;

///////////////////////////////////////////////////////////////////////////
template <typename T, size_t N, typename R, typename A0, typename A1, typename A2,
    typename A3, typename A4, typename A5>
struct ThunkFunc6
{
    typedef void (T::*TMethod)(R&, A0, A1, A2, A3, A4, A5);

    static void Func(const ThunkInfo& ti, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv);
    static const TMethod Method;
};

template <typename T, size_t N, typename R, typename A0, typename A1, typename A2,
typename A3, typename A4, typename A5> 
const typename ThunkFunc6<T, N, R, A0, A1, A2, A3, A4, A5>::TMethod
ThunkFunc6<T, N, R, A0, A1, A2, A3, A4, A5>::Method = NULL;

///////////////////////////////////////////////////////////////////////////
////

template <typename A0>
struct DefArgs1
{
    SF_INLINE
    DefArgs1(A0 a0 = A0())
        : _0(a0)
    {
    }
    DefArgs1& operator=(const DefArgs1&);

    typename Clean<A0>::type _0;
};

template <typename A0, typename A1>
struct DefArgs2 : public DefArgs1<A0>
{
    SF_INLINE
    DefArgs2(A0 a0 = A0(), A1 a1 = A1())
        : DefArgs1<A0>(a0)
        , _1(a1)
    {
    }
    DefArgs2& operator=(const DefArgs2&);

    typename Clean<A1>::type _1;
};

template <typename A0, typename A1, typename A2>
struct DefArgs3 : public DefArgs2<A0, A1>
{
    SF_INLINE
    DefArgs3(A0 a0 = A0(), A1 a1 = A1(), A2 a2 = A2())
        : DefArgs2<A0, A1>(a0, a1)
        , _2(a2)
    {
    }
    DefArgs3& operator=(const DefArgs3&);

    typename Clean<A2>::type _2;
};

template <typename A0, typename A1, typename A2, typename A3>
struct DefArgs4 : public DefArgs3<A0, A1, A2>
{
    SF_INLINE
    DefArgs4(A0 a0 = A0(), A1 a1 = A1(), A2 a2 = A2(), A3 a3 = A3())
        : DefArgs3<A0, A1, A2>(a0, a1, a2)
        , _3(a3)
    {
    }
    DefArgs4& operator=(const DefArgs4&);

    typename Clean<A3>::type _3;
};

template <typename A0, typename A1, typename A2, typename A3, typename A4>
struct DefArgs5 : public DefArgs4<A0, A1, A2, A3>
{
    SF_INLINE
    DefArgs5(A0 a0 = A0(), A1 a1 = A1(), A2 a2 = A2(), A3 a3 = A3(), A4 a4 = A4())
        : DefArgs4<A0, A1, A2, A3>(a0, a1, a2, a3)
        , _4(a4)
    {
    }
    DefArgs5& operator=(const DefArgs5&);

    typename Clean<A4>::type _4;
};

template <typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
struct DefArgs6 : public DefArgs5<A0, A1, A2, A3, A4>
{
    SF_INLINE
    DefArgs6(A0 a0 = A0(), A1 a1 = A1(), A2 a2 = A2(), A3 a3 = A3(), A4 a4 = A4(), A5 a5 = A5())
        : DefArgs5<A0, A1, A2, A3, A4>(a0, a1, a2, a3, a4)
        , _5(a5)
    {
    }
    DefArgs6& operator=(const DefArgs6&);

    typename Clean<A5>::type _5;
};


///////////////////////////////////////////////////////////////////////////
// Forcing inline for the functions below generates a lot of code.

template <class C, int M, typename A0>
inline
DefArgs1<A0> MakeDefArgs(AS3::StringManager& sm)
{
    return DefArgs1<A0>(
        Impl::GetMethodDefArg<C, M, 0, A0>(sm)
        );
}

template <class C, int M, typename A0, typename A1>
inline
DefArgs2<A0, A1> MakeDefArgs(AS3::StringManager& sm)
{
    return DefArgs2<A0, A1>(
        Impl::GetMethodDefArg<C, M, 0, A0>(sm),
        Impl::GetMethodDefArg<C, M, 1, A1>(sm)
        );
}

template <class C, int M, typename A0, typename A1, typename A2>
inline
DefArgs3<A0, A1, A2> MakeDefArgs(AS3::StringManager& sm)
{
    return DefArgs3<A0, A1, A2>(
        Impl::GetMethodDefArg<C, M, 0, A0>(sm),
        Impl::GetMethodDefArg<C, M, 1, A1>(sm),
        Impl::GetMethodDefArg<C, M, 2, A2>(sm)
        );
}

template <class C, int M, typename A0, typename A1, typename A2, typename A3>
inline
DefArgs4<A0, A1, A2, A3> MakeDefArgs(AS3::StringManager& sm)
{
    return DefArgs4<A0, A1, A2, A3>(
        Impl::GetMethodDefArg<C, M, 0, A0>(sm),
        Impl::GetMethodDefArg<C, M, 1, A1>(sm),
        Impl::GetMethodDefArg<C, M, 2, A2>(sm),
        Impl::GetMethodDefArg<C, M, 3, A3>(sm)
        );
}

template <class C, int M, typename A0, typename A1, typename A2, typename A3, typename A4>
inline
DefArgs5<A0, A1, A2, A3, A4> MakeDefArgs(AS3::StringManager& sm)
{
    return DefArgs5<A0, A1, A2, A3, A4>(
        Impl::GetMethodDefArg<C, M, 0, A0>(sm),
        Impl::GetMethodDefArg<C, M, 1, A1>(sm),
        Impl::GetMethodDefArg<C, M, 2, A2>(sm),
        Impl::GetMethodDefArg<C, M, 3, A3>(sm),
        Impl::GetMethodDefArg<C, M, 4, A4>(sm)
        );
}

template <class C, int M, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
inline
DefArgs6<A0, A1, A2, A3, A4, A5> MakeDefArgs(AS3::StringManager& sm)
{
    return DefArgs6<A0, A1, A2, A3, A4, A5>(
        Impl::GetMethodDefArg<C, M, 0, A0>(sm),
        Impl::GetMethodDefArg<C, M, 1, A1>(sm),
        Impl::GetMethodDefArg<C, M, 2, A2>(sm),
        Impl::GetMethodDefArg<C, M, 3, A3>(sm),
        Impl::GetMethodDefArg<C, M, 4, A4>(sm),
        Impl::GetMethodDefArg<C, M, 5, A5>(sm)
        );
}

///////////////////////////////////////////////////////////////////////////
// Args does not depend on T and N template arguments.

template <typename R>
class Args0
{
public:
    SF_INLINE
    Args0(VM& vm, Value& result)
        : Vm(vm)
        , Result(result)
        , r(DefaultValue<R>(GetStringManager()))
    {
    }
    SF_INLINE
    ~Args0()
    {
        if (GetVM().IsException())
            return;

        AS3::ConvertUnsafe(Result, r);
    }

public:
    VM& GetVM() const
    {
        return Vm;
    }
    SF_INLINE
    StringManager& GetStringManager() const
    {
        return GetVM().GetStringManager();
    }

private:
    Args0& operator =(const Args0&);

private:
    VM& Vm;

public:
    Value& Result;
    R r;
};

template <>
class Args0<Value>
{
public:
    SF_INLINE
    Args0(VM& vm, Value& result)
        : Vm(vm)
        , r(result)
    {
    }
    SF_INLINE
    ~Args0()
    {
        // No conversion is necessary.
    }

public:
    VM& GetVM() const
    {
        return Vm;
    }
    SF_INLINE
    StringManager& GetStringManager() const
    {
        return GetVM().GetStringManager();
    }

private:
    Args0& operator =(const Args0&);

private:
    VM& Vm;

public:
    Value& r;
};

////
template <typename R, typename A0>
class Args1 : public Args0<R>
{
public:
    SF_INLINE
    Args1(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs1<A0>& da)
        : Args0<R>(vm, result)
        , a0(da._0)
    {
        ReadArg(0, a0, argc, argv);
    }

private:
    Args1& operator =(const Args1&);

public:
    typename Clean<A0>::type a0;
};

template <typename R>
class Args1<R, Value> : public Args0<R>
{
public:
    SF_INLINE
    Args1(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs1<Value>& da)
        : Args0<R>(vm, result)
        , a0(argc > 0 ? argv[0] : da._0)
    {
    }

private:
    Args1& operator =(const Args1&);

public:
    const Value& a0;
};

template <typename R>
class Args1<R, const Value&> : public Args0<R>
{
public:
    SF_INLINE
    Args1(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs1<const Value&>& da)
        : Args0<R>(vm, result)
        , a0(argc > 0 ? argv[0] : da._0)
    {
    }

private:
    Args1& operator =(const Args1&);

public:
    const Value& a0;
};

////
template <typename R, typename A0, typename A1>
class Args2 : public Args1<R, A0>
{
public:
    Args2(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs2<A0, A1>& da)
        : Args1<R, A0>(vm, result, argc, argv, da)
        , a1(da._1)
    {
        if (vm.IsException())
            return;

        ReadArg(1, a1, argc, argv);
    }

private:
    Args2& operator =(const Args2&);

public:
    typename Clean<A1>::type a1;
};

template <typename R, typename A0>
class Args2<R, A0, Value> : public Args1<R, A0>
{
public:
    Args2(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs2<A0, Value>& da)
        : Args1<R, A0>(vm, result, argc, argv, da)
        , a1(argc > 1 ? argv[1] : da._1)
    {
    }

private:
    Args2& operator =(const Args2&);

public:
    const Value& a1;
};

template <typename R, typename A0>
class Args2<R, A0, const Value&> : public Args1<R, A0>
{
public:
    Args2(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs2<A0, const Value&>& da)
        : Args1<R, A0>(vm, result, argc, argv, da)
        , a1(argc > 1 ? argv[1] : da._1)
    {
    }

private:
    Args2& operator =(const Args2&);

public:
    const Value& a1;
};

////
template <typename R, typename A0, typename A1, typename A2>
class Args3 : public Args2<R, A0, A1>
{
public:
    Args3(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs3<A0, A1, A2>& da)
        : Args2<R, A0, A1>(vm, result, argc, argv, da)
        , a2(da._2)
    {
        if (vm.IsException())
            return;

        ReadArg(2, a2, argc, argv);
    }

private:
    Args3& operator =(const Args3&);

public:
    typename Clean<A2>::type a2;
};

template <typename R, typename A0, typename A1>
class Args3<R, A0, A1, Value> : public Args2<R, A0, A1>
{
public:
    Args3(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs3<A0, A1, Value>& da)
        : Args2<R, A0, A1>(vm, result, argc, argv, da)
        , a2(argc > 2 ? argv[2] : da._2)
    {
    }

private:
    Args3& operator =(const Args3&);

public:
    const Value& a2;
};

template <typename R, typename A0, typename A1>
class Args3<R, A0, A1, const Value&> : public Args2<R, A0, A1>
{
public:
    Args3(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs3<A0, A1, const Value&>& da)
        : Args2<R, A0, A1>(vm, result, argc, argv, da)
        , a2(argc > 2 ? argv[2] : da._2)
    {
    }

private:
    Args3& operator =(const Args3&);

public:
    const Value& a2;
};

////
template <typename R, typename A0, typename A1, typename A2, typename A3>
class Args4 : public Args3<R, A0, A1, A2>
{
public:
    Args4(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs4<A0, A1, A2, A3>& da)
        : Args3<R, A0, A1, A2>(vm, result, argc, argv, da)
        , a3(da._3)
    {
        if (vm.IsException())
            return;

        ReadArg(3, a3, argc, argv);
    }

private:
    Args4& operator =(const Args4&);

public:
    typename Clean<A3>::type a3;
};

////
template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
class Args5 : public Args4<R, A0, A1, A2, A3>
{
public:
    Args5(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs5<A0, A1, A2, A3, A4>& da)
        : Args4<R, A0, A1, A2, A3>(vm, result, argc, argv, da)
        , a4(da._4)
    {
        if (vm.IsException())
            return;

        ReadArg(4, a4, argc, argv);
    }

private:
    Args5& operator =(const Args5&);

public:
    typename Clean<A4>::type a4;
};

////
template <typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
class Args6 : public Args5<R, A0, A1, A2, A3, A4>
{
public:
    Args6(VM& vm, Value& result, unsigned argc, const Value* argv, const DefArgs6<A0, A1, A2, A3, A4, A5>& da)
        : Args5<R, A0, A1, A2, A3, A4>(vm, result, argc, argv, da)
        , a5(da._5)
    {
        if (vm.IsException())
            return;

        ReadArg(5, a5, argc, argv);
    }

private:
    Args6& operator =(const Args6&);

public:
    typename Clean<A5>::type a5;
};

///////////////////////////////////////////////////////////////////////////
// This method definition is intentionally not declared as *inline* ...
template <typename T, size_t N, typename R>
void ThunkFunc0<T, N, R>::Func(const ThunkInfo& /*ti*/, VM& vm, const Value& obj, Value& result, unsigned /*argc*/, const Value* /*argv*/)
{
    T& _this = static_cast<T&>(*obj.GetObject());
    Args0<R> args(vm, result);

    (_this.*Method)(args.r);
}

// This method definition is intentionally not declared as *inline* ...
template <typename T, size_t N, typename R, typename A0>
void ThunkFunc1<T, N, R, A0>::Func(const ThunkInfo& /*ti*/, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv)
{
    T& _this = static_cast<T&>(*obj.GetObject());
#if 0
    StringManager& sm = vm.GetStringManager();
    DefArgs1<A0> def_ags(
        Impl::GetMethodDefArg<T, N, 0, A0>(sm)
        );
    Args1<R, A0> args(vm, result, argc, argv, def_ags);
#else
    Args1<R, A0> args(vm, result, argc, argv, MakeDefArgs<T, N, A0>(vm.GetStringManager()));
#endif

    if (vm.IsException())
        return;

    (_this.*Method)(args.r, args.a0);
}

// This method definition is intentionally not declared as *inline* ...
template <typename T, size_t N, typename R, typename A0, typename A1>
void ThunkFunc2<T, N, R, A0, A1>::Func(const ThunkInfo& /*ti*/, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv)
{
    T& _this = static_cast<T&>(*obj.GetObject());
#if 0
    StringManager& sm = vm.GetStringManager();
    DefArgs2<A0, A1> def_ags(
        Impl::GetMethodDefArg<T, N, 0, A0>(sm),
        Impl::GetMethodDefArg<T, N, 1, A1>(sm)
        );
    Args2<R, A0, A1> args(vm, result, argc, argv, def_ags);
#else
    Args2<R, A0, A1> args(vm, result, argc, argv, MakeDefArgs<T, N, A0, A1>(vm.GetStringManager()));
#endif

    if (vm.IsException())
        return;

    (_this.*Method)(args.r, args.a0, args.a1);
}

// This method definition is intentionally not declared as *inline* ...
template <typename T, size_t N, typename R, typename A0, typename A1, typename A2>
void ThunkFunc3<T, N, R, A0, A1, A2>::Func(const ThunkInfo& /*ti*/, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv)
{
    T& _this = static_cast<T&>(*obj.GetObject());
#if 1
    StringManager& sm = vm.GetStringManager();
    DefArgs3<A0, A1, A2> def_ags(
        Impl::GetMethodDefArg<T, N, 0, A0>(sm),
        Impl::GetMethodDefArg<T, N, 1, A1>(sm),
        Impl::GetMethodDefArg<T, N, 2, A2>(sm)
        );
    Args3<R, A0, A1, A2> args(vm, result, argc, argv, def_ags);
#else
    Args3<R, A0, A1, A2> args(vm, result, argc, argv, MakeDefArgs<T, N, A0, A1, A2>(vm.GetStringManager()));
#endif

    if (vm.IsException())
        return;

    (_this.*Method)(args.r, args.a0, args.a1, args.a2);
}

// This method definition is intentionally not declared as *inline* ...
template <typename T, size_t N, typename R, typename A0, typename A1, typename A2, typename A3>
void ThunkFunc4<T, N, R, A0, A1, A2, A3>::Func(const ThunkInfo& /*ti*/, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv)
{
    T& _this = static_cast<T&>(*obj.GetObject());
#if 1
    StringManager& sm = vm.GetStringManager();
    DefArgs4<A0, A1, A2, A3> def_ags(
        Impl::GetMethodDefArg<T, N, 0, A0>(sm),
        Impl::GetMethodDefArg<T, N, 1, A1>(sm),
        Impl::GetMethodDefArg<T, N, 2, A2>(sm),
        Impl::GetMethodDefArg<T, N, 3, A3>(sm)
        );
    Args4<R, A0, A1, A2, A3> args(vm, result, argc, argv, def_ags);
#else
    Args4<R, A0, A1, A2, A3> args(vm, result, argc, argv, MakeDefArgs<T, N, A0, A1, A2, A3>(vm.GetStringManager()));
#endif

    if (vm.IsException())
        return;

    (_this.*Method)(args.r, args.a0, args.a1, args.a2, args.a3);
}

// This method definition is intentionally not declared as *inline* ...
template <typename T, size_t N, typename R, typename A0, typename A1, typename A2, typename A3, typename A4>
void ThunkFunc5<T, N, R, A0, A1, A2, A3, A4>::Func(const ThunkInfo& /*ti*/, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv)
{
    T& _this = static_cast<T&>(*obj.GetObject());
#if 1
    StringManager& sm = vm.GetStringManager();
    DefArgs5<A0, A1, A2, A3, A4> def_ags(
        Impl::GetMethodDefArg<T, N, 0, A0>(sm),
        Impl::GetMethodDefArg<T, N, 1, A1>(sm),
        Impl::GetMethodDefArg<T, N, 2, A2>(sm),
        Impl::GetMethodDefArg<T, N, 3, A3>(sm),
        Impl::GetMethodDefArg<T, N, 4, A4>(sm)
        );
    Args5<R, A0, A1, A2, A3, A4> args(vm, result, argc, argv, def_ags);
#else
    Args5<R, A0, A1, A2, A3, A4> args(vm, result, argc, argv, MakeDefArgs<T, N, A0, A1, A2, A3, A4>(vm.GetStringManager()));
#endif

    if (vm.IsException())
        return;

    (_this.*Method)(args.r, args.a0, args.a1, args.a2, args.a3, args.a4);
}

// This method definition is intentionally not declared as *inline* ...
template <typename T, size_t N, typename R, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
void ThunkFunc6<T, N, R, A0, A1, A2, A3, A4, A5>::Func(const ThunkInfo& /*ti*/, VM& vm, const Value& obj, Value& result, unsigned argc, const Value* argv)
{
    T& _this = static_cast<T&>(*obj.GetObject());
#if 1
    StringManager& sm = vm.GetStringManager();
    DefArgs6<A0, A1, A2, A3, A4, A5> def_ags(
        Impl::GetMethodDefArg<T, N, 0, A0>(sm),
        Impl::GetMethodDefArg<T, N, 1, A1>(sm),
        Impl::GetMethodDefArg<T, N, 2, A2>(sm),
        Impl::GetMethodDefArg<T, N, 3, A3>(sm),
        Impl::GetMethodDefArg<T, N, 4, A4>(sm),
        Impl::GetMethodDefArg<T, N, 5, A5>(sm)
        );
    Args6<R, A0, A1, A2, A3, A4, A5> args(vm, result, argc, argv, def_ags);
#else
    Args6<R, A0, A1, A2, A3, A4, A5> args(vm, result, argc, argv, MakeDefArgs<T, N, A0, A1, A2, A3, A4, A5>(vm.GetStringManager()));
#endif

    if (vm.IsException())
        return;

    (_this.*Method)(args.r, args.a0, args.a1, args.a2, args.a3, args.a4, args.a5);
}

}}} // namespace Scaleform { namespace GFx { namespace AS3 {

#endif // INC_AS3_MARSHALLING_H

