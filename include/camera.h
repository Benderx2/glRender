#ifndef camera_h
#define camera_h

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class camera {
public:
  camera(const glm::vec3& pos, const glm::vec3& forward, const glm::vec3& up, float fov, float aspect, float znear, float zfar) {
    matrix_perspective = glm::perspective(fov, aspect, znear, zfar);
    v_pos = pos;
    v_forward = forward;
    v_up = up;
  }
  inline glm::vec3 get_pos(void) const {
    return v_pos;
  }
  inline glm::vec3 get_forward(void) const {
    return v_forward;
  }
  inline glm::vec3 get_up(void) const {
    return v_up;
  }
  inline void set_pos(const glm::vec3& pos) {
    v_pos = pos;
  }
  inline void set_forward(const glm::vec3& forward) {
    v_forward = forward;
  }
  inline void set_up(const glm::vec3& up) {
    v_up = up;
  }
  inline glm::mat4 get_matrix(void) const {
    // Return View * Projection Matrix
    return matrix_perspective * glm::lookAt(v_pos, v_forward, v_up);
  }
private:
  glm::mat4 matrix_perspective;
  glm::vec3 v_pos;
  glm::vec3 v_forward;
  glm::vec3 v_up;
};
#endif
