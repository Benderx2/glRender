#include <gameobject.h>

void gameobject::draw(const camera& cam) {
  (obj_shdr).bind();
  if(predraw != NULL) {
    predraw(obj_msh, obj_shdr, obj_tex, obj_trans);
  }
  (obj_shdr).update(obj_trans, cam);
  (obj_tex).bind(0);
  (obj_msh).draw();
}
