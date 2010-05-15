#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

extern HDC hdc;
extern HGLRC hrc;
extern HWND hwnd;
extern HINSTANCE hinstance;
extern int keys[256];
extern int active;
extern int fullscreen;
extern char *classname;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void GL_ResizeScene(GLsizei width, GLsizei height);
int GL_Init();

BOOL GL_CreateWindow();
void GL_KillWindow();
