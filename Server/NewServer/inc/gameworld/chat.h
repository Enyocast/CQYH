#ifndef _CHAT_MGR_H_
#define _CHAT_MGR_H_

typedef struct rsa_st RSA;

BOOL Buffer2String(UINT8* pBuffer, INT32 nBufferSize, char* pText, INT32& nTextSize);

// 返回false 表示 ownerid 跟装备的owner不对或者签名验证不对
BOOL String2Buffer(UCHAR* pBuffer, INT32& nBufferSize, char* pText);

#endif // _CHAT_MGR_H_
