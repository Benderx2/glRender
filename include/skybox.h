#ifndef skybox_h
#define skybox_h

#include <string>

#include <texture.h>
#include <shader.h>

class skybox {
public:
  // create skybox with 1 shader and 6 textures
  skybox(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, float);
  void draw(camera);

private:
  texture* skybox_cubemap;
  shader* skybox_shader;
  float scale;
  GLuint VBO;
  GLuint VAO;
};

#endif
