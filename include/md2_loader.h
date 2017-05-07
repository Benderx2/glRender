#ifndef md2_loader_h
#define md2_loader_h

#include <mesh.>
#include <render_types.h>

#define MD2_MAX_TRIANGLES 4096
#define MD2_MAX_VERTICES 2048
#define MD2_MAX_TEXCOORDS 2048
#define MD2_MAX_FRAMES 512
#define MD2_MAX_FRAME_SIZE (MD2_MAX_VERTICES * 4 + 128)

#define ANIMATION_KEY_SPEED 5.0f

typedef struct {
  int magic;
  int version;
  int skin_w;
  int skin_h;
  int frame_size;
  int n_skins;
  int n_vertices;
  int n_texcoords;
  int n_triangles;
  int n_glcommands;
  int n_frames;
  int skin_ptr;
  int texcoord_ptr;
  int triangle_ptr;
  int frame_ptr;
  int glcommands_ptr;
  int end_ptr;
} md2_header;

typedef struct {
  u8 v[3];
  u8 normal_index;
} md2_triangle_alias;

typedef struct {
  float v[3];
  float n[3];
} md2_triangle;

typedef struct {
  u16 v_index[3];
  u16 tex_index[3];
} md2_face;

typedef struct {
  u16 u, v;
} md2_texcoord;

typedef struct {
  float scale[3];
  float translate[3];
  char name[16];
} md2_frame_alias;

typedef struct {
  char name[16];
  md2_triangle* v;
} md2_frame;

typedef char md2_skin[64];

class md2_loader {
public:
  md2_loader(mesh* destination, const std::string& model_file, const std::string& texture_file);
private:
  std::ifstream md2_file;
  md2_header header;
  md2_skin* skins;
  md2_texcoord* texcoords;
  md2_face* triangles;
  md_frame* frames;
};

#endif
