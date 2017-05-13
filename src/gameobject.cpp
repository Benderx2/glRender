#include <gameobject.h>

void GameObject::Draw(const Camera& cam) {
  (obj_shdr)->Bind();
  if(predraw != NULL) {
    predraw(obj_msh, obj_shdr, obj_tex, obj_trans);
  }
  (obj_shdr)->Update(*obj_trans, cam);
  (obj_tex)->Bind(0);
  (obj_msh)->Draw();
}
