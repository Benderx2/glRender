#ifndef scene_h
#define scene_h

#include <display.h>
#include <gameobject.h>
#include <camera.h>

class scene {
public:
  scene(unsigned int);

  void add_camera(camera* cam);

  gameobject* remove_object(const std::string& name);
  int add_object(gameobject* object);

  gameobject* get_object_ptr(const std::string& name);

  void draw(void);

  virtual ~scene();
  
private:
  gameobject** scene_objects;
  camera* scene_cam;
  // N objects;
  unsigned int n_objects;
};

#endif
