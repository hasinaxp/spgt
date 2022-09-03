#pragma once
#ifdef UNICODE
#undef UNICODE
#endif
#ifdef _UNICODE
#undef _UNICODE
#endif

#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>
#include <string>
#include <memory>
#include <dwmapi.h>
#include <gl/GL.h>
#include <iostream>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "Shlwapi.lib")

#if defined(_WIN32) && !defined(__MINGW32__)
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#endif
#if !defined(__MINGW32__)
#pragma comment(lib, "Dwmapi.lib")
#endif

#define SPGL_LOAD(t, n) (t *)wglGetProcAddress(#n)
#define CALLSTYLE __stdcall

// opengl loading
namespace sp
{
	typedef char GLchar;
	typedef ptrdiff_t GLsizeiptr;
	typedef GLuint CALLSTYLE locCreateShader_t(GLenum type);
	typedef GLuint CALLSTYLE locCreateProgram_t(void);
	typedef void CALLSTYLE locDeleteShader_t(GLuint shader);

	typedef void CALLSTYLE locShaderSource_t(GLuint shader, GLsizei count, const GLchar **string, const GLint *length);

	typedef void CALLSTYLE locCompileShader_t(GLuint shader);
	typedef void CALLSTYLE locLinkProgram_t(GLuint program);
	typedef void CALLSTYLE locDeleteProgram_t(GLuint program);
	typedef void CALLSTYLE locAttachShader_t(GLuint program, GLuint shader);
	typedef void CALLSTYLE locBindBuffer_t(GLenum target, GLuint buffer);
	typedef void CALLSTYLE locBufferData_t(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
	typedef void CALLSTYLE locGenBuffers_t(GLsizei n, GLuint *buffers);
	typedef void CALLSTYLE locVertexAttribPointer_t(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
	typedef void CALLSTYLE locEnableVertexAttribArray_t(GLuint index);
	typedef void CALLSTYLE locUseProgram_t(GLuint program);
	typedef void CALLSTYLE locBindVertexArray_t(GLuint array);
	typedef void CALLSTYLE locGenVertexArrays_t(GLsizei n, GLuint *arrays);
	typedef void CALLSTYLE locGetShaderInfoLog_t(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);




	static locCreateShader_t *glCreateShader = nullptr;
	static locShaderSource_t *glShaderSource = nullptr;
	static locCompileShader_t *glCompileShader = nullptr;
	static locDeleteShader_t *glDeleteShader = nullptr;
	static locCreateProgram_t *glCreateProgram = nullptr;
	static locDeleteProgram_t *glDeleteProgram = nullptr;
	static locLinkProgram_t *glLinkProgram = nullptr;
	static locAttachShader_t *glAttachShader = nullptr;
	static locBindBuffer_t *glBindBuffer = nullptr;
	static locBufferData_t *glBufferData = nullptr;
	static locGenBuffers_t *glGenBuffers = nullptr;
	static locVertexAttribPointer_t *glVertexAttribPointer = nullptr;
	static locEnableVertexAttribArray_t *glEnableVertexAttribArray = nullptr;
	static locUseProgram_t *glUseProgram = nullptr;
	static locBindVertexArray_t *glBindVertexArray = nullptr;
	static locGenVertexArrays_t *glGenVertexArrays = nullptr;
	static locGetShaderInfoLog_t *glGetShaderInfoLog = nullptr;

	static bool gl_loaded = false;

	static void load_gl_func_ptrs()
	{
		if (!gl_loaded)
		{
			glCreateShader = SPGL_LOAD(locCreateShader_t, glCreateShader);
			glCompileShader = SPGL_LOAD(locCompileShader_t, glCompileShader);
			glShaderSource = SPGL_LOAD(locShaderSource_t, glShaderSource);
			glDeleteShader = SPGL_LOAD(locDeleteShader_t, glDeleteShader);
			glCreateProgram = SPGL_LOAD(locCreateProgram_t, glCreateProgram);
			glDeleteProgram = SPGL_LOAD(locDeleteProgram_t, glDeleteProgram);
			glLinkProgram = SPGL_LOAD(locLinkProgram_t, glLinkProgram);
			glAttachShader = SPGL_LOAD(locAttachShader_t, glAttachShader);
			glBindBuffer = SPGL_LOAD(locBindBuffer_t, glBindBuffer);
			glBufferData = SPGL_LOAD(locBufferData_t, glBufferData);
			glGenBuffers = SPGL_LOAD(locGenBuffers_t, glGenBuffers);
			glVertexAttribPointer = SPGL_LOAD(locVertexAttribPointer_t, glVertexAttribPointer);
			glEnableVertexAttribArray = SPGL_LOAD(locEnableVertexAttribArray_t, glEnableVertexAttribArray);
			glUseProgram = SPGL_LOAD(locUseProgram_t, glUseProgram);
			glGetShaderInfoLog = SPGL_LOAD(locGetShaderInfoLog_t, glGetShaderInfoLog);
			glBindVertexArray = SPGL_LOAD(locBindVertexArray_t, glBindVertexArray);
			glGenVertexArrays = SPGL_LOAD(locGenVertexArrays_t, glGenVertexArrays);

			gl_loaded = true;
		}
	}


};//namespace sp

namespace sp
{

	using namespace std;

	enum class keycode
	{
		A = 'A',
		B = 'B',
		C = 'C',
		D = 'D',
		E = 'E',
		F = 'F',
		G = 'G',
		H = 'H',
		I = 'I',
		J = 'J',
		K = 'K',
		L = 'L',
		M = 'M',
		N = 'N',
		O = 'O',
		P = 'P',
		Q = 'Q',
		R = 'R',
		S = 'S',
		T = 'T',
		U = 'U',
		V = 'V',
		W = 'W',
		X = 'X',
		Y = 'Y',
		Z = 'Z',
		UP = VK_UP,
		DOWN = VK_DOWN,
		LEFT = VK_LEFT,
		RIGHT = VK_RIGHT,
		ENTER = VK_RETURN,
		SPACE = VK_SPACE,
		LEFT_SHIFT = VK_LSHIFT,
		RIGHT_SHIFT = VK_RSHIFT,
		CAPS = VK_CAPITAL,
		TAB = VK_TAB,
		LEFT_CTRL = VK_LCONTROL,
		RIGHT_CTRL = VK_RIGHT,
		ALT = VK_MENU,
		ESC = VK_ESCAPE,
		LEFT_BRACKET = VK_OEM_5,
		RIGHT_BRACKET = VK_OEM_6,
		BACK_SLASH = VK_OEM_5,
		COMMA = VK_OEM_COMMA,
		PERIOD = VK_OEM_PERIOD,

		LEFT_MOUSE = 252,
		RIGHT_MOUSE = 253,
		MIDDLE_MOUSE = 254
	};

	struct keystate
	{
		bool pressed;
		bool released;
		bool held;
	};

	class input
	{
	public:
		struct ipevent
		{
			uint32_t type;
			WPARAM wparam;
			LPARAM lparam;
		};
		static std::unordered_map<void *, std::queue<ipevent>> ipev_queuemap;

		keystate keys[256];
		std::vector<keycode> releasedkeys;
		std::vector<keycode> pressedkeys;

		std::vector<char> charbuff;

		int mouse_x;
		int mouse_y;
		int mouse_dx;
		int mouse_dy;

		bool shouldquit;

	public:
		input()
		{

			for (int i = 0; i < 256; i++)
			{
				keys[i] = {false, false, false};
			}
			releasedkeys = {};
			pressedkeys = {};

			mouse_x = 0;
			mouse_y = 0;
			mouse_dx = 0;
			mouse_dy = 0;

			shouldquit = false;
		}
		~input()
		{
		}
		void capture(void *handle)
		{
			// keyboard event cleanup
			for (auto &k : releasedkeys)
				keys[static_cast<WPARAM>(k)].released = false;
			releasedkeys = {};
			for (auto &k : pressedkeys)
				keys[static_cast<WPARAM>(k)].pressed = false;
			pressedkeys = {};

			auto &current_queue = ipev_queuemap[handle];
			while (!current_queue.empty())
			{
				const ipevent &ev = current_queue.front();
				int x = 0, y = 0;
				switch (ev.type)
				{
				case WM_CHAR:
					charbuff.push_back(ev.wparam);
					break;
				case WM_SYSKEYDOWN:
				case WM_KEYDOWN:
					if (!keys[ev.wparam].held)
					{
						keys[ev.wparam].held = true;
						keys[ev.wparam].pressed = true;
						keys[ev.wparam].released = false;
					}
					else
					{
						keys[ev.wparam].held = true;
						keys[ev.wparam].pressed = false;
						keys[ev.wparam].released = false;
					}
					break;
				case WM_SYSKEYUP:
				case WM_KEYUP:
					keys[ev.wparam].held = false;
					keys[ev.wparam].pressed = false;
					keys[ev.wparam].released = true;
				case WM_MOUSEMOVE:
					x = ev.lparam & 0x0000ffff;
					y = ev.lparam >> 16;
					mouse_dx = x - mouse_x;
					mouse_dy = y - mouse_y;
					mouse_x = x;
					mouse_y = y;
					break;
				case WM_LBUTTONDOWN:
					if (!keys[252].held)
					{
						keys[252].held = true;
						keys[252].pressed = true;
						keys[252].released = false;
					}
					else
					{
						keys[252].held = true;
						keys[252].pressed = false;
						keys[252].released = false;
					}
					break;
				case WM_RBUTTONDOWN:
					if (!keys[253].held)
					{
						keys[253].held = true;
						keys[253].pressed = true;
						keys[253].released = false;
					}
					else
					{
						keys[253].held = true;
						keys[253].pressed = false;
						keys[253].released = false;
					}
					break;
				case WM_MBUTTONDOWN:
					if (!keys[254].held)
					{
						keys[254].held = true;
						keys[254].pressed = true;
						keys[254].released = false;
					}
					else
					{
						keys[254].held = true;
						keys[254].pressed = false;
						keys[254].released = false;
					}
					break;
				case WM_LBUTTONUP:
					keys[252].held = false;
					keys[252].pressed = false;
					keys[252].released = true;
					break;
				case WM_RBUTTONUP:
					keys[253].held = false;
					keys[253].pressed = false;
					keys[253].released = true;
					break;
				case WM_MBUTTONUP:
					keys[254].held = false;
					keys[254].pressed = false;
					keys[254].released = true;

				case WM_QUIT:
				case WM_CLOSE:
					shouldquit = true;
					break;
				default:
					break;
				}

				current_queue.pop();
			}
		}

		keystate &get_keystate(keycode code)
		{
			keystate &state = keys[static_cast<WPARAM>(code)];
			if (state.pressed)
				pressedkeys.push_back(code);
			if (state.released)
				releasedkeys.push_back(code);
			return state;
		}

		std::string get_text()
		{
			std::string chars(charbuff.begin(), charbuff.end());
			charbuff.clear();
			return chars;
		}
		bool has_text() const { return charbuff.size() != 0; };

		static LRESULT CALLBACK wnd_proc(HWND hwnd, uint32_t msg, WPARAM wparam, LPARAM lparam)
		{
			ipev_queuemap[hwnd].push({msg, wparam, lparam});
			return DefWindowProc(hwnd, msg, wparam, lparam);
		}
	};

	unordered_map<void *, queue<input::ipevent>> input::ipev_queuemap = {};

	class window
	{
	public:
		void *handle = nullptr;
		int width = 640;
		int height = 480;
		string title = "window";

	public:
		window(bool fullscreen = false)
		{
			WNDCLASSEXA wc = {0};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.lpszClassName = "sp_window_class";
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wc.hInstance = GetModuleHandle(nullptr);
			wc.lpfnWndProc = input::wnd_proc;

			RegisterClassExA(&wc);

			DWORD exstyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			DWORD dwstyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE;

			RECT wsize = {0, 0, width, height};
			if (fullscreen)
			{
				exstyle = 0;
				dwstyle = WS_VISIBLE | WS_POPUP;
				HMONITOR hmon = MonitorFromWindow((HWND)handle, MONITOR_DEFAULTTONEAREST);
				MONITORINFO mi = {sizeof(mi)};
				if (GetMonitorInfo(hmon, &mi))
				{
					wsize = mi.rcMonitor;
				}
				else
				{
					exstyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
					dwstyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
				}
			}

			AdjustWindowRectEx(&wsize, dwstyle, FALSE, exstyle);
			int w = wsize.right - wsize.left;
			int h = wsize.bottom - wsize.top;

			handle = CreateWindowExA(exstyle, wc.lpszClassName, title.c_str(), dwstyle, CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, GetModuleHandle(nullptr), this);

			ShowWindow((HWND)handle, true);
			UpdateWindow((HWND)handle);

			input::ipev_queuemap[handle] = {};
		}
		~window()
		{
			DestroyWindow((HWND)handle);
		}

		void set_title(string t)
		{
			title = t;
			SetWindowText((HWND)handle, t.c_str());
		}
	};


	class graphics
	{
	public:
		using color = float[4];
		unique_ptr<window> wnd;
		HDC dc;
		HGLRC glrc;
	public:
		graphics(bool fullscreen = false)
		{
			wnd = make_unique<window>(fullscreen);
			dc = GetDC((HWND)(wnd->handle));
			PIXELFORMATDESCRIPTOR pfd =
					{
							sizeof(PIXELFORMATDESCRIPTOR), 1,
							PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
							PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							PFD_MAIN_PLANE, 0, 0, 0, 0};

			int pf = 0;
			if (!(pf = ChoosePixelFormat(dc, &pfd)))
				cout << "unable to choose pixel format" << endl;
			SetPixelFormat(dc, pf, &pfd);

			

			if (!(glrc = wglCreateContext(dc)))
				cout << "unable to create gl context" << endl;
			wglMakeCurrent(dc, glrc);
			load_gl_func_ptrs();
		}
		~graphics()
		{
			wglDeleteContext(glrc);
		}

		void *get_handle() { return wnd->handle; }

		void begin()
		{
			MSG msg;
			while (PeekMessageA(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			SwapBuffers(dc);
			wglMakeCurrent(dc, glrc);
		}
		void end()
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}
		void clear_color(const color & c)
		{
			glClearColor(c[0], c[1], c[2], c[3]);
		
		}

	};

}; // namespace sp