#ifndef shader_h
#define shader_h

#include <string>
#include <GL/glew.h>
#include <transform.h>
#include <camera.h>

#define SHADER_VERTEX 0
#define SHADER_PIXEL 1

inline void ReleaseShaders(void) {
  glUseProgram(0);
}

class Shader {
public:
  Shader(const std::string&, bool);
  Shader() {
    // None
  }
  virtual ~Shader();

  void Update(const Transform& t, const Camera& cam);
  void Bind(void);

  void SetUniform(const std::string& name, int i);
  void SetUniform(const std::string& name, float f);
  void SetUniform(const std::string& name, vector2 v);
  void SetUniform(const std::string& name, vector3 v);
  void SetUniform(const std::string& name, vector4 v);
  void SetUniform(const std::string& name, matrix4 m);

  inline GLuint GetUniform(const std::string& name) {
    return glGetUniformLocation(shader_program, name.c_str());
  }
  inline GLuint GetShaderProgram(void) {
    return shader_program;
  }
  inline void MarkAttribute(unsigned int attr_no, const std::string& attribute) {
    glBindAttribLocation(shader_program, attr_no, attribute.c_str());
  }
  inline GLint GetAttribute(const std::string& attribute) {
    return glGetAttribLocation(shader_program, attribute.c_str());
  }
private:
  enum {
    TRANSFORM_UFORM,
    N_UFORMS
  };

  GLint shader_uniforms[N_UFORMS];
  GLuint shader_program;
  static const unsigned int N_SHADERS = 2;
  GLuint shaders[N_SHADERS];

  std::string LoadShader(const std::string& name);
  void CheckErr(GLuint shader, GLuint flag, bool is_program, const std::string& error_msg);
  GLuint CreateShader(const std::string& text, unsigned int type);
};
#endif
