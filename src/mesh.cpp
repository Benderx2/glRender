#include <iostream>
#include <vector>
#include <mesh.h>
#include <shader_attribute.h>

mesh::mesh(vertex* vp, unsigned int vcount, unsigned int* idx, unsigned int nidx, GLenum m) {
  IndexedModel model;
  for(unsigned int i = 0; i < vcount; i++) {
    model.positions.push_back(*vp[i].get_pos());
    model.texCoords.push_back(*vp[i].get_texcord());
    model.normals.push_back(*vp[i].get_normal());
  }
  for(unsigned int i = 0; i < nidx; i++) {
    model.indices.push_back(idx[i]);
  }
  mode = m;
  init_mesh(model);
}

mesh::mesh(const std::string& name) {
  std::cout << "Loading mesh: '" << name << "' ..." << std::endl;
  mode = GL_TRIANGLES;
  init_mesh(OBJModel(name).ToIndexedModel());
  mesh_name = name;
}

mesh::mesh() {
  //
}

mesh::~mesh(void) {
  glDeleteBuffers(N_BUFFERS, vertex_buffers);
  glDeleteVertexArrays(1, &vertex_buffer_object);
}

void mesh::draw(void) {
  glBindVertexArray(vertex_buffer_object);
  glDrawElements(mode, vb_drawcount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  //std::cout << "Drawing mesh: " << mesh_name << std::endl;
}

void mesh::init_mesh(const IndexedModel& model) {
  vb_drawcount = model.indices.size();
  // Create 1 VBO object
  glGenVertexArrays(1, &vertex_buffer_object);
  // Bind the Array
  glBindVertexArray(vertex_buffer_object);
  // Generate buffer
  glGenBuffers(N_BUFFERS, vertex_buffers);
  // Send data to GPU
  // First the vertex buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW); // GL_STATIC_DRAW = Read-Only data
  glEnableVertexAttribArray(ATTRIBUTE_POSITION); // Attribute 0 = This Vertex Array (see shader.cpp where the literal 'position' is set to point to this attribute)
  glVertexAttribPointer(ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
  // ^ (Attribute 0, 3 pieces of data, floating point, do not normalize, do not skip any entries, start at 0)
  // Now the texture coordinates
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[TEXCORD_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.texCoords.size()*sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
  // Attribute 1: Texture coordintes
  glEnableVertexAttribArray(ATTRIBUTE_TEXCORD);
  glVertexAttribPointer(ATTRIBUTE_TEXCORD, 2, GL_FLOAT, GL_FALSE, 0, 0);
  // Now the normals
  // Attribute 2: normals
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[NORMAL_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.normals.size()*sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW); // GL_STATIC_DRAW = Read-Only data
  glVertexAttribPointer(ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(ATTRIBUTE_NORMAL);
  // And now the index buffer, which specifies the order in which to draw the vertices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_buffers[INDEX_VB]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size()*sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);
  // Reset
  glBindVertexArray(0);
}
