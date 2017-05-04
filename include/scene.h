#ifndef sceneobject_h
#define sceneobject_h

#include <display.h>
#include <gameobject.h>
#include <camera.h>

class scene {
public:
  scene(unsigned int);

  void add_camera(camera* cam);
  int add_object(gameobject* object);

  void draw(void);

private:
  gameobject** scene_objects;
  camera* scene_cam;
  // N objects;
  unsigned int n_objects;
};

#endif
