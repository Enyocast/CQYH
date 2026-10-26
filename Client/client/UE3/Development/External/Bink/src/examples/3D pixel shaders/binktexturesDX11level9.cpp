#include <d3d11.h> 
#include <d3dcompiler.h>
#include <float.h>
#include "binktextures.h"

RADDEFSTART

//
// define what type of sampling to use - usually use bilinear, but 
//   if you are using a software renderer, point sampling is faster.
//   

#define SAMPLING_TYPE D3D11_FILTER_MIN_MAG_MIP_LINEAR 
//#define SAMPLING_TYPE D3D11_FILTER_MIN_MAG_MIP_POINT 


//
// pointers to our local vertex and pixel shader
//

static ID3D11PixelShader  * YCrCbToRGBNoPixelAlpha = 0;
static ID3D11PixelShader  * YCrCbAToRGBA = 0;
static ID3D11VertexShader * PositionAndTexCoordGen = 0;
static ID3D11BlendState * alpha_pm_state = 0;
static ID3D11BlendState * alpha_state = 0;
static ID3D11SamplerState * sampler_state = 0;
static ID3D11DepthStencilState * depth_stencil_state = 0;
static ID3D11InputLayout * input_layout = 0;
static ID3D11Buffer * vertex_buffer = 0;

//
// include shader code
//
#include "shaders_11level9.inl"

static F32 const bink1_consts[16] = {   1.595794678f, -0.813476563f,             0, 0.0,
                                                   0, -0.391448975f,  2.017822266f, 0.0,
                                        -0.87406939f,  0.531782323f, -1.085910693f, 0.0,
                                        1.164123535f,  1.164123535f,  1.164123535f, 1.0f };

static F32 const bink2_consts[16] = {       1.402f,    -0.71414f,            0, 0.0,
                                                 0,    -0.34414f,       1.772f, 0.0,
                                      -0.70374902f,  0.53121506f, -0.88947451f, 0.0,
                                              1.0f,         1.0f,         1.0f, 1.0f };


//############################################################################
//##                                                                        ##
//## Free the shaders that we use.                                          ##
//##                                                                        ##
//############################################################################

void Free_Bink_shaders( void )
{
  if ( PositionAndTexCoordGen )
  {
    PositionAndTexCoordGen->Release();
    PositionAndTexCoordGen = 0;
  }

  if ( YCrCbToRGBNoPixelAlpha )
  {
    YCrCbToRGBNoPixelAlpha->Release();
    YCrCbToRGBNoPixelAlpha = 0;
  }

  if ( YCrCbAToRGBA )
  {
    YCrCbAToRGBA->Release();
    YCrCbAToRGBA = 0;
  }

  if ( alpha_pm_state )
  {
    alpha_pm_state->Release();
    alpha_pm_state = 0;
  }
      
  if ( alpha_state )
  {
    alpha_state->Release();
    alpha_state = 0;
  }
      
  if ( sampler_state )
  {
    sampler_state->Release();
    sampler_state = 0;
  }
      
  if ( depth_stencil_state )
  {
    depth_stencil_state->Release();
    depth_stencil_state = 0;
  }

  if ( input_layout )
  {
    input_layout->Release();
    input_layout = 0;
  }

  if ( vertex_buffer )
  {
    vertex_buffer->Release();
    vertex_buffer = 0;
  }
}


//############################################################################
//##                                                                        ##
//## Create the three shaders that we use.                                  ##
//##                                                                        ##
//############################################################################

S32 Create_Bink_shaders( ID3D11Device * d3d_device )
{
  //
  // create a vertex shader that generates positions and tex coords
  //
  
  if ( PositionAndTexCoordGen == 0 )
  {
    if ( FAILED( d3d_device->CreateVertexShader( (DWORD*) CodeVSData, CodeVSSize, 0, &PositionAndTexCoordGen ) ) )
      goto fail;
  }

  //
  // create matching input layout
  // 
  if ( input_layout == 0 )
  {
    static const D3D11_INPUT_ELEMENT_DESC desc[] =
    {
      { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    if ( FAILED ( d3d_device->CreateInputLayout( desc, 1, CodeVSData, CodeVSSize, &input_layout ) ) )
      goto fail;
  }

  //
  // create a pixel shader that goes from YcRcB to RGB (without alpha)
  //

  if ( YCrCbToRGBNoPixelAlpha == 0 )
  {
    if ( FAILED( d3d_device->CreatePixelShader( (DWORD*) CodeYCrCbToRGBAData, CodeYCrCbToRGBASize, 0, &YCrCbToRGBNoPixelAlpha ) ) )
      goto fail;
  }

  //
  // create a pixel shader that goes from YcRcB to RGB with an alpha plane
  //

  if ( YCrCbAToRGBA == 0 )
  {
    if ( FAILED( d3d_device->CreatePixelShader( (DWORD*) CodeYCrCbAToRGBAData, CodeYCrCbAToRGBASize, 0, &YCrCbAToRGBA ) ) )
      goto fail;
  }

  // create our blend state - gad, this is crazy
  if ( alpha_pm_state == 0 )
  {
    D3D11_BLEND_DESC bd = { 0 };
    
    bd.RenderTarget[0].BlendEnable = 1;
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
    bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    if ( FAILED( d3d_device->CreateBlendState( &bd, &alpha_pm_state ) ) )
      goto fail;
  
    bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
      
    if ( FAILED( d3d_device->CreateBlendState( &bd, &alpha_state ) ) )
      goto fail;
  }


  // create the sampler state
  if ( sampler_state == 0 )
  {
    D3D11_SAMPLER_DESC sd;
    
    sd.Filter = SAMPLING_TYPE;
    sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    sd.MinLOD = 0.0f;
    sd.MaxLOD = FLT_MAX;
    sd.MipLODBias = 0.0f;
    sd.MaxAnisotropy = 16;
    sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sd.BorderColor[ 0 ] = 0.0f; 
    sd.BorderColor[ 1 ] = 0.0f; 
    sd.BorderColor[ 2 ] = 0.0f; 
    sd.BorderColor[ 3 ] = 0.0f; 
    
    if ( FAILED( d3d_device->CreateSamplerState( &sd, &sampler_state ) ) )
      goto fail;
  }
  
  
  // create depth/stencil state - omg!
  if ( depth_stencil_state == 0 )
  {
    D3D11_DEPTH_STENCIL_DESC dsd;
    
    dsd.DepthEnable = 0;
    dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
    dsd.DepthFunc = D3D11_COMPARISON_ALWAYS;
    dsd.StencilEnable = 0;
    dsd.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
    dsd.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
    dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
    dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    
    if ( FAILED( d3d_device->CreateDepthStencilState( &dsd, &depth_stencil_state ) ) )
      goto fail;
  }

  // create vertex buffer
  if ( vertex_buffer == 0 )
  {
    static const float vertex_data[4][2] = {
      { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f }
    };
    D3D11_BUFFER_DESC bd;
    D3D11_SUBRESOURCE_DATA data;

    bd.ByteWidth = sizeof(vertex_data);
    bd.Usage = D3D11_USAGE_IMMUTABLE;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    bd.StructureByteStride = 0;

    data.pSysMem = vertex_data;
    data.SysMemPitch = 0;
    data.SysMemSlicePitch = 0;

    if ( FAILED( d3d_device->CreateBuffer( &bd, &data, &vertex_buffer ) ) )
      goto fail;
  }

  return( 1 );
  
 fail:
  Free_Bink_shaders( );
  return( 0 );
}


//############################################################################
//##                                                                        ##
//## Free the textures that we allocated.                                   ##
//##                                                                        ##
//############################################################################

void Free_Bink_textures( ID3D11Device * d3d_device,
                         BINKTEXTURESET * set_textures )
{
  int i;

  // free the constant buffer
  if ( set_textures->const_buf )
  {
    set_textures->const_buf->Release();
    set_textures->const_buf = 0;
  }

  // Free the textures 
  for ( i = 0; i < BINKPLANECOUNT; ++i )
  {
    if ( set_textures->tex[ i ] )
    {
      set_textures->tex[ i ]->Release();
      set_textures->tex[ i ] = 0;
    }

    if ( set_textures->srv[ i ] )
    {
      set_textures->srv[ i ]->Release();
      set_textures->srv[ i ] = 0;
    }
  }
}


//############################################################################
//##                                                                        ##
//## Create a texture while allocating the memory ourselves.                ##
//##                                                                        ##
//############################################################################

static S32 make_texture( ID3D11Device * d3d_device,
                         U32 width, U32 height, DXGI_FORMAT format,
                         ID3D11Texture2D ** out_texture )
{
  ID3D11Texture2D * texture = NULL;

  //
  // Create a texture.
  //

  D3D11_TEXTURE2D_DESC desc;
  
  desc.Width = width;
  desc.Height = height;
  desc.MipLevels = 1;
  desc.ArraySize = 1;
  desc.Format = format;
  desc.SampleDesc.Count = 1;
  desc.SampleDesc.Quality = 0;
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;
  
  if ( SUCCEEDED( d3d_device->CreateTexture2D( &desc, 0, &texture ) ) )
  {
    *out_texture = texture;

    return( 1 );
  }

  //
  // Failed
  //

  return( 0 );
}


//############################################################################
//##                                                                        ##
//## Create 2 sets of textures for Bink to decompress into...               ##
//## Also does some basic sampler and render state init                     ##
//##                                                                        ##
//############################################################################

S32 Create_Bink_textures( ID3D11Device * d3d_device,
                          BINKTEXTURESET * set_textures,
                          S32 video_width, S32 video_height )
{
  BINKFRAMEBUFFERS * bb;
  int i;

  set_textures->video_width = video_width;
  set_textures->video_height = video_height;

  bb = &set_textures->bink_buffers;
  
  //
  // Create our output draw texture (this should be in video card memory)
  //

  for ( i = 0; i < BINKPLANECOUNT; ++i )
  {
    set_textures->tex[ i ] = 0;
    set_textures->srv[ i ] = 0;
  }

  D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
  srvd.Format = DXGI_FORMAT_R8_UNORM;
  srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  srvd.Texture2D.MostDetailedMip = 0;
  srvd.Texture2D.MipLevels = 1;

  // Create Y plane
  if ( bb->Frames[ 0 ].YPlane.Allocate )
  {
    if ( !make_texture( d3d_device,
                        bb->YABufferWidth, bb->YABufferHeight,
                        DXGI_FORMAT_R8_UNORM,
                        &set_textures->tex[ BINKPLANEY ] ) )
      goto fail;
  }

  // Create cR plane
  if ( bb->Frames[ 0 ].cRPlane.Allocate )
  {
    if ( !make_texture( d3d_device,
                        bb->cRcBBufferWidth, bb->cRcBBufferHeight,
                        DXGI_FORMAT_R8_UNORM,
                        &set_textures->tex[ BINKPLANECR ] ) )
      goto fail;
  }

  // Create cB plane
  if ( bb->Frames[ 0 ].cBPlane.Allocate )
  {
    if ( !make_texture( d3d_device,
                        bb->cRcBBufferWidth, bb->cRcBBufferHeight,
                        DXGI_FORMAT_R8_UNORM,
                        &set_textures->tex[ BINKPLANECB ] ) )
      goto fail;
  }

  // Create alpha plane
  if ( bb->Frames[ 0 ].APlane.Allocate )
  {
    if ( !make_texture( d3d_device,
                        bb->YABufferWidth, bb->YABufferHeight,
                        DXGI_FORMAT_R8_UNORM,
                        &set_textures->tex[ BINKPLANEA ] ) )
      goto fail;
  }

  // create views
  for ( i = 0; i < BINKPLANECOUNT; ++i )
  {
    if ( set_textures->tex[ i ] && FAILED( d3d_device->CreateShaderResourceView( set_textures->tex[ i ], &srvd, &set_textures->srv[ i ] ) ) )
      goto fail;
  }

  // create a small constant buffer

  D3D11_BUFFER_DESC desc;
  desc.ByteWidth = 28 * sizeof( F32 );
  desc.Usage = D3D11_USAGE_DEFAULT;
  desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;

  if ( FAILED( d3d_device->CreateBuffer( &desc, 0, &set_textures->const_buf ) ) )
    goto fail;
 
  return( 1 );

fail:

  Free_Bink_textures( d3d_device, set_textures );
  return( 0 );
}


//############################################################################
//##                                                                        ##
//## Update a single Bink texture for use by D3D.                           ##
//##                                                                        ##
//############################################################################

static void Update_texture( ID3D11DeviceContext * d3d_context, ID3D11Texture2D * dest, BINKPLANE * src, D3D11_BOX * rc )
{
  d3d_context->UpdateSubresource( dest, 0, rc, (U8 *) src->Buffer + rc->top * src->BufferPitch + rc->left, src->BufferPitch, 0 );
}


//############################################################################
//##                                                                        ##
//## Update Bink textures for use by D3D.                                   ##
//##                                                                        ##
//############################################################################

void Update_Bink_textures( ID3D11Device * d3d_device, BINKTEXTURESET * set_textures, HBINK Bink )
{
  //
  // Update the pixels on the video card texture
  //

  S32 num_rects;
  BINKFRAMEPLANESET * bp_src;

  bp_src = &Bink->FrameBuffers->Frames[ Bink->FrameBuffers->FrameNum ];

  num_rects = BinkGetRects( Bink, BINKSURFACEFAST );
  if ( num_rects > 0 )
  {
    BINKRECT * brc;
    ID3D11DeviceContext * d3d_context;
    D3D11_BOX rc;
    S32 i;
    
    d3d_device->GetImmediateContext( &d3d_context );
    rc.front = 0;
    rc.back = 1;

    for ( i = 0; i < num_rects; ++i )
    {
      brc = &Bink->FrameRects[ i ];

      rc.left = brc->Left;
      rc.top = brc->Top;
      rc.right = rc.left + brc->Width;
      rc.bottom = rc.top + brc->Height;

      Update_texture( d3d_context, set_textures->tex[ BINKPLANEY ], &bp_src->YPlane, &rc );
      if ( set_textures->tex[ BINKPLANEA ] )
        Update_texture( d3d_context, set_textures->tex[ BINKPLANEA ], &bp_src->APlane, &rc );

      rc.left >>= 1;
      rc.top >>= 1;
      rc.right = ( rc.right + 1 ) >> 1;
      rc.bottom = ( rc.bottom + 1 ) >> 1;

      Update_texture( d3d_context, set_textures->tex[ BINKPLANECR ], &bp_src->cRPlane, &rc );
      Update_texture( d3d_context, set_textures->tex[ BINKPLANECB ], &bp_src->cBPlane, &rc );
    }

    d3d_context->Release();
  }
}


//############################################################################
//##                                                                        ##
//## Draw our textures onto the screen with our vertex and pixel shaders.   ##
//##                                                                        ##
//############################################################################

void Draw_Bink_textures( ID3D11Device * d3d_device,
                         HBINK Bink,
                         BINKTEXTURESET * set_textures,
                         U32 width,
                         U32 height,
                         F32 x_offset,
                         F32 y_offset,
                         F32 x_scale,
                         F32 y_scale,
                         F32 alpha_level,
                         S32 is_premultiplied_alpha )
{
  ID3D11DeviceContext * d3d_context;
  ID3D11BlendState * blend;
  F32 consts[ 28 ];

  d3d_device->GetImmediateContext( &d3d_context );

  //
  // Pixel shader alpha constants
  //

  consts[ 0 ] = ( is_premultiplied_alpha ) ? alpha_level : 1.0f;
  consts[ 1 ] = consts [ 0 ];
  consts[ 2 ] = consts [ 0 ];
  consts[ 3 ] = alpha_level;

  //
  // set the constants for the type of ycrcb we have
  //

  if ( Bink->OpenFlags & BINKYCRCBNEW )
  {
    memcpy( consts + 4, bink2_consts, sizeof( bink2_consts ) );
  }
  else
  {
    memcpy( consts + 4, bink1_consts, sizeof( bink2_consts ) );
  }

  //
  // Vertex shader constants
  //

  consts[ 20 ] =  x_scale * 2.0f;
  consts[ 21 ] = -y_scale * 2.0f;
  consts[ 22 ] = x_offset * 2.0f / (F32) (S32) width - 1.0f;
  consts[ 23 ] = 1.0f - y_offset * 2.0f / (F32) (S32) height;
  consts[ 24 ] = (F32) set_textures->video_width  / (F32) set_textures->bink_buffers.YABufferWidth;
  consts[ 25 ] = (F32) set_textures->video_height / (F32) set_textures->bink_buffers.YABufferHeight;
  consts[ 26 ] = (F32) ( set_textures->video_width  / 2 ) / (F32) set_textures->bink_buffers.cRcBBufferWidth;
  consts[ 27 ] = (F32) ( set_textures->video_height / 2 ) / (F32) set_textures->bink_buffers.cRcBBufferHeight;

  //
  // upload the constant buffer
  //

  d3d_context->UpdateSubresource( set_textures->const_buf, 0, 0, consts, sizeof( consts ), 1 );
  d3d_context->PSSetConstantBuffers( 0, 1, &set_textures->const_buf );
  d3d_context->VSSetConstantBuffers( 0, 1, &set_textures->const_buf );

  //
  // Turn on texture filtering and texture clamping
  //

  d3d_context->PSSetSamplers( 0, 1, &sampler_state );

  //
  // turn off Z buffering, culling, and projection (since we are drawing orthographically)
  //

  d3d_context->RSSetState( NULL );
  d3d_context->OMSetDepthStencilState( depth_stencil_state, 0 );

  //
  // Set the textures.
  //
  
  d3d_context->PSSetShaderResources( 0, 4, set_textures->srv );

  //
  // set vertex shader
  //
  
  d3d_context->VSSetShader( PositionAndTexCoordGen, 0, 0 );

  //
  // are we using an alpha plane? set the pixel shader accordingly.
  //

  blend = ( is_premultiplied_alpha ) ? alpha_pm_state : alpha_state;

  if ( set_textures->tex[ BINKPLANEA ] )
  {
    d3d_context->PSSetShader( YCrCbAToRGBA, 0, 0 );
  }
  else
  {
    d3d_context->PSSetShader( YCrCbToRGBNoPixelAlpha, 0, 0 );

    //
    // are we completely opaque or somewhat transparent?
    //

    if ( alpha_level >= 0.999f )
      blend = 0;
  }

  //
  // set blend state
  //

  d3d_context->OMSetBlendState( blend, 0, 0xffffffff );

  //
  // Draw the vertices.
  //
  UINT stride = sizeof(float) * 2;
  UINT offset = 0;

  d3d_context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
  d3d_context->IASetInputLayout( input_layout );
  d3d_context->IASetVertexBuffers( 0, 1, &vertex_buffer, &stride, &offset );
  d3d_context->Draw( 4, 0 );

  //
  // unselect everything
  //
  
  static void * zeros[4] = { 0, 0, 0, 0 };
  
  d3d_context->VSSetConstantBuffers( 0, 1, (ID3D11Buffer**)zeros );
  d3d_context->VSSetShader( 0, 0, 0 );
  d3d_context->PSSetSamplers( 0, 1, (ID3D11SamplerState**)zeros );
  d3d_context->PSSetConstantBuffers( 0, 1, (ID3D11Buffer**)zeros );
  d3d_context->PSSetShaderResources( 0, 4, (ID3D11ShaderResourceView**)zeros );
  d3d_context->PSSetShader( 0, 0, 0 );
  d3d_context->OMSetDepthStencilState( 0, 0 );
  d3d_context->OMSetBlendState( 0, 0, 0xffffffff );
  d3d_context->IASetInputLayout( 0 );
  d3d_context->IASetVertexBuffers( 0, 1, (ID3D11Buffer**)zeros, (UINT*)zeros, (UINT*)zeros );

  d3d_context->Release();
}

RADDEFEND

// some stuff for the RAD build utility
// @cdep pre $set(c8sysincludes, -I$dxPath/include $c8sysincludes)
// @cdep pre $set(csysincludes64EMT, -I$dxPath/include $csysincludes64EMT)
