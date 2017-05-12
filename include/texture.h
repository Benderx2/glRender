#ifndef texture_h
#define texture_h

#include <string>
#include <GL/glew.h>

typedef enum {
  TEXTURE_TEXTURE2D,
  TEXTURE_CUBEMAP
} texture_type;

class texture {
public:
  texture(const std::string& filename);
  texture(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
  texture() {
    // None
  }
  void bind(unsigned int unit);
  void draw_block(unsigned int x, unsigned int y, unsigned int w, unsigned int h);
  virtual ~texture();
private:
  GLuint texture_id;
  texture_type type;
};
#endif
