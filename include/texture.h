#ifndef texture_h
#define texture_h

#include <string>
#include <GL/glew.h>

typedef enum {
  TEXTURE_TEXTURE2D,
  TEXTURE_CUBEMAP
} texture_type;

class Texture {
public:
  Texture(const std::string& filename);
  Texture(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
  Texture() {
    // None
  }
  void Bind(unsigned int unit);
  void DrawBlock(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
  virtual ~Texture();
private:
  GLuint texture_id;
  texture_type type;
};

#endif
