
#include <Windows.h>
#include <gl/GL.h>
#include <math.h>
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

void pahangFlag();
void n9Flag();
void englandFlag();
void scotlandFlag();

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	scotlandFlag();
	//pahangFlag();

	//glClearColor(1.0, 1.0, 1.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT);

	//glLineWidth(10.0);
	//glBegin(GL_LINE_LOOP);
	//glPointSize(10.0);
	//glBegin(GL_POINTS);

	//glColor3f(1.0, 0.0, 0.0);
	//glVertex2f(-0.5, 0);
	//glColor3f(0.0, 0.0, 1.0);
	//glVertex2f(0, 0.5);
	//glColor3f(0.0, 1.0, 0.0);
	//glVertex2f(0.5, 0);


	// Exercise Q1


	//glRectf(-1, 0, 1, 1);
	//glColor3f(0, 1, 0);
	
	//glRectf(0, -1, 0, 0);
	//glColor3f(1, 0, 0);
	//glRectf(0, 0, -1, -1);
	//glColor3f(0, 0, 0);

	// Exercise Q2
	// glRectf(-1, 0, 1, 1);
	// glColor3f(1, 0, 0);
	// glRectf(0, 0, 1, 1);
	// glColor3f(1, 1, 0);



	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}

void pahangFlag() {

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-1, 1);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(1, 1);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-1, 0);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, 0);
	glEnd();
}

void n9Flag() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex2f(0, 0);
	glVertex2f(-1, 0);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, 1);
	glVertex2f(0, 1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(-1, 1);
	glVertex2f(-1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(0, 1);
	glVertex2f(-1, 1);
	glEnd();

}

void englandFlag() {
	glBegin(GL_QUADS);
	glColor3f(0.8078f, 0.0666f, 0.1490f);
	glVertex2f(1, 0.13f);
	glVertex2f(1, -0.13f);
	glVertex2f(-1, -0.13f);
	glVertex2f(-1, 0.13f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.8078f, 0.0666f, 0.1490f);
	glVertex2f(0.06f, 1);
	glVertex2f(-0.06f, 1);
	glVertex2f(-0.06f, -1);
	glVertex2f(0.06f, -1);
	glEnd();

	//glBegin(GL_QUADS);
	//glColor3f(0.8078f, 0.0666f, 0.1490f);
	//glVertex2f(1, 1);
	//glColor3f(0.1f, 0.1f, 0.1f);
	//glVertex2f(-1, 1);
	//glColor3f(0.1f, 0.1f, 0.1f);
	//glVertex2f(-1, -1);
	//glColor3f(0.1f, 0.1f, 0.1f);
	//glVertex2f(1, -1);
	//glEnd();


	//glBegin(GL_POLYGON);
	//	glPointSize(10.0);
	//glBegin(GL_POINTS);

	//glColor3f(1, 0, 0);
	//glVertex2f(0.0588f, -1);
	//glVertex2f(0.0588f, -0.1333f);
	//glVertex2f(1, -0.1333f);
	//glVertex2f(1, 0.1333f);
	//glVertex2f(0.0588f, 0.1333f);
	//glVertex2f(0.0588f, 1);
	//glVertex2f(-0.0588f, 1);
	//glVertex2f(-0.0588f, 0.1333f);
	//glVertex2f(-1, 0.1333f);
	//glVertex2f(-1, -0.1333f);
	//glVertex2f(-0.0588f, -0.1333f);
	//glVertex2f(-0.0588f, -1);
	//glVertex2f(0.0588f, -1);

}

void scotlandFlag() {
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.3960f, 0.7490f);
	glVertex2f(-0.8f, -1); 
	glVertex2f(0.8f, -1);
	glVertex2f(0, -0.21f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.3960f, 0.7490f);
	glVertex2f(0.8f, 1);
	glVertex2f(-0.8f, 1);
	glVertex2f(0, 0.21f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.3960f, 0.7490f);
	glVertex2f(-1, 0.8f);
	glVertex2f(-1, -0.8f);
	glVertex2f(-0.2f, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.3960f, 0.7490f);
	glVertex2f(1, -0.8f);
	glVertex2f(1, 0.8f);
	glVertex2f(0.2f, 0);
	glEnd();
}

void scotlandFlag() {
	
}
