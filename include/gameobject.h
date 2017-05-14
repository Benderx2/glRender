#ifndef gameobject_h
#define gameobject_h

#include <mesh.h>
#include <transform.h>
#include <shader.h>
#include <texture.h>

class GameObject {
public:

  void (*predraw)(Mesh* msh, Shader* shdr, Texture* tex, Transform* t) = NULL;

  inline GameObject(const std::string& name) {
    // Empty initialiser
    obj_name = name;
  }
  inline GameObject(const std::string& name, Mesh* msh, Texture* tex, Shader* shd, Transform* tfm, void(*pdraw)(Mesh*, Shader*, Texture*, Transform*)) {
    obj_name = name;
    obj_tex = tex;
    obj_msh = msh;
    obj_shdr = shd;
    obj_trans = tfm;
    predraw = pdraw;
  }

  inline void SetProperties(Mesh* msh, Texture* tex, Shader* shd, Transform* tfm, void(*pdraw)(Mesh*, Shader*, Texture*, Transform*)) {
    obj_tex = tex;
    obj_msh = msh;
    obj_shdr = shd;
    obj_trans = tfm;
    predraw = pdraw;
  }

  inline void SetProperty(Texture* tex) {
    obj_tex = tex;
  }
  inline void SetProperty(Mesh* msh) {
    obj_msh = msh;
  }
  inline void SetProperty(Shader* shd) {
    obj_shdr = shd;
  }
  inline void SetProperty(Transform* tfm) {
    obj_trans = tfm;
  }

  inline void SetProperty(void(*pdraw)(Mesh*, Shader*, Texture*, Transform*)) {
    predraw = pdraw;
  }

  inline Texture* GetTexture() { return obj_tex; }
  inline Shader* GetShader() { return obj_shdr; }
  inline Mesh* GetMesh() { return obj_msh; }
  inline Transform* GetTransform() { return obj_trans; }
  inline std::string GetName() { return obj_name; }

  void Draw(const Camera& cam);

private:
  // Transformations
  Transform* obj_trans;
  // Object meshses, shaders and textures
  Mesh* obj_msh;
  Shader* obj_shdr;
  Texture* obj_tex;
  std::string obj_name;
};
#endif
