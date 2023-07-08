enum e_string_input_result
{
	e_string_input_result_none,
	e_string_input_result_submit,
};

enum e_state
{
	e_state_main_menu,
	e_state_game,
	e_state_count,
};

enum e_font
{
	e_font_small,
	e_font_medium,
	e_font_big,
	e_font_count,
};

struct s_glyph
{
	int advance_width;
	int width;
	int height;
	int x0;
	int y0;
	int x1;
	int y1;
	s_v2 uv_min;
	s_v2 uv_max;
};

struct s_font
{
	float size;
	float scale;
	int ascent;
	int descent;
	int line_gap;
	s_texture texture;
	s_glyph glyph_arr[1024];
};


enum e_shader
{
	e_shader_default,
	e_shader_count,
};

struct s_shader_paths
{
	#ifdef m_debug
	#ifdef _WIN32
	FILETIME last_write_time;
	#else
	time_t last_write_time;
	#endif // _WIN32
	#endif // m_debug
	char* vertex_path;
	char* fragment_path;
};

struct s_ball
{
	float speed;
	union
	{
		struct
		{
			float x;
			float y;
		};
		s_v2 pos;
	};
	s_v2 dir;
	float hit_time;
};

struct s_paddle
{
	union
	{
		struct
		{
			float x;
			float y;
		};
		s_v2 pos;
	};
};

struct s_pickup
{
	union
	{
		struct
		{
			float x;
			float y;
		};
		s_v2 pos;
	};
};

struct s_particle
{
	s8 render_type;
	float time;
	float duration;
	float speed;
	s_v2 pos;
	s_v2 dir;
	float radius;
	s_v4 color;
};

struct s_game
{
	b8 initialized;
	int score;
	int max_score;
	int level_count;
	int update_count;
	int frame_count;
	b8 reset_game;
	s_ball ball;
	s_paddle paddle;
	float total_time;
	f64 update_timer;
	s_rng rng;
	e_state state;
	s_font font_arr[e_font_count];

	s_sarray<s_particle, 16384> particles;
	s_sarray<s_pickup, 64> pickups;

	u32 default_vao;
	u32 default_ssbo;

	u32 programs[e_shader_count];

	s_sound big_dog_sound;
	s_sound jump_sound;
	s_sound jump2_sound;
	s_sound win_sound;
};

func void update();
func void render(float dt);
func b8 check_for_shader_errors(u32 id, char* out_error);
func void input_system(int start, int count);
func void draw_system(int start, int count, float dt);
func void revive_every_player(void);
func void draw_circle_system(int start, int count, float dt);
func void collision_system(int start, int count);
func s_font load_font(const char* path, float font_size, s_lin_arena* arena);
func s_texture load_texture_from_data(void* data, int width, int height, u32 filtering);
func s_v2 get_text_size(const char* text, e_font font_id);
func s_v2 get_text_size_with_count(const char* text, e_font font_id, int count);
func u32 load_shader(const char* vertex_path, const char* fragment_path);
func void handle_instant_movement_(int entity);
func void handle_instant_resize_(int entity);
func b8 is_key_down(int key);
func b8 is_key_up(int key);
func b8 is_key_pressed(int key);
func b8 is_key_released(int key);
void gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
func void sine_alpha_system(int start, int count);
func s_v4 get_ball_color(s_ball ball);


template <typename T>
func e_string_input_result handle_string_input(T* str);

#ifdef m_debug
func void hot_reload_shaders(void);
#endif // m_debug
