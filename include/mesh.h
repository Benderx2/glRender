#ifndef mesh_h
#define mesh_h

#include <GL/glew.h>
#include <vector>
#include <time.h>

#include <formats/obj.h>
#include <formats/md2.h>

#include <vertex.h>
#include <render_type.h>

typedef enum {

  MESH_OBJ,
  MESH_MD2,
  MESH_STATIC

} model_type;

class Mesh {
public:
  Mesh(Vertex* vp, unsigned int vcount, unsigned int* idx, unsigned int nidx, GLenum m);
  Mesh(const std::string& name, model_type type);
  Mesh();

  void SetFrame(int);
  void SetFrameInterpolation(int, int, float);
  int Animate(int start, int end, float* interp);

  void SetAnimation(const std::string&);
  int CycleAnimation(void);

  void UpdateVertexData(Vertex*, unsigned int, unsigned int*, unsigned int, GLenum);
  void Draw(void);

  virtual ~Mesh(void);

  inline void SetAnimationSpeed(double speed) {
    anim_speed = speed;
  }

private:

  enum {
    POSITION_VB,
    TEXCORD_VB,
    INDEX_VB,
    NORMAL_VB,
    N_BUFFERS
  };
  model_type type = MESH_STATIC;

  GLenum mode;
  GLuint vertex_buffer_object;
  GLuint vertex_buffers[N_BUFFERS];
  unsigned int vb_drawcount;

  std::string mesh_name;
  // MD2 Extras
  MD2Loader* md2_loader;
  // For animations...
  int current_frame;
  int next_frame;
  double then;
  double now;
  double anim_speed;
  float interpolation;
  MD2Anim current_anim;

  void InitMesh(const IndexedModel& model);
};
#endif
