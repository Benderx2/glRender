#ifndef controller_h
#define controller_h

#include <scene.h>

typedef enum {

  CONTROLLER_UP,
  CONTROLLER_DOWN,
  CONTROLLER_LEFT,
  CONTROLLER_RIGHT,
  CONTROLLER_Z,
  CONTROLLER_X

} controller_key;

class controller {
public:
    inline controller(scene* scene_ptr) {
      controller_scene = scene_ptr;
    }
    inline void call_process(controller_key key, float x, float y) {
      this->process(controller_scene, key, x, y);
    }
    inline void set_callback(void (*func)(scene*, controller_key, float, float)) {
      this->process = func;
    }
    void (*process)(scene* s, controller_key key, float x, float y);
private:
    scene* controller_scene;
};

#endif
