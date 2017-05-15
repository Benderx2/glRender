#ifndef texture_h
#define texture_h

#include <string>
#include <GL/glew.h>

typedef enum {

  TEXTURE_TEXTURE2D,
  TEXTURE_CUBEMAP,
  TEXTURE_SPRITESHEET

} texture_type;

class Texture {
public:
  Texture(const std::string&);
  Texture(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
  // Sprite width, Sprite height, no. of sprites
  Texture(const std::string&, int, int, int);
  Texture() {
    // None
  }
  void Bind(unsigned int unit, int frame=0);
  void DrawBlock(unsigned int x, unsigned int y, unsigned int w, unsigned int h, int frame=0);
  virtual ~Texture();
private:
  int n_textures;
  GLuint* texture_id;
  texture_type type;
};

#endif
