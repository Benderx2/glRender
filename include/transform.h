#ifndef transform_h
#define transform_h

#include <glm/gtc/type_ptr.hpp>

#include <render_type.h>

class Transform {
public:
    Transform(const vector3& translation = vector3(), const vector3& rotation = vector3(), const vector3& scale = vector3(1.0f, 1.0f, 1.0f)) :
    v_translate(translation),
    v_rot(rotation),
    v_scale(scale)
    {
      // Empty function
    }

    inline vector3& GetTranslation() { return v_translate; }
    inline vector3& GetRotation() { return v_rot; }
    inline vector3& GetScale() { return v_scale; }

    inline void SetTranslation(float x, float y, float z) {
      v_translate.x = x;
      v_translate.y = y;
      v_translate.z = z;
    }

    inline void SetTranslation(vector3& translation) {
      v_translate = translation;
    }

    inline void SetRotation(float x, float y, float z) {
      v_rot.x = x;
      v_rot.y = y;
      v_rot.z = z;
    }

    inline void SetRotation(vector3& rotation) {
      v_rot = rotation;
    }

    inline void SetScale(float x, float y, float z) {
      v_scale.x = x;
      v_scale.y = y;
      v_scale.z = z;
    }

    inline void SetScale(vector3& scale) {
      v_scale = scale;
    }

    inline matrix4 GetMatrix(void) const {
      matrix4 matrix_trans = glm::translate(v_translate);
      matrix4 matrix_scale = glm::scale(v_scale);
      // Rotate around x, y and z-axis
      matrix4 matrix_rotx = glm::rotate(v_rot.x, vector3(1,0,0));
      matrix4 matrix_roty = glm::rotate(v_rot.y, vector3(0,1,0));
      matrix4 matrix_rotz = glm::rotate(v_rot.z, vector3(0,0,1));

      matrix4 matrix_rot = matrix_rotz * matrix_roty * matrix_rotx;
      matrix_rot = matrix_rot;

      return matrix_trans * matrix_rot * matrix_scale;
    }

private:
  vector3 v_translate;
  vector3 v_rot;
  vector3 v_scale;
};

#endif
