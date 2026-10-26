//// Bruce@snda 
// encry.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>

typedef unsigned char       BYTE;

class FArchiveEncodeDncode
{
public:
	BYTE  offsetEnCode[256];
	BYTE  offsetDeCode[256]; 

	FArchiveEncodeDncode()
	{
		int	 seedEncode = 897502;
		for ( int i=0; i<256; i++ )
		{
			offsetEnCode[i] = i;
		}

		srand( seedEncode );
		BYTE  buf;
		int  iBuf;
		for(int i=0;i<256;i++)
		{
			iBuf = rand()%256; 
			buf  = offsetEnCode[i];
			offsetEnCode[i]		= offsetEnCode[iBuf];
			offsetEnCode[iBuf]	= buf;
		}

		for(int i=0;i<256;i++)
		{
			offsetDeCode[offsetEnCode[i]] = i;
		}
	};

	~FArchiveEncodeDncode()
	{
	};

	static FArchiveEncodeDncode* GetInstance()
	{
		static FArchiveEncodeDncode ins;
		return &ins;
	};

	void DoEncode(void* V, int Length)
	{
		BYTE* pData = (BYTE*)V;

		for ( int i = 0; i < Length; i++ )
		{
			*(pData+i) = offsetEnCode[*(pData+i)];
		}
	}

	void DoDecode(void* V, int Length)
	{
		BYTE* pData = (BYTE*)V;

		for ( int i=0; i<Length; i++ )
		{
			*(pData+i) = offsetDeCode[*(pData+i)];
		}
	}
};

#define PATH_SEPARATOR _T("\\")
#define appIsPathSeparator( Ch )	((Ch) == PATH_SEPARATOR[0])


bool _MakeDirectory( const TCHAR* Path, bool Tree = true)
{
	// Support code for making a directory tree.
	//check(Tree);
	int CreateCount=0;
	for( TCHAR Full[256]=_T(""), *Ptr=Full; ; *Ptr++=*Path++ )
	{
		if( appIsPathSeparator(*Path) || *Path==0 )
		{
			*Ptr = 0;
			if( Ptr != Full )// && !IsDrive(Full) )
			{
				if( !_MakeDirectory( Full, 0 ) )
				{
					return 0;
				}
				CreateCount++;
			}
		}
		if( *Path==0 )
		{
			break;
		}
	}
	return CreateCount!=0;
}

int _tmain(int argc, TCHAR* argv[])
{
	FILE* OriginFile = NULL;
	_tfopen_s(&OriginFile, argv[1], L"rb" );
	if ( OriginFile == NULL )
	{
		_tprintf(L"[Error] Original File: Open file %s Error! \n", argv[1]);
		//getch();
		return -1;
	}


	//_MakeDirectory(argv[2]);

	FILE* DestiFile = NULL;

	if(argc == 2)
	{
		std::wstring autoFile = argv[1];
		autoFile += L".txt";
		_tfopen_s(&DestiFile, autoFile.c_str(), L"wb+" );
	}
	else
	{
		_tfopen_s(&DestiFile, argv[2], L"wb+" );
	}
	if ( DestiFile == NULL )
	{
		_tprintf(L"[Error] Target File: Create file %s Error !\n", argv[2]);
		//getch();
		return -1;
	}

	//printf("Reading and writing files are succeeded!\n");

	FArchiveEncodeDncode* pEncode = FArchiveEncodeDncode::GetInstance();
	long lSize = 0;
	char* buffer = 0;

	fseek( OriginFile, 0, SEEK_END );
	lSize = ftell ( OriginFile );
	rewind( OriginFile );

	//printf("Getting File's size is succeeded!\n");

	buffer = (char*)malloc( sizeof( char ) * lSize );

	fread( buffer, sizeof( char ), lSize, OriginFile );

	if((argc == 2) || (argc > 3))
	{
		pEncode->DoDecode( buffer, lSize );
	}
	else
	{
		pEncode->DoEncode( buffer, lSize );
	}

	//printf("Encode File is succeeded!\n");

	//pEncode->DoDecode( buffer, lSize );

	fwrite( buffer, sizeof( char ), lSize, DestiFile );

	fclose( OriginFile );
	fclose( DestiFile );
	free ( buffer );

	_tprintf(L"[OK] %s\r\n", argv[2]);
	//printf("Encode is finished!\n\n");

	//printf("Press any key to quit...");

// 	while ( !_kbhit() )
// 	{
// 		::_sleep( 10 );
// 	}

	return 0;
}



//int  _tmain(int argc, _TCHAR* argv[])
//{
//	FILE* OriginFile;
//	FILE* DestiFile;
//
//	int FileLength = 0;
//	if ( ( OriginFile = fopen( argv[1],"rb+" ) ) == NULL )
//	{
//		printf("Original File: Open file %s Error! \n", argv[1]);
//		getch();
//		return -1;
//	}
//	while ( !feof( OriginFile ) )
//	{
//		unsigned char ch = fgetc( OriginFile );
//		FileLength++;		
//	}
//	fclose( OriginFile );
//
//	if ( ( OriginFile = fopen( argv[1],"rb+" ) ) == NULL )
//	{
//		printf("Original File: Open file %s Error! \n", argv[1]);
//		getch();
//		return -1;
//	}
//
//	if ( ( DestiFile = fopen( argv[2],"wb+" ) ) == NULL )
//	{
//		printf("Temporary File: Create file %s Error !\n", argv[2]);
//		getch();
//		return -1;
//	}
//
//	FArchiveEncodeDncode* pEncode = FArchiveEncodeDncode::GetInstance();
//	int EncodeLen = 0;
//	while ( !feof( OriginFile ) )
//	{
//		unsigned char ch = fgetc( OriginFile );
//		EncodeLen++;
//
//		if ( FileLength == EncodeLen )
//			break;
//
//		ch = pEncode->offsetEnCode[(int)ch];		
//		//ch = pEncode->offsetDeCode[(int)ch];	
//
//		fputc( ch, DestiFile );
//
//	}
//
//	fclose( OriginFile );
//	fclose( DestiFile );
//
//	getch();
//	return 0;
//}
