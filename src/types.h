

typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef uint8_t b8;
typedef uint32_t b32;

typedef double f64;

#define c_max_u64 UINT64_MAX

constexpr float c_max_f32 = 999999999.0f;

#define zero {}
#define func static
#define global static
#define null NULL

#ifdef __linux__
typedef int BOOL;
#endif
