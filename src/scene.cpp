#include <scene.h>
#include <render_constant.h>

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
int scene::add_skybox(skybox* sky) {
  scene_skybox = sky;
}
gameobject* scene::remove_object(const std::string& name) {
  for(unsigned int i = 0; i < n_objects; i++) {
    if(scene_objects[i] != NULL) {
      if((*scene_objects[i]).get_name() == name) {
        gameobject* ptr = scene_objects[i];
        scene_objects[i] = NULL;
        return ptr;
      }
    }
  }
  return NULL;
}

gameobject* scene::get_object_ptr(const std::string& name) {
  for(unsigned int i = 0; i < n_objects; i++) {
    if(scene_objects[i] != NULL) {
      if((*scene_objects[i]).get_name() == name) {
        return scene_objects[i];
      }
    }
  }
  return NULL;
}

camera* scene::get_camera_ptr(void) {
  return scene_cam;
}
void scene::draw(void) {
  if(scene_skybox != NULL)
    scene_skybox->draw(*scene_cam);
    
  for(unsigned int i = 0; i < n_objects; i++) {
    if(scene_objects[i] != NULL) {
      (*scene_objects[i]).draw(*scene_cam);
    }
  }
}

scene::~scene() {
  free((void*)scene_objects);
}
