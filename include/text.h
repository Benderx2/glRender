#ifndef text_h
#define text_h

#include <string>

#include <GL/glew.h>

#include <display.h>


class TextRender {
public:
  TextRender(const std::string& font);
  void Render(const std::string& str, int x, int y, float scale);
private:
  int box_w, box_h;
  GLuint tex;
  GLuint display_list;
  GLuint mat_list;
  int w[256];
};
#endif
