#ifndef engine_h
#define engine_h

#include <display.h>
#include <shader.h>

typedef enum {
  ENGINE_3D,
  ENGINE_2D
} engine_mode;

inline void internal_engine3d(Display& dp) {
  glPopAttrib();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

inline void internal_engine2d(Display& dp) {
  ReleaseShaders();

  // Reset matrices
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0.0f, dp.GetWidth(), dp.GetHeight(), 0.0f, -1.0f, 1.0f);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  // Disable 3D attributes
  glPushAttrib(GL_ALL_ATTRIB_BITS);

  glDisable(GL_CULL_FACE);
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);

  glClear(GL_DEPTH_BUFFER_BIT);

}

inline void EngineSetMode(Display& dp, engine_mode mode) {
  if(dp.is3D == false && mode == ENGINE_3D) {
    internal_engine3d(dp);
    dp.is3D = true;
  }
  if(dp.is3D == true && mode == ENGINE_2D) {
    internal_engine2d(dp);
    dp.is3D = false;
  }
}

#endif
