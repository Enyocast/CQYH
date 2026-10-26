/*
This is RAD's high level API for using 3D hardware to do color conversion.
It is supported on every 3D platform that Bink runs on.

It's a simple API, so you should see your platform's example code
to see all the nitty-gritty details.


There are three main cross platform functions:

  Create_Bink_textures:  This function takes a BINKTEXTURESET structure and
    creates the texture resources to render it quickly.
  
  Free_Bink_textures:  Frees the resources allocated in Create_Bink_textures.

  Draw_Bink_textures:  Renders the textures onto the screen.


There are also a few platform specific functions:

  Wait_for_Bink_textures:  On Wii, Xbox, Xbox 360 and PS3, this function 
    waits for the GPU to finish using the given texture set. Call
    before BinkOpen.


  Create_Bink_shaders:  On everything but the Wii, this function creates
    the pixel shaders we use to do the color conversion. Call this function
    before the first call to Create_Bink_textures.

  Free_Bink_shaders:  Frees the pixel shaders created in Create_Bink_shaders.


  Lock_Bink_textures:  On Windows, locks the textures so that BinkDoFrame can
    decompress into them.

  Unlock_Bink_textures:  On Windows, unlocks the textures after BinkDoFrame.


On Windows DX9, there are two other functions:

  Before_Reset_Bink_textures: Call before you call the D3D Reset function.

  After_Reset_Bink_textures: Call after you call the D3D Reset function.

For Windows DX10 or DX11, you simply free and re-create the textures completely
  whenever the device is lost or reset.



So, basically, playback works like this:

  1) Create the pixel shaders on the platforms that need it.
  
  2) If you are on DX10, DX11, or OpenGL, open the Bink file normally.  Otherwise,
     open the Bink file with the BINKNOFRAMEBUFFERS flag.  We will use our API
     to create the frame buffers that Bink will use.  On DX10, DX11, and OpenGL,
     we let Bink allocate the buffers and then copy out of them.

  3) Call BinkGetFrameBuffersInfo to get the details on the frame buffers 
     that we need.

  4) Call Create_Bink_textures to create the textures.

  5) On anything but DX10, DX11, and OpenGL, call BinkRegisterFrameBuffers to 
     register these new textures with Bink.

  6) Call Wait_for_Bink_textures before BinkDoFrame (or Lock_Bink_textures 
     on Windows).

  7) Call BinkDoFrame to decompress a video frame.

  8) Draw the frame using Draw_Bink_textures.


And that's it! (Skipping over a few details - see the examples for all 
the details...)

Should drop in really quickly and it hides a ton of platform specific ugliness!

*/

#ifndef BINKTEXTURESH
#define BINKTEXTURESH


#include "bink.h"

RADDEFSTART

#if defined(__gl_h_) || defined(__gl3_h_) || defined(__RADPS3__) || defined(__RADWII__) || defined(__RAD3DS__) || defined(__RADWIIU__) 
  #define if_used_3d_device
  #define if_used_3d_device_solo void
#elif defined( __RADPSP2__ )
  #define if_used_3d_device
  #define if_used_3d_device_solo void
  #define if_used_3d_device_draw SceGxmContext* i_GxmContext,
#elif defined( __RADPS4__ )
  #define if_used_3d_device
  #define if_used_3d_device_solo void
  #define if_used_3d_device_draw Gnmx::GfxContext * Gfx,
#elif defined( __d3d11_x_h__ )
  #define if_used_3d_device_solo ID3DXboxPerformanceDevice * d3d_device
  #define if_used_3d_device ID3DXboxPerformanceDevice * d3d_device,
#elif defined( __d3d11_h__ ) // order matters here because D3D11 includes d3d10.h!
  #define if_used_3d_device_solo ID3D11Device * d3d_device
  #define if_used_3d_device ID3D11Device * d3d_device,
#elif defined( __d3d10_h__ )
  #define if_used_3d_device_solo ID3D10Device * d3d_device
  #define if_used_3d_device ID3D10Device * d3d_device,
#elif defined( _D3D9_H_ )
  #define if_used_3d_device_solo LPDIRECT3DDEVICE9 d3d_device
  #define if_used_3d_device LPDIRECT3DDEVICE9 d3d_device,
#else
  #error Unknown 3D API! (put 3D header file, gl.h, d3d.h, etc, before binktextures.h)
#endif

#ifndef if_used_3d_device_draw
  #define if_used_3d_device_draw if_used_3d_device
#endif

typedef struct BINKFRAMETEXTURES
{
#ifdef __RADPS3__

  UINTa Ytexture;
  UINTa cRtexture;
  UINTa cBtexture;
  UINTa Atexture;
  UINTa fence;
  
#elif defined( __gl_h_ ) || defined(__gl3_h_) 

  // OpenGL
  U32 Ytexture;
  U32 cRtexture;
  U32 cBtexture;
  U32 Atexture;

#elif defined( __RADWIIU__ )

  // The createtexture function expects the GX2Texture to be right after the void*
  void* Ydata;
  GX2Texture Ytexture;
  void* cRdata;
  GX2Texture cRtexture;
  void* cBdata;
  GX2Texture cBtexture;
  void* Adata;
  GX2Texture Atexture;

#elif defined (__RADPS4__ )

  void* Ydata;
  U32 Ytexture[8];
  void* cRdata;
  U32 cRtexture[8];
  void* cBdata;
  U32 cBtexture[8];
  void* Adata;
  U32 Atexture[8];

  U64 marker_wait;

#elif defined( __RADWII__ )

  GXTexObj Ytexture;
  GXTexObj cRtexture;
  GXTexObj cBtexture;
  GXTexObj Atexture;

#elif defined(__RADPSP2__)

  SceUID AllocId;
  SceGxmTexture Ytexture, cRtexture, cBtexture, Atexture;

#elif defined(__RAD3DS__)

  U32 Ytexture;
  U32 cRtexture;
  U32 cBtexture;
  U32 Atexture;

#elif defined( __d3d11_x_h__ )

  #define BINKPLANEY      0
  #define BINKPLANECR     1
  #define BINKPLANECB     2
  #define BINKPLANEA      3
  #define BINKPLANECOUNT  4

  ID3D11Texture2D * tex[ BINKPLANECOUNT ];
  ID3D11ShaderResourceView * srv[ BINKPLANECOUNT ];
  BINKPLANE plane[ BINKPLANECOUNT ];

  U64 fence;

#elif defined( __d3d10_h__ ) || defined( __d3d11_h__ )

  U32 Ysize;
  U32 cRsize;
  U32 cBsize;
  U32 Asize;

  #define BINKPLANEY      0
  #define BINKPLANECR     1
  #define BINKPLANECB     2
  #define BINKPLANEA      3
  #define BINKPLANECOUNT  4

#elif defined( _D3D9_H_ )

  U32 Ysize;
  U32 cRsize;
  U32 cBsize;
  U32 Asize;

  LPDIRECT3DTEXTURE9 Ytexture;
  LPDIRECT3DTEXTURE9 cRtexture;
  LPDIRECT3DTEXTURE9 cBtexture;
  LPDIRECT3DTEXTURE9 Atexture;

#endif
} BINKFRAMETEXTURES;

#if defined( __d3d11_x_h__ )

#define BINKTEXTURESMAXBACKING 3 // triple-buffer; double-buffer is often not enough.

#else

#define BINKTEXTURESMAXBACKING BINKMAXFRAMEBUFFERS

#endif

typedef struct BINKTEXTURESET
{
  // this is the Bink info on the textures
  BINKFRAMEBUFFERS bink_buffers;

  // this is the GPU info for the textures
  BINKFRAMETEXTURES textures[ BINKTEXTURESMAXBACKING ];

  // this is specialized global data for each platform
  #if defined( __RADPS3__ )

    UINTa pbo;
    U32 framesize;

  #elif defined( __gl_h_ ) || defined(__gl3_h_) || defined( __RADPS4__ )
  
    S32 video_width, video_height;

  #elif defined( __d3d11_x_h__ ) // must be before d3d11.h test, since D3D11.X includes D3D11

    U32 cur_spare, num_backing;

    ID3D11Buffer * const_buf;

    S32 video_width, video_height;

  #elif defined( __d3d11_h__ ) // must be before d3d10.h test, d3d11.h includes d3d10.h

    ID3D11Buffer * const_buf;

    ID3D11Texture2D * tex[ BINKPLANECOUNT ];
    ID3D11ShaderResourceView * srv[ BINKPLANECOUNT ];

    S32 video_width, video_height;

  #elif defined( __d3d10_h__ )

    ID3D10Buffer * const_buf;

    ID3D10Texture2D * tex[ BINKPLANECOUNT ];
    ID3D10ShaderResourceView * srv[ BINKPLANECOUNT ];

    S32 video_width, video_height;

  #elif defined( _D3D9_H_ )

    // on windows, we need a second set of textures to draw with
    BINKFRAMETEXTURES tex_draw;

    S32 video_width, video_height;

  #elif defined( __RAD3DS__ )

    U32 YWidthPow2, YHeightPow2, CWidthPow2, CHeightPow2;
    BINKSWIZZLEBUFFERS swizzle_buffers;

  #elif defined( __RADWII__ )
  
    void * base_ptr;
    U32 framesize;
    
    U32 YAdeswizzle_width; 
    U32 YAdeswizzle_height; 
    U32 cRcBdeswizzle_width; 
    U32 cRcBdeswizzle_height; 

    GXTexObj YAdeswizzle;
    GXTexObj cRcBdeswizzle;
    
    S32 drawing[ 2 ];
    U32 fence[ 2 ];

  #endif
} BINKTEXTURESET;

//=============================================================================

//
// allocate the textures that we'll need
//
RADDEFFUNC S32 Create_Bink_textures( if_used_3d_device
                                     BINKTEXTURESET * set_textures,
                                     S32 video_width, S32 video_height );

#ifdef __d3d11_x_h__

//
// Allocate the textures that we'll need
//
// Pass 2 for num_buffers to use double-buffering (also the default on
// invalid input), 3 if you want triple buffering. This can help if you're
// seeing a lot of time spent in Lock_Bink_textures when under high GPU load.
//
RADDEFFUNC S32 Create_Bink_textures_numbufs( if_used_3d_device
                                             BINKTEXTURESET * set_textures,
                                             S32 video_width, S32 video_height,
                                             S32 num_buffers );

#endif

// frees the textures
RADDEFFUNC void Free_Bink_textures( if_used_3d_device
                                    BINKTEXTURESET * set_textures );

// draws the textures with D3D
RADDEFFUNC void Draw_Bink_textures( if_used_3d_device_draw
                                    HBINK Bink, 
                                    BINKTEXTURESET * set_textures,
                                    U32 width,
                                    U32 height,
                                    F32 x_offset,
                                    F32 y_offset,
                                    F32 x_scale,
                                    F32 y_scale,
                                    F32 alpha_level
#ifndef __RAD3DS__
                                    , S32 is_premultiplied_alpha  // not on 3DS, since you *always* use pre-mult on 3DS
#endif

#ifdef __RAD3DS__
                                    , S32 src_x, S32 src_y, S32 src_w, S32 src_h
                                    , U32 screen_width, U32 screen_height, S32 isrighteye
#endif
                                    );

//=============================================================================

// DX10, DX11, or OpenGL, but not on DX11.X or PS3.
#if ( defined( __d3d10_h__ ) || defined( __d3d11_h__) || defined( __gl_h_ ) || defined(__gl3_h_) ) && ( !defined( __d3d11_x_h__ ) && !defined( __RADPS3__ ) )

  // Update the textures after rendering
  RADDEFFUNC void Update_Bink_textures( if_used_3d_device  BINKTEXTURESET * set_textures, HBINK Bink );

#elif defined( __d3d11_x_h__ )

  // make sure the GPU isn't using the next set of textures
  RADDEFFUNC void Wait_for_Bink_textures( ID3DXboxPerformanceDevice * dev, BINKTEXTURESET * set_textures );

#else

  // on Consoles, we generally use flush and wait semantics - 
  //   we flush the CPU memory out to the GPU and then
  //   we wait before using the frame again

  // make sure the GPU isn't using the next set of textures
  RADDEFFUNC void Wait_for_Bink_textures( BINKTEXTURESET * set_textures );

#endif

//=============================================================================

// Every platform we support except for Wii needs shaders.
#if !defined( __RADWII__ )

#if defined(__RADPS3__)

  // creates the couple of shaders that we use
  // for GCM, local_mem should be a pointer that is BINK_TEXTURES_LOCAL_MEM bytes long
  // for PSGL, local mem should be zero
  RADDEFFUNC S32 Create_Bink_shaders( U32 width, U32 height, void * local_mem );

  #define BINK_TEXTURES_LOCAL_MEM 768

#else

  // creates the couple of shaders that we use
  RADDEFFUNC S32 Create_Bink_shaders( if_used_3d_device_solo );

#endif

  // free our shaders
  RADDEFFUNC void Free_Bink_shaders( void );

#endif


// For DX9
#if defined( _D3D9_H_ )

  // Lock the textures for use by D3D 
  RADDEFFUNC void Lock_Bink_textures( BINKTEXTURESET * set_textures );

  // Unlock the textures after rendering
  RADDEFFUNC void Unlock_Bink_textures( if_used_3d_device  BINKTEXTURESET * set_textures, HBINK Bink );
  
  RADDEFFUNC void Before_Reset_Bink_textures( if_used_3d_device BINKTEXTURESET * set_textures, HBINK Bink );
  RADDEFFUNC S32 After_Reset_Bink_textures( if_used_3d_device  BINKTEXTURESET * set_textures );

#endif

#undef if_used_3d_device
#undef if_used_3d_device_solo
#undef if_used_3d_device_draw

RADDEFEND

//=============================================================================

#endif
