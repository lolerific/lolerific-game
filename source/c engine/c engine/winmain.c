#include "gamedef.h"
#include "m_test.h"

cvar_t gl_classname = {"gl_classname", "0", gtrue};
cvar_t gl_windowtext = {"gl_windowtext", "game", gtrue};

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{

	case WM_CREATE:
		return 0;

	case WM_CLOSE:
		PostQuitMessage (0);
		return 0;

	case WM_DESTROY:
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage (0);
			return 0;
		}
		return 0;

	default:
		return DefWindowProc (hWnd, message, wParam, lParam);

	}

}

void EnableOpenGL (HWND hWnd, HDC * hDC, HGLRC * hRC)
{
	PIXELFORMATDESCRIPTOR pfd;
	int format;

	*hDC = GetDC (hWnd);

	ZeroMemory (&pfd, sizeof (pfd));
	pfd.nSize = sizeof (pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat (*hDC, &pfd);
	SetPixelFormat (*hDC, format, &pfd);

	*hRC = wglCreateContext (*hDC);
	wglMakeCurrent (*hDC, *hRC);

}

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
	wglMakeCurrent (NULL, NULL);
	wglDeleteContext (hRC);
	ReleaseDC (hWnd, hDC);
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASS wc;
	HWND hWnd;
	HDC hDC;
	HGLRC hRC;
	MSG msg;
	gboolean quit = gfalse;
	entity_t ent, ent2;

	G_Init();
	Cmd_Init();
	ES_Init();

	Cvar_RegisterVariable (&gl_classname);
	Cvar_RegisterVariable (&gl_windowtext);

	SP_Spawn("test_entity", &ent, "test1");
	SP_Spawn("test_entity", &ent2, "test2");

	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject (BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = Cvar_VariableString ("gl_classname");
	RegisterClass (&wc);

	hWnd = CreateWindow (Cvar_VariableString ("gl_classname"), Cvar_VariableString ("gl_windowtext"), WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE, 0, 0, 256, 256, NULL, NULL, hInstance, NULL);

	EnableOpenGL (hWnd, &hDC, &hRC);

	while (!quit)
	{
		if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) 
			{
				FILE *f = fopen("vars.rc", "w");
				Cvar_WriteVariables(f);
				fclose(f);
				quit = gtrue;
			} 
			else 
			{
				TranslateMessage (&msg);
				DispatchMessage (&msg);
			}

		} 
		else 
		{
			glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
			glClear (GL_COLOR_BUFFER_BIT);
			SwapBuffers (hDC);
		}
		if(1)
		{
			static float counter = 0;
			float tick = clock();
			if(tick-counter >= 1)
			{
				counter = tick;
				G_AdvanceFrame();
			}
		}
	}

	DisableOpenGL (hWnd, hDC, hRC);

	DestroyWindow (hWnd);

	return msg.wParam;

}