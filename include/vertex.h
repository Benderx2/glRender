#ifndef vertex_h
#define vertex_h

#include <glm/glm.hpp>

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

#endif
