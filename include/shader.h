#ifndef shader_h
#define shader_h

#include <string>
#include <GL/glew.h>
#include <transform.h>
#include <camera.h>

#define SHADER_VERTEX 0
#define SHADER_PIXEL 1

inline void shader_release(void) {
  glUseProgram(0);
}

class shader {
public:
  shader(const std::string&, bool);
  shader() {
    // None
  }
  virtual ~shader();
  void update(const transform& t, const camera& cam);
  void bind(void);

  void set_uniform(const std::string& name, glm::vec2 v);
  void set_uniform(const std::string& name, glm::vec3 v);
  void set_uniform(const std::string& name, glm::vec4 v);
  void set_uniform(const std::string& name, glm::mat4 m);

  inline GLuint get_uniform(const std::string& name) {
    return glGetUniformLocation(shader_program, name.c_str());
  }
  inline GLuint get_shader_program(void) {
    return shader_program;
  }
  inline void mark_attribute(unsigned int attr_no, const std::string& attribute) {
    glBindAttribLocation(shader_program, attr_no, attribute.c_str());
  }
  inline GLint get_attribute(const std::string& attribute) {
    return glGetAttribLocation(shader_program, attribute.c_str());
  }
private:
  enum {
    TRANSFORM_UFORM,
    N_UFORMS
  };

  GLuint shader_uniforms[N_UFORMS];
  GLuint shader_program;
  static const unsigned int N_SHADERS = 2;
  GLuint shaders[N_SHADERS];

  std::string load_shader(const std::string& name);
  void check_error(GLuint shader, GLuint flag, bool is_program, const std::string& error_msg);
  GLuint create_shader(const std::string& text, unsigned int type);
};
#endif
