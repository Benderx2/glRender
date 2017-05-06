#ifndef transform_h
#define transform_h

#include <glm/glm.hpp>
// Include transformations (glm::mat4)
#include <glm/gtx/transform.hpp>

class transform {
public:
    transform(const glm::vec3& translation = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
    v_translate(translation),
    v_rot(rotation),
    v_scale(scale)
    {
      // Empty function
    }

    inline glm::vec3& get_translation() { return v_translate; }
    inline glm::vec3& get_rotation() { return v_rot; }
    inline glm::vec3& get_scale() { return v_scale; }

    inline void set_translation(float x, float y, float z) {
      v_translate.x = x;
      v_translate.y = y;
      v_translate.z = z;
    }

    inline void set_translation(glm::vec3& translation) {
      v_translate = translation;
    }

    inline void set_rotation(float x, float y, float z) {
      v_rot.x = x;
      v_rot.y = y;
      v_rot.z = z;
    }

    inline void set_rotation(glm::vec3& rotation) {
      v_rot = rotation;
    }

    inline void set_scale(float x, float y, float z) {
      v_scale.x = x;
      v_scale.y = y;
      v_scale.z = z;
    }

    inline void set_scale(glm::vec3& scale) {
      v_scale = scale;
    }
    
    inline glm::mat4 get_matrix(void) const {
      glm::mat4 matrix_trans = glm::translate(v_translate);
      glm::mat4 matrix_scale = glm::scale(v_scale);
      // Rotate around x, y and z-axis
      glm::mat4 matrix_rotx = glm::rotate(v_rot.x, glm::vec3(1,0,0));
      glm::mat4 matrix_roty = glm::rotate(v_rot.y, glm::vec3(0,1,0));
      glm::mat4 matrix_rotz = glm::rotate(v_rot.z, glm::vec3(0,0,1));

      glm::mat4 matrix_rot = matrix_rotz * matrix_roty * matrix_rotx;

      return matrix_trans * matrix_rot * matrix_scale;
    }
private:
  glm::vec3 v_translate;
  glm::vec3 v_rot;
  glm::vec3 v_scale;
};

#endif
