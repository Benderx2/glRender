#ifndef texture_h
#define texture_h

#include <string>
#include <GL/glew.h>

class texture {
public:
  texture(const std::string& filename);
  texture() {
    // None
  }
  void bind(unsigned int unit);
  void draw_block(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
  virtual ~texture();
private:
  GLuint texture_id;
};
#endif
