#ifndef mesh_h
#define mesh_h

#include <GL/glew.h>
#include <vector>

#include <obj_loader.h>
#include <render_type.h>

class Vertex {
public:
  Vertex(const vector3& pos, const vector2& texcord, const vector3& normal = glm::vec3(0,0,0)) {
    this->pos = pos;
    this->texcord = texcord;
    this->normal = normal;
  }
  Vertex() {

  }
  inline vector3* GetPos(void) {
    return &pos;
  }
  inline vector2* GetTexCoord(void) {
    return &texcord;
  }
  inline vector3* GetNormal(void) {
    return &normal;
  }

  vector3 pos;
  vector2 texcord;
  vector3 normal;
};

class Mesh {
public:
  Mesh(Vertex* vp, unsigned int vcount, unsigned int* idx, unsigned int nidx, GLenum m);
  Mesh(const std::string& name);
  Mesh();

  void Draw(void);

  virtual ~Mesh(void);

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
  
  void InitMesh(const IndexedModel& model);
};
#endif
