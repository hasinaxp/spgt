#pragma once
#ifdef UNICODE
#undef UNICODE
#endif
#ifdef _UNICODE
#undef _UNICODE
#endif

#include "sp_graphics_data.hpp"

#include <Windows.h>
#include <dwmapi.h>
#include <gl/GL.h>

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

// opengl constants
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_DELETE_STATUS 0x8B80
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_VALIDATE_STATUS 0x8B83
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_TEXTURE_BASE_LEVEL 0x813C
#define GL_TEXTURE_MAX_LEVEL 0x813D
#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_STATIC_DRAW 0x88E4
#define GL_STATIC_READ 0x88E5
#define GL_STATIC_COPY 0x88E6
#define GL_DYNAMIC_DRAW 0x88E8
#define GL_DYNAMIC_READ 0x88E9
#define GL_DYNAMIC_COPY 0x88EA
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
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
	typedef void CALLSTYLE locDetachShader_t(GLuint program, GLuint shader);
	typedef void CALLSTYLE locglGetShaderiv_t(GLuint shader, GLenum pname, GLint *params);
	typedef void CALLSTYLE locglGetProgramiv_t(GLuint program, GLenum pname, GLint *params);

	typedef void CALLSTYLE locBindBuffer_t(GLenum target, GLuint buffer);
	typedef void CALLSTYLE locBufferData_t(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
	typedef void CALLSTYLE locGenBuffers_t(GLsizei n, GLuint *buffers);
	typedef void CALLSTYLE locglDeleteBuffers_t(GLsizei n, const GLuint *buffers);
	typedef void CALLSTYLE locVertexAttribPointer_t(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
	typedef void CALLSTYLE locEnableVertexAttribArray_t(GLuint index);
	typedef void CALLSTYLE locUseProgram_t(GLuint program);
	typedef void CALLSTYLE locBindVertexArray_t(GLuint array);
	typedef void CALLSTYLE locGenVertexArrays_t(GLsizei n, GLuint *arrays);
	typedef void CALLSTYLE locGetShaderInfoLog_t(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
	typedef void CALLSTYLE locGetProgramInfoLog_t(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
	typedef void CALLSTYLE locglUniform1i_t(GLint location, GLint v0);
	typedef void CALLSTYLE locglUniform1f_t(GLint location, GLfloat v0);
	typedef void CALLSTYLE locglUniform2f_t(GLint location, GLfloat v0, GLfloat v1);
	typedef void CALLSTYLE locglUniform3f_t(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	typedef void CALLSTYLE locglUniform4f_t(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	typedef void CALLSTYLE locglUniformMatrix2fv_t(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	typedef void CALLSTYLE locglUniformMatrix3fv_t(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	typedef void CALLSTYLE locglUniformMatrix4fv_t(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
	typedef GLuint CALLSTYLE locglGetUniformLocation_t(GLuint program, const GLchar *name);
	typedef void CALLSTYLE locglGenerateMipmap_t(GLenum target);
	typedef void CALLSTYLE locglVertexAttribDivisor_t(GLuint index, GLuint divisor);
	typedef void CALLSTYLE locglDeleteVertexArrays_t(GLsizei n, const GLuint *arrays);
	typedef void CALLSTYLE locglDrawElementsInstanced_t(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount);
	typedef void CALLSTYLE locglActiveTexture_t(GLenum texture);
	typedef void CALLSTYLE locglBindTexture_t(GLenum target, GLenum texture);

	static locCreateShader_t *glCreateShader = nullptr;
	static locShaderSource_t *glShaderSource = nullptr;
	static locCompileShader_t *glCompileShader = nullptr;
	static locDeleteShader_t *glDeleteShader = nullptr;
	static locCreateProgram_t *glCreateProgram = nullptr;
	static locDeleteProgram_t *glDeleteProgram = nullptr;
	static locLinkProgram_t *glLinkProgram = nullptr;
	static locAttachShader_t *glAttachShader = nullptr;
	static locDetachShader_t *glDetachShader = nullptr;
	static locglGetShaderiv_t *glGetShaderiv = nullptr;
	static locglGetProgramiv_t *glGetProgramiv = nullptr;

	static locBindBuffer_t *glBindBuffer = nullptr;
	static locBufferData_t *glBufferData = nullptr;
	static locGenBuffers_t *glGenBuffers = nullptr;
	static locglDeleteBuffers_t *glDeleteBuffers = nullptr;
	static locVertexAttribPointer_t *glVertexAttribPointer = nullptr;
	static locEnableVertexAttribArray_t *glEnableVertexAttribArray = nullptr;
	static locUseProgram_t *glUseProgram = nullptr;
	static locBindVertexArray_t *glBindVertexArray = nullptr;
	static locGenVertexArrays_t *glGenVertexArrays = nullptr;
	static locGetShaderInfoLog_t *glGetShaderInfoLog = nullptr;
	static locGetProgramInfoLog_t *glGetProgramInfoLog = nullptr;
	static locglUniform1i_t *glUniform1i = nullptr;
	static locglUniform1f_t *glUniform1f = nullptr;
	static locglUniform2f_t *glUniform2f = nullptr;
	static locglUniform3f_t *glUniform3f = nullptr;
	static locglUniform4f_t *glUniform4f = nullptr;
	static locglUniformMatrix2fv_t *glUniformMatrix2fv = nullptr;
	static locglUniformMatrix3fv_t *glUniformMatrix3fv = nullptr;
	static locglUniformMatrix4fv_t *glUniformMatrix4fv = nullptr;
	static locglGetUniformLocation_t *glGetUniformLocation = nullptr;
	static locglGenerateMipmap_t *glGenerateMipmap = nullptr;
	static locglVertexAttribDivisor_t *glVertexAttribDivisor = nullptr;
	static locglDeleteVertexArrays_t *glDeleteVertexArrays = nullptr;
	static locglDrawElementsInstanced_t *glDrawElementsInstanced = nullptr;
	static locglActiveTexture_t *glActiveTexture = nullptr;
	static locglBindTexture_t *glBindTexture = nullptr;

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
			glDetachShader = SPGL_LOAD(locDetachShader_t, glDetachShader);
			glGetShaderiv = SPGL_LOAD(locglGetShaderiv_t, glGetShaderiv);
			glGetProgramiv = SPGL_LOAD(locglGetProgramiv_t, glGetProgramiv);

			glBindBuffer = SPGL_LOAD(locBindBuffer_t, glBindBuffer);
			glBufferData = SPGL_LOAD(locBufferData_t, glBufferData);
			glGenBuffers = SPGL_LOAD(locGenBuffers_t, glGenBuffers);
			glDeleteBuffers = SPGL_LOAD(locglDeleteBuffers_t, glDeleteBuffers);
			glVertexAttribPointer = SPGL_LOAD(locVertexAttribPointer_t, glVertexAttribPointer);
			glEnableVertexAttribArray = SPGL_LOAD(locEnableVertexAttribArray_t, glEnableVertexAttribArray);
			glUseProgram = SPGL_LOAD(locUseProgram_t, glUseProgram);
			glGetShaderInfoLog = SPGL_LOAD(locGetShaderInfoLog_t, glGetShaderInfoLog);
			glGetProgramInfoLog = SPGL_LOAD(locGetShaderInfoLog_t, glGetProgramInfoLog);
			glBindVertexArray = SPGL_LOAD(locBindVertexArray_t, glBindVertexArray);
			glGenVertexArrays = SPGL_LOAD(locGenVertexArrays_t, glGenVertexArrays);
			glUniform1i = SPGL_LOAD(locglUniform1i_t, glUniform1i);
			glUniform1f = SPGL_LOAD(locglUniform1f_t, glUniform1f);
			glUniform2f = SPGL_LOAD(locglUniform2f_t, glUniform2f);
			glUniform3f = SPGL_LOAD(locglUniform3f_t, glUniform3f);
			glUniform4f = SPGL_LOAD(locglUniform4f_t, glUniform4f);
			glUniformMatrix2fv = SPGL_LOAD(locglUniformMatrix2fv_t, glUniformMatrix2fv);
			glUniformMatrix3fv = SPGL_LOAD(locglUniformMatrix3fv_t, glUniformMatrix3fv);
			glUniformMatrix4fv = SPGL_LOAD(locglUniformMatrix4fv_t, glUniformMatrix4fv);
			glGetUniformLocation = SPGL_LOAD(locglGetUniformLocation_t, glGetUniformLocation);
			glGenerateMipmap = SPGL_LOAD(locglGenerateMipmap_t, glGenerateMipmap);
			glVertexAttribDivisor = SPGL_LOAD(locglVertexAttribDivisor_t, glVertexAttribDivisor);
			glDeleteVertexArrays = SPGL_LOAD(locglDeleteVertexArrays_t, glDeleteVertexArrays);
			glDrawElementsInstanced = SPGL_LOAD(locglDrawElementsInstanced_t, glDrawElementsInstanced);
			glActiveTexture = SPGL_LOAD(locglActiveTexture_t, glActiveTexture);
			glBindTexture = SPGL_LOAD(locglBindTexture_t, glBindTexture);

			gl_loaded = true;
		}
	}

}; // namespace sp

namespace sp
{

	using namespace std;

	class input
	{
	public:
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
		bool fullscreen = false;

	public:
		window(string t, uint32_t w = 640, uint32_t h = 480, bool fscr = false) : title(t), width(w), height(h), fullscreen(fscr)
		{
			WNDCLASSEXA wc = {0};
			wc.cbSize = sizeof(WNDCLASSEX);
			wc.lpszClassName = "sp_window_class";
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wc.hInstance = GetModuleHandle(nullptr);
			wc.lpfnWndProc = input::wnd_proc;

			RegisterClassExA(&wc);

			DWORD exstyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			DWORD dwstyle = WS_SYSMENU | WS_VISIBLE | WS_CAPTION;

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
			w = wsize.right - wsize.left;
			h = wsize.bottom - wsize.top;

			handle = CreateWindowExA(exstyle, wc.lpszClassName, title.c_str(), dwstyle, CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, GetModuleHandle(nullptr), this);

			if (title.length() == 0)
				SetWindowLong((HWND)handle, GWL_STYLE, WS_BORDER);

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
		static HGLRC glrc;
		static bool context_created;

	public:
		graphics(string t = "window", uint32_t w = 640, uint32_t h = 480, bool fullscreen = false)
		{
			wnd = make_unique<window>(t, w, h, fullscreen);
			if (valid())
				create_gl_context();
		}

		~graphics()
		{
			wglDeleteContext(glrc);
		}

		void *get_handle() { return wnd->handle; }
		bool valid() { return IsWindow((HWND)wnd->handle); }

		bool create_gl_context()
		{
			dc = GetDC((HWND)(wnd->handle));
			PIXELFORMATDESCRIPTOR pfd =
					{
							sizeof(PIXELFORMATDESCRIPTOR), 1,
							PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
							PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0,
							PFD_MAIN_PLANE, 0, 0, 0, 0};

			int pf = 0;
			if (!(pf = ChoosePixelFormat(dc, &pfd)))
				return false;
			SetPixelFormat(dc, pf, &pfd);
			if (!context_created)
			{
				if (!(glrc = wglCreateContext(dc)))
					return false;
				context_created = true;
			}

			wglMakeCurrent(dc, glrc);

			cout << (char *)glGetString(GL_VERSION) << endl;
			load_gl_func_ptrs();
			return true;
		}

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
			glEnable(GL_DEPTH_TEST);
			glViewport(0, 0, wnd->width, wnd->height);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		void end()
		{
		}
		void clear_color(const vec4 &c)
		{
			glClearColor(c[0], c[1], c[2], c[3]);
		}
	};
	bool graphics::context_created = false;
	HGLRC graphics::glrc;

	//--------------------------- rendering stuff ---------------------------------//

	class shader
	{
	public:
		uint32_t program = 0;
		std::unordered_map<std::string, uint32_t> locationCache = {};

	public:
		shader(std::string vShaderSource, std::string fShaderSource)
		{

			uint32_t vid;
			uint32_t fid;
			bool vc = Compile(vid, GL_VERTEX_SHADER, vShaderSource.c_str());
			bool fc = Compile(fid, GL_FRAGMENT_SHADER, fShaderSource.c_str());
			if (vc && fc)
			{
				Link({vid, fid});
			}
		}
		~shader()
		{
			glDeleteProgram(program);
			program = 0;
		}

		void Bind()
		{

			glUseProgram(program);
		}
		uint32_t GetUniformLocation(const std::string &name)
		{
			if (locationCache.find(name) != locationCache.end())
				return locationCache[name];
			locationCache[name] = glGetUniformLocation(program, name.c_str());
			return locationCache[name];
		}

		void Uniform(const matrix &m, const std::string &name)
		{
			glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, (const GLfloat *)m.data.data);
		}
		void Uniform(const vec4 &v, const std::string &name)
		{
			glUniform4f(GetUniformLocation(name), v[0], v[1], v[2], v[3]);
		}
		void Uniform(const vec3 &v, const std::string &name)
		{
			glUniform3f(GetUniformLocation(name), v[0], v[1], v[2]);
		}

		void Uniform(const vec2 &v, const std::string &name)
		{
			glUniform2f(GetUniformLocation(name), v[0], v[1]);
		}

		void Uniform(const float &f, const std::string &name)
		{
			glUniform1f(GetUniformLocation(name), f);
		}
		void Uniform(const int &i, const std::string &name)
		{
			glUniform1i(GetUniformLocation(name), i);
		}

	private:
		bool Compile(uint32_t &shaderId, uint32_t shaderType, const char *shaderSource)
		{
			shaderId = glCreateShader(shaderType);
			glShaderSource(shaderId, 1, &shaderSource, 0);
			glCompileShader(shaderId);
			int32_t success;
			char infoLog[512];
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shaderId, 512, 0, infoLog);
				std::cerr << "error compiling : " << infoLog << std::endl;
				return false;
			}
			return true;
		}
		bool Link(std::vector<uint32_t> shaders)
		{
			if (program == 0)
				program = glCreateProgram();
			for (uint32_t id : shaders)
			{
				glAttachShader(program, id);
			}

			glLinkProgram(program);

			int32_t success;
			char infoLog[512];
			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(program, 512, 0, infoLog);
				std::cerr << "error linking : " << infoLog << std::endl;
				return false;
			}

			// remove all shaders
			// for (uint32_t id : shaders)
			//{
			//	glDetachShader(program, id);
			//	glDeleteShader(id);
			//}
			return true;
		}
	};

	class Texture
	{
	public:
		uint32_t id = 0;

	public:
		Texture(int width, int height, bool smooth = false)
		{
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			if (smooth)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture(const image &img, bool smooth = false)
		{
			glGenTextures(1, &id);
			set_image(img, smooth);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		Texture(const greyscale_image &img, bool smooth = false)
		{
			glGenTextures(1, &id);
			set_greyscale_image(img, smooth);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		~Texture()
		{
			glDeleteTextures(1, &id);
			id = 0;
		}
		void set_image(const image &img, bool smooth = false)
		{
			glBindTexture(GL_TEXTURE_2D, id);

			set_filters(smooth);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.col, img.row, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)img.data.data);
			int highest = img.col;
			if (img.row > img.col)
				highest = img.row;
			gen_mipmaps(highest);
		}

		void set_greyscale_image(const greyscale_image &img, bool smooth = false)
		{
			glBindTexture(GL_TEXTURE_2D, id);
			set_filters(smooth);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.col, img.row, 0, GL_RED, GL_UNSIGNED_BYTE, (void *)img.data.data);
			int highest = img.col;
			if (img.row > img.col)
				highest = img.row;
			gen_mipmaps(highest);
		}

	private:
		void set_filters(bool smooth)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			if (smooth)
			{
				cout << "set to linear" << endl;
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			}
			else
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
		}
		void gen_mipmaps(u32 highest)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
			if (highest >= 1024)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
			else if (highest >= 512)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3);
			else if (highest >= 256)
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 2);
			else
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	};

	constexpr u32 SPRITE_PER_BATCH = 256;

	struct Sprite
	{
		vec4 rect = vec4(0.f, 0.f, 1.f, 1.f);
		vec4 crop = vec4(0.f, 0.f, 1.f, 1.f);
		vec4 color = vec4(1.0f);
		float textureId = 0.0f;
		float zindex = 1.0f;
		float rotation = 0.0f;
		float scale = 1.0f;
		vec4 extra = vec4(0.0f);
		vec4 extra2 = vec4(0.0f);
		vec4 extra3 = vec4(0.0f);
		vec4 extra4 = vec4(0.0f);

		Sprite(){};
		Sprite(const Sprite &s)
		{
			rect = s.rect;
			crop = s.crop;
			color = s.color;
			textureId = s.textureId;
			zindex = s.zindex;
			rotation = s.rotation;
			scale = s.scale;
			extra = s.extra;
			extra2 = s.extra2;
		}
		Sprite &operator=(const Sprite &s)
		{
			rect = s.rect;
			crop = s.crop;
			color = s.color;
			textureId = s.textureId;
			zindex = s.zindex;
			rotation = s.rotation;
			scale = s.scale;
			extra = s.extra;
			extra2 = s.extra2;
			return *this;
		}
	};

	class sprite_renderer
	{
	public:
		std::vector<Sprite> sprites = {};
		u32 batchSize = SPRITE_PER_BATCH;
		matrix projectionMatrix = mat4_identity();
		matrix viewMatrix = mat4_identity();

		float aspect;
		float width;
		float height;

		uint32_t vao = 0;
		uint32_t vbo = 0;
		uint32_t ebo = 0;
		uint32_t ibo = 0;

	private:
		std::unordered_map<int, int> textureMap;

	public:
		sprite_renderer(float width, float height)
		{
			float px = width / 2;
			float py = height / 2;

			set_projection(-px, py, px, -py);

			// x,y,u,v
			const float quadVertices[] = {
					-0.5, -0.5, 0.0, 1.0,
					0.5, -0.5, 1.0, 1.0,
					0.5, 0.5, 1.0, 0.0,
					-0.5, 0.5, 0.0, 0.0};
			const unsigned int quadIndices[] = {0, 1, 2, 0, 2, 3};

			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &ebo);
			glGenBuffers(1, &ibo);

			glBindVertexArray(vao);

			// vertex buffer
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			glBufferData(GL_ARRAY_BUFFER, 4 * 4 * sizeof(float), quadVertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid *)0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid *)(2 * sizeof(float)));

			// index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), quadIndices, GL_STATIC_DRAW);

			// instance buffer
			glBindBuffer(GL_ARRAY_BUFFER, ibo);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite), (GLvoid *)offsetof(Sprite, rect));
			glVertexAttribDivisor(2, 1);

			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite), (GLvoid *)offsetof(Sprite, crop));
			glVertexAttribDivisor(3, 1);

			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite), (GLvoid *)offsetof(Sprite, color));
			glVertexAttribDivisor(4, 1);

			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite), (GLvoid *)offsetof(Sprite, textureId));
			glVertexAttribDivisor(5, 1);

			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite), (GLvoid *)offsetof(Sprite, extra));
			glVertexAttribDivisor(6, 1);

			glEnableVertexAttribArray(7);
			glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite), (GLvoid *)offsetof(Sprite, extra2));
			glVertexAttribDivisor(7, 1);

			glEnableVertexAttribArray(8);
			glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite), (GLvoid *)offsetof(Sprite, extra3));
			glVertexAttribDivisor(8, 1);
			
			glEnableVertexAttribArray(9);
			glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(Sprite), (GLvoid *)offsetof(Sprite, extra4));
			glVertexAttribDivisor(9, 1);
			
			glBindVertexArray(0);
		}
		~sprite_renderer()
		{
			sprites = {};
			batchSize = SPRITE_PER_BATCH;
			projectionMatrix = mat4_identity();
			viewMatrix = mat4_identity();

			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ebo);
			glDeleteBuffers(1, &ibo);
			vao = vbo = ebo = ibo = 0;
		}

		void set_projection(float l, float t, float r, float b)
		{
			projectionMatrix = orthogonal_projection_matrix(l, t, r, b);

			width = abs(r - l);
			height = abs(t - b);
			aspect = width / height;
		}

		void draw(const Sprite &sprite)
		{
			sprites.push_back(sprite);
			sprites.back().textureId = textureMap[sprites.back().textureId];
			if (sprites.size() == batchSize)
			{
				RenderBatch();
			}
		}

		void begin(shader &sd, const buffer<u32> &textureIds)
		{

			sd.Bind();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);

			float time = (float)GetTickCount() / 1000;

			sd.Uniform(projectionMatrix, "u_projectionMatrix");
			sd.Uniform(viewMatrix, "u_viewMatrix");
			sd.Uniform(time, "u_time");
			sd.Uniform(aspect, "u_aspect");
			sd.Uniform(width, "u_width");

			textureMap = {};
			textureMap[0] = -1;

			for (int i = 0; i < textureIds.len; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, textureIds[i]);
				std::string tName = "textures[" + std::to_string(i) + "]";
				glUniform1i(sd.GetUniformLocation(tName), i);
				textureMap[textureIds[i]] = i;
			}

			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, ibo);

			sprites = {};
		}

		void end()
		{
			RenderBatch();
			glDisable(GL_BLEND);
			glDepthMask(GL_TRUE);
		}

	private:
		void RenderBatch()
		{
			glBindVertexArray(vao);

			glBufferData(GL_ARRAY_BUFFER, sizeof(Sprite) * sprites.size(), sprites.data(), GL_DYNAMIC_DRAW);

			glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0, sprites.size());

			sprites = {};
		}
	};
}; //namespace sp

#define PEN_NONE 0
#define PEN_TEXT_BOLD 1
#define PEN_TEXT_ITALIC 2
#define PEN_ORIGIN_CENTER 1
#define PEN_ORIGIN_TOPLEFT 0
#define PEN_CANVAS_CENTER 1
#define PEN_CANVAS_TOPLEFT 0

namespace sp
{

	class pen2d
	{
	public:
		unique_ptr<shader> sdr;
		unique_ptr<sprite_renderer> spr;
		vec4 fillcolor = vec4(1.0, 1.0, 1.0, 1.0);
		vec4 drawcolor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		float thickness = 1.0f;
		buffer<Texture *> textures;
		unordered_map<string, fontdata> fonts;
		buffer<Texture *> font_textures;
		string fontfamily = "default";
		u32 fontsize = 20;
		u8 origin = PEN_ORIGIN_CENTER;
		u8 canvas = PEN_CANVAS_CENTER; 
		u32 textstyle = 0;
		float textoutline = 0.1;

	public:
		pen2d()
		{
			sdr = make_unique<shader>(sprite_renderer_vertex_shader, sprite_renderer_fragment_shader);
			spr = make_unique<sprite_renderer>(1.0f, 1.0f);
			textures = buffer<Texture *>();

			fonts["default"] = fontdata();
			fonts["default"].load_default();
			Texture *t = new Texture(fonts["default"].spritesheet, true);
			font_textures.push(t);
			fonts["default"].id = t->id;
		}
		~pen2d()
		{
			for (u32 i = 0; i < font_textures.len; i++)
			{
				delete font_textures[i];
			}
		}

		void pen_down(u32 width, u32 height)
		{
			buffer<u32> tids(textures.len + font_textures.len);
			u32 k = 0;
			for (u32 i = 0; i < textures.len; i++)
				tids[k++] = textures[i]->id;
			for (u32 i = 0; i < font_textures.len; i++)
				tids[k++] = font_textures[i]->id;
			if(canvas)
			{
				float px = (float)width / 2.0;
				float py = (float)height / 2.0;
				spr->set_projection(-px, py, px, -py);
				spr->begin(*sdr, tids);
			}
			else
			{
				float w = width;
				float h = height;
				spr->set_projection(0, 0, w, h);
				spr->begin(*sdr, tids);
			}
		}
		void pen_up()
		{
			spr->end();
		}

		void fill_rect(vec4 rect, float r = 0.0f)
		{
			Sprite s;
			if (origin)
				s.rect = rect;
			else
			{
				float px = rect[2] / 2.0f;
				float py = rect[3] / 2.0f;
				s.rect = vec4(rect[0] + px, rect[1] - py, rect[2], rect[3]);
			}
			s.color = fillcolor;
			s.extra[0] = 0.0f;
			spr->draw(s);
		}
		void draw_rect(vec4 rect, float r = 0.0f)
		{
			Sprite s;
			if (origin)
				s.rect = rect;
			else
			{
				float px = rect[2] / 2.0f;
				float py = rect[3] / 2.0f;
				s.rect = vec4(rect[0] + px, rect[1] - py, rect[2], rect[3]);
			}
			s.rotation = r;
			s.color = drawcolor;
			s.extra[0] = 1.0f;
			s.extra[1] = thickness / rect[2];
			s.extra[2] = thickness / rect[3];
			spr->draw(s);
		}
		void draw_line(vec2 p1, vec2 p2)
		{
			float l = (p1 - p2).len();
			float r = -atan((p2[1] - p1[1]) / (p2[0] - p1[0]));

			vec2 center = (p1 + p2) / 2.0f;
			Sprite s;
			s.rect = {center[0], center[1], l, thickness};
			s.rotation = -r;
			s.color = drawcolor;
			s.extra[0] = 2.0f;

			spr->draw(s);
		}
		void fill_circle(vec2 pos, float r)
		{
			Sprite s;
			s.rect = {pos[0], pos[1], r * 2, r * 2};
			if (origin)
				s.rect = s.rect;
			else
			{
				float px = s.rect[2] / 2.0f;
				float py = s.rect[3] / 2.0f;
				s.rect = vec4(s.rect[0] + px, s.rect[1] - py, s.rect[2], s.rect[3]);
			}
			s.color = fillcolor;

			s.extra[0] = 3.0f;
			spr->draw(s);
		}
		void draw_circle(vec2 pos, float r)
		{
			Sprite s;
			s.rect = {pos[0], pos[1], r * 2, r * 2};
			if (origin)
				s.rect = s.rect;
			else
			{
				float px = s.rect[2] / 2.0f;
				float py = s.rect[3] / 2.0f;
				s.rect = vec4(s.rect[0] + px, s.rect[1] - py, s.rect[2], s.rect[3]);
			}
			s.color = drawcolor;
			s.extra[1] = thickness / r;
			s.extra[0] = 4.0f;
			spr->draw(s);
		}
		void fill_symmetric_polygon(vec2 pos, float size, float n = 3, float aspect = 1.0)
		{
			Sprite s;
			s.rect = {pos[0], pos[1], size * 4, size * 4 / aspect};
			if (origin)
				s.rect = s.rect;
			else
			{
				float px = s.rect[2] / 2.0f;
				float py = s.rect[3] / 2.0f;
				s.rect = vec4(s.rect[0] + px, s.rect[1] - py, s.rect[2], s.rect[3]);
			}
			s.color = fillcolor;

			s.extra[0] = 5.0f;
			s.extra[1] = n;
			spr->draw(s);
		}
		void draw_symmetric_polygon(vec2 pos, float size, float n = 3, float aspect = 1.0)
		{
			Sprite s;
			s.rect = {pos[0], pos[1], size * 4, size * 4 / aspect};
			if (origin)
				s.rect = s.rect;
			else
			{
				float px = s.rect[2] / 2.0f;
				float py = s.rect[3] / 2.0f;
				s.rect = vec4(s.rect[0] + px, s.rect[1] - py, s.rect[2], s.rect[3]);
			}
			s.color = fillcolor;

			s.extra[0] = 6.0f;
			s.extra[1] = n;
			s.extra[2] = thickness / size;
			spr->draw(s);
		}
		u32 push(const image &img, bool smooth = false)
		{
			Texture *t = new Texture(img, smooth);
			textures.push(t);
			return textures.len - 1;
		}
		u32 push(const greyscale_image &img, bool smooth = false)
		{
			Texture *t = new Texture(img, smooth);
			textures.push(t);
			return textures.len - 1;
		}
		void addfont(string family, string filepath)
		{
			fonts[family] = fontdata();
			fonts[family].load(filepath);
			Texture *t = new Texture(fonts[family].spritesheet, true);
			font_textures.push(t);
			fonts[family].id = t->id;
		}

		u32 clear()
		{
			for (u32 i = 0; i < textures.len; i++)
				delete textures[i];

			textures.clear();
		}
		void draw_image(u32 id, vec4 rect, vec4 crop = vec4(0.0f, 0.0f, 1.0f, 1.0f), bool center = true)
		{
			Sprite s;
			if (center)
				s.rect = rect;
			else
			{
				float px = rect[2] / 2.0f;
				float py = rect[3] / 2.0f;
				s.rect = vec4(rect[0] + px, rect[1] - py, rect[2], rect[3]);
			}
			s.textureId = textures[id]->id;
			s.crop = crop;
			s.extra[0] = 7.0f;
			spr->draw(s);
		}

		void draw_text(vec2 pos, string text, vec2 block = vec2(0.0f, 0.0f), bool breakbyword = false)
		{
			fontdata &f = fonts[fontfamily];
	
			vec2 cursor = pos;
			cursor[1] -= fontsize;
			for (u32 i = 0; i < text.length(); i++)
			{
				char c = text[i];
				if (block[1] > 0.001 && cursor[1] >= block[1] - (fontsize * f.currentheight))
				{
					return;
				}
				else if (c == ' ')
				{
					cursor[0] += fontsize * 0.5;
					if (breakbyword)
					{
						int j = i + 1;
						float l = 0.0f;
						while (j < text.length() && !(text[j] == ' ' || text[j] == '\n'))
						{

							l += f.glyphs[text[j]].advance * fontsize;
							j++;
						}

						if (block[0] > 0.001f && cursor[0] + l > block[0])
						{
							cursor[0] = pos[0];
							cursor[1] += fontsize * f.currentheight;
						}
					}
					continue;
				}
				else if (c == '\t')
				{
					cursor[0] += fontsize * 2.0;
					continue;
				}
				else if ((block[0] > 0.001f && cursor[0] + f.glyphs[c].advance * fontsize > block[0]) || c == '\n')
				{
					cursor[0] = pos[0];
					cursor[1] -= fontsize;
					if (c == '\n')
						continue;
				}

				Sprite s;
				vec2 posfinal = cursor;
				posfinal += f.glyphs[c].offset * fontsize;
				vec2 v = f.glyphs[c].size * fontsize;
				vec4 rect = vec4(posfinal[0], posfinal[1] - v[1], v[0], v[1]);
				float px = rect[2] / 2.0f;
				float py = rect[3] / 2.0f;
				s.rect = vec4(rect[0] + px, rect[1] - py, rect[2], rect[3]);
				s.crop = f.glyphs[c].crop;
				s.color = fillcolor;
				s.textureId = f.id;
				s.scale = fontsize;
				s.extra[0] = 8.0;
				s.extra[1] = textoutline;
				s.extra[2] = fontsize;
				s.extra[3] = (textstyle & PEN_TEXT_BOLD) ? 1.4: 1.0; 
				s.extra2 = drawcolor;
				s.extra3[0] = (textstyle & PEN_TEXT_ITALIC) ? .2: 0.0; 
				spr->draw(s);
				cursor[0] += f.glyphs[c].advance * fontsize + (fontsize < 16.0 ? .66: 0.0);
			}
		}
	};

	namespace colorcode
	{
		const vec4 White = vec4(1.0f);
		const vec4 PaperWhite = vec4(0.953f, 0.898f, 0.961f, 1.0f);
		const vec4 Red = vec4(0.835f, 0.000f, 0.000f, 1.0f);
		const vec4 Tomato = vec4(1.000f, 0.388f, 0.278f, 1.0f);
		const vec4 Brick = vec4(0.718f, 0.110f, 0.110f, 1.0f);
		const vec4 Pink = vec4(0.961f, 0.000f, 0.341f, 1.0f);
		const vec4 LightPink = vec4(1.000f, 0.502f, 0.671f, 1.0f);
		const vec4 SalmonRed = vec4(0.937f, 0.325f, 0.314f, 1.0f);
		const vec4 Purple = vec4(0.533f, 0.055f, 0.310f, 1.0f);
		const vec4 Skin = vec4(1.000f, 0.541f, 0.502f, 1.0f);
		const vec4 PurpleBlue = vec4(0.290f, 0.078f, 0.549f, 1.0f);
		const vec4 IndigoBlue = vec4(0.188f, 0.247f, 0.624f, 1.0f);
		const vec4 Blue = vec4(0.188f, 0.310f, 0.996f, 1.0f);
		const vec4 SkyBlue = vec4(0.733f, 0.871f, 0.984f, 1.0f);
		const vec4 CerulianBlue = vec4(0.259f, 0.647f, 0.961f, 1.0f);
		const vec4 NeviBlue = vec4(0.000f, 0.000f, 0.502f, 1.0f);
		const vec4 Cyan = vec4(0.161f, 0.714f, 0.965f, 1.0f);
		const vec4 GreenBlue = vec4(0.000f, 0.898f, 1.000f, 1.0f);
		const vec4 Teal = vec4(0.000f, 0.588f, 0.533f, 1.0f);
		const vec4 Green = vec4(0.000f, 0.784f, 0.325f, 1.0f);
		const vec4 SapGreen = vec4(0.220f, 0.557f, 0.235f, 1.0f);
		const vec4 DarkSapGreen = vec4(0.106f, 0.369f, 0.125f, 1.0f);
		const vec4 OliveGreen = vec4(0.463f, 1.000f, 0.012f, 1.0f);
		const vec4 LightGreen = vec4(0.392f, 0.867f, 0.090f, 1.0f);
		const vec4 GrassGreen = vec4(0.408f, 0.624f, 0.220f, 1.0f);
		const vec4 Lime = vec4(0.776f, 1.000f, 0.000f, 1.0f);
		const vec4 Yellow = vec4(1.000f, 1.000f, 0.000f, 1.0f);
		const vec4 Orange = vec4(0.976f, 0.659f, 0.145f, 1.0f);
		const vec4 IndianYellow = vec4(1.000f, 0.671f, 0.000f, 1.0f);
		const vec4 Steel = vec4(0.329f, 0.431f, 0.478f, 1.0f);
		const vec4 InkBlack = vec4(0.149f, 0.196f, 0.220f, 1.0f);
		const vec4 Black = vec4(0.0f, 0.0f, 0.0f, 1.0f);
		const vec4 Grey = vec4(0.459f, 0.459f, 0.459f, 1.0f);
		const vec4 LightGrey = vec4(0.741f, 0.741f, 0.741f, 1.0f);
		const vec4 Brown = vec4(0.427f, 0.298f, 0.255f, 1.0f);
		const vec4 TreeBrown = vec4(0.545f, 0.217f, 0.075f, 1.0f);

		inline vec4 Hex(uint32_t hexValue)
		{
			vec4 rgbColor;
			rgbColor[0] = ((hexValue >> 16) & 0xFF) / 255.0f; // Extract the RR byte
			rgbColor[1] = ((hexValue >> 8) & 0xFF) / 255.0f;	// Extract the GG byte
			rgbColor[2] = ((hexValue)&0xFF) / 255.0f;
			rgbColor[3] = 1.0f;
			return rgbColor;
		}
	};

}; // namespace sp