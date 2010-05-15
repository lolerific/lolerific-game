#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "gl_window.h"

int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncommandshow)
{
    MSG msg;
    BOOL done = FALSE;
    
    if(MessageBox(NULL, "Would you like to run in fullscreen mode?", "Start FullScreen", MB_YESNO))
    {
        fullscreen = FALSE;
    }
    
    if(!GL_CreateWindow("WindowTitle", 640, 480, 32, fullscreen))
    {
        MessageBox(NULL, "LOL!", "LOL!", MB_OK);
        return 0;
    }
    
    while(!done)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
            {
                done = TRUE;               
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            if((active && !GL_DrawScene()) || keys[VK_ESCAPE])
            {
                done = TRUE;
            }
            else
            {
                SwapBuffers(hdc);    
            }    
        }
        if(keys[VK_F1])
        {
            keys[VK_F1] = FALSE;
            GL_KillWindow();
            fullscreen = !fullscreen;
            if(!GL_CreateWindow("WindowTitle", 640, 480, 32, fullscreen))
            {
                return 0;
            }               
        }                                
    }
    GL_KillWindow();
    return msg.wParam;   
}
