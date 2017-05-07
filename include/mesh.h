#ifndef mesh_h
#define mesh_h

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>

#include <obj_loader.h>


class vertex {
public:
  vertex(const glm::vec3& pos, const glm::vec2& texcord, const glm::vec3& normal = glm::vec3(0,0,0)) {
    this->pos = pos;
    this->texcord = texcord;
    this->normal = normal;
  }
  vertex() {

  }
  inline glm::vec3* get_pos(void) {
    return &pos;
  }
  inline glm::vec2* get_texcord(void) {
    return &texcord;
  }
  inline glm::vec3* get_normal(void) {
    return &normal;
  }

  glm::vec3 pos;
  glm::vec2 texcord;
  glm::vec3 normal;
};
class mesh {
public:
  mesh(vertex* vp, unsigned int vcount, unsigned int* idx, unsigned int nidx, GLenum m);
  mesh(const std::string& name);
  mesh();
  virtual ~mesh(void);
  void draw(void);
private:
  enum {
    POSITION_VB,
    TEXCORD_VB,
    INDEX_VB,
    NORMAL_VB,
    N_BUFFERS
  };
  GLenum mode;
  GLuint vertex_buffer_object;
  GLuint vertex_buffers[N_BUFFERS];
  unsigned int vb_drawcount;
  std::string mesh_name;

  void init_mesh(const IndexedModel& model);
};
#endif
