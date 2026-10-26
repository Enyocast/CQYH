/**************************************************************************

Filename    :   SF_FileWiiU.cpp
Content     :   

Created     :   
Authors     :   

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "SF_Types.h"
#include "SF_Debug.h"

#include "SF_SysFile.h"
#include "SF_HeapNew.h"

#include <cafe/fsa.h>

namespace Scaleform {

FSAClientHandle FsaClient;

void SysFile::initializeSysFileSystem()
{
    FsaClient = FSAAddClient(0);
}

void SysFile::shutdownSysFileSystem()
{
    FSADelClient(FsaClient);
}


// ***** File interface

static int SFerror (FSAStatus err)
{
    if (err == FSA_STATUS_NOT_FOUND)
        return FileConstants::Error_FileNotFound;
    else if (err == FSA_STATUS_ACCESS_ERROR || err == FSA_STATUS_PERMISSION_ERROR)
        return FileConstants::Error_Access;
    else if (err == FSA_STATUS_OK)
        return 0;
    else
        return FileConstants::Error_IOError;
};


class FileWiiU : public File
{
protected:

    // Allocated filename
    String        FileName;

    // File handle & open mode
    FSAFileHandle Fs;
    bool          Opened;
    int           OpenFlags;
    // Error code for last request
    int           ErrorCode;
    int           LastOp;

    // buffer for unaligned calls
    UByte*        pABuffer;
    UPInt         ABufferSize;

public:

    FileWiiU()
    {
        Opened = 0; FileName = "";
        pABuffer = 0; ABufferSize = 0;
    }
    // Initialize file by opening it
    FileWiiU(const String& fileName, int flags, int Mode);
    // The 'pfileName' should be encoded as UTF-8 to support international file names.
    FileWiiU(const char* pfileName, int flags, int Mode);

    ~FileWiiU()
    {
        if (Opened)
            Close();
        if (pABuffer)
            SF_FREE(pABuffer);
    }

    virtual const char* GetFilePath();

    // ** File Information
    virtual bool        IsValid();
    virtual bool        IsWritable();
    //virtual bool      IsRecoverable();
    // Return position / file size
    virtual int         Tell();
    virtual SInt64      LTell();
    virtual int         GetLength();
    virtual SInt64      LGetLength();

    virtual int         GetErrorCode();

    // ** Stream implementation & I/O
    virtual int         Write(const UByte *pbuffer, int numBytes);
    virtual int         Read(UByte *pbuffer, int numBytes);
    virtual int         SkipBytes(int numBytes);
    virtual int         BytesAvailable();
    virtual bool        Flush();
    virtual int         Seek(int offset, int origin);
    virtual SInt64      LSeek(SInt64 offset, int origin);

    virtual bool        ChangeSize(int newSize);
    virtual int         CopyFromStream(File *pStream, int byteSize);
    virtual bool        Close();
    //virtual bool      CloseCancel();
private:
    void                init();
};


// Initialize file by opening it
FileWiiU::FileWiiU(const String& fileName, int flags, int mode)
  : FileName(fileName), OpenFlags(flags)
{
    SF_UNUSED(mode);
    pABuffer = 0; ABufferSize = 0;
    init();
}

// The 'pfileName' should be encoded as UTF-8 to support international file names.
FileWiiU::FileWiiU(const char* pfileName, int flags, int mode)
  : FileName(pfileName), OpenFlags(flags)
{
    SF_UNUSED(mode);
    pABuffer = 0; ABufferSize = 0;
    init();
}

void FileWiiU::init()
{
    const char *omode = "r";

    // this is all wrong
    if ((OpenFlags & (Open_Truncate|Open_Create)) == (Open_Truncate|Open_Create))
    {
        if (OpenFlags & Open_Read)
            omode = "w+";
        else
            omode = "w";
    }
    else if (OpenFlags & Open_Create)
    {
        if (OpenFlags & Open_Read)
            omode = "r+";
        else
            omode = "";
    }
    else if (OpenFlags & Open_Write)
        omode = "r+";

    ErrorCode = SFerror(FSAOpenFile(FsaClient, FileName.ToCStr(), omode, &Fs));
    Opened = (ErrorCode == 0);
    LastOp = 0;
}


const char* FileWiiU::GetFilePath()
{
    return FileName.ToCStr();
}


// ** File Information
bool    FileWiiU::IsValid()
{
    return Opened;
}
bool    FileWiiU::IsWritable()
{
    return IsValid() && (OpenFlags&Open_Write);
}

// Return position / file size
int     FileWiiU::Tell()
{
    FSAFilePosition pos;
    ErrorCode = SFerror(FSAGetPosFile(FsaClient, Fs, &pos));
    return ErrorCode ? -1 : pos;
}

SInt64  FileWiiU::LTell()
{
    FSAFilePosition pos;
    ErrorCode = SFerror(FSAGetPosFile(FsaClient, Fs, &pos));
    return ErrorCode ? -1 : pos;
}

int     FileWiiU::GetLength()
{
    return LGetLength();
}
SInt64  FileWiiU::LGetLength()
{
    FSAStat st;
    ErrorCode = SFerror(FSAStatFile(FsaClient, Fs, &st));
    if (!ErrorCode)
        return st.size;
    else
        return -1;
}

int     FileWiiU::GetErrorCode()
{
    return ErrorCode;
}

// ** Stream implementation & I/O
int     FileWiiU::Write(const UByte *pbuffer, int numBytes)
{
    LastOp = Open_Write;
    FSAStatus result;

    if (((UPInt)pbuffer & (PPC_IO_BUFFER_ALIGN-1)) || (numBytes & (PPC_IO_BUFFER_ALIGN-1)))
    {
        int roundedSize = (numBytes+PPC_IO_BUFFER_ALIGN-1) & ~(PPC_IO_BUFFER_ALIGN-1);
        if (ABufferSize < roundedSize)
        {
            SF_FREE(pABuffer);
            SF_DEBUG_WARNING(1, "FileWiiU::Write: buffer or count not aligned, allocating extra buffer");
            pABuffer = (UByte*) SF_MEMALIGN(roundedSize, PPC_IO_BUFFER_ALIGN, Stat_Default_Mem);
            ABufferSize = roundedSize;
        }

        memcpy(pABuffer, pbuffer, numBytes);
        result = FSAWriteFile(FsaClient, pABuffer, 1, numBytes, Fs, 0);
    }
    else
        result = FSAWriteFile(FsaClient, const_cast<UByte*>(pbuffer), 1, numBytes, Fs, 0);

    ErrorCode = result < 0 ? SFerror(result) : 0;
    return result;
}

int     FileWiiU::Read(UByte *pbuffer, int numBytes)
{
    LastOp = Open_Read;

    FSAStatus result;

    if (((UPInt)pbuffer & (PPC_IO_BUFFER_ALIGN-1)) || (numBytes & (PPC_IO_BUFFER_ALIGN-1)))
    {
        int roundedSize = (numBytes+PPC_IO_BUFFER_ALIGN-1) & ~(PPC_IO_BUFFER_ALIGN-1);
        if (ABufferSize < roundedSize)
        {
            SF_FREE(pABuffer);
            SF_DEBUG_WARNING(1, "FileWiiU::Read: buffer or count not aligned, allocating extra buffer");
            pABuffer = (UByte*) SF_MEMALIGN(roundedSize, PPC_IO_BUFFER_ALIGN, Stat_Default_Mem);
            ABufferSize = roundedSize;
        }

        result = FSAReadFile(FsaClient, pABuffer, 1, numBytes, Fs, 0);
        if (result < 0)
        {
            ErrorCode = SFerror(result);
            return -1;
        }
        memcpy(pbuffer, pABuffer, result);
    }
    else
        result = FSAReadFile(FsaClient, pbuffer, 1, numBytes, Fs, 0);

    ErrorCode = result < 0 ? SFerror(result) : 0;
    return result;
}

// Seeks ahead to skip bytes
int     FileWiiU::SkipBytes(int numBytes)
{
    SInt64 pos    = LTell();
    SInt64 newPos = LSeek(numBytes, Seek_Cur);

    // Return -1 for major error
    if ((pos==-1) || (newPos==-1))
    {
        return -1;
    }
    //ErrorCode = ((NewPos-Pos)<numBytes) ? errno : 0;

    return int (newPos-(int)pos);
}

// Return # of bytes till EOF
int     FileWiiU::BytesAvailable()
{
    SInt64 pos    = LTell();
    SInt64 endPos = LGetLength();

    // Return -1 for major error
    if ((pos==-1) || (endPos==-1))
    {
        return 0;
    }
    else
        ErrorCode = 0;

    return int (endPos-(int)pos);
}

// Flush file contents
bool    FileWiiU::Flush()
{
    return true;
}

int     FileWiiU::Seek(int offset, int origin)
{
    return (int)LSeek(offset, origin);
}

SInt64  FileWiiU::LSeek(SInt64 offset, int origin)
{
    if (origin == Seek_Cur)
        offset += LTell();
    else if (origin == Seek_End)
        offset += LGetLength();

    ErrorCode = SFerror(FSASetPosFile(FsaClient, Fs, offset));
    return ErrorCode ? -1 : offset;
}

bool    FileWiiU::ChangeSize(int newSize)
{
    SF_UNUSED(newSize);
    SF_DEBUG_WARNING(1, "File::ChangeSize not supported");
    ErrorCode = Error_IOError;
    return 0;
}

int     FileWiiU::CopyFromStream(File *pstream, int byteSize)
{
    UByte   buff[0x4000];
    int     count = 0;
    int     szRequest, szRead, szWritten;

    while (byteSize)
    {
        szRequest = (byteSize > int(sizeof(buff))) ? int(sizeof(buff)) : byteSize;

        szRead    = pstream->Read(buff, szRequest);
        szWritten = 0;
        if (szRead > 0)
            szWritten = Write(buff, szRead);

        count    += szWritten;
        byteSize -= szWritten;
        if (szWritten < szRequest)
            break;
    }
    return count;
}


bool    FileWiiU::Close()
{
    ErrorCode = SFerror(FSACloseFile(FsaClient, Fs));
    Opened    = 0;
    Fs        = 0;

    return (ErrorCode == 0);
}

File *FileWiiUOpen(const String& path, int flags, int mode)
{
    return SF_NEW FileWiiU(path, flags, mode);
}

bool    SysFile::GetFileStat(FileStat* pfileStat, const String& path)
{
    FSAFileHandle fs;
    FSAStat       st;
    FSAStatus     result = FSAOpenFile(FsaClient, path.ToCStr(), "r", &fs);

    if (result)
        return false;

    result = FSAStatFile(FsaClient, fs, &st);
    FSACloseFile(FsaClient, fs);

    if (result == 0)
    {
        pfileStat->AccessTime = 0;
        pfileStat->ModifyTime = st.mtime;
        pfileStat->FileSize = st.size;
        return true;
    }
    else
        return false;
}

} // Scaleform
