#include "bink.h"

#ifdef __RADMAC__

  #include <OpenGL/gl3.h>
  #include <dlfcn.h>

  #define TARGET_GL_CORE
  #define TEXFORMAT GL_RED

  #define glGenVertexArrays(c, p)
  #define glBindVertexArray(c)
  #define glDeleteVertexArrays(c,p)

#elif defined(__RADIPHONE__)

  #include <OpenGLES/ES2/gl.h>
  #include <OpenGLES/ES2/glext.h>

  #define TARGET_GL_ES
  #define TEXFORMAT GL_LUMINANCE

  #define glGenVertexArrays glGenVertexArraysOES
  #define glBindVertexArray glBindVertexArrayOES

#elif defined(__RADANDROID__)

  #include <EGL/egl.h>
  #include <GLES2/gl2.h>
  #include <GLES2/gl2ext.h>

  #define TARGET_GL_ES
  #define glGenVertexArrays(c, p)
  #define glBindVertexArray(c)

  #define TEXFORMAT GL_LUMINANCE

  #include <android/log.h>
  #define dprintf(...) ((void)__android_log_print(ANDROID_LOG_INFO, "bink-gl-textures", __VA_ARGS__))

#elif defined(__RADLINUX__)

  #define GL_GLEXT_PROTOTYPES
  #include <GL/gl.h>
  #include <GL/glext.h>

  #define TARGET_GL_COMPAT
  #define TEXFORMAT GL_RED

#elif defined(__RADNT__)

  #include <windows.h>
  #include <malloc.h>
  #include <GL/gl.h>
  #include <GL/glcorearb.h>

  #define TARGET_GL_CORE
  #define TEXFORMAT GL_RED
  #define LOAD_AS_EXTENSION
  #define NO_OPTIONAL_EXTENSIONS

  static void * glbStartLoad( void )
  {
      return (void *)LoadLibraryA("opengl32.dll");
  }
  
  static void * glbGetProcAddress( void * handle, char const * proc )
  {
      void * res = wglGetProcAddress( proc );
      if ( !res )
          res = GetProcAddress( (HMODULE)handle, proc );
  
      return res;
  }
  
  static void glbEndLoad( void * handle )
  {
      FreeLibrary( (HMODULE)handle );
  }

#endif

#include "binktextures.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef dprintf
#define dprintf(...) printf(__VA_ARGS__)
#endif

// GL Objects...
static GLuint s_Program = 0;
static GLuint s_IndexBuffer = 0;
static GLuint s_VertexBuffer = 0;
static GLuint s_VAO = 0;

// Flags
static S32 s_HasUnpackRowLength = 1;

// Attributes/uniforms in the shaders.
static S32 yscaleNPAIndex = 0;
static S32 crcNPAIndex = 0;
static S32 cbcNPAIndex = 0;
static S32 adjNPAIndex = 0;
static S32 AlphaNPAIndex = 0;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// Extensions and GL3+ stuff we use that might not be defined in system headers

// GL_EXT_unpack_subimage
#ifndef GL_UNPACK_ROW_LENGTH
#define GL_UNPACK_ROW_LENGTH 0x0CF2
#endif

#ifdef LOAD_AS_EXTENSION

#include <GL/glcorearb.h>

#define GLTEXTURES_EXTENSION_LIST \
    /*  id                                      procname */ \
    GLE(ActiveTexture,                          ACTIVETEXTURE) \
    GLE(AttachShader,                           ATTACHSHADER) \
    GLE(BindAttribLocation,                     BINDATTRIBLOCATION) \
    GLE(BindBuffer,                             BINDBUFFER) \
    GLE(BindVertexArray,                        BINDVERTEXARRAY) \
    GLE(BufferData,                             BUFFERDATA) \
    GLE(CompileShader,                          COMPILESHADER) \
    GLE(CreateProgram,                          CREATEPROGRAM) \
    GLE(CreateShader,                           CREATESHADER) \
    GLE(DeleteBuffers,                          DELETEBUFFERS) \
    GLE(DeleteProgram,                          DELETEPROGRAM) \
    GLE(DeleteShader,                           DELETESHADER) \
    GLE(DeleteVertexArrays,                     DELETEVERTEXARRAYS) \
    GLE(DetachShader,                           DETACHSHADER) \
    GLE(EnableVertexAttribArray,                ENABLEVERTEXATTRIBARRAY) \
    GLE(GenBuffers,                             GENBUFFERS) \
    GLE(GenVertexArrays,                        GENVERTEXARRAYS) \
    GLE(GetProgramiv,                           GETPROGRAMIV) \
    GLE(GetShaderInfoLog,                       GETSHADERINFOLOG) \
    GLE(GetShaderiv,                            GETSHADERIV) \
    GLE(GetStringi,                             GETSTRINGI) \
    GLE(GetUniformLocation,                     GETUNIFORMLOCATION) \
    GLE(LinkProgram,                            LINKPROGRAM) \
    GLE(ShaderSource,                           SHADERSOURCE) \
    GLE(Uniform1i,                              UNIFORM1I) \
    GLE(Uniform4f,                              UNIFORM4F) \
    GLE(Uniform4fv,                             UNIFORM4FV) \
    GLE(UseProgram,                             USEPROGRAM) \
    GLE(VertexAttribPointer,                    VERTEXATTRIBPOINTER) \
    /* end */

#define GLE(id, procname) static PFNGL##procname##PROC glb##id;
GLTEXTURES_EXTENSION_LIST
#undef GLE

static void load_extensions( void )
{
    void *handle = glbStartLoad();
#define GLE(id, procname) glb##id = (PFNGL##procname##PROC) glbGetProcAddress(handle, "gl" #id);
    GLTEXTURES_EXTENSION_LIST
#undef GLE
    glbEndLoad( handle );
}

#define glActiveTexture glbActiveTexture
#define glAttachShader glbAttachShader
#define glBindAttribLocation glbBindAttribLocation
#define glBindBuffer glbBindBuffer
#define glBindVertexArray glbBindVertexArray
#define glBufferData glbBufferData
#define glCompileShader glbCompileShader
#define glCreateProgram glbCreateProgram
#define glCreateShader glbCreateShader
#define glDeleteBuffers glbDeleteBuffers
#define glDeleteProgram glbDeleteProgram
#define glDeleteShader glbDeleteShader
#define glDeleteVertexArrays glbDeleteVertexArrays
#define glDetachShader glbDetachShader
#define glEnableVertexAttribArray glbEnableVertexAttribArray
#define glGenBuffers glbGenBuffers
#define glGenVertexArrays glbGenVertexArrays
#define glGetProgramiv glbGetProgramiv
#define glGetShaderInfoLog glbGetShaderInfoLog
#define glGetShaderiv glbGetShaderiv
#define glGetStringi glbGetStringi
#define glGetUniformLocation glbGetUniformLocation
#define glLinkProgram glbLinkProgram
#define glShaderSource glbShaderSource
#define glUseProgram glbUseProgram
#define glUniform1i glbUniform1i
#define glUniform4f glbUniform4f
#define glUniform4fv glbUniform4fv
#define glVertexAttribPointer glbVertexAttribPointer

#endif

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static S32 CheckGL(S32 Line)
{
  S32 err = glGetError();
  if (err == 0)
    return 0;
  dprintf("GL Error: %d @ %d\n", err, Line);
  return 1;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static S32 Shader_Link(U32 i_Shader)
{
  S32 Success = 0;

  glLinkProgram(i_Shader);
  if (CheckGL(__LINE__))
    return 0;

  glGetProgramiv(i_Shader, GL_LINK_STATUS, &Success);
  if (Success == 0)
    return 0;

  return 1;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static S32 Shader_Compile(S32 i_Target, char const* i_Source, U32* o_Shader)
{
  if (i_Source == 0)
    return 0;

  *o_Shader = glCreateShader(i_Target);
  if (CheckGL(__LINE__))
    return 0;

  glShaderSource(*o_Shader, 1, (const char**)&i_Source, 0);
  if (CheckGL(__LINE__))
    return 0;

  //
  // Periodically we get a failure here on OSX. Generally on teh first run after
  // a build. However, trying to chase it down and it disappears. Future code maintainers:
  // know that this has inexplicably failed for no reason on OSX 10.7.5
  //
  glCompileShader(*o_Shader);
  if (CheckGL(__LINE__))
    return 0;

  {
    S32 Success = 0;
    glGetShaderiv(*o_Shader, GL_COMPILE_STATUS, &Success);
    if (Success == 0)
    {
      char Log[1024];
      glGetShaderInfoLog(*o_Shader, 1024, 0, Log);
      dprintf("%s\n", Log);
      dprintf("%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
      return 0;
    }
  }
  return 1;
}

static F32 const bink1_consts[16] = {   1.595794678f, -0.813476563f,             0, 0.0,
                                                   0, -0.391448975f,  2.017822266f, 0.0,
                                        -0.87406939f,  0.531782323f, -1.085910693f, 0.0,
                                        1.164123535f,  1.164123535f,  1.164123535f, 1.0f };

static F32 const bink2_consts[16] = {       1.402f,    -0.71414f,            0, 0.0,
                                                 0,    -0.34414f,       1.772f, 0.0,
                                      -0.70374902f,  0.53121506f, -0.88947451f, 0.0,
                                              1.0f,         1.0f,         1.0f, 1.0f };


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#ifndef NO_OPTIONAL_EXTENSIONS

static S32 hasext( char const * which )
{
#ifdef TARGET_GL_CORE
  // GL Core deprecates glGetString(GL_EXTENSIONS)
  GLint i, num_exts;

  glGetIntegerv( GL_NUM_EXTENSIONS, &num_exts );
  for ( i = 0 ; i < num_exts ; i++ )
    if ( strcmp( which, (char const *) glGetStringi( GL_EXTENSIONS, i ) ) == 0 )
      return 1;

  return 0;
#else
  GLubyte const * start = glGetString( GL_EXTENSIONS );
  GLubyte const * current = start;

  for (;;)
  {
    GLubyte const * terminator;
    GLubyte const * where = (GLubyte *) strstr( (const char *) current, which );
    if (!where)
      break;

    terminator = where + strlen(which);
    if ( where == start || *(where - 1) == ' ' )
      if ( *terminator == ' ' || *terminator == '\0' )
        return 1;

    current = terminator;
  }

  return 0;
#endif
}

#endif

static S32 Platform_Init()
{
#ifdef TARGET_GL_ES
  s_HasUnpackRowLength = hasext( "GL_EXT_unpack_subimage" );
#endif

#ifdef LOAD_AS_EXTENSION
  load_extensions();
#endif

  return 1;
}

static S32 Shader_BuildOurShaders()
{
  GLuint vert_shader, frag_shader;

#if defined(TARGET_GL_CORE) || defined(TARGET_GL_COMPAT)
  char const* VertexShader =
      "#version 120\n"

      "attribute vec4 a_position;\n"
      "attribute vec2 a_texcoords;\n"

      "varying vec2 v_texcoords;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = a_position;\n"
      "   v_texcoords = a_texcoords;\n"
      "}\n";

  char const* FragmentShader =
      "#version 120\n"
      "uniform sampler2D YTex;\n"
      "uniform sampler2D cRTex;\n"
      "uniform sampler2D cBTex;\n"
      "uniform sampler2D ATex;\n"
      "varying vec2 v_texcoords;\n"
      "uniform vec4 crcNPA;\n"
      "uniform vec4 cbcNPA;\n"
      "uniform vec4 adjNPA;\n"
      "uniform vec4 yscaleNPA;\n"
      "uniform vec4 AlphaNPA;\n"
      "void main (void)\n"
      "{\n"
      "   float Y = texture2D(YTex, v_texcoords).x;\n"
      "   float cR = texture2D(cRTex, v_texcoords).x;\n"
      "   float cB = texture2D(cBTex, v_texcoords).x;\n"
      "   float A = texture2D(ATex, v_texcoords).x;\n"
      "   vec4 p;\n"
      "   p = yscaleNPA * Y;\n"
      "   p += crcNPA * cR;\n"
      "   p += cbcNPA * cB;\n"
      "   p += adjNPA;\n"
      "   p.w = A;\n"
      "   p *= AlphaNPA;\n"
      "   gl_FragColor = p;\n"
      "}\n";
#elif defined(TARGET_GL_ES)
  char const* VertexShader =
      "attribute vec4 a_position;\n"
      "attribute vec2 a_texcoords;\n"
      "varying vec2 outUV;\n"
      "void main(void)\n"
      "{\n"
      "   gl_Position = a_position;\n"
      "   outUV = a_texcoords;\n"
      "}\n";

  char const* FragmentShader =
      "uniform sampler2D YTex;\n"
      "uniform sampler2D cRTex;\n"
      "uniform sampler2D cBTex;\n"
      "uniform sampler2D ATex;\n"
      "uniform mediump vec4 crcNPA;\n"
      "uniform mediump vec4 cbcNPA;\n"
      "uniform mediump vec4 adjNPA;\n"
      "uniform mediump vec4 yscaleNPA;\n"
      "uniform mediump vec4 AlphaNPA;\n"
      "varying mediump vec2 outUV;\n"
      "void main (void)\n"
      "{\n"
      "   mediump float Y = texture2D(YTex, outUV.st).x;\n"
      "   mediump float cR = texture2D(cRTex, outUV.st).x;\n"
      "   mediump float cB = texture2D(cBTex, outUV.st).x;\n"
      "   mediump float A = texture2D(ATex, outUV.st).x;\n"
      "   mediump vec4 p;\n"
      "   p = yscaleNPA * Y;\n"
      "   p += crcNPA * cR;\n"
      "   p += cbcNPA * cB;\n"
      "   p += adjNPA;\n"
      "   p.w = A;\n"
      "   p *= AlphaNPA;\n"
      "   gl_FragColor = p;\n"
      "}\n";
#endif

  if (Shader_Compile(GL_VERTEX_SHADER, VertexShader, &vert_shader) == 0)
  {
    dprintf("Couldn't compile vertex shader.\n");
    return 0;
  }
  if (Shader_Compile(GL_FRAGMENT_SHADER, FragmentShader, &frag_shader) == 0)
  {
    glDeleteShader(vert_shader);
    dprintf("Couldn't compile fragment shader.\n");
    return 0;
  }

  s_Program = glCreateProgram();
  glAttachShader(s_Program, vert_shader);
  glAttachShader(s_Program, frag_shader);

  glBindAttribLocation(s_Program, 0, "a_position");
  glBindAttribLocation(s_Program, 1, "a_texcoords");

  if (Shader_Link(s_Program) == 0)
  {
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
    glDeleteProgram(s_Program);
    dprintf("Couldn't link program.\n");
    return 0;
  }

  glDetachShader(s_Program, vert_shader);
  glDetachShader(s_Program, frag_shader);
  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  glUseProgram(s_Program);
  glUniform1i(glGetUniformLocation(s_Program, "YTex"), 0);
  glUniform1i(glGetUniformLocation(s_Program, "cRTex"), 1);
  glUniform1i(glGetUniformLocation(s_Program, "cBTex"), 2);
  glUniform1i(glGetUniformLocation(s_Program, "ATex"), 3);

  yscaleNPAIndex = glGetUniformLocation(s_Program, "yscaleNPA");
  crcNPAIndex = glGetUniformLocation(s_Program, "crcNPA");
  cbcNPAIndex = glGetUniformLocation(s_Program, "cbcNPA");
  adjNPAIndex = glGetUniformLocation(s_Program, "adjNPA");
  AlphaNPAIndex = glGetUniformLocation(s_Program, "AlphaNPA");

  glGenBuffers(1, &s_VertexBuffer);
  glGenBuffers(1, &s_IndexBuffer);

  // GL core requires a VAO to be bound.
  glGenVertexArrays(1, &s_VAO);
  glBindVertexArray(s_VAO);

  static GLushort const Indices[] = {0, 1, 2, 0, 2, 3};

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_IndexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

  static GLfloat const Vertices[] = 
  {
    -1, -1, 0, 1, 0, 1,
    1, -1, 0, 1, 1, 1,
    1, 1, 0, 1, 1, 0,
    -1, 1, 0, 1, 0, 0,
  };

  glBindBuffer(GL_ARRAY_BUFFER, s_VertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  glBindVertexArray(0);

  return CheckGL( __LINE__ ) == 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
extern "C" RADDEFFUNC int Create_Bink_shaders()
{
  return Platform_Init() && Shader_BuildOurShaders();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
extern "C" RADDEFFUNC void Free_Bink_shaders()
{
  glDeleteProgram(s_Program);
  glDeleteBuffers(1, &s_VertexBuffer);
  glDeleteBuffers(1, &s_IndexBuffer);
  glDeleteVertexArrays(1, &s_VAO);

  s_Program = 0;
  s_VertexBuffer = 0;
  s_IndexBuffer = 0;
  s_VAO = 0;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void CreateTexture( void* texture, GLsizei width, GLsizei height, GLubyte clear_value )
{
  glGenTextures( 1, (U32*)texture );
  glBindTexture( GL_TEXTURE_2D, *(U32*)texture );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

#ifdef TARGET_GL_ES
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
#else
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0 );
#endif

  // make sure the texture is created here.
  glTexImage2D( GL_TEXTURE_2D, 0, TEXFORMAT, width, height, 0, TEXFORMAT, GL_UNSIGNED_BYTE, NULL );

  // clear
  U8 * init = (U8 *) alloca( width );
  memset( init, clear_value, width );
  for ( GLsizei y = 0 ; y < height ; y++ )
    glTexSubImage2D( GL_TEXTURE_2D, 0, 0, y, width, 1, TEXFORMAT, GL_UNSIGNED_BYTE, init );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
extern "C" RADDEFFUNC int Create_Bink_textures( BINKTEXTURESET * set_textures, S32 video_width, S32 video_height )
{
  BINKFRAMEBUFFERS * bb;
  int i = 0;

  set_textures->video_width = video_width;
  set_textures->video_height = video_height;

  bb = &set_textures->bink_buffers;

  // If we're on GL ES and the platform doesn't have GL_EXT_unpack_subimage,
  // we hit the slow texture update path if the video size isn't a multiple of the
  // internal Bink buffer size. Warn about this!
  if ( !s_HasUnpackRowLength && ( video_width != (S32) bb->YABufferWidth || ( video_width / 2 ) != (S32) bb->cRcBBufferWidth ) )
  {
    dprintf( "Video width isn't properly aligned and GL device doesn't support GL_EXT_unpack_subimage - this will result in slow texture uploads." );
  }

  for ( ; i < bb->TotalFrames ; i++ )
  {
    if ( bb->Frames[i].YPlane.Allocate )
      CreateTexture( &set_textures->textures[i].Ytexture, video_width, video_height, 0 );

    if ( bb->Frames[i].cRPlane.Allocate )
      CreateTexture( &set_textures->textures[i].cRtexture, video_width / 2, video_height / 2, 128 );

    if ( bb->Frames[i].cBPlane.Allocate )
      CreateTexture( &set_textures->textures[i].cBtexture, video_width / 2, video_height / 2, 128 );

    if ( bb->Frames[i].APlane.Allocate )
      CreateTexture( &set_textures->textures[i].Atexture, video_width, video_height, 0 );
  }

  return 1;
}  

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
extern "C" RADDEFFUNC void Free_Bink_textures(BINKTEXTURESET* set_textures)
{
  int i = 0;
  for ( ; i < set_textures->bink_buffers.TotalFrames ; i++ )
  {
    if (set_textures->bink_buffers.Frames[i].YPlane.Allocate)
    {
      glDeleteTextures(1, &set_textures->textures[i].Ytexture);
    }

    if (set_textures->bink_buffers.Frames[i].cRPlane.Allocate)
    {
      glDeleteTextures(1, &set_textures->textures[i].cRtexture);
    }

    if (set_textures->bink_buffers.Frames[i].cBPlane.Allocate)
    {
      glDeleteTextures(1, &set_textures->textures[i].cBtexture);
    }

    if (set_textures->bink_buffers.Frames[i].APlane.Allocate)
    {
      glDeleteTextures(1, &set_textures->textures[i].Atexture);
    }
  }
}

static void update_plane_texture_rect( GLuint tex, GLuint subsample_shift, BINKRECT const * rect, BINKPLANE const * plane, S32 w, S32 h )
{
  // calculate effective update rect
  GLuint rounding_bias = ( 1u << subsample_shift ) - 1;
  GLuint x0 = rect->Left >> subsample_shift;
  GLuint y0 = rect->Top >> subsample_shift;
  GLuint x1 = RR_MIN( rect->Left + rect->Width + rounding_bias, (U32)w ) >> subsample_shift;
  GLuint y1 = RR_MIN( rect->Top + rect->Height + rounding_bias, (U32)h ) >> subsample_shift;

  glBindTexture( GL_TEXTURE_2D, tex );

  if ( s_HasUnpackRowLength )
  {
    glPixelStorei( GL_UNPACK_ROW_LENGTH, plane->BufferPitch );
    glTexSubImage2D( GL_TEXTURE_2D, 0, x0, y0, x1 - x0, y1 - y0, TEXFORMAT, GL_UNSIGNED_BYTE, (char *)plane->Buffer + y0*plane->BufferPitch + x0 );
    glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
  }
  else
  {
    // No unpack row length. But if the texture has the right stride, we can at least
    // upload it in one call by transferring whole rows.
    if ( plane->BufferPitch == ( (U32)w >> subsample_shift ) )
    {
      glTexSubImage2D( GL_TEXTURE_2D, 0, 0, y0, w >> subsample_shift, y1 - y0, TEXFORMAT, GL_UNSIGNED_BYTE, (char *)plane->Buffer + y0*plane->BufferPitch );
    }
    else
    {
      // Slow path - upload strided textures line by line.
      for ( GLuint y = y0 ; y < y1 ; y++ )
        glTexSubImage2D( GL_TEXTURE_2D, 0, x0, y, x1 - x0, 1, TEXFORMAT, GL_UNSIGNED_BYTE, (char *)plane->Buffer + y*plane->BufferPitch + x0 );
    }
  }
}


RADDEFFUNC void Update_Bink_textures( BINKTEXTURESET * set_textures, HBINK Bink )
{
  BINKFRAMEPLANESET * bp_src;
  S32 FrameNum =  Bink->FrameBuffers->FrameNum;
  S32 num_rects;

  bp_src = &Bink->FrameBuffers->Frames[ FrameNum ];

  glActiveTexture(GL_TEXTURE0);

  num_rects = BinkGetRects( Bink, BINKSURFACEFAST );
  if ( num_rects > 0 )
  {
    S32 i;

    for ( i = 0 ; i < num_rects ; i++ )
    {
      update_plane_texture_rect(set_textures->textures[FrameNum].Ytexture,  0, &Bink->FrameRects[ i ], &bp_src->YPlane,  set_textures->video_width, set_textures->video_height);
      update_plane_texture_rect(set_textures->textures[FrameNum].cRtexture, 1, &Bink->FrameRects[ i ], &bp_src->cRPlane, set_textures->video_width, set_textures->video_height);
      update_plane_texture_rect(set_textures->textures[FrameNum].cBtexture, 1, &Bink->FrameRects[ i ], &bp_src->cBPlane, set_textures->video_width, set_textures->video_height);
      if ( set_textures->bink_buffers.Frames[0].APlane.Allocate )
        update_plane_texture_rect(set_textures->textures[FrameNum].Atexture, 0, &Bink->FrameRects[ i ], &bp_src->APlane, set_textures->video_width, set_textures->video_height);
    }
  }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
extern "C" RADDEFFUNC void Draw_Bink_textures(HBINK Bink,BINKTEXTURESET* iTextureSet, U32 w, U32 h, F32 xo, F32 yo, F32 xs, F32 ys, F32 alpha_level, S32 is_premul)
{
  F32 rgb_alpha_level = ( is_premul ) ? alpha_level : 1.0f;

  glUseProgram(s_Program);
  
  glBindVertexArray(s_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, s_VertexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_IndexBuffer);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(4*sizeof(GLfloat)));

  // set the textures
  BINKFRAMETEXTURES * textures = &iTextureSet->textures[ Bink->FrameBuffers->FrameNum ];

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures->Ytexture);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, textures->cRtexture);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, textures->cBtexture);

  if (iTextureSet->bink_buffers.Frames[0].APlane.Allocate)
  {
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, textures->Atexture);

    glEnable(GL_BLEND);
    if (is_premul)
      glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    else
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
  else
  {
    glDisable(GL_BLEND);
  }

  glActiveTexture(GL_TEXTURE0);

  // get the right colorspace values
  F32 const * bink_consts = ( Bink->OpenFlags & BINKYCRCBNEW ) ? bink2_consts : bink1_consts;

  glUniform4fv( yscaleNPAIndex, 1, bink_consts + 12);
  glUniform4fv( crcNPAIndex,    1, bink_consts + 0);
  glUniform4fv( cbcNPAIndex,    1, bink_consts + 4);
  glUniform4fv( adjNPAIndex,    1, bink_consts + 8);
  glUniform4f( AlphaNPAIndex,  rgb_alpha_level,rgb_alpha_level,rgb_alpha_level,alpha_level );

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

  glBindVertexArray(0);
}
