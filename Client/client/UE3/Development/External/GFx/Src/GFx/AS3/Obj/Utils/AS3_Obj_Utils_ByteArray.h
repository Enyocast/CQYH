//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_ByteArray.h
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#ifndef INC_AS3_Obj_Utils_ByteArray_H
#define INC_AS3_Obj_Utils_ByteArray_H

#include "../AS3_Obj_Object.h"
//##protect##"includes"
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{
//##protect##"forward_declaration"
//##protect##"forward_declaration"

namespace ClassTraits
{
    class ByteArray;
}

namespace InstanceTraits
{
    class ByteArray;
}

namespace Classes
{
    class ByteArray;
}

namespace Instances
{
    class ByteArray : public Instances::Object
    {
        friend class InstanceTraits::ByteArray;
        
    public:
        typedef ByteArray SelfType;
        typedef Classes::ByteArray ClassType;
        typedef InstanceTraits::ByteArray TraitsType;

#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Instances::ByteArray"; }
#endif
    protected:
        ByteArray(InstanceTraits::Traits& t);

//##protect##"instance$methods"
    public:
        enum EncodingType { encAMF0 = 0, encAMF3 = 3 };
        enum EndianType { endianBig = 0, endianLittle = 1 };

    protected:
        ByteArray(InstanceTraits::Traits& t, EncodingType enc);

        void ThrowEOFError();
        void ThrowMemoryError();

        // Return true in case of an error.
        CheckResult EOFError();

        UInt32 GetAvailableNum() const { return static_cast<UInt32>(Data.GetSize() - Position); }
        void Resize(UInt32 size);

        static EndianType GetNativeEndian()
        {
#if (SF_BYTE_ORDER == SF_LITTLE_ENDIAN)
            return endianLittle;
#else
            return endianBig;
#endif
        }

        static EndianType GetDefaultEndian()
        {
            return endianBig;
        }

        EndianType GetEndian() const
        {
            return Endian;
        }

        template <typename T>
        void AdjustByteOrder(T& v) const
        {
            if (GetEndian() != GetNativeEndian())
                v = Alg::ByteUtil::SwapOrder(v);
        }

        static bool IsUTF8BOM(const char* str)
        {
            return (UInt8)str[0] == 0xEF && (UInt8)str[1] == 0xBB && (UInt8)str[2] == 0xBF;
        }
        static bool IsUTF16BE(const char* str)
        {
            return (UInt8)str[0] == 0xFE && (UInt8)str[1] == 0xFF;
        }
        static bool IsUTF16LE(const char* str)
        {
            return (UInt8)str[0] == 0xFF && (UInt8)str[1] == 0xFE;
        }

        // Return true on success.
        CheckResult Read(void* dest, UInt32 buff_size);
		// Return true if we can read num bytes.
		CheckResult CanRead(UInt32 num)
		{
			return (Position + num <= Data.GetSize());
		}

        void Write(const void* src, UInt32 buff_size);
        void Write(bool v);
        void Write(UInt8 v);
        void Write(SInt8 v);
        void Write(UInt16 v)
        {
            AdjustByteOrder(v);
            Write((void*)&v, sizeof(v));
        }
        void Write(SInt16 v)
        {
            AdjustByteOrder(v);
            Write((void*)&v, sizeof(v));
        }

        UInt16 ReadU16();
        SInt16 ReadS16() { return static_cast<SInt16>(ReadU16()); }
        // !!! It doesn't check for EOF.
        // Return false in case of an error.
        CheckResult ReadUTFBytes(ASString& result, UInt32 len);

    public:
        // Array-like access.
        UInt8 Get(UInt32 ind) const;
        void Set(UInt32 ind, UInt8 v);

        // sets content of bytearray
        void Set(const void* data, UPInt sz);
        UInt32 GetLength() const { return Length; }
        const void* GetDataPtr() const { return Data.GetDataPtr(); }

        virtual CheckResult SetProperty(const Multiname& prop_name, const Value& value);
        virtual CheckResult GetProperty(const Multiname& prop_name, Value& value);
        virtual void GetDynamicProperty(AbsoluteIndex ind, Value& value);

//##protect##"instance$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_bytesAvailableGet, 
            mid_endianGet, 
            mid_endianSet, 
            mid_lengthGet, 
            mid_lengthSet, 
            mid_objectEncodingGet, 
            mid_objectEncodingSet, 
            mid_positionGet, 
            mid_positionSet, 
            mid_compress, 
            mid_readBoolean, 
            mid_readByte, 
            mid_readBytes, 
            mid_readDouble, 
            mid_readFloat, 
            mid_readInt, 
            mid_readMultiByte, 
            mid_readObject, 
            mid_readShort, 
            mid_readUnsignedByte, 
            mid_readUnsignedInt, 
            mid_readUnsignedShort, 
            mid_readUTF, 
            mid_readUTFBytes, 
            mid_toString, 
            mid_uncompress, 
            mid_writeBoolean, 
            mid_writeByte, 
            mid_writeBytes, 
            mid_writeDouble, 
            mid_writeFloat, 
            mid_writeInt, 
            mid_writeMultiByte, 
            mid_writeObject, 
            mid_writeShort, 
            mid_writeUnsignedInt, 
            mid_writeUTF, 
            mid_writeUTFBytes, 
        };
        void bytesAvailableGet(UInt32& result);
        void endianGet(ASString& result);
        void endianSet(Value& result, const ASString& value);
        void lengthGet(UInt32& result);
        void lengthSet(Value& result, UInt32 value);
        void objectEncodingGet(UInt32& result);
        void objectEncodingSet(Value& result, UInt32 value);
        void positionGet(UInt32& result);
        void positionSet(Value& result, UInt32 value);
        void compress(Value& result, unsigned argc, const Value* const argv);
        void readBoolean(bool& result);
        void readByte(SInt32& result);
        void readBytes(Value& result, Instances::ByteArray* bytes, UInt32 offset, UInt32 length);
        void readDouble(Value::Number& result);
        void readFloat(Value::Number& result);
        void readInt(SInt32& result);
        void readMultiByte(ASString& result, UInt32 length, const ASString& charSet);
        void readObject(Value& result);
        void readShort(SInt32& result);
        void readUnsignedByte(UInt32& result);
        void readUnsignedInt(UInt32& result);
        void readUnsignedShort(UInt32& result);
        void readUTF(ASString& result);
        void readUTFBytes(ASString& result, UInt32 length);
        void toString(ASString& result);
        void uncompress(Value& result, unsigned argc, const Value* const argv);
        void writeBoolean(Value& result, bool value);
        void writeByte(Value& result, SInt32 value);
        void writeBytes(Value& result, Instances::ByteArray* bytes, UInt32 offset, UInt32 length);
        void writeDouble(Value& result, Value::Number value);
        void writeFloat(Value& result, Value::Number value);
        void writeInt(Value& result, SInt32 value);
        void writeMultiByte(Value& result, const ASString& value, const ASString& charSet);
        void writeObject(Value& result, const Value& object);
        void writeShort(Value& result, SInt32 value);
        void writeUnsignedInt(Value& result, UInt32 value);
        void writeUTF(Value& result, const ASString& value);
        void writeUTFBytes(Value& result, const Value& value);

//##protect##"instance$data"
    protected:
		static const char* ASCII_Names[];
		static const char* UTF8_Names[];
		static const char* UTF16_Names[];
		// No ISO support for the time being.
		//static const char* ISO_Names[];

        EncodingType Encoding:3; // One bit for sign.
        EndianType Endian:2; // One bit for sign.
        UInt32 Position;
        // Length is different from Data.GetSize().
        // Data doesn't get truncated when Length get set to zero.
        UInt32 Length;
        ArrayLH_POD<UInt8> Data;
//##protect##"instance$data"

    };
} // namespace Instances

namespace InstanceTraits
{
    class ByteArray : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "InstanceTraits::ByteArray"; }
#endif
    public:
        ByteArray(VM& vm, const ClassInfo& ci);

    public: 
        Pickable<Instances::ByteArray> MakeInstance(Traits& t);

        virtual void MakeObject(Value& result, Traits& t);

        enum { ThunkInfoNum = 73 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

//##protect##"instance_traits$data"
//##protect##"instance_traits$data"

    };
    
}
    
namespace ClassTraits
{
    class ByteArray : public Traits
    {
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "ClassTraits::ByteArray"; }
#endif
    public:
        typedef Classes::ByteArray ClassType;

    public:
        ByteArray(VM& vm);
        static Pickable<Traits> MakeClassTraits(VM& vm);
        enum { ThunkInfoNum = 2 };
        static const ThunkInfo ti[ThunkInfoNum];
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

    };
}

namespace Classes
{
    class ByteArray : public Class
    {
        friend class ClassTraits::ByteArray;
        
#ifdef GFX_AS3_VERBOSE
    private:
        virtual const char* GetAS3ObjectType() const { return "Classes::ByteArray"; }
#endif
    public:
        typedef ByteArray SelfType;
        typedef ByteArray ClassType;
        
    private:
        ByteArray(ClassTraits::Traits& t);
       
    private:
        SelfType& GetSelf()
        {
            return *this;
        }

//##protect##"class_$methods"
    public:
        Instances::ByteArray::EncodingType GetDefEncoding() const { return DefEncoding; }
//##protect##"class_$methods"

    public:
        // AS3 API methods.
        enum MethodID {
            mid_defaultObjectEncodingSet, 
            mid_defaultObjectEncodingGet, 
        };
        void defaultObjectEncodingSet(Value& result, UInt32 value);
        void defaultObjectEncodingGet(UInt32& result);

//##protect##"class_$data"
        Instances::ByteArray::EncodingType DefEncoding;
//##protect##"class_$data"

    };
}

//##protect##"methods"
//##protect##"methods"

}}} // namespace Scaleform { namespace GFx { namespace AS3

#endif

