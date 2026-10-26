//############################################################################
//##                                                                        ##
//##  EXAMTEX.CPP                                                           ##
//##                                                                        ##
//##  Example of playing a Bink movie using pixel shaders with threads.     ##
//##                                                                        ##
//##  Author: Jeff Roberts                                                  ##
//##                                                                        ##
//############################################################################
//##                                                                        ##
//##  Copyright (C) RAD Game Tools, Inc.                                    ##
//##                                                                        ##
//##  For technical support, contact RAD Game Tools at 425 - 893 - 4300.    ##
//##                                                                        ##
//############################################################################

#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glcorearb.h>
#include <GL/wglext.h>

#include "bink.h"

#include "binktextures.h"


//
// Example globals
//

static HBINK Bink = 0;
static BINKTEXTURESET texture_set = { 0 };

static F32 x_scale = 1.0f;
static F32 y_scale = 1.0f;

static HDC gl_dc;
static HGLRC gl_rc;

static U32 num_cpus = 0;
static U32 extra_thread_index;

//
// Statistics variables.
//

static U64 Timer_freq = 0;
static U64 Last_timer = 0;
static U32 Frame_count;
static U64 Render_time = 0;


//############################################################################
//##                                                                        ##
//## Simple utility functions                                               ##
//##                                                                        ##
//############################################################################

static U32 get_num_cpus( void )
{
  SYSTEM_INFO info;

  info.dwNumberOfProcessors = 1;

  GetSystemInfo( &info );
  if ( info.dwNumberOfProcessors )
    return info.dwNumberOfProcessors;

  return 1;
}

static U64 get_time( void )
{
  U64 ret;
  
  //
  // Read the fast timer.
  //

  QueryPerformanceCounter( ( LARGE_INTEGER* ) &ret );

  return ret;
}

static void Clear_to_black( HWND window )
{
  PAINTSTRUCT ps;
  HDC dc;

  //
  // Get the repaint DC and then fill the window with black.
  //

  dc = BeginPaint( window, &ps );
  FillRect( dc, &ps.rcPaint, (HBRUSH) GetStockObject( BLACK_BRUSH ) );
  EndPaint( window, &ps );
}

void Show_error( LPCSTR text, LPCSTR title )
{
  MessageBox( 0, text, title, MB_OK | MB_ICONSTOP );
}

//############################################################################
//##                                                                        ##
//## Call this function to actually set up a GL context.                    ##
//##                                                                        ##
//############################################################################

static int Init_GL( HWND window, U32 width, U32 height )
{
  static const PIXELFORMATDESCRIPTOR pfd = {
      sizeof( pfd ),
      1,
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
      PFD_TYPE_RGBA,
      24, 0,0, 0,0, 0,0, 8,0, // 24 bits color, 8 bits alpha
      0,0,0,0,0, // no accumulation buffer
      24,8, // at least 24 bits Z, at least 8 bits stencil
      0, // no aux
      PFD_MAIN_PLANE,
      0,0,0,0,
  };

  // Set the pixel format
  gl_dc = GetDC( window );
  if ( !SetPixelFormat( gl_dc, ChoosePixelFormat( gl_dc, &pfd ), &pfd ) )
    return 0;

  // Create a temp rendering context - we need this so we can call wglGetProcAddress.
  HGLRC tempglrc = wglCreateContext( gl_dc );
  wglMakeCurrent( gl_dc, tempglrc );

  PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress( "wglCreateContextAttribsARB" );
  if ( !wglCreateContextAttribsARB )
    return 0;

  wglMakeCurrent( gl_dc, NULL );
  wglDeleteContext( tempglrc );

  // Create our real context.
  int ctxAttribs[] = {
      WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
      WGL_CONTEXT_MINOR_VERSION_ARB, 0,
#ifdef _DEBUG
      WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
      WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
      0
  };

  gl_rc = wglCreateContextAttribsARB( gl_dc, NULL, ctxAttribs );
  if ( !gl_rc )
    return 0;

  wglMakeCurrent( gl_dc, gl_rc );
  glViewport( 0, 0, width, height );

  // And return success.
  return 1;
}


//############################################################################
//##                                                                        ##
//## Call this function to close our GL context.                            ##
//##                                                                        ##
//############################################################################

static void Close_GL( void )
{
  wglMakeCurrent( gl_dc, NULL );
  wglDeleteContext( gl_rc );
  ReleaseDC( WindowFromDC( gl_dc ), gl_dc );
}


//############################################################################
//##                                                                        ##
//## Calc_window_values - calculates the extra width and height to add to   ##
//##   the windows's size so that the video fits.                           ##
//##                                                                        ##
//############################################################################

static void Calc_window_values( HWND window,
                                S32* out_extra_width,
                                S32* out_extra_height )
{
  RECT r, c;

  //
  // Get the current window rect (in screen space).
  //

  GetWindowRect( window, &r );

  //
  // Get the client rectangle of the window.
  //

  GetClientRect( window, &c );

  *out_extra_width = ( r.right - r.left ) - ( c.right - c.left );
  *out_extra_height = ( r.bottom - r.top ) - ( c.bottom - c.top );
}


//############################################################################
//##                                                                        ##
//## Update the playback statistics.                                        ##
//##                                                                        ##
//############################################################################

static void Update_statistics( HWND window )
{
  char buffer[256];
  U64 cur;

  cur = get_time();
  
  if ( Last_timer == 0 )
  {
    Last_timer = cur;
  }
  else
  {
    cur -= Last_timer; // get delta

    sprintf( buffer,
             "Frame rate: %3.1f   GL Rendering: %2.1f%%",
             ( ( F32 ) Frame_count * (F32) Timer_freq ) / ( F32 ) cur,
             ( ( F32 ) Render_time * 100.0F ) / ( F32 ) cur );

    Last_timer += cur; // add delta

    SetWindowText( window, buffer );
  }

  Frame_count = 0;
  Render_time = 0;
}


//############################################################################
//##                                                                        ##
//## WindowProc - the main window message procedure.                        ##
//##                                                                        ##
//############################################################################

LRESULT WINAPI WindowProc( HWND   window,
                           UINT   message,
                           WPARAM wparam,
                           LPARAM lparam )
{
  switch( message )
  {
    //
    // Just close the window if the user hits a key.
    //

    case WM_CHAR:
      DestroyWindow( window );
      break;

    //
    // Pause/resume the video when the focus changes.
    //

    case WM_KILLFOCUS:
      BinkPause( Bink, 1 );
      break;

    case WM_SETFOCUS:
      BinkPause( Bink, 0 );
      break;

    //
    // Handle the window paint messages.
    //

    case WM_PAINT:
      Clear_to_black( window );
      return( 0 );

    case WM_ERASEBKGND:
      return( 1 );

    //
    // Use a timer to display periodic playback statistics.
    //

    case WM_TIMER:
      Update_statistics( window );
      break;

    //
    // Post the quit message.
    //

    case WM_DESTROY:
      PostQuitMessage( 0 );
      return( 0 );
  }

  //
  // Call the OS default window procedure.
  //

  return( DefWindowProc( window, message, wparam, lparam ) );
}


//############################################################################
//##                                                                        ##
//## Build_window_handle - creates a window class and window handle.        ##
//##                                                                        ##
//############################################################################

static HWND Build_window_handle( HINSTANCE instance,
                                 HINSTANCE previous_instance )
{
  //
  // Create the window class if this is the first instance.
  //

  if ( !previous_instance )
  {
    WNDCLASS wc;

    wc.style = 0;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = instance;
    wc.hIcon = LoadIcon( instance, MAKEINTRESOURCE( 101 ) );
    wc.hCursor = LoadCursor( 0, IDC_ARROW );
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = "BinkExam";

    //
    // Try to register the class.
    //

    if ( !RegisterClass( &wc ) )
    {
      return( 0 );
    }
  }

  //
  // Return the new window with a tiny initial default size (it is resized
  //   later on).
  //

  return( CreateWindow( "BinkExam",
                        "Bink Example Player",
                        WS_CAPTION | WS_POPUP| WS_CLIPCHILDREN |
                        WS_SYSMENU | WS_MINIMIZEBOX | WS_SIZEBOX,
                        64, 64,
                        64, 64,
                        0, 0, instance,0 ) );
}


//############################################################################
//##                                                                        ##
//## Show_frame - shows the next Bink frame.                                ##
//##                                                                        ##
//############################################################################

static void Show_frame( HBINK Bink, BINKTEXTURESET * texture_set )
{
  Render_time -= get_time();
  
  //
  // Keep track of how many frames we've played.
  //

  ++Frame_count;

  //
  // Clear the screen.
  //

  glClearColor( 0.0f, 0.125f, 0.3f, 1.0f );
  glClear( GL_COLOR_BUFFER_BIT );

  //
  // Draw the image on the screen.
  //

  Draw_Bink_textures( Bink,
                      texture_set,
                      Bink->Width, Bink->Height,
                      0, 0,
                      x_scale, y_scale,
                      1.0f, 1 );

  Render_time += get_time();

  //
  // End the rendering.
  //

  SwapBuffers( gl_dc );
}


//############################################################################
//##                                                                        ##
//## Checks and advanced the Bink video if necessary.                       ##
//##                                                                        ##
//############################################################################

static S32 Check_bink( HBINK Bink, BINKTEXTURESET * texture_set )
{
  S32 new_frame = 0;
    
  //
  // Is it time for a new Bink frame?
  //

  if ( ! BinkWait( Bink ) )
  {
    //
    // is the previous frame done yet (wait for a ms)
    //   note that this logic assumes you already 
    //   have a frame decompressing the first time 
    //   this function is called
    //

    if ( BinkDoFrameAsyncWait( Bink, 1000 ) )
    {
      //
      // do we need to skip a frame?
      //

      while ( BinkShouldSkip( Bink ) )
      {
        BinkNextFrame( Bink );
        BinkDoFrameAsync( Bink, 0, extra_thread_index );
        BinkDoFrameAsyncWait( Bink, -1 );
      }

      Render_time -= get_time();

      //
      // Update the textures.
      //

      Update_Bink_textures( texture_set, Bink );

      Render_time += get_time();

      //
      // we have finished a frame, so set a flag to draw it
      //
      
      new_frame = 1;
    
      //
      // Keep playing the movie.
      //

      BinkNextFrame( Bink );

      //
      // start decompressing the next frame
      //

      BinkDoFrameAsync( Bink, 0, extra_thread_index ); 
     }
  }

  return( new_frame );
}


//############################################################################
//##                                                                        ##
//## WinMain - the primary function entry point                             ##
//##                                                                        ##
//############################################################################

int PASCAL WinMain( HINSTANCE instance,
                    HINSTANCE previous_instance,
                    LPSTR cmd_line,
                    int cmd_show )
{
  //
  // Win32 locals.
  //

  HWND window;
  MSG msg;
  S32 extra_width, extra_height;

  //
  // Try to create our window.
  //

  window = Build_window_handle( instance, previous_instance );
  if ( !window )
  {
    Show_error( "Error creating window.", "Windows" );
    return( 1 );
  }

  //
  // Calculate the extra width and height for the window.
  //

  Calc_window_values( window, &extra_width, &extra_height );

  //
  // init the timer
  //
  
  QueryPerformanceFrequency( ( LARGE_INTEGER* ) &Timer_freq );

  //
  // get the number of cpus and create our threads
  // 

  num_cpus = get_num_cpus();

  // we use one background thread regardless, and if we have
  //   at least two CPUs, we'll use another background one

  BinkStartAsyncThread( 0, 0 );

  if ( num_cpus <= 1 )
  {
    extra_thread_index = 0;
  }
  else
  {
    BinkStartAsyncThread( 1, 0 );
    extra_thread_index = 1;
  }

  
  //
  // Tell Bink to use DirectSound (must be before BinkOpen)!
  //

  BinkSoundUseDirectSound( 0 );

  //
  // Try to open the Bink file.
  //

  Bink = BinkOpen( cmd_line, BINKSNDTRACK | BINKALPHA );
  if ( !Bink )
  {
    Show_error( BinkGetError( ), "Error opening file..." );
    DestroyWindow( window );
    return( 2 );
  }

  //
  // Size the window such that its client area exactly fits our Bink movie.
  //

  SetWindowPos( window, 0,
                0, 0,
                Bink->Width+extra_width,
                Bink->Height+extra_height,
                SWP_NOMOVE );

  //
  // Init GL
  //

  if ( !Init_GL( window, Bink->Width, Bink->Height ) )
  {
    Show_error( "Error initializing GL.", "GL" );
    DestroyWindow( window );
    BinkClose( Bink );
    return( 3 );
  }

  //
  // Create a timer to update the statistics.
  //

  SetTimer( window, 0, 1000, 0 );

  //
  // Create the Bink shaders to use
  //

  if ( Create_Bink_shaders() )
  {
    //
    // Get the frame buffers info, so we know what size/type of textures to create
    //

    BinkGetFrameBuffersInfo( Bink, &texture_set.bink_buffers );

    //
    // Try to create textures for Bink to use.
    //

    if ( Create_Bink_textures( &texture_set, Bink->Width, Bink->Height ) )
    {
      //
      // start the first frame decoding in the background
      //

      BinkDoFrameAsync( Bink, 0, extra_thread_index ); 
      
      //
      // Now display the window and start the message loop.
      //

      ShowWindow( window, cmd_show );

      for ( ; ; )
      {
        //
        // Are there any messages to handle?
        //

        if ( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
        {
          //
          // Yup, handle them.
          //

          if ( msg.message == WM_QUIT )
            break;

          TranslateMessage( &msg );
          DispatchMessage( &msg );
        }
        else
        {
          S32 new_frame;
          
          //
          // check the Bink playback
          //

          new_frame = Check_bink( Bink, &texture_set );

          //
          // do we have a new frame?
          //

          if ( new_frame )
          {
            //
            // Yup, draw it
            //

            Show_frame( Bink, &texture_set );

            //
            // Are we at the end of the movie?
            //

/*            if ( Bink->FrameNum == Bink->Frames )
            {
              break;
            }*/
          }
          else
          {
            //
            // Nope, give the rest of the system a chance to run
            //

            Sleep( 1 );
          }
        }
      }


      //
      // wait until background is done
      //
      
      BinkDoFrameAsyncWait( Bink, -1 );

      //
      // Free textures.
      //

      Free_Bink_textures( &texture_set );
    }

    Free_Bink_shaders( );
  }

  //
  // Close the Bink file.
  //

  BinkClose( Bink );
  Bink = 0;

  //
  // stop the background threads
  //
  
  BinkRequestStopAsyncThread( 0 );
  if ( num_cpus > 1 )
    BinkRequestStopAsyncThread( 1 );

  BinkWaitStopAsyncThread( 0 );
  if ( num_cpus > 1 )
    BinkWaitStopAsyncThread( 1 );


  //
  // Close GL.
  //

  Close_GL( );

  //
  // And exit.
  //

  return( 0 );
}

// some stuff for the RAD build utility
// @cdep pre $DefaultsWin3264EXE
// $// tools/GL has our copy of glcorearb.h
// @cdep pre $addtocswitches(-I$clipfilename($file)\..\..\tools)
// @cdep pre $requires(gltextures.cpp)
// @cdep pre $requiresbinary(opengl32.lib)
// @cdep pre $requiresbinary($builddir\bink2w$platnum.lib)
// @cdep post $BuildWin3264EXE

