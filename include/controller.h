#ifndef controller_h
#define controller_h

#include <scene.h>

typedef enum {

  CONTROLLER_UP,
  CONTROLLER_DOWN,
  CONTROLLER_LEFT,
  CONTROLLER_RIGHT,
  CONTROLLER_Z,
  CONTROLLER_X,
  CONTROLLER_MOUSE,
  CONTROLLER_MOUSE_REL

} controller_key;

class Controller {
public:
    inline Controller(Scene* scene_ptr) {
      controller_scene = scene_ptr;
    }
    inline void CallProcess(controller_key key, float x, float y) {
      this->process(controller_scene, key, x, y);
    }
    inline void SetCallBack(void (*func)(Scene*, controller_key, float, float)) {
      this->process = func;
    }
    void (*process)(Scene* s, controller_key key, float x, float y);
private:
    Scene* controller_scene;
};

#endif
