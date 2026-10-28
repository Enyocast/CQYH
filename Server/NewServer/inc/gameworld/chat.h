#ifndef _CHAT_MGR_H_
#define _CHAT_MGR_H_

typedef struct rsa_st RSA;

BOOL Buffer2String(UINT8* pBuffer, INT32 nBufferSize, char* pText, INT32& nTextSize);

// Return false if ownerid does not match the equipment owner or signature verification fails
BOOL String2Buffer(UCHAR* pBuffer, INT32& nBufferSize, char* pText);

#endif // _CHAT_MGR_H_
