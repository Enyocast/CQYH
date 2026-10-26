//----------------------------------------------------------------------------------
// File:    Blur_Common.hlsl
// Email:   sdkfeedback@nvidia.com
// 
// Copyright (c) 2011 NVIDIA Corporation. All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA OR ITS SUPPLIERS
// BE  LIABLE  FOR  ANY  SPECIAL,  INCIDENTAL,  INDIRECT,  OR  CONSEQUENTIAL DAMAGES
// WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS OF BUSINESS PROFITS,
// BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
// ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
//----------------------------------------------------------------------------------

sampler PointClampSampler      : register(s0);
sampler LinearSamplerClamp     : register(s1);

// Use a static blur radius so the loops can be unrolled by fxc
#define g_BlurRadius KERNEL_RADIUS
#define g_HalfBlurRadius (g_BlurRadius/2)

//----------------------------------------------------------------------------------
float CrossBilateralWeight(float r, float d, float d0)
{
    // The exp2(-r*r*g_BlurFalloff) expression below is pre-computed by fxc.
    // On GF100, this ||d-d0||<threshold test is significantly faster than an exp weight.
    return exp2(-r*r*g_BlurFalloff) * (abs(d - d0) < g_BlurDepthThreshold);
}
