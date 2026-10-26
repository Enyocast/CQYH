// SHANDA GAMES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Shanda Games and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1999-2010 Shanda Games.
//      All Rights Reserved.
//
// Shanda Games Limited, Shanghai, China, 201203
// http://www.shandagames.com

#ifndef _PACKETPARSER_H_
#define _PACKETPARSER_H_


class CCliPacketParser: public ISDPacketParser
{
#define SDLOG_MSG_HEAD_LEN            4
#define SDLOG_MSG_TIMESTAMP_SIZE      20
public:
    CCliPacketParser();
    ~CCliPacketParser();
public:
    virtual INT32 SDAPI ParsePacket(const CHAR* pBuf, UINT32 dwLen);
};

#endif //#ifndef _PACKETPARSER_H_

