#ifndef display_h
#define display_h

#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <glm/glm.hpp>

// A few constants
#define RENDER_SUCCESS 0
#define RENDER_FAIL 1

class color {
public:
  float r;
  float g;
  float b;
  inline color(float R, float G, float B) {
    r = R;
    g = G;
    b = B;
  }
  static const color WHITE;
  static const color BLACK;
  static const color GREEN;
  static const color RED;
  static const color BLUE;
  static const color YELLOW;
  static const color GRAY;
  static const color GREEN_DARK;
  static const color RED_DARK;
  static const color BLUE_DARK;
};

class display {
public:
  GLint gl_major, gl_minor;
  unsigned int width, height;
  unsigned int mouse_x, mouse_y;
  // Keys
  bool k_up, k_down, k_right, k_left, k_z, k_x, k_spc;
  bool lclick, rclick;
  // Quit variable
  bool has_quit;
  // Has the mouse moved after last read?
  bool mouse_moved;
  // Used by engine.engine_set_mode
  bool is3D;
  // Aspect Ratio
  float aspect;
  float fps;

  unsigned int frames;

  display(int w, int h, const std::string& title);
  void clear(color col, double alpha);
  void swap(void);
  void update(void);
  uint32_t ticks(void);
  bool closed(void);
  unsigned int* getmousexy(void);
  unsigned int get_width(void);
  unsigned int get_height(void);
  float get_aspect(void);
  unsigned int get_fps(void);
  void culling(bool);
  virtual ~display();

private:
  SDL_Window* gl_Window;
  SDL_GLContext gl_Context;
  uint32_t t_start, t_end;

  void calculate_fps(void);
};
#endif