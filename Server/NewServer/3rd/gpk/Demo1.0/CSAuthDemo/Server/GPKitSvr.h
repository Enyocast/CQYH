#ifndef SVRDYNCODE_H
#define SVRDYNCODE_H

#ifdef WIN32
	#ifndef GPK_API
		#define GPK_API   __stdcall
	#endif
#else
	#define GPK_API	
#endif

enum GPK_CHECK_INFO
{
	CHECK_EXCEPT = -1,					//CSAUTH error
	CHECK_SUCCEED = 0,					//Check succeeded
	CHECK_CSAUTH_ERROR = 0x1,			//Incorrect client calculation result; abnormal client
	CHECK_NO_ADMIN = 0x2,				//No administrator privileges
	CHECK_WINDOWS64BIT = 0x4,			//The current operating system is 64-bit
	CHECK_CSAUTH_ERRORLEN = 0x8,		//Incorrect client packet length
	CHECK_CSAUTH_ERRORDYN = 0x10,		//Incorrect client packet length
	CHECK_FIND_CHEAT_EXCEPT = 0x20,		//Cheat information packet is corrupted
	CHECK_FIND_CHEAT_NEED_KICK = 0x40,	//Cheat detected; disconnect the player
	CHECK_FIND_CHEAT_ONLY_LOG = 0x80	//Cheat detected; log only, do not disconnect the player
};

enum GPK_CHEAT_INFO_TYPE
{
	TYPE_NOCHAET = 0,		//not find cheat
	TYPE_IDS = 1,			//CHEAT_IDS type
	TYPE_DETAIL = 2			//CHEAT_DETAIL type
};

#pragma pack(push,1)
typedef struct _CHEAT_INFO
{
	DWORD		CHECKSUM;
	BYTE		CHEAT_INFO_TYPE;
	union {
		DWORD		CHEAT_IDS[5];
		struct {
			DWORD		CHEAT_ID;
			char		DetailString[56];
		} CHEAT_DETAIL;
	}CHEATTYPE;
}CHEAT_INFO,*PCHEAT_INFO;
#pragma pack(pop)

/* ====================================================================
 * ISDSvrDynCode: server side dynamic code component. ISDSvrDynCode provides
 * dynamic encrypt and decrypt methods.
 *
 * Dynamic Code Binary File: compiled machine code of Encrypt and Decrypt
 * function are saved in binary files. File name format of these binary 
 * files are *.server.bin and *.client.bin, * stand for number, for example 
 * 1.server.bin, 1.client.bin. These numbers are called CodeIndex. Each 
 * server binary files has a corresponding client binary files with same 
 * CodeIndex. *.server.bin contains binary code for server, *.client.bin 
 * contains binary code for client. Both server and client binary files 
 * are used by server. Generally, there are multiple pairs of server and 
 * client binary files in one server. Each pair contains different encrypt
 * -decrypt binary code.
 *
 * Usage:
 * 1. Create ISDSvrDynCode component, call SDCreateSvrDynCode
 * 2. Load Dynamic Code Binary Files, call ISDSvrDynCode::LoadBinary
 * 3. Get random CodeIndex, call ISDSvrDynCode::GetRandIdx
 * 4. Get Client binary code, call ISDSvrDynCode::GetCltDynCode
 * 5. Transfer the client code to client
 * 6. To encrypt: call ISDSvrDynCode::Encode
 * 7. To decrypt: call ISDSvrDynCode::Decode
 * 8. when finish, call ISDSvrDynCode::Release to release component
 */
typedef void (GPK_API * fnGPK_SvrCallBack)(void * Object,unsigned char *lpData,unsigned long nLen);

namespace SGPK{

class IGPKCSAuth
{
public:
	//Function: Generate CSAuth data
	//Parameter:ppDataRet:address of pointer ,recive the auth data
	//			Object: Callback object pointer; may be a socket, user object or NULL, depending on the game architecture
	//          SendToClt: Callback function
	//return: Positive data length, -1 on error, or 0 if the client did not answer the previous Auth check; a cheat blocked the Auth packet.
	virtual int  GetAuthData(const unsigned char **ppDataRet,void *Object,fnGPK_SvrCallBack SendToClt=NULL) =0;

	//Function: Check Auth data returned by the client.
	//Parameter:ppDataRet:address of pointer ,recive the auth data
	//          lpData: Input data pointer
	//          nLen: Data length
	//return: See GPK_CHECK_INFO for return values;
	virtual int  CheckAuthReply(const unsigned char **ppDataRet,unsigned char * lpData, unsigned long nLen)=0;

	virtual int GetCSAuthDynCode(const unsigned char **ppCodeRet) = 0;

	//Function: Release the object of IGPKCSAuth
	virtual void Release()=0;

};


class IGPKSvrDynCode
{
public:
    virtual GPK_API ~IGPKSvrDynCode() {}

    //Function: import dynamic code
    //Parameter: pszSvrBinDir, path for server dynamic code files
    //           pszsCltBinDir, path for client dynbamic code files
    //Return: the number of successfully imported pairs of files, -1 if error..
    virtual int GPK_API LoadBinary(const char * pszSvrBinDir, const char * pszsCltBinDir) = 0;

    //Function: get a random index for dynamic code
    //Return: >= 0 if successful，-1 if error
    virtual int GPK_API GetRandIdx() = 0;

    //Function: Get client dynamic code
    //Return: return a null string if nCodeIdx is invalid
    virtual int GPK_API GetCltDynCode(int nCodeIdx, const unsigned char **ppCodeRet) = 0;

    //Function: encrypt the data, it will return false if nCodeIdx is invalid
    //Parameter: lpData, the original data, it is used as a [in, out] parameter
    //		       nLen, the data length, it will not change after encryption
    //Return: true if successful
    virtual bool GPK_API Encode(unsigned char * lpData, unsigned long nLen, int nCodeIdx) = 0;

    //Function: decrypt the data, it will return false if nCodeIdx is invalid
    //Parameter: lpData, the original data to be decrypted, it is used as a [in, out] parameter
    //		       nLen, the data length, it will not change after decryption
    //Return: true if successful
    virtual bool GPK_API Decode(unsigned char * lpData, unsigned long nLen, int nCodeIdx) = 0;

	//Function: Release the compoment
    virtual void GPK_API Release() = 0;


	//GPK2.X
	//Function:load Auth DB file
	//Parameter:pszCmdFileName：filename
	//return: true if successful
	virtual bool          GPK_API  LoadAuthFile(const char * pszCmdFileName) = 0;


	////Function: Create an IGPKCSAuth object for one session.
	virtual IGPKCSAuth*   GPK_API  AllocAuthObject() = 0;
};



//Function: Create ISDSvrDynCode component
#ifdef WIN32
IGPKSvrDynCode * GPK_API  GPKCreateSvrDynCode();
//Parameter: Object,A Object of user,it will be use as a parnmeter in GPKCALLBack


#endif

};





#ifndef WIN32
extern "C" SGPK::IGPKSvrDynCode * GPK_API GPKCreateSvrDynCode();
typedef SGPK::IGPKSvrDynCode* (GPK_API *PFN_GPKCreateSvrDynCode)();
#endif

#endif


