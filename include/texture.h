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
  virtual ~texture();
private:
  GLuint texture_id;
};
#endif
