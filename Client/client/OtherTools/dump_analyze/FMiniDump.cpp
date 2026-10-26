

#include "stdafx.h"
#include <dbgHelp.h>
#include <vector>
#include <map>
#include "FMiniDump.h"


#pragma comment(lib, "dbghelp.lib")


FMiniDump* FMiniDump::LPTHIS = 0;


extern BOOL    CALLBACK ReadProcessMemoryProc64(HANDLE hProcess, DWORD64 lpBaseAddress, PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead);
extern PVOID   CALLBACK FunctionTableAccessProc64(HANDLE hProcess, DWORD64 AddrBase);
extern DWORD64 CALLBACK GetModuleBaseProc64(HANDLE hProcess, DWORD64 Address);


FMiniDump::FMiniDump()
	:lpLog(0)
{
    nDump.m_hProcess = 0;
    bIsReadSysinfo = FALSE;
    bIsReadException = FALSE;
    bIsReadModule = FALSE;
    bIsReadMemory = FALSE;
    bIsReadThread = FALSE;
	bIsReadExceptionModule = FALSE;
    hFileMiniDump = INVALID_HANDLE_VALUE;
    hFileMapping = NULL;
    lpMiniDumpAddress = NULL;  
}

FMiniDump::~FMiniDump()
{
    Close();
}

bool FMiniDump::Open(const TCHAR* sFileName, const TCHAR* sSymSearchPath, DUMP_LOG* lg, bool full_analyze)
{
    if (nDump.m_hProcess)
        return false;

    szFilename = sFileName;
    szSymSearchPath = sSymSearchPath;
	lpLog = lg;

    hFileMiniDump = CreateFile(sFileName, FILE_ALL_ACCESS, 0, NULL, OPEN_EXISTING, NULL, NULL);
    if(hFileMiniDump==INVALID_HANDLE_VALUE)
    {
        DWORD id = GetLastError();
        Close();
        return false;
    }

    hFileMapping = CreateFileMapping(hFileMiniDump, NULL, PAGE_READONLY, 0, 0, 0);
    if(hFileMapping==NULL)
    {
        Close();
        return false;
    }

    lpMiniDumpAddress = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
    if(lpMiniDumpAddress==NULL)
    {    
        Close();
        return false;
    }

    static DWORD dwProcessID = 0;
    nDump.m_hProcess = (HANDLE)(++dwProcessID);  

    DWORD dwOptions = 0;
    dwOptions |= SYMOPT_EXACT_SYMBOLS; // Do not load an unmatched .pdb file. 
    dwOptions |= SYMOPT_FAIL_CRITICAL_ERRORS; // Do not display system dialog boxes when there is a media failure such as no media in a drive.
    dwOptions |= SYMOPT_UNDNAME; // All symbols are presented in undecorated form.   
    SymSetOptions(dwOptions);

    BOOL bSymInit = SymInitializeW(nDump.m_hProcess, CStringW(sSymSearchPath), FALSE);
    if(!bSymInit)
    {
        nDump.m_hProcess = NULL;
        Close();
        return false;
    }


	if (full_analyze)
	{
		bIsReadSysinfo = !ReadSysinfo();  
		bIsReadModule = !ReadModule();
		bIsReadThread = !ReadThread();
		bIsReadMemory = !ReadMemory();    
		bIsReadException = !ReadException();
		GetExceptionModuleInfo();
	}
    return true;
}

void FMiniDump::Close()
{
    UnmapViewOfFile(lpMiniDumpAddress);
	lpMiniDumpAddress = 0;
    if(hFileMapping!=NULL)
        CloseHandle(hFileMapping);
	hFileMapping = 0;
    if(hFileMiniDump!=INVALID_HANDLE_VALUE)
        CloseHandle(hFileMiniDump);
	hFileMiniDump = INVALID_HANDLE_VALUE;
    if(nDump.m_hProcess!=NULL)
        SymCleanup(nDump.m_hProcess);
	nDump.m_pExceptionModule = NULL;
	nDump.m_uExceptionOffsetFromModuleBase = 0;
    nDump.m_hProcess = 0;
	nDump.m_Threads.clear();
	nDump.m_ThreadIndex.clear();
	nDump.m_Modules.clear();
	nDump.m_ModuleIndex.clear();
	nDump.m_MemRanges.clear();

	bIsReadSysinfo = FALSE;
    bIsReadException = FALSE;
    bIsReadModule = FALSE;
    bIsReadMemory = FALSE;
    bIsReadThread = FALSE;
	bIsReadExceptionModule = FALSE;
}

BOOL FMiniDump::CheckDbgHelpApiVersion()
{
    // Set valid dbghelp API version
    API_VERSION CompiledApiVer;
    CompiledApiVer.MajorVersion = 6;
    CompiledApiVer.MinorVersion = 1;
    CompiledApiVer.Revision = 11;    
    CompiledApiVer.Reserved = 0;
    LPAPI_VERSION pActualApiVer = ImagehlpApiVersionEx(&CompiledApiVer);    
    if(CompiledApiVer.MajorVersion!=pActualApiVer->MajorVersion ||
        CompiledApiVer.MinorVersion!=pActualApiVer->MinorVersion ||
        CompiledApiVer.Revision!=pActualApiVer->Revision)
    {     
        return FALSE;
    }

    return TRUE;
}

void FMiniDump::RVA2String(LPVOID start_addr, DWORD rva, CString& out)
{
    MINIDUMP_STRING* pms = (MINIDUMP_STRING*)((LPBYTE)start_addr+rva);
    out = pms->Buffer;
}

const char* FMiniDump::GetVerString(CString& str)
{
	str.Format("%d.%d.%d.%d",
		(int)(nDump.m_verExe.dwFileVersionMS>>16),
		(int)(nDump.m_verExe.dwFileVersionMS&0xffff),
		(int)(nDump.m_verExe.dwFileVersionLS>>16),
		(int)(nDump.m_verExe.dwFileVersionLS&0xffff)
		);
	return str;
}

int FMiniDump::ReadSysinfo()
{
    LPVOID pStreamStart = NULL;
    ULONG uStreamSize = 0;
    MINIDUMP_DIRECTORY* pmd = NULL;
    BOOL bRead = FALSE;

    bRead = MiniDumpReadDumpStream(lpMiniDumpAddress, SystemInfoStream, &pmd, &pStreamStart, &uStreamSize);

    if(bRead)
    {
        MINIDUMP_SYSTEM_INFO* pSysInfo = (MINIDUMP_SYSTEM_INFO*)pStreamStart;

        nDump.m_uProcessorArchitecture = pSysInfo->ProcessorArchitecture;
        nDump.m_uchNumberOfProcessors = pSysInfo->NumberOfProcessors;
        nDump.m_uchProductType = pSysInfo->ProductType;
        nDump.m_ulVerMajor = pSysInfo->MajorVersion;
        nDump.m_ulVerMinor = pSysInfo->MinorVersion;
        nDump.m_ulVerBuild = pSysInfo->BuildNumber;
        RVA2String(lpMiniDumpAddress, pSysInfo->CSDVersionRva, nDump.m_sCSDVer);

        // Clean up
        pStreamStart = NULL;
        uStreamSize = 0;    
        pmd = NULL;
    }
    else 
    {
        return 1;    
    }

    return 0;
}

int FMiniDump::ReadException()
{
    LPVOID pStreamStart = NULL;
    ULONG uStreamSize = 0;
    MINIDUMP_DIRECTORY* pmd = NULL;
    BOOL bRead = FALSE;

    bRead = MiniDumpReadDumpStream(lpMiniDumpAddress, ExceptionStream, &pmd, &pStreamStart, &uStreamSize);
    if(bRead)
    {
        MINIDUMP_EXCEPTION_STREAM* pExceptionStream = (MINIDUMP_EXCEPTION_STREAM*)pStreamStart;
        if(pExceptionStream!=NULL && 
            uStreamSize>=sizeof(MINIDUMP_EXCEPTION_STREAM))
        {
            nDump.m_uExceptionThreadId = pExceptionStream->ThreadId;
            nDump.m_uExceptionCode = pExceptionStream->ExceptionRecord.ExceptionCode;
            nDump.m_uExceptionAddress = pExceptionStream->ExceptionRecord.ExceptionAddress;          
            nDump.m_pExceptionThreadContext = 
                (CONTEXT*)(((LPBYTE)lpMiniDumpAddress)+pExceptionStream->ThreadContext.Rva);      

			if (lpLog)
			{
				CString sMsg;
				int nExcModuleRowID = GetModuleRowIdByAddress(nDump.m_uExceptionAddress);
				if(nExcModuleRowID>=0)
				{
					sMsg.Format(_T("Unhandled exception at 0x%I64x in %s: 0x%x : %s"),
						nDump.m_uExceptionAddress,
						nDump.m_Modules[nExcModuleRowID].m_sModuleName,
						nDump.m_uExceptionCode,
						_T("Exception description.")
						);
				}
				else
				{
				}
				lpLog->OnLog(sMsg);
			}
        }    
    }
    else
    {
		if (lpLog)
			lpLog->OnLog(_T("No exception information found in minidump."));
        return 1;
    }

    return 0;
}

int FMiniDump::ReadModule(bool olny_exe)
{
    LPVOID pStreamStart = NULL;
    ULONG uStreamSize = 0;
    MINIDUMP_DIRECTORY* pmd = NULL;
    BOOL bRead = FALSE;

    bRead = MiniDumpReadDumpStream(lpMiniDumpAddress, ModuleListStream, &pmd, &pStreamStart, &uStreamSize);
    if(bRead)
    {
        MINIDUMP_MODULE_LIST* pModuleStream = (MINIDUMP_MODULE_LIST*)pStreamStart;
        if(pModuleStream!=NULL)
        {
            ULONG32 uNumberOfModules = pModuleStream->NumberOfModules;
            ULONG32 i;
            for(i=0; i<uNumberOfModules; i++)
            {
                MINIDUMP_MODULE* pModule = (MINIDUMP_MODULE*)((LPBYTE)pModuleStream->Modules+i*sizeof(MINIDUMP_MODULE));

                CString sModuleName;
                RVA2String(lpMiniDumpAddress, pModule->ModuleNameRva, sModuleName);
				if (olny_exe)
				{
					if (sModuleName.Find(".exe") != -1)
					{
						nDump.m_verExe = pModule->VersionInfo;
						return TRUE;
					}
					continue;
				}

				DWORD64 dwBaseAddr = pModule->BaseOfImage;
				DWORD64 dwImageSize = pModule->SizeOfImage;
                CString sShortModuleName = sModuleName;
                int pos = -1;
                pos = sModuleName.ReverseFind('\\');
                if(pos>=0)
                    sShortModuleName = sShortModuleName.Mid(pos+1);

                CStringW wcsModName(sModuleName);

                DWORD64 rrrtt = SymLoadModuleExW(nDump.m_hProcess, NULL, wcsModName, 0, dwBaseAddr, (DWORD)dwImageSize, NULL, 0);
                DWORD err_id = GetLastError();

                IMAGEHLP_MODULE64 modinfo;
                memset(&modinfo, 0, sizeof(IMAGEHLP_MODULE64));
                modinfo.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
                BOOL bModuleInfo = SymGetModuleInfo64(nDump.m_hProcess, dwBaseAddr, &modinfo);                DUMP_MODULE m;
                if(!bModuleInfo)
                {          
                    m.m_bImageUnmatched = TRUE;
                    m.m_bNoSymbolInfo = TRUE;
                    m.m_bPdbUnmatched = TRUE;
                    m.m_pVersionInfo = NULL;
                    m.m_sImageName = sModuleName;
					m.m_strModuleName = sShortModuleName.GetBuffer();
                    m.m_sModuleName = sShortModuleName;
                    m.m_uBaseAddr = dwBaseAddr;
                    m.m_uImageSize = dwImageSize;          
                }
                else
                {          
                    m.m_uBaseAddr = modinfo.BaseOfImage;
                    m.m_uImageSize = modinfo.ImageSize;        
                    m.m_sModuleName = sShortModuleName;
					m.m_strModuleName = sShortModuleName.GetBuffer();
                    m.m_sImageName = modinfo.ImageName;
                    m.m_sLoadedImageName = modinfo.LoadedImageName;
                    m.m_sLoadedPdbName = modinfo.LoadedPdbName;
                    m.m_pVersionInfo = &pModule->VersionInfo;
                    m.m_bPdbUnmatched = modinfo.PdbUnmatched;          
                    BOOL bTimeStampMatched = pModule->TimeDateStamp == modinfo.TimeDateStamp;
                    m.m_bImageUnmatched = !bTimeStampMatched;
                    m.m_bNoSymbolInfo = !modinfo.GlobalSymbols;
                }        

                nDump.m_Modules.push_back(m);
                nDump.m_ModuleIndex[m.m_uBaseAddr] = nDump.m_Modules.size()-1;          

				if (lpLog)
				{
					CString sMsg;
					if(m.m_bImageUnmatched)
						sMsg.Format(_T("Loaded '*%s'"), sModuleName);
					else
						sMsg.Format(_T("Loaded '%s'"), m.m_sLoadedImageName);

					if(m.m_bImageUnmatched)
						sMsg += _T(", No matching binary found.");          
					else if(m.m_bPdbUnmatched)
						sMsg += _T(", No matching PDB file found.");          
					else
					{
						if(m.m_bNoSymbolInfo)            
							sMsg += _T(", No symbols loaded.");          
						else
							sMsg += _T(", Symbols loaded.");          
					}
					lpLog->OnLog(sMsg);
				}
            }
        }
    }
    else
    {
        return 1;
    }

    return 0;
}

int FMiniDump::GetModuleRowIdByBaseAddr(DWORD64 dwBaseAddr)
{
    std::map<DWORD64, size_t>::iterator it = nDump.m_ModuleIndex.find(dwBaseAddr);
    if(it!=nDump.m_ModuleIndex.end())
        return (int)it->second;
    return -1;
}

int FMiniDump::GetModuleRowIdByAddress(DWORD64 dwAddress)
{
    UINT i;
    for(i=0;i<nDump.m_Modules.size();i++)
    {
        if(nDump.m_Modules[i].m_uBaseAddr<=dwAddress && 
            dwAddress<nDump.m_Modules[i].m_uBaseAddr+nDump.m_Modules[i].m_uImageSize)
            return i;
    }

    return -1;
}

int FMiniDump::GetThreadRowIdByThreadId(DWORD dwThreadId)
{
    std::map<DWORD, size_t>::iterator it = nDump.m_ThreadIndex.find(dwThreadId);
    if(it!=nDump.m_ThreadIndex.end())
        return (int)it->second;
    return -1;
}

int FMiniDump::ReadMemory()
{
    LPVOID pStreamStart = NULL;
    ULONG uStreamSize = 0;
    MINIDUMP_DIRECTORY* pmd = NULL;
    BOOL bRead = FALSE;

    bRead = MiniDumpReadDumpStream(lpMiniDumpAddress, MemoryListStream, &pmd, &pStreamStart, &uStreamSize);
    if(bRead)
    {
        MINIDUMP_MEMORY_LIST* pMemStream = (MINIDUMP_MEMORY_LIST*)pStreamStart;
        if(pMemStream!=NULL)
        {
            ULONG32 uNumberOfMemRanges = pMemStream->NumberOfMemoryRanges;
            ULONG i;
            for(i=0; i<uNumberOfMemRanges; i++)
            {
                MINIDUMP_MEMORY_DESCRIPTOR* pMemDesc = (MINIDUMP_MEMORY_DESCRIPTOR*)(&pMemStream->MemoryRanges[i]);
                DUMP_MEMORY mr;
                mr.m_u64StartOfMemoryRange = pMemDesc->StartOfMemoryRange;
                mr.m_uDataSize = pMemDesc->Memory.DataSize;
                mr.m_pStartPtr = (LPBYTE)lpMiniDumpAddress+pMemDesc->Memory.Rva;

                nDump.m_MemRanges.push_back(mr);
            }
        }
    }
    else    
    {
        return 1;
    }

    return 0;
}

void FMiniDump::GetExceptionModuleInfo()
{
	if(!bIsReadException || !bIsReadModule || bIsReadExceptionModule)
	{
		return;
	}

	for(size_t i = 0 ; i < nDump.m_Modules.size(); ++i)
	{
		if(nDump.m_uExceptionAddress >= nDump.m_Modules.at(i).m_uBaseAddr &&
			nDump.m_uExceptionAddress <= nDump.m_Modules.at(i).m_uBaseAddr + nDump.m_Modules.at(i).m_uImageSize)
		{
			nDump.m_pExceptionModule = &nDump.m_Modules.at(i);
			nDump.m_uExceptionOffsetFromModuleBase = nDump.m_Modules.at(i).m_uBaseAddr - nDump.m_uExceptionAddress;
			break;
		}
	}

	bIsReadExceptionModule = TRUE;
}

int FMiniDump::ReadThread()
{
    LPVOID pStreamStart = NULL;
    ULONG uStreamSize = 0;
    MINIDUMP_DIRECTORY* pmd = NULL;
    BOOL bRead = FALSE;

    bRead = MiniDumpReadDumpStream(lpMiniDumpAddress, ThreadListStream, &pmd, &pStreamStart, &uStreamSize);
    if(bRead)
    {
        MINIDUMP_THREAD_LIST* pThreadList = (MINIDUMP_THREAD_LIST*)pStreamStart;
        if(pThreadList!=NULL && 
            uStreamSize>=sizeof(MINIDUMP_THREAD_LIST))
        {
            ULONG32 uThreadCount = pThreadList->NumberOfThreads;

            ULONG32 i;
            for(i=0; i<uThreadCount; i++)
            {
                MINIDUMP_THREAD* pThread = (MINIDUMP_THREAD*)(&pThreadList->Threads[i]);

                DUMP_THREAD mt;
                mt.m_dwThreadId = pThread->ThreadId;
                mt.m_pThreadContext = (CONTEXT*)(((LPBYTE)lpMiniDumpAddress)+pThread->ThreadContext.Rva);

                nDump.m_Threads.push_back(mt);
                nDump.m_ThreadIndex[mt.m_dwThreadId] = nDump.m_Threads.size()-1;        
            }
        }  
    }
    else
    {
        return 1;
    }

    return 0;
}

int FMiniDump::StackWalk(DWORD dwThreadId)
{ 
    int nThreadIndex = GetThreadRowIdByThreadId(dwThreadId);
    if (nThreadIndex < 0)
        return 0;
    if(nDump.m_Threads[nThreadIndex].m_bStackWalk == TRUE)
        return 0; // Already done

    CONTEXT* pThreadContext = NULL;

    if(nDump.m_Threads[nThreadIndex].m_dwThreadId==nDump.m_uExceptionThreadId)
        pThreadContext = nDump.m_pExceptionThreadContext;
    else
        pThreadContext = nDump.m_Threads[nThreadIndex].m_pThreadContext;  

    if(pThreadContext==NULL)
        return 1;

    // Make modifiable context
    CONTEXT Context;
    memcpy(&Context, pThreadContext, sizeof(CONTEXT));

    LPTHIS = this;

    // Init stack frame with correct initial values
    // See this:
    // http://www.codeproject.com/KB/threads/StackWalker.aspx
    //
    // Given a current dbghelp, your code should:
    //  1. Always use StackWalk64
    //  2. Always set AddrPC to the current instruction pointer (Eip on x86, Rip on x64 and StIIP on IA64)
    //  3. Always set AddrStack to the current stack pointer (Esp on x86, Rsp on x64 and IntSp on IA64)
    //  4. Set AddrFrame to the current frame pointer when meaningful. On x86 this is Ebp, on x64 you 
    //     can use Rbp (but is not used by VC2005B2; instead it uses Rdi!) and on IA64 you can use RsBSP. 
    //     StackWalk64 will ignore the value when it isn't needed for unwinding.
    //  5. Set AddrBStore to RsBSP for IA64. 

    STACKFRAME64 sf;
    memset(&sf, 0, sizeof(STACKFRAME64));

    sf.AddrPC.Mode = AddrModeFlat;  
    sf.AddrFrame.Mode = AddrModeFlat;  
    sf.AddrStack.Mode = AddrModeFlat;  
    sf.AddrBStore.Mode = AddrModeFlat;  

    DWORD dwMachineType = 0;
    switch(nDump.m_uProcessorArchitecture)
    {
#ifdef _X86_
  case PROCESSOR_ARCHITECTURE_INTEL: 
      dwMachineType = IMAGE_FILE_MACHINE_I386;
      sf.AddrPC.Offset = pThreadContext->Eip;    
      sf.AddrStack.Offset = pThreadContext->Esp;
      sf.AddrFrame.Offset = pThreadContext->Ebp;
      break;
#endif
#ifdef _AMD64_
  case PROCESSOR_ARCHITECTURE_AMD64:
      dwMachineType = IMAGE_FILE_MACHINE_AMD64;
      sf.AddrPC.Offset = pThreadContext->Rip;    
      sf.AddrStack.Offset = pThreadContext->Rsp;
      sf.AddrFrame.Offset = pThreadContext->Rbp;
      break;
#endif
#ifdef _IA64_
  case PROCESSOR_ARCHITECTURE_AMD64:
      dwMachineType = IMAGE_FILE_MACHINE_IA64;
      sf.AddrPC.Offset = pThreadContext->StIIP;
      sf.AddrStack.Offset = pThreadContext->IntSp;
      sf.AddrFrame.Offset = pThreadContext->RsBSP;    
      sf.AddrBStore.Offset = pThreadContext->RsBSP;
      break;
#endif 
  default:
      {
          return 1; // Unsupported architecture
      }
    }

    for(;;)
    {    
        BOOL bWalk = ::StackWalk64(
            dwMachineType,               // machine type
            nDump.m_hProcess,       // our process handle
            (HANDLE)dwThreadId,          // thread ID
            &sf,                         // stack frame
            dwMachineType==IMAGE_FILE_MACHINE_I386?NULL:(&Context), // used for non-I386 machines 
            ReadProcessMemoryProc64,     // our routine
            FunctionTableAccessProc64,   // our routine
            GetModuleBaseProc64,         // our routine
            NULL                         // safe to be NULL
            );

        if(!bWalk)
            break;      

        DUMP_STACK stack_frame;
        stack_frame.m_dwAddrPCOffset = sf.AddrPC.Offset;

        // Get module info
        IMAGEHLP_MODULE64 mi;
        memset(&mi, 0, sizeof(IMAGEHLP_MODULE64));
        mi.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);
        BOOL bGetModuleInfo = SymGetModuleInfo64(nDump.m_hProcess, sf.AddrPC.Offset, &mi);     
        if(bGetModuleInfo)
        {
            stack_frame.m_nModuleRowID = GetModuleRowIdByBaseAddr(mi.BaseOfImage);      
        }

        // Get symbol info
        DWORD64 dwDisp64;
        BYTE buffer[4096];
        SYMBOL_INFO* sym_info = (SYMBOL_INFO*)buffer;
        sym_info->SizeOfStruct = sizeof(SYMBOL_INFO);
        sym_info->MaxNameLen = 4096-sizeof(SYMBOL_INFO)-1;
        BOOL bGetSym = SymFromAddr(nDump.m_hProcess, sf.AddrPC.Offset, &dwDisp64, sym_info);

        if(bGetSym)
        {
            stack_frame.m_sSymbolName = CString(sym_info->Name, sym_info->NameLen);
            stack_frame.m_dw64OffsInSymbol = dwDisp64;
        }

        // Get source filename and line
        DWORD dwDisplacement;
        IMAGEHLP_LINE64 line;
        BOOL bGetLine = SymGetLineFromAddr64(nDump.m_hProcess, sf.AddrPC.Offset, &dwDisplacement, &line);

        if(bGetLine)
        {
            stack_frame.m_sSrcFileName = line.FileName;
            stack_frame.m_nSrcLineNumber = line.LineNumber;
        }

        nDump.m_Threads[nThreadIndex].m_StackTrace.push_back(stack_frame);
    }

    CString sStackTrace;
    UINT i;
    for(i=0; i<nDump.m_Threads[nThreadIndex].m_StackTrace.size(); i++)
    {
        DUMP_STACK& frame = nDump.m_Threads[nThreadIndex].m_StackTrace[i];

        if(frame.m_sSymbolName.IsEmpty())
            continue;

        CString sModuleName;
        CString sAddrPCOffset;
        CString sSymbolName;            
        CString sOffsInSymbol;
        CString sSourceFile;
        CString sSourceLine;

        if(frame.m_nModuleRowID>=0)
        {
            sModuleName = nDump.m_Modules[frame.m_nModuleRowID].m_sModuleName;
        }           

        sSymbolName = frame.m_sSymbolName;
        sAddrPCOffset.Format(_T("0x%I64x"), frame.m_dwAddrPCOffset);
        sSourceFile = frame.m_sSrcFileName;
        sSourceLine.Format(_T("%d"), frame.m_nSrcLineNumber);
        sOffsInSymbol.Format(_T("0x%I64x"), frame.m_dw64OffsInSymbol);

        CString str;
        str = sModuleName;
        if(!str.IsEmpty())
            str += _T("!");

        if(sSymbolName.IsEmpty())
            str += sAddrPCOffset;  
        else
        {
            str += sSymbolName;
            str += _T("+");
            str += sOffsInSymbol;
        }

        if(!sSourceFile.IsEmpty())
        {
            size_t pos = sSourceFile.ReverseFind('\\');
            if(pos>=0)
                sSourceFile = sSourceFile.Mid((int)pos+1);
            str += _T(" [ ");
            str += sSourceFile;
            str += _T(": ");
            str += sSourceLine;
            str += _T(" ] ");
        } 

        sStackTrace += str; 
        sStackTrace += _T("\n");
    }

    nDump.m_Threads[nThreadIndex].m_bStackWalk = TRUE;

    return 0;
}

BOOL CALLBACK ReadProcessMemoryProc64(HANDLE hProcess, DWORD64 lpBaseAddress, PVOID lpBuffer, DWORD nSize, LPDWORD lpNumberOfBytesRead)
{
    *lpNumberOfBytesRead = 0;

    if (hProcess != FMiniDump::LPTHIS->nDump.m_hProcess || !lpBaseAddress || !lpBuffer || !nSize)
        return FALSE;

    for (ULONG i = 0; i < FMiniDump::LPTHIS->nDump.m_MemRanges.size(); i++)
    {
        DUMP_MEMORY& mr = FMiniDump::LPTHIS->nDump.m_MemRanges[i];
        if (lpBaseAddress>=mr.m_u64StartOfMemoryRange && lpBaseAddress<mr.m_u64StartOfMemoryRange+mr.m_uDataSize)
        {
            DWORD64 dwOffs = lpBaseAddress-mr.m_u64StartOfMemoryRange;
            LONG64 lBytesRead = 0;

            if(mr.m_uDataSize-dwOffs>nSize)
                lBytesRead = nSize;
            else
                lBytesRead = mr.m_uDataSize-dwOffs;

            if(lBytesRead<=0 || nSize<lBytesRead)
                return FALSE;

            *lpNumberOfBytesRead = (DWORD)lBytesRead;
            memcpy(lpBuffer, (LPBYTE)mr.m_pStartPtr+dwOffs, (size_t)lBytesRead);

            return TRUE;
        }
    }

    return FALSE;
}

PVOID CALLBACK FunctionTableAccessProc64(HANDLE hProcess, DWORD64 AddrBase)
{   
    return SymFunctionTableAccess64(hProcess, AddrBase);
}

DWORD64 CALLBACK GetModuleBaseProc64(HANDLE hProcess, DWORD64 Address)
{  
    return SymGetModuleBase64(hProcess, Address);
}