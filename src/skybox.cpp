#include <skybox.h>
#include <iostream>
#include <shader_attribute.h>

Skybox::Skybox(const std::string& shader_file, const std::string& f1, const std::string& f2, const std::string& f3, const std::string& f4, const std::string& f5, const std::string& f6, float scl) {

  scale = scl;

  skybox_shader = new Shader(shader_file, true);
  skybox_cubemap = new Texture(f1, f2, f3, f4, f5, f6);

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

void Skybox::Draw(Camera& cam) {
  // Identity transformation
  Transform t;
  t.GetScale() = vector3(scale, scale, scale);
  // Bind our skybox shader and update it with the transform and camera
  skybox_shader->Bind();
  skybox_shader->Update(t, cam);
  skybox_cubemap->Bind(0);
  // Disable depth masking for now
  glDepthMask(GL_FALSE);
  // Finally draw our skybox
  glBindVertexArray(VAO);
  skybox_shader->SetUniform("skybox", 0);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  // unbind vertex array
  glBindVertexArray(0);
  glDepthMask(GL_TRUE);
}

Skybox::~Skybox() {
  delete skybox_shader;
  delete skybox_cubemap;
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
}
