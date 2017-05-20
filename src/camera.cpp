#include <camera.h>

Camera::Camera(const vector3& pos, const vector3& forward, const vector3& up, float fov, float aspect, float znear, float zfar, float y, float p) {
  matrix_perspective = glm::perspective(fov, aspect, znear, zfar);
  v_pos = pos;
  v_forward = glm::normalize(forward);
  v_up = glm::normalize(up);
  SetYawPitch(y, p);
}

float Camera::GetYaw(void) {
  return yaw;
}

float Camera::GetPitch(void) {
    return pitch;
}

vector3 Camera::GetPos(void) const {
  return v_pos;
}

vector3 Camera::GetForward(void) const {
  return v_forward;
}

vector3 Camera::GetUp(void) const {
  return v_up;
}

void Camera::SetPos(const vector3& pos) {
  v_pos = pos;
}

void Camera::SetForward(const vector3& forward) {
  v_forward = forward;
}

void Camera::SetYawPitch(float y, float p) {
  yaw = y;
  pitch = p;

  if(pitch > 89.0f)
    pitch = 89.0f;

  if(pitch < -89.0f)
    pitch = -89.0f;

  CalcFront();
}

void Camera::SetUp(const vector3& up) {
  v_up = up;
}

void Camera::Move(cam_direction dir, float speed) {
  switch(dir) {
    case CAMERA_FRONT:
      v_pos = v_pos + (speed * v_forward);
      break;
    case CAMERA_BACK:
      v_pos = v_pos - (speed * v_forward);
      break;
    case CAMERA_LEFT:
      v_pos = v_pos - (glm::normalize(glm::cross(v_forward, v_up)) * speed);
      break;
    case CAMERA_RIGHT:
      v_pos = v_pos + (glm::normalize(glm::cross(v_forward, v_up)) * speed);
      break;
    case CAMERA_UP:
      v_pos = v_pos + (speed * v_up);
      break;
    case CAMERA_DOWN:
      v_pos = v_pos - (speed * v_up);
      break;
    default:
      // WTF?
      break;
  }
}

void Camera::Rotate(cam_direction dir, float angle) {
  switch(dir) {
    case CAMERA_UP:
      SetYawPitch(yaw, pitch + angle);
      break;
    case CAMERA_DOWN:
      SetYawPitch(yaw, pitch - angle);
      break;
    case CAMERA_LEFT:
      SetYawPitch(yaw - angle, pitch);
      break;
    case CAMERA_RIGHT:
      SetYawPitch(yaw + angle, pitch);
      break;
    default:
      break;
  }
}

matrix4 Camera::GetMatrix(void) const {
  // Return View * Projection Matrix
  return matrix_perspective * glm::lookAt(v_pos, v_pos + (v_forward), v_up) ;
}

void Camera::CalcFront(void) {
  glm::vec3 front;
  // Calculate front vector from Euler angles
  front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  front.y = sin(glm::radians(pitch));
  front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

  v_forward = glm::normalize(front);
}
