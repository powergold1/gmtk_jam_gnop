#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <GL/gl.h>
#include <GL/glcorearb.h>
#include <SDL2/SDL.h>
#include <time.h>
#include "types.h"
#include "utils.h"
#include "math.h"
#include "memory.h"
#include "rng.h"
#include "str_builder.h"
#include "platform_shared.h"
#include "config.h"

#define __declspec(X)

#ifdef m_gl_funcs
#undef m_gl_funcs
#endif
#define m_gl_funcs \
X(PFNGLBUFFERDATAPROC, glBufferDataProc) \
X(PFNGLBUFFERSUBDATAPROC, glBufferSubDataProc) \
X(PFNGLGENVERTEXARRAYSPROC, glGenVertexArraysProc) \
X(PFNGLBINDVERTEXARRAYPROC, glBindVertexArrayProc) \
X(PFNGLGENBUFFERSPROC, glGenBuffersProc) \
X(PFNGLBINDBUFFERPROC, glBindBufferProc) \
X(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointerProc) \
X(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArrayProc) \
X(PFNGLCREATESHADERPROC, glCreateShaderProc) \
X(PFNGLSHADERSOURCEPROC, glShaderSourceProc) \
X(PFNGLCREATEPROGRAMPROC, glCreateProgramProc) \
X(PFNGLATTACHSHADERPROC, glAttachShaderProc) \
X(PFNGLLINKPROGRAMPROC, glLinkProgramProc) \
X(PFNGLCOMPILESHADERPROC, glCompileShaderProc) \
X(PFNGLVERTEXATTRIBDIVISORPROC, glVertexAttribDivisorProc) \
X(PFNGLDRAWARRAYSINSTANCEDPROC, glDrawArraysInstancedProc) \
X(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallbackProc) \
X(PFNGLBINDBUFFERBASEPROC, glBindBufferBaseProc) \
X(PFNGLUNIFORM1FVPROC, glUniform1fvProc) \
X(PFNGLUNIFORM2FVPROC, glUniform2fvProc) \
X(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocationProc) \
X(PFNGLUSEPROGRAMPROC, glUseProgramProc) \
X(PFNGLGETSHADERIVPROC, glGetShaderivProc) \
X(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLogProc) \
X(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffersProc) \
X(PFNGLBINDFRAMEBUFFERPROC, glBindFramebufferProc) \
X(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2DProc) \
X(PFNGLCHECKFRAMEBUFFERSTATUSPROC, glCheckFramebufferStatusProc) \
X(PFNGLACTIVETEXTUREPROC, glActiveTextureProc) \
X(PFNGLBLENDEQUATIONPROC, glBlendEquationProc) \
X(PFNGLDELETEPROGRAMPROC, glDeleteProgramProc) \
X(PFNGLDELETESHADERPROC, glDeleteShaderProc) \
X(PFNGLUNIFORM1IPROC, glUniform1i) \
X(PFNGLUNIFORM1FPROC, glUniform1fProc)

#define glBufferData glBufferDataProc
#define glBufferSubData glBufferSubDataProc
#define glGenVertexArrays glGenVertexArraysProc
#define glBindVertexArray glBindVertexArrayProc
#define glGenBuffers glGenBuffersProc
#define glBindBuffer glBindBufferProc
#define glVertexAttribPointer glVertexAttribPointerProc
#define glEnableVertexAttribArray glEnableVertexAttribArrayProc
#define glCreateShader glCreateShaderProc
#define glShaderSource glShaderSourceProc
#define glCreateProgram glCreateProgramProc
#define glAttachShader glAttachShaderProc
#define glLinkProgram glLinkProgramProc
#define glCompileShader glCompileShaderProc
#define glVertexAttribDivisor glVertexAttribDivisorProc
#define glDrawArraysInstanced glDrawArraysInstancedProc
#define glDebugMessageCallback glDebugMessageCallbackProc
#define glBindBufferBase glBindBufferBaseProc
#define glUniform1fv glUniform1fvProc
#define glUniform2fv glUniform2fvProc
#define glGetUniformLocation glGetUniformLocationProc
#define glUseProgram glUseProgramProc
#define glGetShaderiv glGetShaderivProc
#define glGetShaderInfoLog glGetShaderInfoLogProc
#define glGenFramebuffers glGenFramebuffersProc
#define glBindFramebuffer glBindFramebufferProc
#define glFramebufferTexture2D glFramebufferTexture2DProc
#define glCheckFramebufferStatus glCheckFramebufferStatusProc
#define glActiveTexture glActiveTextureProc
#define glBlendEquation glBlendEquationProc
#define glDeleteProgram glDeleteProgramProc
#define glDeleteShader glDeleteShaderProc
#define glUniform1i glUniform1iProc
#define glUniform1f glUniform1fProc

b8 platform_play_sound(s_sound)
{
	// TODO: implement
	return true;
}

void platform_set_swap_interval(int interval)
{
	SDL_GL_SetSwapInterval(interval);
}

int platform_show_cursor(BOOL b)
{
//	int v=-1;
//	if(b==0)
//		v=SDL_DISABLE;
//	else if(b==1)
//		v=SDL_ENABLE;
//	assert(v>=0);
//	SDL_ShowCursor(v);
//	return b-1;
	return 0;
}

void (*platform_load_gl_func(const char *name))(void)
{
	char buf[1024];
	const char *proc = "Proc";
	int m = 0;
	int found = 0;
	for (int i = 0; i < 1024; ++i) {
		buf[i] = name[i];
		if (name[i] == proc[m]) {
			m++;
			if (m == 5) {
				buf[i-m+1] = 0;
				found = 1;
				break;
			}
		} else {
			m = 0;
		}
	}
	assert(found);
	void (*v)(void) = (void(*)(void))SDL_GL_GetProcAddress(buf);
	return v;
}


// a little messy
// these funcs are used in main, but defined in memory.cpp, but not declared in memory.h
// memory.cpp is included later by client.cpp
func void* la_get(s_lin_arena* arena, size_t in_requested);
func s_lin_arena make_lin_arena_from_memory(size_t capacity, void* memory);

typedef struct timespec timespec;

timespec timespec_sub(timespec a, timespec b) {
	struct timespec res;
	res.tv_sec = a.tv_sec - b.tv_sec;
	res.tv_nsec = a.tv_nsec - b.tv_nsec;
	if (res.tv_nsec < 0) {
		res.tv_sec--;
		res.tv_nsec += 1000000000L;
	}
	return res;
}

f64 get_seconds(timespec start_time)
{
	timespec cur_time;
	clock_gettime(CLOCK_REALTIME, &cur_time);
	timespec diff = timespec_sub(cur_time, start_time);
	f64 res = diff.tv_sec + (diff.tv_nsec / 1000000000.0);
	return res;
}

#ifdef m_debug
extern "C" {
#endif
m_update_game(update_game);
#ifdef m_debug
}
#endif

int internal_key(SDL_Keycode k)
{
	// just the sdl keys we need
	static const SDL_Keycode sdl_keycodes[] = {
		SDLK_ESCAPE, SDLK_F1, SDLK_F4, SDLK_F8, SDLK_F9, SDLK_q,
		SDLK_PLUS, SDLK_KP_PLUS, SDLK_MINUS, SDLK_KP_MINUS,
	};
	static const int internal_keycodes[] = {
		c_key_escape, c_key_f1, c_key_f4, c_key_f8, c_key_f9, c_key_q,
		c_key_add, c_key_add, c_key_subtract, c_key_subtract,
	};
	for (int i = 0; i < (int)array_count(sdl_keycodes); ++i)
		if (k == sdl_keycodes[i])
			return internal_keycodes[i];
	return -1;
}

int main(void)
{
	s_input input;
	timespec start_time;
	clock_gettime(CLOCK_REALTIME, &start_time);
	int window_width;
	int window_height;
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetSwapInterval(1);
	SDL_Window *window = SDL_CreateWindow("Gnop", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, c_base_res.x, c_base_res.y, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL);
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, gl_context);
	SDL_ShowWindow(window);
	SDL_GetWindowSize(window, &window_width, &window_height);
	void* game_memory = null;
	s_lin_arena frame_arena = zero;
	s_lin_arena all = zero;
	all.capacity = 20 * c_mb;
	// @Note(tkap, 26/06/2023): We expect this memory to be zero'd
	all.memory = calloc(all.capacity, 1);
	game_memory = la_get(&all, c_game_memory);
	frame_arena = make_lin_arena_from_memory(5 * c_mb, la_get(&all, 5 * c_mb));
	s_platform_data platform_data = zero;
	platform_data.frame_arena = &frame_arena;
	b8 running = true;
	f64 time_passed = 0;
	s32 mousex;
	s32 mousey;
	b8 is_window_active = false;
	while(running)
	{
		f64 start_of_frame_seconds = get_seconds(start_time);
		SDL_Event ev;
		b8 need_size_restore = 0;
		int key = -1;
		while(SDL_PollEvent(&ev)) {
			switch(ev.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				if(ev.type == SDL_KEYDOWN)
					platform_data.any_key_pressed = true;
				key = internal_key(ev.key.keysym.sym);
				if(key >= 0) {
					if(key == c_key_q)
						if (ev.key.keysym.mod & KMOD_CTRL)
							running = 0;
					if(key == c_key_f4)
						if (ev.key.keysym.mod & KMOD_ALT)
							running = 0;
					input.keys[key].count += 1;
					input.keys[key].is_down = ev.type == SDL_KEYDOWN;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				platform_data.any_key_pressed = true;
				break;
			case SDL_WINDOWEVENT:
				switch(ev.window.event) {
					case SDL_WINDOWEVENT_ENTER:
					case SDL_WINDOWEVENT_FOCUS_GAINED:
					case SDL_WINDOWEVENT_RESTORED:
						if (ev.window.event== SDL_WINDOWEVENT_RESTORED)
							need_size_restore = true;
						is_window_active = true;
						break;
					case SDL_WINDOWEVENT_LEAVE:
					case SDL_WINDOWEVENT_FOCUS_LOST:
					case SDL_WINDOWEVENT_MINIMIZED:
					case SDL_WINDOWEVENT_HIDDEN:
					case SDL_WINDOWEVENT_CLOSE:
						if (ev.window.event== SDL_WINDOWEVENT_MINIMIZED)
							need_size_restore = true;
						is_window_active = false;
						if (ev.window.event == SDL_WINDOWEVENT_CLOSE)
							running = false;
						break;
					case SDL_WINDOWEVENT_MAXIMIZED:
						need_size_restore = true;
						break;
					case SDL_WINDOWEVENT_RESIZED:
					case SDL_WINDOWEVENT_SIZE_CHANGED:
						window_width = ev.window.data1;
						window_height = ev.window.data2;
						break;
				}
				break;
			case SDL_MOUSEMOTION:
				mousex = ev.motion.x;
				mousey = ev.motion.y;
				break;
			}
		}
		if (need_size_restore) {
			SDL_GetWindowSize(window, &window_width, &window_height);
		}
		platform_data.input = &input;
		platform_data.quit_after_this_frame = !running;
		platform_data.window_width = window_width;
		platform_data.window_height = window_height;
		platform_data.time_passed = time_passed;
		platform_data.mouse.x = (float)mousex;
		platform_data.mouse.y = (float)mousey;
		platform_data.is_window_active = is_window_active;
		update_game(platform_data, game_memory);
		platform_data.any_key_pressed = false;
		SDL_GL_SwapWindow(window);
		time_passed = get_seconds(start_time) - start_of_frame_seconds;
	}
	return 0;
}
