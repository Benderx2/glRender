#ifndef skybox_h
#define skybox_h

#include <string>

#include <texture.h>
#include <shader.h>

class Skybox {
public:
  // create skybox with 1 shader and 6 textures
  Skybox(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, float);
  void Draw(Camera&);

  virtual ~Skybox();
private:
  Texture* skybox_cubemap;
  Shader* skybox_shader;
  float scale;
  GLuint VBO;
  GLuint VAO;
};

#endif
