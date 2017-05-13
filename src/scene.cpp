#include <scene.h>
#include <render_constant.h>

Scene::Scene(unsigned int N) {
  scene_objects = (GameObject**)calloc(sizeof(GameObject*), N);
  n_objects = N;
}

void Scene::AddCamera(Camera* cam) {
  scene_cam = cam;
}

int Scene::AddObject(GameObject* object) {
  for(unsigned int i = 0; i < n_objects; i++) {
    if(scene_objects[i] == NULL) {
      scene_objects[i] = object;
      return RENDER_SUCCESS;
    }
  }
  return RENDER_FAIL;
}
int Scene::AddSky(Skybox* sky) {
  scene_skybox = sky;
}
GameObject* Scene::RemoveObject(const std::string& name) {
  for(unsigned int i = 0; i < n_objects; i++) {
    if(scene_objects[i] != NULL) {
      if((*scene_objects[i]).GetName() == name) {
        GameObject* ptr = scene_objects[i];
        scene_objects[i] = NULL;
        return ptr;
      }
    }
  }
  return NULL;
}

GameObject* Scene::GetObjectPointer(const std::string& name) {
  for(unsigned int i = 0; i < n_objects; i++) {
    if(scene_objects[i] != NULL) {
      if((*scene_objects[i]).GetName() == name) {
        return scene_objects[i];
      }
    }
  }
  return NULL;
}

Camera* Scene::GetCameraPointer(void) {
  return scene_cam;
}
void Scene::Draw(void) {
  if(scene_skybox != NULL)
    scene_skybox->Draw(*scene_cam);

  for(unsigned int i = 0; i < n_objects; i++) {
    if(scene_objects[i] != NULL) {
      (*scene_objects[i]).Draw(*scene_cam);
    }
  }
}

Scene::~Scene() {
  free((void*)scene_objects);
}
