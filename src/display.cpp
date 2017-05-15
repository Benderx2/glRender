#include <display.h>
#include <render.h>
#include <iostream>

const Color Color::WHITE(1.0f, 1.0f, 1.0f);
const Color Color::BLACK(0.0f, 0.0f, 0.0f);
const Color Color::RED(0.7f, 0.3f, 0.3f);
const Color Color::GREEN(0.3f, 0.7f, 0.3f);
const Color Color::BLUE(0.3f, 0.3f, 0.7f);
const Color Color::GRAY(0.5f, 0.5f, 0.5f);
const Color Color::YELLOW(0.9f, 0.9f, 0.05f);
const Color Color::GREEN_DARK(0.0f, 0.9f, 0.0f);
const Color Color::RED_DARK(0.9f, 0.0f, 0.0f);
const Color Color::BLUE_DARK(0.0f, 0.0f, 0.9f);

Display::Display(int w, int h, const std::string& title) {

  std::cout << "Initialising Display..." << std::endl;

  if(SDL_Init(SDL_INIT_EVERYTHING)) {
    std::cerr << "SDL failed to initialise." << std::endl;
  }

  height = h;
  width = w;
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  gl_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL);
  gl_Context = SDL_GL_CreateContext(gl_Window);

  std::cout << "-- created SDL window with attributes: w: " << w << " h: " << h << " title: '" << title << "'" << std::endl;

  glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
  glGetIntegerv(GL_MINOR_VERSION, &gl_minor);

  std::cout << "-- gl version: " << gl_major << "." << gl_minor << std::endl;
  std::cout << "-- gl initialisation complete. creating glew instance..." << std::endl;

  glewExperimental = GL_TRUE;
  GLenum res = glewInit();
  if(res != GLEW_OK) {
    std::cerr << "-- glew failed to initialise." << std::endl;
  }

  std::cout << "-- glew initialised." << std::endl;
  std::cout << "-- glRender version: " << glRender_version_major << "." << glRender_version_minor << std::endl;

  std::cout << "Display module initialised." << std::endl;

  has_quit = false;
  k_x = false; k_z = false; k_spc = false; k_up = false; k_down = false; k_left = false; k_right = false;
  mouse_x = 0;
  mouse_y = 0;
  mouse_moved = false;
  lclick = false;
  rclick = false;
  is3D = true; // Engine starts in 3D mode.
  aspect = (float)width/(float)height;
  frames = 0;
  t_start = Ticks();
  current_controller = NULL;
}

Display::~Display() {
  SDL_GL_DeleteContext(gl_Context);
  SDL_DestroyWindow(gl_Window);
  SDL_Quit();
}

void Display::Clear(Color col, double alpha) {
  glClearColor(col.r,col.g,col.b,alpha);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Flush(void) {
  glFlush();
  SDL_GL_SwapWindow(gl_Window);
}

unsigned int Display::Ticks(void) {
  return (unsigned int)SDL_GetTicks();
}

bool Display::Closed(void) {
  return has_quit;
}

unsigned int* Display::GetMouseXY(void) {
  mouse_moved = false;
  return new unsigned int[2] { mouse_x, mouse_y };
}

void Display::Update(void) {
// Calculate FPS
  CalculateFPS();
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    if(event.type == SDL_QUIT) {
      has_quit = true;
    } else if(event.type == SDL_KEYDOWN) {
      switch(event.key.keysym.sym) {
        case SDLK_UP:
          k_up = true;
          break;
        case SDLK_DOWN:
          k_down = true;
          break;
        case SDLK_RIGHT:
          k_right = true;
          break;
        case SDLK_LEFT:
          k_left = true;
          break;
        case SDLK_z:
          k_z = true;
          break;
        case SDLK_x:
          k_x = true;
          break;
        case SDLK_SPACE:
          k_spc = true;
          break;
        default:
          break;
      }
    } else if(event.type == SDL_KEYUP) {
      switch(event.key.keysym.sym) {
        case SDLK_UP:
          k_up = false;
          break;
        case SDLK_DOWN:
          k_down = false;
          break;
        case SDLK_RIGHT:
          k_right = false;
          break;
        case SDLK_LEFT:
          k_left = false;
          break;
        case SDLK_z:
          k_z = false;
          break;
        case SDLK_x:
          k_x = false;
          break;
        case SDLK_SPACE:
          k_spc = false;
          break;
        default:
          break;
      }
    } else if(event.type == SDL_MOUSEMOTION) {
      mouse_x = event.motion.x;
      mouse_y = event.motion.y;
      mouse_moved = true;
    } else if(event.type == SDL_MOUSEBUTTONDOWN) {
      if(event.button.button = SDL_BUTTON_LEFT) {
        lclick = true;
      } else if(event.button.button == SDL_BUTTON_RIGHT) {
        rclick = true;
      }
    } else if(event.type == SDL_MOUSEBUTTONUP) {
      if(event.button.button = SDL_BUTTON_LEFT) {
        lclick = false;
      } else if(event.button.button == SDL_BUTTON_RIGHT) {
        rclick = false;
      }
    }
  }
  if(current_controller != NULL) {
    if(k_up == true) current_controller->CallProcess(CONTROLLER_UP, 0.0f, 0.0f);
    if(k_down == true) current_controller->CallProcess(CONTROLLER_DOWN, 0.0f, 0.0f);
    if(k_left == true) current_controller->CallProcess(CONTROLLER_LEFT, 0.0f, 0.0f);
    if(k_right == true) current_controller->CallProcess(CONTROLLER_RIGHT, 0.0f, 0.0f);
    if(k_z == true) current_controller->CallProcess(CONTROLLER_Z, 0.0f, 0.0f);
    if(k_x == true) current_controller->CallProcess(CONTROLLER_X, 0.0f, 0.0f);
    if(mouse_moved == true) current_controller->CallProcess(CONTROLLER_MOUSE, mouse_x, mouse_y);
  }
}
unsigned int Display::GetWidth(void) {
  return width;
}
unsigned int Display::GetHeight(void) {
  return height;
}
float Display::GetAspect(void) {
  return aspect;
}
unsigned int Display::GetFPS(void) {
  return fps;
}
void Display::Culling(bool toggle) {
  if(toggle) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
  } else {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
  }
}

void Display::RegisterController(Controller* ctrl) {
  current_controller = ctrl;
}
void Display::SetMouse(int x, int y) {
  SDL_WarpMouseInWindow(gl_Window, x, y);
}
void Display::CalculateFPS(void) {
  t_end = Ticks();
  frames += 1;
  if(t_end - t_start > 1000) {
    fps = frames;
    t_start = Ticks();
    frames = 0;
  }
}
