#include "stdafx.h"
#include "share_mem_io.h"
#include "cas.h"

CShareMemBuffer::CShareMemBuffer(void)
{
	memset(&m_Ptr, 0, sizeof(m_Ptr));

	m_pHeader = NULL;
	m_pUserBlock = NULL;
	m_nBlockSize = 0;
	m_nReadOffset = 0;
	m_nWriteOffset = 0;
	m_bEmpty = TRUE;
	m_nLastVirtualReadPtr = 0;
}

CShareMemBuffer::~CShareMemBuffer(void)
{

}

BOOL CShareMemBuffer::Create(const char* szName, INT32 nSize, INT32 nUserHeaderSize)
{
	INT32 nRetCode = 0;

	nRetCode = CreateSharedMemory(szName, nSize + sizeof(MemHeader) + nUserHeaderSize, m_Ptr);
	LOG_PROCESS_ERROR(nRetCode);
	LOG_PROCESS_ERROR(m_Ptr.pSharedMem != NULL && m_Ptr.pFd != NULL);

	m_pHeader = (MemHeader*)(m_Ptr.pSharedMem + nUserHeaderSize);
	if(m_pHeader->nMemTag != SHARED_MEM_TAG)
	{
		m_nBlockSize = nSize;
		memset(m_pHeader, 0, sizeof(MemHeader));
		m_pHeader->nMemTag = SHARED_MEM_TAG;
		m_pHeader->nBlockSize = m_nBlockSize;
		m_bEmpty = TRUE;
	}

	m_pUserBlock = (char*)m_pHeader + sizeof(MemHeader);
	m_nBlockSize = m_pHeader->nBlockSize;
	m_nReadOffset = m_pHeader->nReadOffset;
	m_nWriteOffset = m_pHeader->nWriteOffset;
	//m_nReadPtrCycle = m_pHeader->nReadPtrCycle;
	//m_nWritePtrCycle = m_pHeader->nWritePtrCycle;

	return TRUE;
Exit0:
	return FALSE;
}

BOOL CShareMemBuffer::Open(const char* szName)
{
	INT32 nRetCode = 0;

	nRetCode = OpenSharedMemory(szName, m_Ptr);
	LOG_PROCESS_ERROR(nRetCode);
	LOG_PROCESS_ERROR(m_Ptr.pSharedMem != NULL && m_Ptr.pFd != NULL);

	return TRUE;
Exit0:
	return FALSE;
}

void CShareMemBuffer::Clear(void)
{
	m_pHeader->nReadOffset = 0;
	m_pHeader->nWriteOffset = 0;

	m_nReadOffset = 0;
	m_nWriteOffset = 0;
	m_bEmpty = TRUE;
}

void CShareMemBuffer::Destroy(void)
{
	CloseSharedMemory(m_Ptr);
}

BOOL CShareMemBuffer::Write(const char* pBuff, INT32 nSize)
{
	m_nReadOffset = m_pHeader->nReadOffset;
	m_nWriteOffset = m_pHeader->nWriteOffset;

	INT32 nRemain = 0;

	m_bEmpty = FALSE;

	if(m_nWriteOffset < m_nReadOffset)
	{
		nRemain = m_nReadOffset - m_nWriteOffset;
		PROCESS_ERROR(nRemain >= nSize);

		memcpy(m_pUserBlock + m_nWriteOffset, pBuff, nSize);
		m_nWriteOffset += nSize;
		m_pHeader->nWriteOffset = m_nWriteOffset;

		return TRUE;
	}
	else if(m_nWriteOffset + nSize < m_nReadOffset + m_nBlockSize)
	{
		nRemain = m_nBlockSize - m_nWriteOffset;

		if(nRemain >= nSize)
		{
			memcpy(m_pUserBlock + m_nWriteOffset, pBuff, nSize);
			m_nWriteOffset += nSize;
			m_pHeader->nWriteOffset = m_nWriteOffset;

			return TRUE;
		}

		INT32 nRemain2 = nSize - nRemain;
		memcpy(m_pUserBlock + m_nWriteOffset, pBuff, nRemain);
		memcpy(m_pUserBlock, pBuff + nRemain, nRemain2);

		m_nWriteOffset = nRemain2;
		m_pHeader->nWriteOffset = m_nWriteOffset;

		return TRUE;
	}

Exit0:
	return FALSE;
}
BOOL CShareMemBuffer::Read(char* pBuff, INT32 nSize)
{
	m_nReadOffset = m_pHeader->nReadOffset;

	//let cpu flush data immidiately.
	_EVA32(&m_nWriteOffset, m_pHeader->nWriteOffset);

	INT32 nRemain = 0;

	//PROCESS_ERROR(!m_bEmpty);

	if(m_nReadOffset <= m_nWriteOffset)
	{
		nRemain = m_nWriteOffset - m_nReadOffset;
		if(nRemain < nSize)
			return FALSE;

		memcpy(pBuff, m_pUserBlock + m_nReadOffset, nSize);
		m_nReadOffset += nSize;
		m_pHeader->nReadOffset = m_nReadOffset;

		return TRUE;
	}
	else if(m_nReadOffset + nSize < m_nWriteOffset + m_nBlockSize)
	{
		nRemain = m_nBlockSize - m_nReadOffset;

		if(nRemain >= nSize)
		{
			memcpy(pBuff, m_pUserBlock + m_nReadOffset, nSize);
			m_nReadOffset += nSize;
			m_pHeader->nReadOffset = m_nReadOffset;
			return TRUE;
		}

		INT32 nRemain2 = nSize - nRemain;
		memcpy(pBuff, m_pUserBlock + m_nReadOffset, nRemain);
		memcpy(pBuff + nRemain, m_pUserBlock, nRemain2);

		m_nReadOffset = nRemain2;
		m_pHeader->nReadOffset = m_nReadOffset;

		return TRUE;
	}

Exit0:
	return FALSE;
}

