/**************************************************************************

Filename    :   SF_FileSceIO.cpp
Content     :   File using sceIoRead* functions
Created     :
Authors     :   Andrew Reisse

Copyright   :   Copyright 2011 Autodesk, Inc. All Rights reserved.

Use of this software is subject to the terms of the Autodesk license
agreement provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

**************************************************************************/

#include "SF_File.h"
#include "SF_Debug.h"
#include "SF_SysFile.h"

#include <kernel.h>
#define SCE_RTC_USE_LIBC_TIME_H 1
#include <rtc.h>

namespace Scaleform {

class FileSceIO : public File
{
protected:
    // Allocated filename
    char*       pFileName;

    // File handle & open mode
    bool        Opened;
    int         fd;
    // Error code for last request
    int        ErrorCode;

public:

    FileSceIO() { Opened = 0; pFileName =0; }
    // Initialize file by opening it
    FileSceIO(const char* pfileName, int flags, int Mode);

    ~FileSceIO()
    {
        if (Opened)
            Close();
        if (pFileName)
            SF_FREE(pFileName);
    }

    virtual const char* GetFilePath();

    // ** File Information
    virtual bool        IsValid();
    virtual bool        IsWritable();
    // Return position / file size
    virtual int        Tell();
    virtual SInt64      LTell();
    virtual int        GetLength();
    virtual SInt64      LGetLength();

    //  virtual bool        Stat(FileStats *pfs);
    virtual int        GetErrorCode();

    // ** GFxStream implementation & I/O
    virtual int        Write(const UByte *pbuffer, int numBytes);
    virtual int        Read(UByte *pbuffer, int numBytes);
    virtual int        SkipBytes(int numBytes);
    virtual int        BytesAvailable();
    virtual bool        Flush();
    virtual int        Seek(int offset, int origin);
    virtual SInt64      LSeek(SInt64 offset, int origin);

    virtual bool        ChangeSize(int newSize);
    virtual int        CopyFromStream(File *pStream, int byteSize);
    virtual bool        Close();
    //virtual bool      CloseCancel();
};


FileSceIO::FileSceIO(const char *pfileName, int flags, int mode)
{
    SF_UNUSED(mode);
    // Save data
    int nameLength = (int) strlen(pfileName);
    pFileName = (char*)SF_ALLOC(nameLength+1, Stat_Default_Mem);
    memcpy(pFileName, pfileName, nameLength+1);

    int omode = ((flags & Open_Read) ? SCE_O_RDONLY : 0) |
        ((flags & Open_Write) ? SCE_O_WRONLY : 0) |
        ((flags & Open_Truncate) ? SCE_O_TRUNC : 0) |
        ((flags & Open_Create) ? SCE_O_CREAT : 0);

    fd = sceIoOpen(pfileName, omode, mode);

    Opened = (fd>=0);
    if (!Opened)
        ErrorCode = Error_IOError;
    else
    {
        ErrorCode = 0;
    }
}

const char* FileSceIO::GetFilePath()
{
    return pFileName;
}


// ** File Information
bool    FileSceIO::IsValid()
{
    return Opened;
}
bool    FileSceIO::IsWritable()
{
    return 0;
}

// Return position / file size
int    FileSceIO::Tell()
{
    return sceIoLseek32(fd, 0, SCE_SEEK_CUR);
}

SInt64  FileSceIO::LTell()
{
    return sceIoLseek(fd, 0, SCE_SEEK_CUR);
}

int    FileSceIO::GetLength()
{
    SceOff pos = sceIoLseek(fd, 0, SCE_SEEK_CUR);
    int len = sceIoLseek32(fd, 0, SCE_SEEK_END);
    sceIoLseek(fd, pos, SCE_SEEK_SET);
    return len;
}
SInt64  FileSceIO::LGetLength()
{
    SceOff pos = sceIoLseek(fd, 0, SCE_SEEK_CUR);
    SInt64 len = sceIoLseek(fd, 0, SCE_SEEK_END);
    sceIoLseek(fd, pos, SCE_SEEK_SET);
    return len;
}

int    FileSceIO::GetErrorCode()
{
    return ErrorCode;
}

int    FileSceIO::Write(const UByte *pbuffer, int numBytes)
{
    return sceIoWrite(fd, pbuffer, numBytes);
}

int    FileSceIO::Read(UByte *pbuffer, int numBytes)
{
    return sceIoRead(fd, pbuffer, numBytes);
}

// Seeks ahead to skip bytes
int    FileSceIO::SkipBytes(int numBytes)
{
    return sceIoLseek(fd, numBytes, SCE_SEEK_CUR);
}

// Return # of bytes till EOF
int    FileSceIO::BytesAvailable()
{
    SceOff pos = sceIoLseek(fd, 0, SCE_SEEK_CUR);
    int len = sceIoLseek32(fd, 0, SCE_SEEK_END);
    sceIoLseek(fd, pos, SCE_SEEK_SET);
    return len-pos;
}

// Flush file contents
bool    FileSceIO::Flush()
{
    return 1;
}

int    FileSceIO::Seek(int offset, int origin)
{
    int op = SCE_SEEK_SET;
    switch(origin)
    {
    case Seek_Set: op = SCE_SEEK_SET; break;
    case Seek_Cur: op = SCE_SEEK_CUR; break;
    case Seek_End: op = SCE_SEEK_END; break;
    }

    return sceIoLseek32(fd, offset, op);
}

SInt64  FileSceIO::LSeek(SInt64 offset, int origin)
{
    int op = SCE_SEEK_SET;
    switch(origin)
    {
    case Seek_Set: op = SCE_SEEK_SET; break;
    case Seek_Cur: op = SCE_SEEK_CUR; break;
    case Seek_End: op = SCE_SEEK_END; break;
    }

    return sceIoLseek(fd, offset, op);
}

bool    FileSceIO::ChangeSize(int newSize)
{
    SF_UNUSED(newSize);
    SF_DEBUG_WARNING(1, "File::ChangeSize not supported");
    ErrorCode = Error_IOError;
    return 0;
}

int    FileSceIO::CopyFromStream(File *pstream, int byteSize)
{
    ErrorCode = Error_IOError;
    return 0;
}


bool    FileSceIO::Close()
{
    int closeRet = sceIoClose(fd);

    if (closeRet)
    {
        ErrorCode = Error_IOError;
        return 0;
    }
    else
    {
        Opened    = 0;
        ErrorCode = 0;
    }

    return 1;
}

File *FileSceIOOpen(const char *ppath, int flags)
{
    return new FileSceIO(ppath, flags, 0666);
}

bool    SysFile::GetFileStat(FileStat* pfileStat, const String& ppath)
{
    SceIoStat fileStat;
    // Stat returns 0 for success.
    if (sceIoGetstat(ppath, &fileStat) != 0)
        return false;

    pfileStat->FileSize = fileStat.st_size;
    time_t t;
    sceRtcGetTime_t(&fileStat.st_mtime, &t);
    pfileStat->ModifyTime = t;
    sceRtcGetTime_t(&fileStat.st_atime, &t);
    pfileStat->AccessTime = t;
    return true;
}

}
