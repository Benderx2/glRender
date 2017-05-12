#include <iostream>
#include <fstream>
#include <shader.h>
#include <shader_attribute.h>

// The is3D boolean determines whether to mark the position, texcord and normal attributes.
shader::shader(const std::string& name, bool mark_default) {

  shader_program = glCreateProgram();

  std::cout << "Loading shader: '" << name << "'..." << std::endl;

  shaders[SHADER_VERTEX] = create_shader(load_shader(name + ".vx"), GL_VERTEX_SHADER);
  shaders[SHADER_PIXEL] = create_shader(load_shader(name + ".px"), GL_FRAGMENT_SHADER);

  glAttachShader(shader_program, shaders[SHADER_VERTEX]);
  glAttachShader(shader_program, shaders[SHADER_PIXEL]);

  if(mark_default) {
    mark_attribute(ATTRIBUTE_POSITION, "position");
    mark_attribute(ATTRIBUTE_TEXCORD, "texCoord");
    mark_attribute(ATTRIBUTE_NORMAL, "normal");
  }

  glLinkProgram(shader_program);
  check_error(shader_program, GL_LINK_STATUS, true, "-- failed to link shader! Log: \n");

  glValidateProgram(shader_program);
  check_error(shader_program, GL_LINK_STATUS, true, "-- failed to validate shader! Log: \n");
  if(mark_default) {
    shader_uniforms[TRANSFORM_UFORM] = glGetUniformLocation(shader_program, "transform");
    if(shader_uniforms[TRANSFORM_UFORM] == -1)
      std::cout << "-- warning: uniform 'transform' missing for default marked shader." << std::endl;
  }

}

shader::~shader() {
  glDetachShader(shader_program, shaders[SHADER_VERTEX]);
  glDeleteShader(shaders[SHADER_VERTEX]);
  glDetachShader(shader_program, shaders[SHADER_PIXEL]);
  glDeleteShader(shaders[SHADER_PIXEL]);
  glDeleteProgram(shader_program);
}

void shader::bind(void) {
  glUseProgram(shader_program);
}

std::string shader::load_shader(const std::string& name) {
  std::ifstream file;
  file.open(name.c_str());

  std::string output, line;

  if(file.is_open()) {
    while(file.good()) {
      std::getline(file, line);
      output.append(line + "\n");
    }
  } else {
    std::cerr << "Unable to load shader: " << name << std::endl;
  }

  return output;
}

void shader::check_error(GLuint shader, GLuint flag, bool is_program, const std::string& error_msg) {
  GLint success = 0;
  GLchar error[1024] = { 0 };

  if(is_program)
    glGetProgramiv(shader, flag, &success);
  else
    glGetShaderiv(shader, flag, &success);

  if(success == GL_FALSE) {
    if(is_program)
      glGetProgramInfoLog(shader, sizeof(error), NULL, error);
    else
      glGetShaderInfoLog(shader, sizeof(error), NULL, error);

    std::cerr << error_msg << ":" << error << "'" << std::endl;
  }
}

GLuint shader::create_shader(const std::string& text, unsigned int type) {
  GLuint shader = glCreateShader(type);

  if(shader == 0)
    std::cerr << "Shader creation failed for type: " << type << std::endl;

  const GLchar *p[1];
  p[0] = text.c_str();

  GLint lengths[1];
  lengths[0] = text.length();

  glShaderSource(shader, 1, p, lengths);
  glCompileShader(shader);

  check_error(shader, GL_COMPILE_STATUS, false, "Shader compilation failed!");

  return shader;
}

void shader::update(const transform& t, const camera& cam) {
  glm::mat4 model_matrix = cam.get_matrix() * t.get_matrix();
  glUniformMatrix4fv(shader_uniforms[TRANSFORM_UFORM], 1, GL_FALSE, &model_matrix[0][0]);
  // write the transform matrix to the uniform,
}

void shader::set_uniform(const std::string& name, glm::vec2 v) {
  GLint uniform_loc = glGetUniformLocation(shader_program, name.c_str());
  if(uniform_loc == -1)
    std::cout << "warning: uniform not found: " << name << std::endl;
  glUniform2fv(uniform_loc, 1, &v[0]);
}

void shader::set_uniform(const std::string& name, glm::vec3 v) {
  GLint uniform_loc = glGetUniformLocation(shader_program, name.c_str());
  if(uniform_loc == -1)
    std::cout << "warning: uniform not found: " << name << std::endl;
  glUniform3fv(uniform_loc, 1, &v[0]);
}

void shader::set_uniform(const std::string& name, glm::vec4 v) {
  GLint uniform_loc = glGetUniformLocation(shader_program, name.c_str());
  if(uniform_loc == -1)
    std::cout << "warning: uniform not found: " << name << std::endl;
  glUniform4fv(uniform_loc, 1, &v[0]);
}

void shader::set_uniform(const std::string& name, glm::mat4 m) {
  GLint uniform_loc = glGetUniformLocation(shader_program, name.c_str());
  if(uniform_loc == -1)
    std::cout << "warning: uniform not found: " << name << std::endl;
  glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, &m[0][0]);
}

void shader::set_uniform(const std::string& name, int i) {
  GLint uniform_loc = glGetUniformLocation(shader_program, name.c_str());
  if(uniform_loc == -1)
    std::cout << "warning: uniform not found: " << name << std::endl;
  glUniform1i(uniform_loc, i);
}

void shader::set_uniform(const std::string& name, float f) {
  GLint uniform_loc = glGetUniformLocation(shader_program, name.c_str());
  if(uniform_loc == -1)
    std::cout << "warning: uniform not found: " << name << std::endl;
  glUniform1f(uniform_loc, f);
}
