#ifndef camera_h
#define camera_h

#include <render_type.h>

class Camera {
public:
  Camera(const vector3& pos, const vector3& forward, const vector3& up, float fov, float aspect, float znear, float zfar) {
    matrix_perspective = glm::perspective(fov, aspect, znear, zfar);
    v_pos = pos;
    v_forward = forward;
    v_up = up;
  }
  inline vector3 GetPos(void) const {
    return v_pos;
  }
  inline vector3 GetForward(void) const {
    return v_forward;
  }
  inline vector3 GetUp(void) const {
    return v_up;
  }
  inline void SetPos(const vector3& pos) {
    v_pos = pos;
  }
  inline void SetForward(const vector3& forward) {
    v_forward = forward;
  }
  inline void SetUp(const vector3& up) {
    v_up = up;
  }
  // Now, the following functions define the way we can move and rotate our camera
  inline void SetProjection(float xf, float yf, float zf, float xt, float yt, float zt, float xu, float yu, float zu) {
    v_pos.x = xf; v_pos.y = yf; v_pos.z = zf;
    v_forward.x = xt; v_forward.y = yt; v_forward.z = zt;
    v_up.x = xu; v_up.y = yu; v_up.z = zu;
  }
  inline matrix4 GetMatrix(void) const {
    // Return View * Projection Matrix
    return matrix_perspective * glm::lookAt(v_pos, v_forward, v_up);
  }
private:
  matrix4 matrix_perspective;
  vector3 v_pos;
  vector3 v_forward;
  vector3 v_up;
};
#endif
