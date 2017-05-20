#ifndef camera_h
#define camera_h

#include <iostream>
#include <render_type.h>

typedef enum {

  CAMERA_FRONT,
  CAMERA_LEFT,
  CAMERA_RIGHT,
  CAMERA_BACK,
  CAMERA_UP,
  CAMERA_DOWN

} cam_direction;

class Camera {
public:
  Camera(const vector3& pos, const vector3& forward, const vector3& up, float fov, float aspect, float znear, float zfar, float y=-90.0f, float p=0.0f);

  vector3 GetPos(void) const;
  vector3 GetForward(void) const;
  vector3 GetUp(void) const;
  float GetYaw(void);
  float GetPitch(void);

  void SetPos(const vector3& pos);
  void SetForward(const vector3& forward);
  void SetYawPitch(float y, float p);
  void SetUp(const vector3& up);

  void Move(cam_direction dir, float speed);
  void Rotate(cam_direction dir, float angle);

  matrix4 GetMatrix(void) const;

private:
  matrix4 matrix_perspective;

  vector3 v_pos;
  vector3 v_forward;
  vector3 v_up;

  float yaw, pitch;

  void CalcFront(void);
};
#endif
