//##protect##"disclaimer"
/**************************************************************************

Filename    :   AS3_Obj_Utils_ByteArray.cpp
Content     :   
Created     :   Jan, 2010
Authors     :   Sergey Sikorskiy

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/
//##protect##"disclaimer"

#include "AS3_Obj_Utils_ByteArray.h"
#include "../../AS3_VM.h"
#include "../../AS3_Marshalling.h"
//##protect##"includes"
#include <zlib.h>
//##protect##"includes"


namespace Scaleform { namespace GFx { namespace AS3 
{

//##protect##"methods"

class ZStream
{
public:
    ZStream();
    ~ZStream();

public:
    void SetInput(const UInt8* pbCompressed, UInt32 nb)
    {
	    Stream.next_in = (Bytef*)pbCompressed; 
        Stream.avail_in = nb; 
    }

    int GetAvailInput() const
    {
	    return Stream.avail_in; 
    }

    bool Decompress()
    {
        int error = inflate(&Stream, Z_NO_FLUSH);
        SF_ASSERT(error == Z_OK || error == Z_STREAM_END);
        return (error == Z_OK); 
    }
    int DecompressWithStatus()
    {
	    return inflate(&Stream, Z_NO_FLUSH); 
    }

    void SetOutput(UInt8* pbDecompressed, UInt32 nb)
    {
	    Stream.next_out = (Bytef*) pbDecompressed; 
        Stream.avail_out = nb; 
    }

    UInt8* GetOutput() const
    {
        return Stream.next_out; 
    }

    int GetAvailOutput() const
    {
	    return Stream.avail_out; 
    }

    int GetTotalOutput() const
    {
	    return Stream.total_out; 
    }

private:
    z_stream Stream;
};

ZStream::ZStream()
{
    memset(&Stream, 0, sizeof(Stream));
    int error = inflateInit(&Stream);
    SF_ASSERT(error == Z_OK); 
    SF_UNUSED1(error);
}
ZStream::~ZStream()
{
    int error = inflateEnd(&Stream);
    SF_ASSERT(error == Z_OK); 
    SF_UNUSED1(error);
}

//##protect##"methods"

// Values of default arguments.
namespace Impl
{

} // namespace Impl
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_bytesAvailableGet, UInt32> TFunc_Instances_ByteArray_bytesAvailableGet;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_endianGet, ASString> TFunc_Instances_ByteArray_endianGet;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_endianSet, Value, const ASString&> TFunc_Instances_ByteArray_endianSet;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_lengthGet, UInt32> TFunc_Instances_ByteArray_lengthGet;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_lengthSet, Value, UInt32> TFunc_Instances_ByteArray_lengthSet;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_objectEncodingGet, UInt32> TFunc_Instances_ByteArray_objectEncodingGet;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_objectEncodingSet, Value, UInt32> TFunc_Instances_ByteArray_objectEncodingSet;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_positionGet, UInt32> TFunc_Instances_ByteArray_positionGet;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_positionSet, Value, UInt32> TFunc_Instances_ByteArray_positionSet;
typedef ThunkFunc2<Instances::ByteArray, Instances::ByteArray::mid_compress, Value, unsigned, const Value*> TFunc_Instances_ByteArray_compress;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readBoolean, bool> TFunc_Instances_ByteArray_readBoolean;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readByte, SInt32> TFunc_Instances_ByteArray_readByte;
typedef ThunkFunc3<Instances::ByteArray, Instances::ByteArray::mid_readBytes, Value, Instances::ByteArray*, UInt32, UInt32> TFunc_Instances_ByteArray_readBytes;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readDouble, Value::Number> TFunc_Instances_ByteArray_readDouble;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readFloat, Value::Number> TFunc_Instances_ByteArray_readFloat;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readInt, SInt32> TFunc_Instances_ByteArray_readInt;
typedef ThunkFunc2<Instances::ByteArray, Instances::ByteArray::mid_readMultiByte, ASString, UInt32, const ASString&> TFunc_Instances_ByteArray_readMultiByte;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readObject, Value> TFunc_Instances_ByteArray_readObject;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readShort, SInt32> TFunc_Instances_ByteArray_readShort;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readUnsignedByte, UInt32> TFunc_Instances_ByteArray_readUnsignedByte;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readUnsignedInt, UInt32> TFunc_Instances_ByteArray_readUnsignedInt;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readUnsignedShort, UInt32> TFunc_Instances_ByteArray_readUnsignedShort;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_readUTF, ASString> TFunc_Instances_ByteArray_readUTF;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_readUTFBytes, ASString, UInt32> TFunc_Instances_ByteArray_readUTFBytes;
typedef ThunkFunc0<Instances::ByteArray, Instances::ByteArray::mid_toString, ASString> TFunc_Instances_ByteArray_toString;
typedef ThunkFunc2<Instances::ByteArray, Instances::ByteArray::mid_uncompress, Value, unsigned, const Value*> TFunc_Instances_ByteArray_uncompress;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_writeBoolean, Value, bool> TFunc_Instances_ByteArray_writeBoolean;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_writeByte, Value, SInt32> TFunc_Instances_ByteArray_writeByte;
typedef ThunkFunc3<Instances::ByteArray, Instances::ByteArray::mid_writeBytes, Value, Instances::ByteArray*, UInt32, UInt32> TFunc_Instances_ByteArray_writeBytes;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_writeDouble, Value, Value::Number> TFunc_Instances_ByteArray_writeDouble;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_writeFloat, Value, Value::Number> TFunc_Instances_ByteArray_writeFloat;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_writeInt, Value, SInt32> TFunc_Instances_ByteArray_writeInt;
typedef ThunkFunc2<Instances::ByteArray, Instances::ByteArray::mid_writeMultiByte, Value, const ASString&, const ASString&> TFunc_Instances_ByteArray_writeMultiByte;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_writeObject, Value, const Value&> TFunc_Instances_ByteArray_writeObject;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_writeShort, Value, SInt32> TFunc_Instances_ByteArray_writeShort;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_writeUnsignedInt, Value, UInt32> TFunc_Instances_ByteArray_writeUnsignedInt;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_writeUTF, Value, const ASString&> TFunc_Instances_ByteArray_writeUTF;
typedef ThunkFunc1<Instances::ByteArray, Instances::ByteArray::mid_writeUTFBytes, Value, const Value&> TFunc_Instances_ByteArray_writeUTFBytes;

template <> const TFunc_Instances_ByteArray_bytesAvailableGet::TMethod TFunc_Instances_ByteArray_bytesAvailableGet::Method = &Instances::ByteArray::bytesAvailableGet;
template <> const TFunc_Instances_ByteArray_endianGet::TMethod TFunc_Instances_ByteArray_endianGet::Method = &Instances::ByteArray::endianGet;
template <> const TFunc_Instances_ByteArray_endianSet::TMethod TFunc_Instances_ByteArray_endianSet::Method = &Instances::ByteArray::endianSet;
template <> const TFunc_Instances_ByteArray_lengthGet::TMethod TFunc_Instances_ByteArray_lengthGet::Method = &Instances::ByteArray::lengthGet;
template <> const TFunc_Instances_ByteArray_lengthSet::TMethod TFunc_Instances_ByteArray_lengthSet::Method = &Instances::ByteArray::lengthSet;
template <> const TFunc_Instances_ByteArray_objectEncodingGet::TMethod TFunc_Instances_ByteArray_objectEncodingGet::Method = &Instances::ByteArray::objectEncodingGet;
template <> const TFunc_Instances_ByteArray_objectEncodingSet::TMethod TFunc_Instances_ByteArray_objectEncodingSet::Method = &Instances::ByteArray::objectEncodingSet;
template <> const TFunc_Instances_ByteArray_positionGet::TMethod TFunc_Instances_ByteArray_positionGet::Method = &Instances::ByteArray::positionGet;
template <> const TFunc_Instances_ByteArray_positionSet::TMethod TFunc_Instances_ByteArray_positionSet::Method = &Instances::ByteArray::positionSet;
template <> const TFunc_Instances_ByteArray_compress::TMethod TFunc_Instances_ByteArray_compress::Method = &Instances::ByteArray::compress;
template <> const TFunc_Instances_ByteArray_readBoolean::TMethod TFunc_Instances_ByteArray_readBoolean::Method = &Instances::ByteArray::readBoolean;
template <> const TFunc_Instances_ByteArray_readByte::TMethod TFunc_Instances_ByteArray_readByte::Method = &Instances::ByteArray::readByte;
template <> const TFunc_Instances_ByteArray_readBytes::TMethod TFunc_Instances_ByteArray_readBytes::Method = &Instances::ByteArray::readBytes;
template <> const TFunc_Instances_ByteArray_readDouble::TMethod TFunc_Instances_ByteArray_readDouble::Method = &Instances::ByteArray::readDouble;
template <> const TFunc_Instances_ByteArray_readFloat::TMethod TFunc_Instances_ByteArray_readFloat::Method = &Instances::ByteArray::readFloat;
template <> const TFunc_Instances_ByteArray_readInt::TMethod TFunc_Instances_ByteArray_readInt::Method = &Instances::ByteArray::readInt;
template <> const TFunc_Instances_ByteArray_readMultiByte::TMethod TFunc_Instances_ByteArray_readMultiByte::Method = &Instances::ByteArray::readMultiByte;
template <> const TFunc_Instances_ByteArray_readObject::TMethod TFunc_Instances_ByteArray_readObject::Method = &Instances::ByteArray::readObject;
template <> const TFunc_Instances_ByteArray_readShort::TMethod TFunc_Instances_ByteArray_readShort::Method = &Instances::ByteArray::readShort;
template <> const TFunc_Instances_ByteArray_readUnsignedByte::TMethod TFunc_Instances_ByteArray_readUnsignedByte::Method = &Instances::ByteArray::readUnsignedByte;
template <> const TFunc_Instances_ByteArray_readUnsignedInt::TMethod TFunc_Instances_ByteArray_readUnsignedInt::Method = &Instances::ByteArray::readUnsignedInt;
template <> const TFunc_Instances_ByteArray_readUnsignedShort::TMethod TFunc_Instances_ByteArray_readUnsignedShort::Method = &Instances::ByteArray::readUnsignedShort;
template <> const TFunc_Instances_ByteArray_readUTF::TMethod TFunc_Instances_ByteArray_readUTF::Method = &Instances::ByteArray::readUTF;
template <> const TFunc_Instances_ByteArray_readUTFBytes::TMethod TFunc_Instances_ByteArray_readUTFBytes::Method = &Instances::ByteArray::readUTFBytes;
template <> const TFunc_Instances_ByteArray_toString::TMethod TFunc_Instances_ByteArray_toString::Method = &Instances::ByteArray::toString;
template <> const TFunc_Instances_ByteArray_uncompress::TMethod TFunc_Instances_ByteArray_uncompress::Method = &Instances::ByteArray::uncompress;
template <> const TFunc_Instances_ByteArray_writeBoolean::TMethod TFunc_Instances_ByteArray_writeBoolean::Method = &Instances::ByteArray::writeBoolean;
template <> const TFunc_Instances_ByteArray_writeByte::TMethod TFunc_Instances_ByteArray_writeByte::Method = &Instances::ByteArray::writeByte;
template <> const TFunc_Instances_ByteArray_writeBytes::TMethod TFunc_Instances_ByteArray_writeBytes::Method = &Instances::ByteArray::writeBytes;
template <> const TFunc_Instances_ByteArray_writeDouble::TMethod TFunc_Instances_ByteArray_writeDouble::Method = &Instances::ByteArray::writeDouble;
template <> const TFunc_Instances_ByteArray_writeFloat::TMethod TFunc_Instances_ByteArray_writeFloat::Method = &Instances::ByteArray::writeFloat;
template <> const TFunc_Instances_ByteArray_writeInt::TMethod TFunc_Instances_ByteArray_writeInt::Method = &Instances::ByteArray::writeInt;
template <> const TFunc_Instances_ByteArray_writeMultiByte::TMethod TFunc_Instances_ByteArray_writeMultiByte::Method = &Instances::ByteArray::writeMultiByte;
template <> const TFunc_Instances_ByteArray_writeObject::TMethod TFunc_Instances_ByteArray_writeObject::Method = &Instances::ByteArray::writeObject;
template <> const TFunc_Instances_ByteArray_writeShort::TMethod TFunc_Instances_ByteArray_writeShort::Method = &Instances::ByteArray::writeShort;
template <> const TFunc_Instances_ByteArray_writeUnsignedInt::TMethod TFunc_Instances_ByteArray_writeUnsignedInt::Method = &Instances::ByteArray::writeUnsignedInt;
template <> const TFunc_Instances_ByteArray_writeUTF::TMethod TFunc_Instances_ByteArray_writeUTF::Method = &Instances::ByteArray::writeUTF;
template <> const TFunc_Instances_ByteArray_writeUTFBytes::TMethod TFunc_Instances_ByteArray_writeUTFBytes::Method = &Instances::ByteArray::writeUTFBytes;

namespace Instances
{
    ByteArray::ByteArray(InstanceTraits::Traits& t)
    : Instances::Object(t)
//##protect##"instance::ByteArray::ByteArray()$data"
    , Encoding(static_cast<Classes::ByteArray&>(t.GetClass()).GetDefEncoding())
    , Endian(GetDefaultEndian())
    , Position(0)
    , Length(0)
//##protect##"instance::ByteArray::ByteArray()$data"
    {
//##protect##"instance::ByteArray::ByteArray()$code"
//##protect##"instance::ByteArray::ByteArray()$code"
    }

    void ByteArray::bytesAvailableGet(UInt32& result)
    {
//##protect##"instance::ByteArray::bytesAvailableGet()"
        result = GetAvailableNum();
//##protect##"instance::ByteArray::bytesAvailableGet()"
    }
    void ByteArray::endianGet(ASString& result)
    {
//##protect##"instance::ByteArray::endianGet()"
        if (Endian == endianBig)
            result = GetVM().GetStringManager().CreateConstString("bigEndian");
        else
            result = GetVM().GetStringManager().CreateConstString("littleEndian");
//##protect##"instance::ByteArray::endianGet()"
    }
    void ByteArray::endianSet(Value& result, const ASString& value)
    {
//##protect##"instance::ByteArray::endianSet()"
        SF_UNUSED1(result);

        if (value == "bigEndian")
            Endian = endianBig;
        else if (value == "littleEndian")
            Endian = endianLittle;
        else
            return GetVM().ThrowArgumentError(VM::Error(VM::eInvalidArgumentError, GetVM() SF_DEBUG_ARG(value.ToCStr())));
//##protect##"instance::ByteArray::endianSet()"
    }
    void ByteArray::lengthGet(UInt32& result)
    {
//##protect##"instance::ByteArray::lengthGet()"
        // Length is not the same as Data.GetSize().
        result = Length;
//##protect##"instance::ByteArray::lengthGet()"
    }
    void ByteArray::lengthSet(Value& result, UInt32 value)
    {
//##protect##"instance::ByteArray::lengthSet()"
        SF_UNUSED1(result);

        Resize(value);
//##protect##"instance::ByteArray::lengthSet()"
    }
    void ByteArray::objectEncodingGet(UInt32& result)
    {
//##protect##"instance::ByteArray::objectEncodingGet()"
        result = Encoding;
//##protect##"instance::ByteArray::objectEncodingGet()"
    }
    void ByteArray::objectEncodingSet(Value& result, UInt32 value)
    {
//##protect##"instance::ByteArray::objectEncodingSet()"
        SF_UNUSED1(result);

        if (value != encAMF0 || value != encAMF3)
            return GetVM().ThrowRangeError(VM::Error(VM::eIllegalOperandTypeError, GetVM() SF_DEBUG_ARG("some type") SF_DEBUG_ARG("encAMF0 or encAMF3")));

        Encoding = static_cast<EncodingType>(value);
//##protect##"instance::ByteArray::objectEncodingSet()"
    }
    void ByteArray::positionGet(UInt32& result)
    {
//##protect##"instance::ByteArray::positionGet()"
        result = Position;
//##protect##"instance::ByteArray::positionGet()"
    }
    void ByteArray::positionSet(Value& result, UInt32 value)
    {
//##protect##"instance::ByteArray::positionSet()"
        SF_UNUSED1(result);

        Position = value;
//##protect##"instance::ByteArray::positionSet()"
    }
    void ByteArray::compress(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::ByteArray::compress()"
        SF_UNUSED3(result, argc, argv);

        // There is only one argument called "algorithm".
        // We ignore it for the time being.

        if (GetLength() == 0)
            return;

        UPInt zlen = GetLength() * 3/2 + 32; 
        UInt8* zdata = static_cast<UInt8*>(SF_HEAP_AUTO_ALLOC(this, zlen));

        // Call zlib.
        compress2(zdata, (unsigned long*)&zlen, (const Bytef *)Data.GetDataPtr(), GetLength(), 9);

        // Replace current array with the compressed data.
        Resize(0);
        Write(zdata, static_cast<UInt32>(zlen));

        SF_FREE(zdata);
//##protect##"instance::ByteArray::compress()"
    }
    void ByteArray::readBoolean(bool& result)
    {
//##protect##"instance::ByteArray::readBoolean()"
        if (EOFError())
            return;

        result = Data[Position++] != 0;
//##protect##"instance::ByteArray::readBoolean()"
    }
    void ByteArray::readByte(SInt32& result)
    {
//##protect##"instance::ByteArray::readByte()"
        if (EOFError())
            return;

        result = static_cast<SInt8>(Data[Position++]);
//##protect##"instance::ByteArray::readByte()"
    }
    void ByteArray::readBytes(Value& result, Instances::ByteArray* bytes, UInt32 offset, UInt32 length)
    {
//##protect##"instance::ByteArray::readBytes()"
        SF_UNUSED1(result);

        const UInt32 available_num = GetAvailableNum();

        if (length == 0)
            length = available_num;

        if (length > available_num)
            return ThrowEOFError();

        // Adjust size of the output array.
        if (offset + length >= bytes->Data.GetSize())
            bytes->Resize(offset + length);

        Read(bytes->Data.GetDataPtr() + offset, length).DoNotCheck();
//##protect##"instance::ByteArray::readBytes()"
    }
    void ByteArray::readDouble(Value::Number& result)
    {
//##protect##"instance::ByteArray::readDouble()"
        if (!Read(&result, sizeof(result)))
            return;

        AdjustByteOrder(result);
//##protect##"instance::ByteArray::readDouble()"
    }
    void ByteArray::readFloat(Value::Number& result)
    {
//##protect##"instance::ByteArray::readFloat()"
        float v;

        if (!Read(&v, sizeof(v)))
            return;

        AdjustByteOrder(v);
        result = v;
//##protect##"instance::ByteArray::readFloat()"
    }
    void ByteArray::readInt(SInt32& result)
    {
//##protect##"instance::ByteArray::readInt()"
        if (!Read(&result, sizeof(result)))
            return;

        AdjustByteOrder(result);
//##protect##"instance::ByteArray::readInt()"
    }
    void ByteArray::readMultiByte(ASString& result, UInt32 length, const ASString& charSet)
    {
//##protect##"instance::ByteArray::readMultiByte()"
		// In case of ASCII.
		for (unsigned i = 0; ASCII_Names[i]; ++i)
		{
			if (charSet == ASCII_Names[i])
			{
				length = Alg::Min(length, GetLength());
				result = GetVM().GetStringManager().CreateString(reinterpret_cast<char*>(Data.GetDataPtr() + Position), length);
				Position += length;
				return;
			}
		}

		// In case of UTF-8.
		for (unsigned i = 0; UTF8_Names[i]; ++i)
		{
			if (charSet == UTF8_Names[i])
			{
				ReadUTFBytes(result, length).DoNotCheck();
				return;
			}
		}

		/*
		// No ISO support for the time being
		// In case of ISO.
		for (unsigned i = 0; ISO_Names[i]; ++i)
		{
			if (charSet == ISO_Names[i])
			{
				length = Alg::Min(length, GetLength());
				result = GetVM().GetStringManager().CreateString(reinterpret_cast<char*>(Data.GetDataPtr() + Position), length);
				Position += length;
				return;
			}
		}
		*/

		// In case of UTF16.
		for (unsigned i = 0; UTF16_Names[i]; ++i)
		{
			if (charSet == UTF16_Names[i])
			{
				length = Alg::Min(length, GetLength());
				result = GetVM().GetStringManager().CreateString(reinterpret_cast<const wchar_t*>(Data.GetDataPtr() + Position), length);
				Position += length;
				return;
			}
		}

		VM& vm = GetVM();
		vm.ThrowTypeError(VM::Error(VM::eInvalidArgumentError, vm SF_DEBUG_ARG("charSet")));
//##protect##"instance::ByteArray::readMultiByte()"
    }
    void ByteArray::readObject(Value& result)
    {
//##protect##"instance::ByteArray::readObject()"
        SF_UNUSED1(result);
        NOT_IMPLEMENTED("ByteArray::readObject()");
//##protect##"instance::ByteArray::readObject()"
    }
    void ByteArray::readShort(SInt32& result)
    {
//##protect##"instance::ByteArray::readShort()"
        result = ReadS16();
//##protect##"instance::ByteArray::readShort()"
    }
    void ByteArray::readUnsignedByte(UInt32& result)
    {
//##protect##"instance::ByteArray::readUnsignedByte()"
        if (EOFError())
            return;

        result = Data[Position++];
//##protect##"instance::ByteArray::readUnsignedByte()"
    }
    void ByteArray::readUnsignedInt(UInt32& result)
    {
//##protect##"instance::ByteArray::readUnsignedInt()"
        if (!Read(&result, sizeof(result)))
            return;

        AdjustByteOrder(result);
//##protect##"instance::ByteArray::readUnsignedInt()"
    }
    void ByteArray::readUnsignedShort(UInt32& result)
    {
//##protect##"instance::ByteArray::readUnsignedShort()"
        result = ReadU16();
//##protect##"instance::ByteArray::readUnsignedShort()"
    }
    void ByteArray::readUTF(ASString& result)
    {
//##protect##"instance::ByteArray::readUTF()"
        ReadUTFBytes(result, ReadU16()).DoNotCheck();
//##protect##"instance::ByteArray::readUTF()"
    }
    void ByteArray::readUTFBytes(ASString& result, UInt32 length)
    {
//##protect##"instance::ByteArray::readUTFBytes()"
        ReadUTFBytes(result, length).DoNotCheck();
//##protect##"instance::ByteArray::readUTFBytes()"
    }
    void ByteArray::toString(ASString& result)
    {
//##protect##"instance::ByteArray::toString()"
        UPInt size = Data.GetSize();
        union {
            char* str;
            wchar_t* str_w;
        };

        str = (char*)Data.GetDataPtr();

        if (size > 1)
        {
            if (IsUTF16BE(str))
            {
                str +=2;
                size = (size - 2) >> 1;
                // Ignore BE/LE differences for the time being.
                result = GetVM().GetStringManager().CreateString(str_w, size);
                return;
            } else if (IsUTF16LE(str))
            {
                str +=2;
                size = (size - 2) >> 1;
                // Ignore BE/LE differences for the time being.
                result = GetVM().GetStringManager().CreateString(str_w, size);
                return;
            } else if (size > 2 && IsUTF8BOM(str))
            {
                result = GetVM().GetStringManager().CreateString((const char*)(str + 3), size - 3);
                return;
            }
        }

        // We are supposed to copy invalid UTF-8 sequences as single characters here.
        // Let's do it later.
        result = GetVM().GetStringManager().CreateString((const char*)str, size);
//##protect##"instance::ByteArray::toString()"
    }
    void ByteArray::uncompress(Value& result, unsigned argc, const Value* const argv)
    {
//##protect##"instance::ByteArray::uncompress()"
        SF_UNUSED3(result, argc, argv);

        // There is only one argument called "algorithm".
        // We ignore it for the time being.

        if (GetLength() == 0)
            return;

        UPInt zlen = GetLength();
        UInt8* zdata = static_cast<UInt8*>(SF_HEAP_AUTO_ALLOC(this, zlen));
        memcpy(zdata, Data.GetDataPtr(), zlen);

        Resize(0);

        int error = Z_OK;
        ZStream zstream;
        zstream.SetInput(zdata, static_cast<UInt32>(zlen));

        const int kBufferSize = 8192;
        UInt8* buffer = static_cast<UInt8*>(SF_HEAP_AUTO_ALLOC(this, kBufferSize));

        do {
            zstream.SetOutput(buffer, kBufferSize);
            error = zstream.DecompressWithStatus();
            Write(buffer, kBufferSize - zstream.GetAvailOutput());
        } while (error == Z_OK);

        SF_FREE(buffer);
        SF_FREE(zdata);

        Position = 0;

        if (error != Z_OK && error != Z_STREAM_END)
            GetVM().ThrowError(VM::Error(VM::eShellCompressedDataError, GetVM()));
//##protect##"instance::ByteArray::uncompress()"
    }
    void ByteArray::writeBoolean(Value& result, bool value)
    {
//##protect##"instance::ByteArray::writeBoolean()"
        SF_UNUSED1(result);

        Write(value);
//##protect##"instance::ByteArray::writeBoolean()"
    }
    void ByteArray::writeByte(Value& result, SInt32 value)
    {
//##protect##"instance::ByteArray::writeByte()"
        SF_UNUSED1(result);

        Write((SInt8)value);
//##protect##"instance::ByteArray::writeByte()"
    }
    void ByteArray::writeBytes(Value& result, Instances::ByteArray* bytes, UInt32 offset, UInt32 length)
    {
//##protect##"instance::ByteArray::writeBytes()"
        SF_UNUSED1(result);

        if (bytes == NULL)
            return;

        if (bytes->GetLength() < offset)
            offset = bytes->GetLength();

        if (length == 0)
            length = bytes->GetLength() - offset;

        if (length > bytes->GetLength() - offset)
            return GetVM().ThrowRangeError(VM::Error(VM::eParamRangeError, GetVM()));

        if (length > 0)
            Write(bytes->Data.GetDataPtr() + offset, length);
//##protect##"instance::ByteArray::writeBytes()"
    }
    void ByteArray::writeDouble(Value& result, Value::Number value)
    {
//##protect##"instance::ByteArray::writeDouble()"
        SF_UNUSED1(result);

        AdjustByteOrder(value);
        Write(&value, sizeof(value));
//##protect##"instance::ByteArray::writeDouble()"
    }
    void ByteArray::writeFloat(Value& result, Value::Number value)
    {
//##protect##"instance::ByteArray::writeFloat()"
        SF_UNUSED1(result);

        float v = static_cast<float>(value);
        AdjustByteOrder(v);
        Write(&v, sizeof(v));
//##protect##"instance::ByteArray::writeFloat()"
    }
    void ByteArray::writeInt(Value& result, SInt32 value)
    {
//##protect##"instance::ByteArray::writeInt()"
        SF_UNUSED1(result);

        AdjustByteOrder(value);
        Write(&value, sizeof(value));
//##protect##"instance::ByteArray::writeInt()"
    }
    void ByteArray::writeMultiByte(Value& result, const ASString& value, const ASString& charSet)
    {
//##protect##"instance::ByteArray::writeMultiByte()"
		SF_UNUSED3(result, value, charSet);

		// In case of ASCII.
		// No ISO support for the time being.

		// In case of UTF-8.
		for (unsigned i = 0; UTF8_Names[i]; ++i)
		{
			if (charSet == UTF8_Names[i])
			{
				Write((void*)value.ToCStr(), value.GetSize());
				return;
			}
		}

		// In case of ISO.
		// No ISO support for the time being.

		// In case of UTF16.
		for (unsigned i = 0; UTF16_Names[i]; ++i)
		{
			if (charSet == UTF16_Names[i])
			{
				WStringBuffer wbuff;

				wbuff.SetString(value.ToCStr(), value.GetSize());
                if (wbuff.GetLength() <= SF_MAX_UINT32)
				    Write(wbuff.GetBuffer(), static_cast<UInt32>(wbuff.GetLength()));
				return;
			}
		}

		VM& vm = GetVM();
		vm.ThrowTypeError(VM::Error(VM::eInvalidArgumentError, vm SF_DEBUG_ARG("charSet")));
//##protect##"instance::ByteArray::writeMultiByte()"
    }
    void ByteArray::writeObject(Value& result, const Value& object)
    {
//##protect##"instance::ByteArray::writeObject()"
        SF_UNUSED2(result, object);
        NOT_IMPLEMENTED("ByteArray::writeObject()");
//##protect##"instance::ByteArray::writeObject()"
    }
    void ByteArray::writeShort(Value& result, SInt32 value)
    {
//##protect##"instance::ByteArray::writeShort()"
        SF_UNUSED1(result);

        SInt16 v = static_cast<SInt16>(value);
        AdjustByteOrder(v);
        Write(&v, sizeof(v));
//##protect##"instance::ByteArray::writeShort()"
    }
    void ByteArray::writeUnsignedInt(Value& result, UInt32 value)
    {
//##protect##"instance::ByteArray::writeUnsignedInt()"
        SF_UNUSED1(result);

        AdjustByteOrder(value);
        Write(&value, sizeof(value));
//##protect##"instance::ByteArray::writeUnsignedInt()"
    }
    void ByteArray::writeUTF(Value& result, const ASString& value)
    {
//##protect##"instance::ByteArray::writeUTF()"
        SF_UNUSED1(result);

        if (value.GetSize() > 65535)
            return GetVM().ThrowRangeError(VM::Error(VM::eNotImplementedError, GetVM() SF_DEBUG_ARG("ByteArray::writeUTF")));

        const UInt16 size = static_cast<UInt16>(value.GetSize());
        Write(size);
        Write((void*)value.ToCStr(), size);
//##protect##"instance::ByteArray::writeUTF()"
    }
    void ByteArray::writeUTFBytes(Value& result, const Value& value)
    {
//##protect##"instance::ByteArray::writeUTFBytes()"
        SF_UNUSED1(result);

        if (value.IsNullOrUndefined())
            return GetVM().ThrowTypeError(VM::Error(VM::eNullArgumentError, GetVM() SF_DEBUG_ARG("value")));

        StringManager& sm = GetVM().GetStringManager();
        ASString str = sm.CreateEmptyString();
        if (value.Convert2String(str))
        {
            Write((void*)str.ToCStr(), str.GetSize());
        }
//##protect##"instance::ByteArray::writeUTFBytes()"
    }

//##protect##"instance$methods"
	const char* ByteArray::ASCII_Names[] =
	{
		"us-ascii",
		"ANSI_X3.4-1968",
		"ANSI_X3.4-1986",
		"ascii",
		"cp367",
		"csASCII",
		"IBM367",
		"ISO_646.irv:1991",
		"ISO646-US",
		"iso-ir-6us",
		NULL
	};

	const char* ByteArray::UTF8_Names[] =
	{
		"utf-8",
		"unicode-1-1-utf-8",
		"unicode-2-0-utf-8",
		"x-unicode-2-0-utf-8",
		NULL
	};

	const char* ByteArray::UTF16_Names[] =
	{
		"unicode",
		"utf-16",
		NULL
	};

	/*
	// No ISO support for the time being.
	const char* ByteArray::ISO_Names[] =
	{
		"iso-8859-1",
		"cp819",
		"csISO",
		"Latin1",
		"ibm819",
		"iso_8859-1",
		"iso_8859-1:1987",
		"iso8859-1",
		"iso-ir-100, l1",
		"latin1",
		NULL
	};
	*/

    ByteArray::ByteArray(InstanceTraits::Traits& t, EncodingType enc)
    : Instances::Object(t)
    , Encoding(enc)
    , Endian(Instances::ByteArray::GetDefaultEndian())
    , Position(0)
    {
    }

    void ByteArray::ThrowEOFError()
    {
        Value v;
        if (!GetVM().ConstructBuiltinValue(v, "flash.errors.EOFError"))
            return;
        GetVM().Throw(v);
    }

    void ByteArray::ThrowMemoryError()
    {
        Value v;
        if (!GetVM().ConstructBuiltinValue(v, "flash.errors.MemoryError"))
            return;
        GetVM().Throw(v);
    }

    CheckResult ByteArray::EOFError()
    {
        if (Position >= Data.GetSize())
        {
            ThrowEOFError();
            return true;
        }

        return false;
    }

    CheckResult ByteArray::Read(void* dest, UInt32 buff_size)
    {
        if (Position + buff_size > Data.GetSize())
        {
            ThrowEOFError();
            return false;
        }

        memcpy(dest, Data.GetDataPtr() + Position, buff_size);
        Position += buff_size;

        return true;
    }

    void ByteArray::Write(const void* src, UInt32 buff_size)
    {
        const UInt32 size = Position + buff_size;
        if (size >= Data.GetSize())
            // Resize() will take care of Length.
            Resize(Position + buff_size);
        else if (size >= Length)
            Length = size;

        memcpy(Data.GetDataPtr() + Position, src, buff_size);
        Position += buff_size;
    }

    void ByteArray::Write(bool v)
    {
        const UInt32 size = Position + sizeof(v);
        if (size >= Data.GetSize())
            // Resize() will take care of Length.
            Resize(size);
        else if (size >= Length)
            Length = size;

        Data[Position++] = (v ? 1 : 0);
    }

    void ByteArray::Write(UInt8 v)
    {
        const UInt32 size = Position + sizeof(v);
        if (size >= Data.GetSize())
            // Resize() will take care of Length.
            Resize(size);
        else if (size >= Length)
            Length = size;

        Data[Position++] = v;
    }

    void ByteArray::Write(SInt8 v)
    {
        const UInt32 size = Position + sizeof(v);
        if (size >= Data.GetSize())
            // Resize() will take care of Length.
            Resize(size);
        else if (size >= Length)
            Length = size;

        Data[Position++] = static_cast<UInt8>(v);
    }

    void ByteArray::Resize(UInt32 size)
    {
        const UPInt oldSize = Data.GetSize();

        if (size > oldSize)
        {
            Data.Resize(size);
            memset(Data.GetDataPtr() + oldSize, 0, size - oldSize);
        }

        Length = size;

        if (Position > Length)
            Position = Length;
    }

    UInt16 ByteArray::ReadU16()
    {
        UInt16 v;

        if (!Read(&v, sizeof(v)))
            return v;

        AdjustByteOrder(v);
        return v;
    }

	CheckResult ByteArray::ReadUTFBytes(ASString& result, UInt32 len)
	{
		if (!CanRead(len))
		{
			ThrowEOFError();
			return false;
		}

		// Check for UTF8 BOM.
		if (len > 2 && IsUTF8BOM(reinterpret_cast<char*>(Data.GetDataPtr() + Position)))
		{
			len -= 3;
			Position += 3;
		}

		result = GetVM().GetStringManager().CreateString(reinterpret_cast<char*>(Data.GetDataPtr() + Position), len);
        Position += len;

		return true;
	}

    UInt8 ByteArray::Get(UInt32 ind) const
    {
        if (ind < GetLength())
            return Data[ind];

        GetVM().ThrowArgumentError(VM::Error(VM::eInvalidArgumentError, GetVM() SF_DEBUG_ARG("ByteArray::Get") SF_DEBUG_ARG(ind) SF_DEBUG_ARG(0) SF_DEBUG_ARG(GetLength() - 1)));
        return 0;
    }

    void ByteArray::Set(UInt32 ind, UInt8 v)
    {
        if (ind >= GetLength())
            Resize(ind + 1);

        Data[ind] = v;
    }

    void ByteArray::Set(const void* data, UPInt sz)
    {
        Position = 0;
        Write(data, (int)sz);
        Position = 0;
    }

    CheckResult ByteArray::SetProperty(const Multiname& prop_name, const Value& value)
    {
        UInt32 ind;
        if (GetArrayInd(prop_name, ind))
        {
            UInt32 v;
            if (!value.Convert2UInt32(v))
                // Exception.
                return false;

            // Cast and set.
            Set(ind, static_cast<UInt8>(v));
            return true;
        }

        // Not an Array index. Let us treat it as a regular object.
        return Instances::Object::SetProperty(prop_name, value);
    }

    CheckResult ByteArray::GetProperty(const Multiname& prop_name, Value& value)
    {
        UInt32 ind;
        if (GetArrayInd(prop_name, ind))
        {
            if (ind < GetLength())
            {
                // We should return unsigned int here. This is how it works.
                value.SetUInt32(static_cast<UInt8>(Get(ind)));
                return true;
            }

            return false;
        }

        // Not an Array index. Let us treat it as a regular object.
        return Instances::Object::GetProperty(prop_name, value);
    }

    void ByteArray::GetDynamicProperty(AbsoluteIndex ind, Value& value)
    {
        value.SetSInt32(static_cast<SInt8>(Get(ind.Get())));
    }
//##protect##"instance$methods"

} // namespace Instances

namespace InstanceTraits
{
    const ThunkInfo ByteArray::ti[ByteArray::ThunkInfoNum] = {
        {TFunc_Instances_ByteArray_bytesAvailableGet::Func, &uintCI, "bytesAvailable", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_endianGet::Func, &StringCI, "endian", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_endianSet::Func, NULL, "endian", NULL, CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_lengthGet::Func, &uintCI, "length", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_lengthSet::Func, NULL, "length", NULL, CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_objectEncodingGet::Func, &uintCI, "objectEncoding", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_objectEncodingSet::Func, NULL, "objectEncoding", NULL, CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_positionGet::Func, &uintCI, "position", NULL, CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_positionSet::Func, NULL, "position", NULL, CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_compress::Func, NULL, "compress", NULL, CT_Method, 0, 1},
        {TFunc_Instances_ByteArray_readBoolean::Func, &BooleanCI, "readBoolean", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readByte::Func, &int_CI, "readByte", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readBytes::Func, NULL, "readBytes", NULL, CT_Method, 1, 3},
        {TFunc_Instances_ByteArray_readDouble::Func, &NumberCI, "readDouble", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readFloat::Func, &NumberCI, "readFloat", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readInt::Func, &int_CI, "readInt", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readMultiByte::Func, &StringCI, "readMultiByte", NULL, CT_Method, 2, 2},
        {TFunc_Instances_ByteArray_readObject::Func, NULL, "readObject", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readShort::Func, &int_CI, "readShort", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUnsignedByte::Func, &uintCI, "readUnsignedByte", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUnsignedInt::Func, &uintCI, "readUnsignedInt", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUnsignedShort::Func, &uintCI, "readUnsignedShort", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUTF::Func, &StringCI, "readUTF", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUTFBytes::Func, &StringCI, "readUTFBytes", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_toString::Func, &StringCI, "toString", NULL, CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_uncompress::Func, NULL, "uncompress", NULL, CT_Method, 0, 1},
        {TFunc_Instances_ByteArray_writeBoolean::Func, NULL, "writeBoolean", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeByte::Func, NULL, "writeByte", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeBytes::Func, NULL, "writeBytes", NULL, CT_Method, 1, 3},
        {TFunc_Instances_ByteArray_writeDouble::Func, NULL, "writeDouble", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeFloat::Func, NULL, "writeFloat", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeInt::Func, NULL, "writeInt", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeMultiByte::Func, NULL, "writeMultiByte", NULL, CT_Method, 2, 2},
        {TFunc_Instances_ByteArray_writeObject::Func, NULL, "writeObject", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeShort::Func, NULL, "writeShort", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeUnsignedInt::Func, NULL, "writeUnsignedInt", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeUTF::Func, NULL, "writeUTF", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeUTFBytes::Func, NULL, "writeUTFBytes", NULL, CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_bytesAvailableGet::Func, &uintCI, "bytesAvailable", "flash.utils:IDataInput", CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_endianGet::Func, &StringCI, "endian", "flash.utils:IDataInput", CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_endianGet::Func, &StringCI, "endian", "flash.utils:IDataOutput", CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_endianSet::Func, NULL, "endian", "flash.utils:IDataInput", CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_endianSet::Func, NULL, "endian", "flash.utils:IDataOutput", CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_objectEncodingGet::Func, &uintCI, "objectEncoding", "flash.utils:IDataInput", CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_objectEncodingGet::Func, &uintCI, "objectEncoding", "flash.utils:IDataOutput", CT_Get, 0, 0},
        {TFunc_Instances_ByteArray_objectEncodingSet::Func, NULL, "objectEncoding", "flash.utils:IDataInput", CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_objectEncodingSet::Func, NULL, "objectEncoding", "flash.utils:IDataOutput", CT_Set, 1, 1},
        {TFunc_Instances_ByteArray_readBoolean::Func, &BooleanCI, "readBoolean", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readByte::Func, &int_CI, "readByte", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readBytes::Func, NULL, "readBytes", "flash.utils:IDataInput", CT_Method, 1, 3},
        {TFunc_Instances_ByteArray_readDouble::Func, &NumberCI, "readDouble", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readFloat::Func, &NumberCI, "readFloat", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readInt::Func, &int_CI, "readInt", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readMultiByte::Func, &StringCI, "readMultiByte", "flash.utils:IDataInput", CT_Method, 2, 2},
        {TFunc_Instances_ByteArray_readObject::Func, NULL, "readObject", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readShort::Func, &int_CI, "readShort", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUnsignedByte::Func, &uintCI, "readUnsignedByte", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUnsignedInt::Func, &uintCI, "readUnsignedInt", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUnsignedShort::Func, &uintCI, "readUnsignedShort", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUTF::Func, &StringCI, "readUTF", "flash.utils:IDataInput", CT_Method, 0, 0},
        {TFunc_Instances_ByteArray_readUTFBytes::Func, &StringCI, "readUTFBytes", "flash.utils:IDataInput", CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeBoolean::Func, NULL, "writeBoolean", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeByte::Func, NULL, "writeByte", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeBytes::Func, NULL, "writeBytes", "flash.utils:IDataOutput", CT_Method, 1, 3},
        {TFunc_Instances_ByteArray_writeDouble::Func, NULL, "writeDouble", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeFloat::Func, NULL, "writeFloat", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeInt::Func, NULL, "writeInt", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeMultiByte::Func, NULL, "writeMultiByte", "flash.utils:IDataOutput", CT_Method, 2, 2},
        {TFunc_Instances_ByteArray_writeObject::Func, NULL, "writeObject", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeShort::Func, NULL, "writeShort", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeUnsignedInt::Func, NULL, "writeUnsignedInt", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeUTF::Func, NULL, "writeUTF", "flash.utils:IDataOutput", CT_Method, 1, 1},
        {TFunc_Instances_ByteArray_writeUTFBytes::Func, NULL, "writeUTFBytes", "flash.utils:IDataOutput", CT_Method, 1, 1},
    };

    ByteArray::ByteArray(VM& vm, const ClassInfo& ci)
    : Traits(vm, ci)
    {
//##protect##"InstanceTraits::ByteArray::ByteArray()"
        SetArrayLike();
//##protect##"InstanceTraits::ByteArray::ByteArray()"
        SetMemSize(sizeof(Instances::ByteArray));
        RegisterImplementedInterface(Multiname(GetVM(), "flash.utils.IDataInput"));
        RegisterImplementedInterface(Multiname(GetVM(), "flash.utils.IDataOutput"));

    }

    Pickable<Instances::ByteArray> ByteArray::MakeInstance(Traits& t)
    {
        return Pickable<Instances::ByteArray>(new(t.Alloc()) Instances::ByteArray(t));
    }

    void ByteArray::MakeObject(Value& result, Traits& t)
    {
        result = MakeInstance(t);
    }

//##protect##"instance_traits$methods"
//##protect##"instance_traits$methods"

} // namespace InstanceTraits

namespace Classes
{
    ByteArray::ByteArray(ClassTraits::Traits& t)
    : Class(t)
    {
//##protect##"class_::ByteArray::ByteArray()"
        DefEncoding = Instances::ByteArray::encAMF3;
//##protect##"class_::ByteArray::ByteArray()"
    }
    void ByteArray::defaultObjectEncodingSet(Value& result, UInt32 value)
    {
//##protect##"class_::ByteArray::defaultObjectEncodingSet()"
        SF_UNUSED1(result);

        if (value != Instances::ByteArray::encAMF0 || value != Instances::ByteArray::encAMF3)
            return GetVM().ThrowRangeError(VM::Error(VM::eIllegalOperandTypeError, GetVM() SF_DEBUG_ARG("something") SF_DEBUG_ARG("encAMF0 or encAMF3")));

        DefEncoding = static_cast<Instances::ByteArray::EncodingType>(value);
//##protect##"class_::ByteArray::defaultObjectEncodingSet()"
    }
    void ByteArray::defaultObjectEncodingGet(UInt32& result)
    {
//##protect##"class_::ByteArray::defaultObjectEncodingGet()"
        result = DefEncoding;
//##protect##"class_::ByteArray::defaultObjectEncodingGet()"
    }
//##protect##"class_$methods"
//##protect##"class_$methods"

} // namespace Classes

typedef ThunkFunc1<Classes::ByteArray, Classes::ByteArray::mid_defaultObjectEncodingSet, Value, UInt32> TFunc_Classes_ByteArray_defaultObjectEncodingSet;
typedef ThunkFunc0<Classes::ByteArray, Classes::ByteArray::mid_defaultObjectEncodingGet, UInt32> TFunc_Classes_ByteArray_defaultObjectEncodingGet;

template <> const TFunc_Classes_ByteArray_defaultObjectEncodingSet::TMethod TFunc_Classes_ByteArray_defaultObjectEncodingSet::Method = &Classes::ByteArray::defaultObjectEncodingSet;
template <> const TFunc_Classes_ByteArray_defaultObjectEncodingGet::TMethod TFunc_Classes_ByteArray_defaultObjectEncodingGet::Method = &Classes::ByteArray::defaultObjectEncodingGet;

namespace ClassTraits
{
    const ThunkInfo ByteArray::ti[ByteArray::ThunkInfoNum] = {
        {TFunc_Classes_ByteArray_defaultObjectEncodingSet::Func, NULL, "defaultObjectEncoding", NULL, CT_Set, 1, 1},
        {TFunc_Classes_ByteArray_defaultObjectEncodingGet::Func, &uintCI, "defaultObjectEncoding", NULL, CT_Get, 0, 0},
    };
    ByteArray::ByteArray(VM& vm)
    : Traits(vm, ByteArrayCI)
    {
//##protect##"ClassTraits::ByteArray::ByteArray()"
//##protect##"ClassTraits::ByteArray::ByteArray()"
        MemoryHeap* mh = vm.GetMemoryHeap();

        Pickable<InstanceTraits::Traits> it(SF_HEAP_NEW_ID(mh, StatMV_VM_ITraits_Mem) InstanceTraits::ByteArray(vm, ByteArrayCI));
        SetInstanceTraits(it);

        Pickable<Class> cl(SF_HEAP_NEW_ID(mh, StatMV_VM_Class_Mem) Classes::ByteArray(*this));
        it->SetConstructor(cl);

    }

    Pickable<Traits> ByteArray::MakeClassTraits(VM& vm)
    {
        return Pickable<Traits>(SF_HEAP_NEW_ID(vm.GetMemoryHeap(), StatMV_VM_CTraits_Mem) ByteArray(vm));
    }
//##protect##"ClassTraits$methods"
//##protect##"ClassTraits$methods"

} // namespace ClassTraits

const ClassInfo ByteArrayCI = {
    ClassInfo::CompileTime,
    "ByteArray", "flash.utils", &ObjectCI,
    ClassTraits::ByteArray::MakeClassTraits,
    ClassTraits::ByteArray::ThunkInfoNum,
    0,
    InstanceTraits::ByteArray::ThunkInfoNum,
    0,
    ClassTraits::ByteArray::ti,
    NULL,
    InstanceTraits::ByteArray::ti,
    NULL,
};


}}} // namespace Scaleform { namespace GFx { namespace AS3

