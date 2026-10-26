#include "Core.h"
#include "FFileManagerWindows.h"
#if M_HASH_FILE_NAME
INT g_fileHashTableSize = 2;
const TCHAR* g_fileHashTable[] = {
	TEXT("Core.u") , TEXT("Core.u")
};
#endif
