#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "gl_window.h"
#include "gamedef.h"

HDC hdc = NULL;
HGLRC hrc = NULL;
HWND hwnd = NULL;
HINSTANCE hinstance = NULL;

int keys[256];
int active = TRUE;
int fullscreen = FALSE;
char *classname = "OpenGL";

void GL_ResizeScene(GLsizei width, GLsizei height)
{
       if(height <= 0)
           height = 1;
       glViewport(0, 0, width, height);

       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
}

int GL_Init()
{
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    return TRUE;
}

void GL_KillWindow()
{
     if(fullscreen)
     {
         ChangeDisplaySettings(NULL, 0);
         ShowCursor(TRUE);
     }

     if(hrc)
     {
         if(!wglMakeCurrent(NULL, NULL))
         {
             MessageBox(NULL, "Release of DC & RC failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
         }
         if(!wglDeleteContext(hrc))
         {
             MessageBox(NULL, "Release Rendering Context failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
         }
         hrc = NULL;
     }

     if(hdc && !ReleaseDC(hwnd, hdc))
     {
         MessageBox(NULL, "Release of device context failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
         hwnd = NULL;
     }

     if(hwnd && !DestroyWindow(hwnd))
     {
         MessageBox(NULL, "Could not destroy window.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
         hwnd = NULL;
     }

     if(!UnregisterClass("OpenGL", hinstance))
     {
         MessageBox(NULL, "Could not unregister window class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
         hinstance = NULL;
     }
}

BOOL GL_CreateWindow(char* title, int width, int height, int bits, BOOL fullscreenflag)
{
	static PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            32,
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            16,
            0,
            0,
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
     };

     DEVMODE dmscreensettings;

     GLuint pixelformat;
     WNDCLASS wc;

     DWORD exstyle;
     DWORD style;

     RECT windowrect;

     fullscreen = fullscreenflag;

     hinstance = GetModuleHandle(NULL);

	 windowrect.left = (long)0;
     windowrect.right = (long)width;
     windowrect.top = (long)0;
     windowrect.bottom = (long)height;

     wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
     wc.lpfnWndProc = (WNDPROC) WndProc;
     wc.cbClsExtra = 0;
     wc.cbWndExtra = 0;
     wc.hInstance = hinstance;
     wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
     wc.hCursor = LoadCursor(NULL, IDC_ARROW);
     wc.hbrBackground = NULL;
     wc.lpszMenuName = NULL;
     wc.lpszClassName = classname;

     if (!RegisterClass(&wc))
     {
         MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
         return FALSE;
     }

     if(fullscreen)
     {
         memset(&dmscreensettings,0,sizeof(dmscreensettings));
         dmscreensettings.dmSize = sizeof(dmscreensettings);
         dmscreensettings.dmPelsWidth = width;
         dmscreensettings.dmPelsHeight = height;
         dmscreensettings.dmBitsPerPel = bits;
         dmscreensettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
     }

     if (ChangeDisplaySettings(&dmscreensettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
     {
         if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported.","Error", MB_OK | MB_ICONEXCLAMATION))
         {
             fullscreen = FALSE;
         }
         else
         {
             MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
             return FALSE;
         }
     }

     if(fullscreen)
     {
         exstyle = WS_EX_APPWINDOW;
         style = WS_POPUP;
         ShowCursor(FALSE);
     }
     else
     {
         exstyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
         style = WS_OVERLAPPEDWINDOW;
     }
     AdjustWindowRectEx(&windowrect, style, FALSE, exstyle);
     if (!(hwnd = CreateWindowEx(exstyle, classname, title,
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN | style,
        0, 0, windowrect.right - windowrect.left,
        windowrect.bottom - windowrect.top,
        NULL, NULL, hinstance, NULL)))
     {
         GL_KillWindow();
         MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
         return FALSE;
     }

     if (!(hdc = GetDC(hwnd)))
     {
         GL_KillWindow();
         MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
         return FALSE;
     }

     if (!(pixelformat = ChoosePixelFormat(hdc,&pfd)))
     {
         GL_KillWindow();
         MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
         return FALSE;
     }

     if(!SetPixelFormat(hdc,pixelformat,&pfd))
      {
          GL_KillWindow();
          MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
          return FALSE;
      }

      if (!(hrc = wglCreateContext(hdc)))
      {
          GL_KillWindow();
          MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
          return FALSE;
      }

      if(!wglMakeCurrent(hdc,hrc))
      {
          GL_KillWindow();
          MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
          return FALSE;
      }

      if (!GL_Init())
      {
          GL_KillWindow();
          MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
          return FALSE;
      }

      ShowWindow(hwnd, 1);
      return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch(msg)
    {
    case WM_ACTIVATE:
         {
             if(!HIWORD(wparam))
             {
                 active = TRUE;
             }
             else
             {
                 active = FALSE;
             }
             return 0;
         }
    case WM_SYSCOMMAND:
         {
             switch(wparam)
             {
                 case SC_SCREENSAVE:
                 case SC_MONITORPOWER:
                 return 0;
             }
             break;
         }
    case WM_CLOSE:
         {
             PostQuitMessage(0);
             return 0;
         }
    case WM_KEYDOWN:
         {
             keys[wparam] = TRUE;
             return 0;
         }
    case WM_KEYUP:
         {
             keys[wparam] = FALSE;
             return 0;
         }
    case WM_SIZE:
         {
             GL_ResizeScene(LOWORD(lparam), HIWORD(lparam));
             return 0;
         }
    }
    return DefWindowProc(hwnd,msg,wparam,lparam);
}
