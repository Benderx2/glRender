#ifndef primitive_h
#define primitive_h

#include <mesh.h>

typedef enum {

  PRIMITIVE_CUBE,
  PRIMITIVE_SPHERE,
  PRIMITIVE_CONE

} primitive_type;

class primitive {
public:

  primitive(primitive_type);

  inline mesh& get_mesh() {
    return *primitive_mesh;
  }

  virtual ~primitive();

private:
  mesh* primitive_mesh;
};

#endif
