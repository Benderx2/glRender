#ifndef display_h
#define display_h

#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <controller.h>


class Color {
public:
  float r;
  float g;
  float b;
  inline Color(float R, float G, float B) {
    r = R;
    g = G;
    b = B;
  }
  static const Color WHITE;
  static const Color BLACK;
  static const Color GREEN;
  static const Color RED;
  static const Color BLUE;
  static const Color YELLOW;
  static const Color GRAY;
  static const Color GREEN_DARK;
  static const Color RED_DARK;
  static const Color BLUE_DARK;
};

class Display {
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
  // Frames per second
  float fps;

  Display(int w, int h, const std::string& title);

  void Clear(Color col, double alpha);
  void Flush(void);

  void Update(void);
  unsigned int Ticks(void);

  bool Closed(void);

  unsigned int* GetMouseXY(void);

  unsigned int GetWidth(void);
  unsigned int GetHeight(void);
  float GetAspect(void);

  unsigned int GetFPS(void);

  void Culling(bool);

  void RegisterController(Controller* ctrl);
  void SetMouse(int x, int y);
  void GrabCursor(bool grab);
  virtual ~Display();

private:
  SDL_Window* gl_Window;
  SDL_GLContext gl_Context;

  Controller* current_controller;

  unsigned int t_start, t_end;
  unsigned int frames;

  void CalculateFPS(void);
};
#endif
