#ifndef scene_h
#define scene_h

#include <gameobject.h>
#include <camera.h>
#include <skybox.h>

class scene {
public:
  scene(unsigned int);

  void add_camera(camera* cam);

  gameobject* remove_object(const std::string& name);
  int add_object(gameobject* object);
  int add_skybox(skybox* sky);

  gameobject* get_object_ptr(const std::string& name);
  camera* get_camera_ptr(void);

  void draw(void);

  virtual ~scene();

private:
  gameobject** scene_objects;
  camera* scene_cam;
  skybox* scene_skybox;
  // N objects;
  unsigned int n_objects;
};

#endif
