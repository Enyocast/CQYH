#ifndef _INTERNAL_MESSAGE_HEADER_H_
#define _INTERNAL_MESSAGE_HEADER_H_


#include "common.h"
#include "server_def.h"

#ifdef WIN32
    #pragma warning(disable:4200)
#endif  // WIN32

#pragma pack(push, 1)

namespace InternalMessage
{
	struct MESSAGE_HEADER
	{
		UINT16 wMsg;
	};

    enum
    {
        max_message_count = 65536
    };

    enum
    {
        m2a_message_begin = 0x0000,
        m2a_message_end =   0x0100,
		b2m_message_begin,
		b2m_message_end =   0x0200,
		m2b_message_begin,
		m2b_message_end =   0x0300,
		o2m_message_begin,
		o2m_message_end	  = 0x0400,
		m2o_message_begin,
		m2o_message_end =   0x0500,
		o2g_message_begin,
		o2g_message_end	=   0x0600,
		g2o_message_begin,
		g2o_message_end	=   0x0700,
        d2m_message_begin,
        d2m_message_end =   0x0800,
        d2g_message_begin,
        d2g_message_end =   0x0900,
        d2t_message_begin,
        d2t_message_end =   0x0A00,
        g2d_message_begin,
        g2d_message_end =   0x0B00,
        g2t_message_begin,
        g2t_message_end =   0x0C00,
        l2t_message_begin,
        l2t_message_end =   0x0D00,
        m2t_message_begin,
        m2t_message_end =   0x0E00,
        t2d_message_begin,
        t2d_message_end =   0x0F00,
        t2g_message_begin,
        t2g_message_end =   0x1000,
        t2l_message_begin,
        t2l_message_end =   0x1100,
        t2m_message_begin,
        t2m_message_end =   0x1200,
        l2m_message_begin,
        l2m_message_end =   0x1300,
        m2l_message_begin,
        m2l_message_end =   0x1400,
        m2d_message_begin,
        m2d_message_end =   0x1500,
        gmsvr_message_begin,
        gmsvr_message_end = 0x1600,
        gmtl_message_begin,
        gmtl_message_end =  0x1700,
        cer_message_begin,
        cer_message_end =   0x1800,
        ns_message_begin,
        ns_message_end =   0x1900,
		mg2mm_message_begin,
		mg2mm_message_end = 0x1A00,
		mm2mg_message_begin,
		mm2mg_message_end = 0x1B00,
		mg2l_message_begin,
		mg2l_message_end = 0x1C00,
		l2mg_message_begin,
		l2mg_message_end = 0x1D00,
		mm2m_message_begin,
		mm2m_message_end = 0x1E00,
		m2mm_message_begin,
		m2mm_message_end = 0x1F00,

        g2m_message_begin = 0x8000,
        g2m_message_end =   0x9000,
        m2g_message_begin,
        m2g_message_end =   0xA000,
    };
};

#pragma pack(pop)

#endif // _internal_message_header_h__
