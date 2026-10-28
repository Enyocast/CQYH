//-----------------------------------------------------------------------------
// File: Textures.cpp
//
// Desc: Better than just lights and materials, 3D objects look much more
//       convincing when texture-mapped. Textures can be thought of as a sort
//       of wallpaper, that is shrinkwrapped to fit a texture. Textures are
//       typically loaded from image files, and D3DX provides a utility to
//       function to do this for us. Like a vertex buffer, textures have
//       Lock() and Unlock() functions to access (read or write) the image
//       data. Textures have a width, height, miplevel, and pixel format. The
//       miplevel is for "mipmapped" textures, an advanced performance-
//       enhancing feature which uses lower resolutions of the texture for
//       objects in the distance where detail is less noticeable. The pixel
//       format determines how the colors are stored in a texel. The most
//       common formats are the 16-bit R5G6B5 format (5 bits of red, 6-bits of
//       green and 5 bits of blue) and the 32-bit A8R8G8B8 format (8 bits each
//       of alpha, red, green, and blue).
//
//       Textures are associated with geometry through texture coordinates.
//       Each vertex has one or more sets of texture coordinates, which are
//       named tu and tv and range from 0.0 to 1.0. Texture coordinates can be
//       supplied by the geometry, or can be automatically generated using
//       Direct3D texture coordinate generation (which is an advanced feature).
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 ) 

#include "SDOA4Client.h"
#include "SDOADx9.h"
#include "SDOACfg.h"

/* 接入相关全局变量  */
HINSTANCE          g_hInstIGWDll = 0;
LPigwInitialize    igwInitialize = NULL;
LPigwGetModule     igwGetModule = NULL;
LPigwTerminal      igwTerminal = NULL;

ISDOADx9*			g_SDOADx9 = NULL;
ISDOAApp*			g_SDOAApp = NULL;
ISDOACfg*			g_SDOACfg = NULL;

/* 释放IGW */
void CloseIGW()
{
	if (g_SDOADx9)
	{
		g_SDOADx9->Release();
		g_SDOADx9 = NULL;
	}

	if (g_SDOAApp)
	{
		g_SDOAApp->Release();
		g_SDOAApp = NULL;
	}

	if (g_SDOACfg)
	{
		g_SDOACfg->Release();
		g_SDOACfg = NULL;
	}

	if (igwTerminal)
	{  // 释放DLL前总是先调用igwTerminal
		igwTerminal();
		igwTerminal = NULL;
	}
	if (g_hInstIGWDll)
	{
		FreeLibrary(g_hInstIGWDll);
		g_hInstIGWDll = 0;
	}
	igwInitialize = NULL;
}

/* 加载IGW */
void OpenIGW()
{
	WCHAR strExePath[MAX_PATH] = {0};
	WCHAR strExeName[MAX_PATH] = {0};
	WCHAR* strLastSlash = NULL;
	GetModuleFileNameW( NULL, strExePath, MAX_PATH );
	strExePath[MAX_PATH-1]=0;
	strLastSlash = wcsrchr( strExePath, TEXT('\\') );
	if( strLastSlash )
	{	// 得到EXE所在路径
		StringCchCopyW( strExeName, MAX_PATH, &strLastSlash[1] );
		*strLastSlash = 0;
		strLastSlash = wcsrchr( strExeName, TEXT('.') );
		if( strLastSlash )
			*strLastSlash = 0;
	}

	WCHAR strGameWidgetDll[MAX_PATH] = {0};
	StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\GameWidget.dll", strExePath );

	if ( !(GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF) )
	{ // 如果程序运行路径中不存在则换个路径再试
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
	}


	if ( !(GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF) )
	{ // 如果程序运行路径中不存在则换个路径再试
		StringCchPrintfW( strGameWidgetDll, MAX_PATH, L"%s\\..\\..\\..\\..\\..\\..\\..\\bin\\GameWidget.dll", strExePath );
	}


	CloseIGW();

	if ( GetFileAttributesW(strGameWidgetDll) != 0xFFFFFFFF )
	{	// 找到组件则加载	
		g_hInstIGWDll = LoadLibraryW(strGameWidgetDll);
		if (g_hInstIGWDll)
		{
			igwInitialize = (LPigwInitialize)GetProcAddress( g_hInstIGWDll, "igwInitialize" );
			igwGetModule = (LPigwGetModule)GetProcAddress( g_hInstIGWDll, "igwGetModule" );
			igwTerminal = (LPigwTerminal)GetProcAddress( g_hInstIGWDll, "igwTerminal" );
			if ( igwInitialize && igwGetModule && igwTerminal)
			{
				// 加载成功

				// 注意AppInfo类型所有字段必须填
				AppInfo tmpAppInfo = {
					sizeof(AppInfo),       // 结构体大小，方便扩展
					9999,                  // 接入应用ID，从开发者网站中申请
					L"龙潭虎穴OnLine",     // 应用名称
					L"0.1.2.0",            // 应用客户端当前版本号
					SDOA_RENDERTYPE_D3D9,  // 客户端支持的图形引擎类型，这里同时支持d3d9和d3d8
					1,                     // 可同时在一台机器上游戏的最大人数（通常为1，例如:KOF应该是2）
					-1,                    // 游戏区ID，不可用时传入-1
					-1                     // 游戏组ID，不可用时传入-1

				};

				if (igwInitialize(SDOA_SDK_VERSION, &tmpAppInfo) == SDOA_OK)
				{	// 初始化组件成功

					igwGetModule(__uuidof(ISDOADx9), (void**)&g_SDOADx9);
					igwGetModule(__uuidof(ISDOAApp), (void**)&g_SDOAApp);
					igwGetModule(__uuidof(ISDOACfg), (void**)&g_SDOACfg);

					if ( (!g_SDOADx9) || (!g_SDOAApp) || (!g_SDOACfg))
						CloseIGW();

				}
				else // 初始化失败清除环境
					CloseIGW();
			}
			else  // 加载DLL失败清除环境
				CloseIGW();
		}
	}	
}


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D       = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB        = NULL; // Buffer to hold vertices
LPDIRECT3DTEXTURE9      g_pTexture   = NULL; // Our texture
D3DPRESENT_PARAMETERS	d3dpp;
bool					g_DeviceLost = false;
// 是否变换
bool					g_SetupMatrices = true;
HWND					g_MainWin_hWnd = 0;
// 当前窗口的大小
int						g_WinWidth = 640;
int						g_WinHeight = 480;
// 在窗口中显示的区域
RECT					g_WinRenderRect = {0, 0, g_WinWidth, g_WinHeight};
// 使用D3D背景缓冲的区域（仅在窗口模式下有效）
//RECT					g_D3DRenderRect = g_WinRenderRect;
RECT					g_D3DRenderRect = {100, 100, g_WinWidth + 100, g_WinHeight + 100};
// 是否为窗口模式
BOOL					g_IsWindow = TRUE;

// A structure for our custom vertex type. We added texture coordinates
struct CUSTOMVERTEX
{
    D3DXVECTOR3 position; // The position
    D3DCOLOR    color;    // The color
#ifndef SHOW_HOW_TO_USE_TCI
    FLOAT       tu, tv;   // The texture coordinates
#endif
};

// Our custom FVF, which describes our custom vertex structure
#ifdef SHOW_HOW_TO_USE_TCI
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)
#else
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#endif


// 画个框框需要的全局变量
LPDIRECT3DVERTEXBUFFER9 g_pVB_MyRect			= NULL; 
LPDIRECT3DINDEXBUFFER9	g_pIndexVB_MyRect		= NULL;
struct CUSTOMVERTEX_MYRECT
{
	FLOAT		x, y, z, rhw;
	D3DCOLOR    color;    
	FLOAT       tu, tv;   
};

#define D3DFVF_CUSTOMVERTEX_MYRECT (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    //D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	
    d3dpp.Windowed = g_IsWindow;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_INTERVAL_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	// 如果使用垂直刷新同步则以下参数
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;	
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.BackBufferWidth = 800;
	d3dpp.BackBufferHeight = 600;


	D3DDISPLAYMODE tmpMode;
	
	if ( D3D_OK == g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &tmpMode) )
	{	// 能取到背景格式则设置
		d3dpp.BackBufferFormat = tmpMode.Format;
		if ( !d3dpp.Windowed )
		{// 全屏模式下使用获取到的刷新率
		  d3dpp.FullScreen_RefreshRateInHz = tmpMode.RefreshRate;
		}
	}
	if (d3dpp.Windowed)	
	{	// 窗口模式
		SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,SWP_NOSIZE | SWP_SHOWWINDOW | SWP_DRAWFRAME | SWP_FRAMECHANGED);
	}
	else
	{	// 全屏模式
		SetWindowLong(hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,SWP_NOSIZE | SWP_SHOWWINDOW | SWP_DRAWFRAME | SWP_FRAMECHANGED);
	}
    // Create the D3DDevice
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{	// 优先使用硬件顶点处理
		if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pd3dDevice ) ) )
		{	// 硬件顶点处理支持创建失败则用软件的
			return E_FAIL;
		}
	}

    // Turn off culling
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    return S_OK;
}

bool CreateRenderRes()
{
	// 重建绘制资源
	if ( !g_pd3dDevice )
		return false;

	// 顶点索引
	unsigned short MyRectTriList[] =
	{
		0, 1, 2,
		2, 1, 3
	};
	// 顶点位置
	float fWidth, fHeight;
	fWidth = 640 - 1.0;
	fHeight = 480 - 1.0;


	// 顶点位置
	CUSTOMVERTEX_MYRECT MyRectVertex[4] = 
	{
		{ 0.0f,		0.0f,	0.0f, 1.0f, 0xffff0000, 0.0f, 0.0f }, // x, y, z, rhw, color, u, v
		{ fWidth,	0.0f,	0.0f, 1.0f, 0xffff0000, 1.0f, 0.0f },
		{ 0.0f,		fHeight, 0.0f, 1.0f, 0xffff0000, 0.0f, 1.0f },
		{ fWidth,	fHeight,	0.0f, 1.0f, 0xffff0000, 1.0f, 1.0f }
	};

	if( FAILED( g_pd3dDevice->CreateIndexBuffer(sizeof(MyRectTriList), 
		D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIndexVB_MyRect, NULL)))
	{
		return false;
	}

	if( FAILED( g_pd3dDevice->CreateVertexBuffer(sizeof(MyRectVertex),
		0, D3DFVF_CUSTOMVERTEX_MYRECT,
		D3DPOOL_DEFAULT, &g_pVB_MyRect, NULL ) ) )
	{
		return false;
	}

	VOID* pVertices;
	if( FAILED( g_pVB_MyRect->Lock( 0, sizeof(MyRectVertex), (void**)&pVertices, 0 ) ) )
		return false;
	memcpy( pVertices, MyRectVertex, sizeof(MyRectVertex) );
	g_pVB_MyRect->Unlock();

	VOID* pIndexVertices;
	if( FAILED( g_pIndexVB_MyRect->Lock( 0, sizeof(MyRectTriList), (void**)&pIndexVertices, 0 ) ) )
		return false;
	memcpy( pIndexVertices, MyRectTriList, sizeof(MyRectTriList) );
	g_pIndexVB_MyRect->Unlock();

	return true;
}

//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Create the textures and vertex buffers
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
    // Use D3DX to create a texture from a file based image
    if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "banana.bmp", &g_pTexture ) ) )
    {
        // If texture is not in current folder, try parent folder
        if( FAILED( D3DXCreateTextureFromFile( g_pd3dDevice, "..\\banana.bmp", &g_pTexture ) ) )
        {
            MessageBox(NULL, "Could not find banana.bmp", "Textures.exe", MB_OK);
            return E_FAIL;
        }
    }

    // Create the vertex buffer.
    if( FAILED( g_pd3dDevice->CreateVertexBuffer( 50*2*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
    {
        return E_FAIL;
    }

    // Fill the vertex buffer. We are setting the tu and tv texture
    // coordinates, which range from 0.0 to 1.0
    CUSTOMVERTEX* pVertices;
    if( FAILED( g_pVB->Lock( 0, 0, (void**)&pVertices, 0 ) ) )
        return E_FAIL;
    for( DWORD i=0; i<50; i++ )
    {
        FLOAT theta = (2*D3DX_PI*i)/(50-1);

        pVertices[2*i+0].position = D3DXVECTOR3( sinf(theta),-1.0f, cosf(theta) );
        pVertices[2*i+0].color    = 0xffffffff;
#ifndef SHOW_HOW_TO_USE_TCI
        pVertices[2*i+0].tu       = ((FLOAT)i)/(50-1);
        pVertices[2*i+0].tv       = 1.0f;
#endif

        pVertices[2*i+1].position = D3DXVECTOR3( sinf(theta), 1.0f, cosf(theta) );
        pVertices[2*i+1].color    = 0xff808080;
#ifndef SHOW_HOW_TO_USE_TCI
        pVertices[2*i+1].tu       = ((FLOAT)i)/(50-1);
        pVertices[2*i+1].tv       = 0.0f;
#endif
    }
    g_pVB->Unlock();

	if ( !CreateRenderRes() )
	{
		return E_FAIL;
	}
    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if ( g_pVB_MyRect != NULL )
	{
		g_pVB_MyRect->Release();
		g_pVB_MyRect = NULL;
	}
	if ( g_pIndexVB_MyRect != NULL )
	{
		g_pIndexVB_MyRect->Release();
		g_pIndexVB_MyRect = NULL;
	}
    if( g_pTexture != NULL )
	{
        g_pTexture->Release();
		g_pTexture = NULL;
	}

    if( g_pVB != NULL )
	{
        g_pVB->Release();
		g_pVB = NULL;
	}

    if( g_pd3dDevice != NULL )
	{
        g_pd3dDevice->Release();
		g_pd3dDevice = NULL;
	}

    if( g_pD3D != NULL )
	{
        g_pD3D->Release();
		g_pD3D = NULL;
	}
}



//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
FLOAT	g_Angle = 0.0f;	
VOID SetupMatrices()
{
    // Set up world matrix
    D3DXMATRIXA16 matWorld;
    D3DXMatrixIdentity( &matWorld );
	if (g_SetupMatrices)
	{// 允许旋转
		g_Angle = timeGetTime()/1000.0f;
	}
    D3DXMatrixRotationX( &matWorld, g_Angle );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix. A view matrix can be defined given an eye point,
    // a point to lookat, and a direction for which way is up. Here, we set the
    // eye five units back along the z-axis and up three units, look at the
    // origin, and define "up" to be in the y-direction.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    // Clear the backbuffer and the zbuffer
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {

		if (g_pVB_MyRect)
		{	// 简单的画个框框，做个参考值
			g_pd3dDevice->SetTexture( 0, NULL );
			g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			g_pd3dDevice->SetStreamSource( 0, g_pVB_MyRect, 0, sizeof(CUSTOMVERTEX_MYRECT) );
			g_pd3dDevice->SetIndices(g_pIndexVB_MyRect);
			g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX_MYRECT );			
			g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
			g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}		

        // Setup the world, view, and projection matrices		
		SetupMatrices();

        // Setup our texture. Using textures introduces the texture stage states,
        // which govern how textures get blended together (in the case of multiple
        // textures) and lighting information. In this case, we are modulating
        // (blending) our texture with the diffuse color of the vertices.
        g_pd3dDevice->SetTexture( 0, g_pTexture );
        g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
        g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
        g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
        g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );

    #ifdef SHOW_HOW_TO_USE_TCI
        // Note: to use D3D texture coordinate generation, use the stage state
	// D3DTSS_TEXCOORDINDEX, as shown below. In this example, we are using
	// the position of the vertex in camera space (D3DTSS_TCI_CAMERASPACEPOSITION)
	// to generate texture coordinates. Camera space is the vertex position
	// multiplied by the World and View matrices.  The tex coord index (TCI)  
	// parameters are passed into a texture transform, which is a 4x4 matrix  
	// which transforms the x,y,z TCI coordinates into tu, tv texture coordinates.

	// In this example, the texture matrix is setup to transform the input
	// camera space coordinates (all of R^3) to projection space (-1,+1) 
	// and finally to texture space (0,1).
	//    CameraSpace.xyzw = (input vertex position) * (WorldView)
	//    ProjSpace.xyzw = CameraSpace.xyzw * Projection           //move to -1 to 1
	//    TexSpace.xyzw = ProjSpace.xyzw * ( 0.5, -0.5, 1.0, 1.0 ) //scale to -0.5 to 0.5 (flip y)
	//    TexSpace.xyzw += ( 0.5, 0.5, 0.0, 0.0 )                  //shift to 0 to 1

	// Setting D3DTSS_TEXTURETRANSFORMFLAGS to D3DTTFF_COUNT4 | D3DTTFF_PROJECTED
	// tells D3D to divide the input texture coordinates by the 4th (w) component.
	// This divide is necessary when performing a perspective projection since
	// the TexSpace.xy coordinates prior to the homogeneous divide are not actually 
	// in the 0 to 1 range.
	D3DXMATRIXA16 mTextureTransform;
	D3DXMATRIXA16 mProj;
	D3DXMATRIXA16 mTrans;
	D3DXMATRIXA16 mScale;

	g_pd3dDevice->GetTransform( D3DTS_PROJECTION, &mProj );
	D3DXMatrixTranslation( &mTrans, 0.5f, 0.5f, 0.0f );
	D3DXMatrixScaling( &mScale, 0.5f, -0.5f, 1.0f );
	mTextureTransform = mProj * mScale * mTrans;

	g_pd3dDevice->SetTransform( D3DTS_TEXTURE0, &mTextureTransform );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT4 | D3DTTFF_PROJECTED );
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );
    #endif

        // Render the vertex buffer contents
        g_pd3dDevice->SetStreamSource( 0, g_pVB, 0, sizeof(CUSTOMVERTEX) );
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
        g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2*50-2 );

		if (g_SDOADx9)
			g_SDOADx9->RenderEx();

        // End the scene
        g_pd3dDevice->EndScene();
    }
	
	if (g_IsWindow)
	{// 窗口模式
		// g_D3DRenderRect为指定将背景缓冲哪一部分区域翻转到前景缓冲中(即显示)
		g_pd3dDevice->Present( &g_D3DRenderRect, &g_WinRenderRect, g_MainWin_hWnd, NULL );
	}
	else
	{// 全屏模式
		// Present the backbuffer contents to the display
		g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
	}
} 

void RefreshUseBackBuffer()
{
	if (g_SDOACfg)
	{
		if (g_IsWindow)
		{// 仅窗口模式下才有效的
			// 通知当前图形引擎使用背景缓冲的区域是哪一部分
			g_SDOACfg->SetUseBackBufferRect(g_D3DRenderRect);
		}
		else
		{// 真全屏模式下无法仅使用部分背景缓冲区域的
			g_D3DRenderRect.left = 0;
			g_D3DRenderRect.top = 0;
			g_D3DRenderRect.bottom = 0;
			g_D3DRenderRect.right = 0;
			g_SDOACfg->SetUseBackBufferRect(g_D3DRenderRect);
		}
	}
}

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if(g_SDOADx9) 
	{	// 把消息交给IGW模块处理 
		LRESULT lResult = 0; 
		if (g_SDOADx9->OnWindowProc( hWnd, msg, wParam, lParam, &lResult ) == SDOA_OK ) 
		{ 			
			return lResult; 
		} 
	}
    switch( msg )
    {
		case WM_SIZE:
			{	// 注意这里收到的窗口大小总是客户区大小
				g_WinWidth = LOWORD(lParam);
				g_WinHeight = HIWORD(lParam);
				g_WinRenderRect.right = g_WinWidth;
				g_WinRenderRect.bottom = g_WinHeight;
				if (g_pd3dDevice)
				{
					if (g_WinWidth < d3dpp.BackBufferWidth) 
					{
						g_D3DRenderRect.right = g_WinWidth + g_D3DRenderRect.left;
					}

					if (g_D3DRenderRect.right > d3dpp.BackBufferWidth)
					{
						g_D3DRenderRect.right = d3dpp.BackBufferWidth;
					}

					if ( g_WinHeight < d3dpp.BackBufferHeight )
					{
						g_D3DRenderRect.bottom = g_WinHeight + g_D3DRenderRect.top;
					}
					if (g_D3DRenderRect.bottom > d3dpp.BackBufferHeight)
					{
						g_D3DRenderRect.bottom = d3dpp.BackBufferHeight;
					}
					RefreshUseBackBuffer();
				}
				WCHAR strMyOutput[100] = {0};
				StringCchPrintfW( strMyOutput, 100, L"MsgProc WM_SIZE(%d, %d)\n", g_WinWidth, g_WinHeight);
				OutputDebugStringW(strMyOutput);
			}
		break;
		case WM_ENTERSIZEMOVE:
			g_SetupMatrices = false;
			OutputDebugStr("MsgProc WM_ENTERSIZEMOVE\n");
			break;
		case WM_EXITSIZEMOVE:
			g_SetupMatrices = true;
			OutputDebugStr("MsgProc WM_EXITSIZEMOVE\n");
			break;
		case WM_PAINT:
			if ( (!g_SetupMatrices) && (!g_DeviceLost) && g_pd3dDevice && g_pTexture && g_pVB)
			{
				Render();
				return 0;
			}
			break;
		case WM_SYSKEYDOWN:
			{
			 DWORD dwMask = (1 << 29);
			 bool bAltDown = ( (lParam & dwMask) != 0 );
			 if (bAltDown && (VK_RETURN == wParam))
			 {	// 在全屏与窗口模式间切换，使用笨办法全部重建
				g_IsWindow = !g_IsWindow;
				OutputDebugStr("MsgProc WM_SYSKEYDOWN ALT+ENTER begin\n");
				if (g_SDOADx9)
				{	// 释放图形引擎资源
					g_SDOADx9->Finalize();
				}
				Cleanup();
				InitD3D(g_MainWin_hWnd);
				GetClientRect(g_MainWin_hWnd, &g_D3DRenderRect);
				RefreshUseBackBuffer();
				if (g_SDOADx9)
				{	// 初始化IGW内部图形引擎
					g_SDOADx9->Initialize(g_pd3dDevice, &d3dpp, false);
				}
				InitGeometry();
				
				OutputDebugStr("MsgProc WM_SYSKEYDOWN ALT+ENTER end\n");
				return 0;
			 }

			 if (bAltDown && (VK_HOME == wParam))
			 {// 测试显示数据				
				if (g_SDOACfg) 
				{
					RECT MySetUseBackBufferRect = {0, 0, 0, 0};
					RECT MyWin;

					GetClientRect(g_MainWin_hWnd, &MyWin);
					g_SDOACfg->GetUseBackBufferRect(&MySetUseBackBufferRect);
					WCHAR strMyOutput[100] = {0};
					StringCchPrintfW( strMyOutput, 100, L"MsgProc WM_SYSKEYDOWN ALT+HOME(%d, %d, %d, %d)-Client(%d, %d)\n", 
						MySetUseBackBufferRect.left, MySetUseBackBufferRect.top, 
						MySetUseBackBufferRect.right, MySetUseBackBufferRect.bottom,
						MyWin.right - MyWin.left,
						MyWin.bottom - MyWin.top);
					OutputDebugStringW(strMyOutput);

				}
			 }
			}
			 break;
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
    }// case

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

void CALLBACK OnLostDevice()
{   /* 通知d3d设备丢失 */
	if ( g_pVB_MyRect != NULL )
	{
		g_pVB_MyRect->Release();
		g_pVB_MyRect = NULL;
	}
	if ( g_pIndexVB_MyRect != NULL )
	{
		g_pIndexVB_MyRect->Release();
		g_pIndexVB_MyRect = NULL;
	}
	if( g_pTexture != NULL )
	{
		g_pTexture->Release();
		g_pTexture = NULL;
	}

	if( g_pVB != NULL )
	{
		g_pVB->Release();
		g_pVB = NULL;
	}

	if (g_SDOADx9)
		g_SDOADx9->OnDeviceLost();

	OutputDebugStr("OnLostDevice\n");
}

void CALLBACK OnResetDevice()
{
	/* 通知d3d设备重置成功 */
	InitGeometry();
	if ( g_pd3dDevice )
	{
		// Turn off culling
		g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

		// Turn off D3D lighting
		g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

		// Turn on the zbuffer
		g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	}
	if (g_SDOADx9)
		g_SDOADx9->OnDeviceReset(&d3dpp);

	OutputDebugStr("OnResetDevice\n");
}


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, LoadCursor( NULL, IDC_ARROW ), NULL, NULL,
                      "D3D Tutorial", NULL };
    RegisterClassEx( &wc );

    // Create the application's window
    g_MainWin_hWnd = CreateWindow( "D3D Tutorial", "D3D Tutorial 05: Textures",
                              WS_OVERLAPPEDWINDOW, 100, 100, g_WinWidth, g_WinHeight,
                              NULL, NULL, wc.hInstance, NULL );
	RECT rtCurRect;
	GetClientRect(g_MainWin_hWnd, &rtCurRect);
	// 注意CreateWindow的窗口大小包括标题与边框的，下面准确的设置客户区的大小
	SetWindowPos(g_MainWin_hWnd, HWND_TOP, 0, 0, 
		g_WinWidth - (rtCurRect.right - rtCurRect.left) + g_WinWidth, 
		g_WinHeight - (rtCurRect.bottom - rtCurRect.top) + g_WinHeight, SWP_NOZORDER + SWP_NOACTIVATE);

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( g_MainWin_hWnd ) ) )
    {
		OpenIGW();
		if (igwInitialize)
		{	// 说明加载成功，表示下......			
			SetWindowText(g_MainWin_hWnd, "D3D Tutorial [加载IGW组件成功]");
		}	
		RefreshUseBackBuffer();
		if (g_SDOADx9)
		{	// 初始化IGW内部图形引擎
			g_SDOADx9->Initialize(g_pd3dDevice, &d3dpp, false);
		}
        // Create the scene geometry
        if( SUCCEEDED( InitGeometry() ) )
        {
            // Show the window
            ShowWindow( g_MainWin_hWnd, SW_SHOWDEFAULT );
            UpdateWindow( g_MainWin_hWnd );

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof(msg) );
            while( msg.message!=WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
				{	// 简单处理设备丢失问题
					if (g_DeviceLost)
					{	// 处于设备丢失中可慢点恢复，避免长时间丢失占用过多CPU
						Sleep(100);
					}
					if (g_pd3dDevice)
					{
						switch (g_pd3dDevice->TestCooperativeLevel())
						{
						case D3D_OK:
							{	// 绘制
								if (g_pTexture && g_pVB)
									Render();
								g_DeviceLost = false;
								break;
							}

						case D3DERR_DEVICELOST:
							{
								if ( !g_DeviceLost )
								{
									OnLostDevice();
									g_DeviceLost = true;
								}							
								break;
							}
						case D3DERR_DEVICENOTRESET:
							{
								if ( g_pd3dDevice->Reset( &d3dpp ) == D3D_OK )
								{
									OnResetDevice();
									g_DeviceLost = false;
								}
								break;
							}
						}// switch
					}// if					
				}
            }
        }
    }

	if (g_SDOADx9)
	{	// 释放IGW内部图形引擎
		g_SDOADx9->Finalize();
	}
	/* 释放IGW */
	CloseIGW();
	/* 完全第一 */
	Cleanup();
    UnregisterClass( "D3D Tutorial", wc.hInstance );
    return 0;
}



