#ifndef render_types_h
#define render_types_h

// Architecture specific header, might be rewritten for other arcs!
#include <stdint.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

typedef glm::vec4 vector4;
typedef glm::vec3 vector3;
typedef glm::vec2 vector2;
typedef glm::mat4 matrix4;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef float f32;
typedef double f64;

#endif
