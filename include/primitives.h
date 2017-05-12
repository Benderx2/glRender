#ifndef primitive_h
#define primitive_h

#include <mesh.h>

typedef enum {

  PRIMITIVE_CUBE,
  PRIMITIVE_SPHERE,
  PRIMITIVE_FLOOR,
  PRIMITIVE_CUSTOM

} primitive_type;

class primitive {
public:

  primitive(primitive_type);

  inline mesh& get_mesh() {
    return *primitive_mesh;
  }
  inline primitive_type get_type() {
    return type;
  }

  void map_vertex(glm::vec3);
  void map_face(unsigned int, unsigned int, unsigned int);
  void map_texcoord(glm::vec2);
  void map_normal(glm::vec3);

  void build_mesh();

  virtual ~primitive();

private:
  void create_floor(void);
  void create_sphere(void);
  void create_cube(void);

  mesh* primitive_mesh;

  std::vector<glm::vec3> custom_vertices;
  std::vector<glm::vec3> custom_normals;
  std::vector<unsigned int> custom_indices;
  std::vector<glm::vec2> custom_texcoords;

  primitive_type type;
};

#endif
