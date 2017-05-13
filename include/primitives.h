#ifndef primitive_h
#define primitive_h

#include <mesh.h>

typedef enum {

  PRIMITIVE_CUBE,
  PRIMITIVE_SPHERE,
  PRIMITIVE_FLOOR,
  PRIMITIVE_CUSTOM

} primitive_type;

class Primitive {
public:

  Primitive(primitive_type);

  inline Mesh& GetMesh() {
    return *primitive_mesh;
  }
  inline primitive_type GetType() {
    return type;
  }

  void MapVertex(glm::vec3);
  void MapFace(unsigned int, unsigned int, unsigned int);
  void MapTexCoord(glm::vec2);
  void MapNormal(glm::vec3);

  void BuildMesh();

  virtual ~Primitive();

private:
  void CreateFloor(void);
  void CreateSphere(void);
  void CreateCube(void);

  Mesh* primitive_mesh;

  std::vector<glm::vec3> custom_vertices;
  std::vector<glm::vec3> custom_normals;
  std::vector<unsigned int> custom_indices;
  std::vector<glm::vec2> custom_texcoords;

  primitive_type type;
};

#endif
