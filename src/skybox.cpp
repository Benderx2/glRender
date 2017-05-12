#include <skybox.h>
#include <iostream>
#include <shader_attribute.h>

skybox::skybox(const std::string& shader_file, const std::string& f1, const std::string& f2, const std::string& f3, const std::string& f4, const std::string& f5, const std::string& f6, float scl) {

  scale = scl;

  skybox_shader = new shader(shader_file, true);
  skybox_cubemap = new texture(f1, f2, f3, f4, f5, f6);

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);

  float skybox_vertices[] = {
    // Positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
   };

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertices), &skybox_vertices, GL_STATIC_DRAW);
   glEnableVertexAttribArray(ATTRIBUTE_POSITION);
   glVertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
   glBindVertexArray(0);

}

void skybox::draw(camera cam) {
  // Identity transformation
  transform t;
  t.get_scale() = glm::vec3(scale, scale, scale);
  skybox_shader->bind();
  skybox_shader->update(t, cam);
  skybox_cubemap->bind(0);
  glDepthMask(GL_FALSE);
  glBindVertexArray(VAO);
  glUniform1i(glGetUniformLocation(skybox_shader->get_shader_program(), "skybox"), 0);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
  glDepthMask(GL_TRUE);
}
