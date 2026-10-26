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

#ifndef _CLIDEFINE_H_
#define _CLIDEFINE_H_

#include <sdbase.h>

/// 发送缓冲区大小
#define SD_CLIENT_SENDBUFFER    64 * 1024
/// 报文最大长度
#define PACKAGE_LENGTH          64 * 1024

/**
 * @brief 网络层报文头
 */
#pragma pack(push, 1)
struct STNetMsgHeader
{
    UINT16	wMsgID;         ///< 包头标示
    UINT32	dwDataLen;      ///< 数据包长度
};
#pragma pack(pop)

/// 报文内容最大长度
#define PACKAGE_CONTENT_LENGTH  PACKAGE_LENGTH - sizeof(STNetMsgHeader)

/// 客户端版本
const SGDP::SSGDPVersion SDCLIENT_MODULE_VERSION = {3, 2, 0, 0};

#endif // #ifndef _CLIDEFINE_H_
