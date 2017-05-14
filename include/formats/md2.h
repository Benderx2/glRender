#ifndef md2_h
#define md2_h

#include <iostream>
#include <string>
#include <vector>

#include <vertex.h>
#include <render_type.h>

typedef float md2_vec3_t[3];

typedef struct {

  i32 magic;
  i32 version;

  i32 skin_w;
  i32 skin_h;

  i32 frame_size;

  i32 n_skins;
  i32 n_vertices;
  i32 n_texcoords;
  i32 n_triangles;
  i32 n_frames;
  i32 n_glcmds;

  i32 skins_ptr;
  i32 texcoords_ptr;
  i32 triangles_ptr;
  i32 frames_ptr;
  i32 glcmds_ptr;
  i32 end_ptr;

} md2_header_t;

typedef struct {
  u8 name[64];
} md2_skin_t;

typedef struct {
  u16 vertex_indices[3];
  u16 texcoord_indices[3];
} md2_triangle_t;

// Compressed vertex
typedef struct {
    u8 v[3];
    u8 normal_index;
} md2_vertex_t;

typedef struct {
  u16 s;
  u16 t;
} md2_texcoord_t;

typedef struct {
  md2_vec3_t scale;
  md2_vec3_t translate;
  i8 name[16];
  md2_vertex_t* vertices;
} md2_frame_t;

class MD2Model {
public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
};

class MD2Loader {
public:
  MD2Loader(const std::string&);

  MD2Model GetFrameData(int n);

  inline md2_header_t* GetHeader(void) {
    return &header;
  }

  virtual ~MD2Loader();

private:
  md2_header_t header;
  md2_skin_t* skins;
  md2_texcoord_t* texcoords;
  md2_frame_t* frames;
  md2_triangle_t* triangles;
  u32* glcmds;
};

#endif
