#include <scene.h>

scene::scene(unsigned int N) {
  scene_objects = (gameobject**)calloc(sizeof(gameobject*), N);
  n_objects = N;
}

void scene::add_camera(camera* cam) {
  scene_cam = cam;
}

int scene::add_object(gameobject* object) {
  for(unsigned int i = 0; i < n_objects; i++) {
    if(scene_objects[i] == NULL) {
      scene_objects[i] = object;
      return RENDER_SUCCESS;
    }
  }
  return RENDER_FAIL;
}

void scene::draw(void) {
  for(unsigned int i = 0; i < n_objects; i++) {
    if(scene_objects[i] != NULL) {
      (*scene_objects[i]).draw(*scene_cam);
    }
  }
}
