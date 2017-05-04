#ifndef gameobject_h
#define gameobject_h

#include <display.h>
#include <mesh.h>
#include <transform.h>
#include <shader.h>
#include <texture.h>


class gameobject {
public:
  void (*predraw)(mesh& msh, shader& shdr, texture& tex, transform& t) = NULL;

  inline gameobject(const std::string& name) {
    // Empty initialiser
    obj_name = name;
  }

  inline void set_property(const texture& tex) {
    obj_tex = tex;
  }
  inline void set_property(const mesh& msh) {
    obj_msh = msh;
  }
  inline void set_property(const shader& shd) {
    obj_shdr = shd;
  }
  inline void set_property(const transform& tfm) {
    obj_trans = tfm;
  }
  inline void set_property(void(*pdraw)(mesh&, shader&, texture&, transform&)) {
    predraw = pdraw;
  }
  inline texture& get_texture() { return obj_tex; }
  inline shader& get_shader() { return obj_shdr; }
  inline mesh& get_mesh() { return obj_msh; }
  inline transform& get_transform() { return obj_trans; }
  inline std::string& get_name() { return obj_name; }
  
  void draw(const camera& cam);

private:
  // Transformations
  transform obj_trans;
  // Object meshses, shaders and textures
  mesh obj_msh;
  shader obj_shdr;
  texture obj_tex;
  std::string obj_name;
};
#endif
