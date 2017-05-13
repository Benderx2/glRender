#ifndef scene_h
#define scene_h

#include <gameobject.h>
#include <camera.h>
#include <skybox.h>

class Scene {
public:
  Scene(unsigned int);

  void AddCamera(Camera* cam);

  GameObject* RemoveObject(const std::string& name);
  int AddObject(GameObject* object);
  int AddSky(Skybox* sky);

  GameObject* GetObjectPointer(const std::string& name);
  Camera* GetCameraPointer(void);

  void Draw(void);

  virtual ~Scene();

private:
  GameObject** scene_objects;
  Camera* scene_cam;
  Skybox* scene_skybox;
  // N objects;
  unsigned int n_objects;
};

#endif
