#include <cassert>
#include <iostream>
#include <texture.h>
#include <stb_image.h>

Texture::Texture(const std::string& name) {
  type = TEXTURE_TEXTURE2D;
  int width, height, n_comp;

  std::cout << "Loading texture: '" << name << "' ..." << std::endl;

  unsigned char* image_data = stbi_load(name.c_str(), &width, &height, &n_comp, 4);
  if(image_data == NULL) {
    std::cerr << "-- texture loading failed: " << name << std::endl;
  }
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);

  // If we read something outside the texture, wrap that.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(image_data);
}

// Cubemap constructor
Texture::Texture(const std::string& px, const std::string& nx, const std::string& py, const std::string& ny, const std::string& pz, const std::string& nz) {
  type = TEXTURE_CUBEMAP;
  glGenTextures(1, &texture_id);
  glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

  std::cout << "Loading cubemap..." << std::endl;

  std::string filenames[] = { px, nx, py, ny, pz, nz };
  for(int i = 0; i < 6; i++) {
    std::cout << "-- loading cube map: idx: " << i << " name: " << filenames[i] << std::endl;

    int width, height, n_comp;
    unsigned char* image_data = stbi_load(filenames[i].c_str(), &width, &height, &n_comp, 4);
    if(image_data == NULL) {
      std::cout << "-- error loading cubemap: " << filenames[i] << std::endl;
    }
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    stbi_image_free(image_data);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
// Destructor
Texture::~Texture() {
  glDeleteTextures(1, &texture_id);
}

void Texture::Bind(unsigned int unit) {
  assert(unit >= 0 && unit <= 31);
  glActiveTexture(GL_TEXTURE0 + unit);
  if(type == TEXTURE_TEXTURE2D)
    glBindTexture(GL_TEXTURE_2D, texture_id);
  else if(type == TEXTURE_CUBEMAP)
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
}

void Texture::DrawBlock(unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
  glEnable(GL_TEXTURE_2D);
  Bind(0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);

  glBegin(GL_QUADS);

  glTexCoord2f(0, 0);
  glVertex3f(x, y, 0);
  glTexCoord2f(0, 1);
  glVertex3f(x, y + h, 0);
  glTexCoord2f(1, 1);
  glVertex3f(x + w, y + h, 0);
  glTexCoord2f(1, 0);
  glVertex3f(x + w, y, 0);

  glEnd();

  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
}
