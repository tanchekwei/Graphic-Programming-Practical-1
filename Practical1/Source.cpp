#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <iostream>
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 1"
#define DEG2RAD 3.14159/180.0

void pahangFlag();
void n9Flag();
void englandFlag();
void scotlandFlag();
void smileyFace();
void drawCirle(float x1, float y1, float radius);
int page = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		else if (wParam == VK_RIGHT || wParam == VK_DOWN) {
			page = ++page % 5;
			printf("[%d]\n", page);
		}
		else if (wParam == VK_LEFT || wParam == VK_UP) {
			page = --page % 5;
			if (page < 0) {
				page += 5;
			}
			printf("[%d]\n", page);
		}
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

void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// handle resolution problem
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double w = 1920;
	double h = 1080;
	double ar = w / h;
	glOrtho(-2 * ar, 2 * ar, -2, 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	switch (page)
	{
	case 0:
		pahangFlag();
		break;
	case 1:
		n9Flag();
		break;
	case 2:
		englandFlag();
		break;
	case 3:
		scotlandFlag();
		break;
	case 4:
		smileyFace();
		break;
	default:
		break;
	}

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

	//AllocConsole();
	//freopen("CONIN$", "r", stdin);
	//freopen("CONOUT$", "w", stdout);
	//freopen("CONOUT$", "w", stderr);

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//glViewport(0, 0, 1920, 1080);
		//glMatrixMode(GL_PROJECTION);
		//glLoadIdentity();
		//float aspect = (float)1920 / (float)1080;
		//glOrtho(-aspect, aspect, -1, 1, -1, 1);
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}

void drawCirle(float x1, float y1, float radius) {
	float  x2 = x1, y2 = y1;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (float angle = 0; angle <= 360; angle += 0.1) {
		x2 = x1 + cos(angle) * radius;
		y2 = y1 + sin(angle) * radius;
		glVertex2f(x2, y2);
	}
	glEnd();
}

//16:9
//0.5625f

void pahangFlag() {
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(-1, 0.5625f);
	glVertex2f(-1, 0);
	glVertex2f(1, 0);
	glVertex2f(1, 0.5625f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-1, 0);
	glVertex2f(-1, -0.5625f);
	glVertex2f(1, -0.5625f);
	glVertex2f(1, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f(-1, 0.5625f);
	glVertex2f(-1, -0.5625f);
	glVertex2f(1, -0.5625f);
	glVertex2f(1, 0.5625f);
	glEnd();
}

void n9Flag() {
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex2f(0, 0);
	glVertex2f(-1, 0);
	glVertex2f(-1, -0.5625f);
	glVertex2f(1, -0.5625f);
	glVertex2f(1, 0.5625f);
	glVertex2f(0, 0.5625f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(-1, 0.5625f);
	glVertex2f(-1, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(0, 0.5625f);
	glVertex2f(-1, 0.5625f);
	glEnd();
}

void englandFlag() {
	glBegin(GL_QUADS);
	glColor3f(0.6823f, 0, 0);
	glVertex2f(1, 0.09f);
	glVertex2f(1, -0.09f);
	glVertex2f(-1, -0.09f);
	glVertex2f(-1, 0.09f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.6823f, 0, 0);
	glVertex2f(0.09f, 0.5625f);
	glVertex2f(-0.09f, 0.5625f);
	glVertex2f(-0.09f, -0.5625f);
	glVertex2f(0.09f, -0.5625f);
	glEnd();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBegin(GL_QUADS);
	glColor4f(0.4f, 0.4f, 0.4f, 0.2);
	glVertex2f(-1, 0.5625f);
	glVertex2f(-1, -0.5625f);
	glColor4f(1, 1, 1, 0);
	glVertex2f(-0.6f, -0.5625f);
	glVertex2f(-0.6f, 0.5625f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.4f, 0.4f, 0.4f, 0.2);
	glVertex2f(1, -0.5625f);
	glVertex2f(1, 0.5625f);
	glColor4f(1, 1, 1, 0);
	glVertex2f(0.6f, 0.5625f);
	glVertex2f(0.6f, -0.5625f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.4f, 0.4f, 0.4f, 0.2);
	glVertex2f(1, 0.5625f);
	glVertex2f(-1, 0.5625f);
	glColor4f(1, 1, 1, 0);
	glVertex2f(-1, 0.28125f);
	glVertex2f(1, 0.28125f);
	glEnd();

	glBegin(GL_QUADS);
	glColor4f(0.4f, 0.4f, 0.4f, 0.2);
	glVertex2f(-1, -0.5625f);
	glVertex2f(1, -0.5625f);
	glColor4f(1, 1, 1, 0);
	glVertex2f(1, -0.28125f);
	glVertex2f(-1, -0.28125f);
	glEnd();
}

void scotlandFlag() {
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.3960f, 0.7490f);
	glVertex2f(-0.8f, -0.5625f);
	glVertex2f(0.8f, -0.5625f);
	glVertex2f(0, -0.118125f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.3960f, 0.7490f);
	glVertex2f(0.8f, 0.5625f);
	glVertex2f(-0.8f, 0.5625f);
	glVertex2f(0, 0.118125f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.3960f, 0.7490f);
	glVertex2f(-1, 0.45f);
	glVertex2f(-1, -0.45f);
	glVertex2f(-0.2f, 0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0, 0.3960f, 0.7490f);
	glVertex2f(1, -0.45f);
	glVertex2f(1, 0.45f);
	glVertex2f(0.2f, 0);
	glEnd();
}

void smileyFace() {
	glClearColor(1.0, 0.97647f, 0.768627f, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	float x, y;

	glEnable(GL_BLEND);
	glColor3f(0.9922f, 0.9451f, 0);
	drawCirle(0.0, 0.0, 0.5);

	// outline
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < 180; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(180);
		float x = 0.5 * cosf(theta);
		float y = 0.5 * sinf(theta);
		glVertex2f(x + 0, y + 0);
	}
	glEnd();

	//glColor3f(1, 1, 1);
	//drawCirle(0.12, 0.15, 0.12);
	//drawCirle(-0.12, 0.15, 0.12);

	//// outline
	//glPointSize(1.0);
	//glColor3f(0, 0, 0);
	//float x1 = 0.12, x2 = 0.12, y1 = 0.15, y2 = 0.15;
	//glBegin(GL_POINTS);
	//glVertex2f(x1, y1);
	//for (float angle = 0; angle <= 180; angle += 0.1) {
	//	x2 = x1 + cos(angle) * 0.12;
	//	y2 = y1 + sin(angle) * 0.12;
	//	glVertex2f(x2, y2);
	//}
	//glEnd();

	//glColor3f(0, 0, 0);
	//x1 = -0.12, x2 = -0.12, y1 = 0.15, y2 = 0.15;
	//glBegin(GL_POINTS);
	//glVertex2f(x1, y1);
	//for (float angle = 0; angle <= 180; angle += 0.1) {
	//	x2 = x1 + cos(angle) * 0.12;
	//	y2 = y1 + sin(angle) * 0.12;
	//	glVertex2f(x2, y2);
	//}
	//glEnd();

	int t;

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
	for (t = 0; t <= 360; t += 1)
	{
		x = 0.15 * sin((2 * t * 3.14) / 360) * 0.8 + 0.12;
		y = 0.20 * cos((2 * t * 3.14) / 360) * 0.8 + 0.15;
		float z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
	for (t = 0; t <= 360; t += 1)
	{
		x = 0.15 * sin((2 * t * 3.14) / 360) * 0.8 + -0.12;
		y = 0.20 * cos((2 * t * 3.14) / 360) * 0.8 + 0.15;
		float z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();

	glColor3f(0.4018f, 0.6234f, 0.98f);
	glBegin(GL_TRIANGLE_FAN);
	for (t = 0; t <= 360; t += 1)
	{
		x = 0.15 * sin((2 * t * 3.14) / 360) * 0.5  + 0.10;
		y = 0.20 * cos((2 * t * 3.14) / 360) * 0.5 + 0.13;
		float z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();

	glColor3f(0.4018f, 0.6234f, 0.98f);
	glBegin(GL_TRIANGLE_FAN);
	for (t = 0; t <= 360; t += 1)
	{
		x = 0.15 * sin((2 * t * 3.14) / 360) * 0.5 + -0.10;
		y = 0.20 * cos((2 * t * 3.14) / 360) * 0.5 + 0.13;
		float z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	for (t = 0; t <= 360; t += 1)
	{
		x = 0.15 * sin((2 * t * 3.14) / 360) * 0.3 + 0.1;
		y = 0.20 * cos((2 * t * 3.14) / 360) * 0.3 + 0.12;
		float z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	for (t = 0; t <= 360; t += 1)
	{
		x = 0.15 * sin((2 * t * 3.14) / 360) * 0.3 + -0.1;
		y = 0.20 * cos((2 * t * 3.14) / 360) * 0.3 + 0.12;
		float z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
	for (t = 0; t <= 360; t += 1)
	{
		x = 0.15 * sin((2 * t * 3.14) / 360) * 0.1 + 0.08;
		y = 0.20 * cos((2 * t * 3.14) / 360) * 0.1 + 0.130;
		float z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLE_FAN);
	for (t = 0; t <= 360; t += 1)
	{
		x = 0.15 * sin((2 * t * 3.14) / 360) * 0.1 + -0.12;
		y = 0.20 * cos((2 * t * 3.14) / 360) * 0.1 + 0.130;
		float z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();

	//glColor3f(0.4018f, 0.6234f, 0.98f);
	//drawCirle(0.12, 0.15, 0.08);
	//drawCirle(-0.12, 0.15, 0.08);

	//glColor3f(0.0, 0.0, 0.0);
	//drawCirle(0.12, 0.15, 0.05);
	//drawCirle(-0.12, 0.15, 0.05);

	//glColor3f(1, 1, 1);
	//drawCirle(0.11, 0.16, 0.02);
	//drawCirle(-0.13, 0.16, 0.02);



	glColor3f(0.0, 0.0, 0.0);
	glPointSize(2.0);
	for (int i = 240; i < 300; i++)
	{
		glBegin(GL_POINTS);
		x = cos((2 * i*3.14) / 360) * .3;
		y = sin((2 * i*3.14) / 360) * .7 + 0.4;
		glVertex2f(x, y);
		glEnd();
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0.1294f, 0.58823f, 0.95294f, 0.7);
	glBegin(GL_TRIANGLE_FAN);
	for (t = 0; t <= 360; t += 1)
	{
		x = 0.6 * sin((2 * t * 3.14) / 360) * 1.0005;
		y = 0.2 * cos((2 * t * 3.14) / 360) * 1.0005 + 0.6;
		float z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(1.0, 0.97647f, 0.768627f, 0.99);
	glBegin(GL_TRIANGLE_FAN);
	for (t = 0; t <= 360; t += 1)
	{
		x = 0.6 * sin((2 * t * 3.14) / 360)  * 0.7;
		y = 0.1 * cos((2 * t  * 3.14) / 360) * 0.7 + 0.6;
		float z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();

	// circle gradient


	/*
		float x1 = 0, x2 = 0, y1 = -0.2, y2 = -0.2;
		float radius = 0.2;
		glBegin(GL_POINTS);
		glVertex2f(x1, y1);
		for (float angle = 240; angle <= 300; angle += 0.1) {
			x2 = x1 + cos(angle) * radius;
			y2 = y1 + sin(angle) * radius;
			glVertex2f(x2, y2);
		}
		glEnd();
	*/
}


void drawEllipse(float radiusX, float radiusY)
{
	int i;

	glBegin(GL_LINE_LOOP);

	for (i = 0; i < 360; i++)
	{
		float rad = i * DEG2RAD;
		glVertex2f(cos(rad)*radiusX * 0.5f + 1.0f, sin(rad) * radiusY * 0.5f + 1.0f);
		//glVertex2f(cos(rad)*radiusX,
		//	sin(rad)*radiusY);
	}

	glEnd();
}

//Draws a ellpise made out of points.
void DrawEllipse()
{
	glColor3f(1, 1, 1);
	float x, y, z;
	int t;
	glBegin(GL_POINTS);
	for (t = 0; t <= 360; t += 1)
	{
		x = 5 * sin(t);
		y = 4 * cos(t);
		z = 0;
		glVertex3f(x, y, z);
	}
	glEnd();
}
