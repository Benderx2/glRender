#include <iostream>
#include <vector>
#include <mesh.h>
#include <shader_attribute.h>

Mesh::Mesh(Vertex* vp, unsigned int vcount, unsigned int* idx, unsigned int nidx, GLenum m) {
  IndexedModel model;
  for(unsigned int i = 0; i < vcount; i++) {
    model.positions.push_back(*vp[i].GetPos());
    model.texCoords.push_back(*vp[i].GetTexCoord());
    model.normals.push_back(*vp[i].GetNormal());
  }
  for(unsigned int i = 0; i < nidx; i++) {
    model.indices.push_back(idx[i]);
  }
  mode = m;
  InitMesh(model);
}

Mesh::Mesh(const std::string& name, model_type mtype) {
  type = mtype;
  mode = GL_TRIANGLES;

  std::cout << "Loading mesh: '" << name << "' ..." << std::endl;

  if(mtype == MESH_OBJ) {
    InitMesh(OBJModel(name).ToIndexedModel());
  } else if(mtype == MESH_MD2) {
    md2_loader = new MD2Loader(name);
  }

  mesh_name = name;
}

Mesh::Mesh() {
  //
}

Mesh::~Mesh(void) {
  glDeleteBuffers(N_BUFFERS, vertex_buffers);
  glDeleteVertexArrays(1, &vertex_buffer_object);
  if(md2_loader)
    delete md2_loader;
}

void Mesh::Draw(void) {
  // Quake2 uses counter-clockwise faces
  if(type == MESH_MD2)
    glCullFace(GL_FRONT);

  glBindVertexArray(vertex_buffer_object);
  glDrawElements(mode, vb_drawcount, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  if(type == MESH_MD2)
    glCullFace(GL_BACK);

  //std::cout << "Drawing mesh: " << mesh_name << std::endl;
}

void Mesh::SetFrame(int n) {
  if(type != MESH_MD2)
    return;

  current_frame = n;
  MD2Model model = md2_loader->GetFrameData(n);
  UpdateVertexData(&model.vertices[0], model.vertices.size(), &model.indices[0], model.indices.size(), mode);
}
// MD2 Animation
void Mesh::SetFrameInterpolation(int n, int n2, float interp) {
  if(type != MESH_MD2)
    return;

  if((n < 0) || (n > md2_loader->GetHeader()->n_frames))
    return;


  MD2Model model = md2_loader->GetFrameData(n);
  MD2Model next_model = md2_loader->GetFrameData(n2);

  for(int i = 0; i < model.vertices.size(); i++) {
    // Interpolate vertices and normals
    model.vertices[i].pos.x = model.vertices[i].pos.x + interp * (next_model.vertices[i].pos.x - model.vertices[i].pos.x);
    model.vertices[i].pos.y = model.vertices[i].pos.y + interp * (next_model.vertices[i].pos.y - model.vertices[i].pos.y);
    model.vertices[i].pos.z = model.vertices[i].pos.z + interp * (next_model.vertices[i].pos.z - model.vertices[i].pos.z);

    model.vertices[i].normal.x = model.vertices[i].normal.x + interp * (next_model.vertices[i].normal.x - model.vertices[i].normal.x);
    model.vertices[i].normal.y = model.vertices[i].normal.y + interp * (next_model.vertices[i].normal.y - model.vertices[i].normal.y);
    model.vertices[i].normal.z = model.vertices[i].normal.z + interp * (next_model.vertices[i].normal.z - model.vertices[i].normal.z);
  }
  UpdateVertexData(&model.vertices[0], model.vertices.size(), &model.indices[0], model.indices.size(), mode);
}

// Returns 1 if end is reached, 0 if not reached
int Mesh::Animate(int start, int end, float* interp) {
  int retval = 0;

  if(type != MESH_MD2)
    return retval;

  if(current_frame < start || current_frame > end) {
    current_frame = start;
    next_frame = current_frame + 1;
  }

  if(*interp >= 1.0f) {
    *interp = 0.0f;
    if(current_frame <= end)
      current_frame++;

    if(next_frame == start) {
      current_frame = start;
      next_frame = current_frame + 1;
    }

    if(current_frame <= end)
      next_frame = current_frame + 1;
  }
  // For smooth transition between last and first framestart
  if(current_frame >= end) {
    next_frame = start;
    // We reached last frame, now tell the caller exactly that.
    retval = 1;
  }

  SetFrameInterpolation(current_frame, next_frame, *interp);
  return retval;
}

// These must be called every cycle
int Mesh::CycleAnimation(void) {
  if(type != MESH_MD2)
    return 0;

  then = now;
  now = (float)clock() / CLOCKS_PER_SEC;
  interpolation += anim_speed * (now - then);
  return Animate(current_anim.start, current_anim.end, &interpolation);
}
// Preferred to call this before, not every cycle as it uses string functions
void Mesh::SetAnimation(const std::string& anim_name) {
  if(type != MESH_MD2)
    return;

  MD2Anim new_anim = md2_loader->GetAnimationData(anim_name);
  current_anim.start = new_anim.start;
  current_anim.end = new_anim.end;
  current_anim.name = new_anim.name;
  SetFrame(current_anim.start);
}

void Mesh::UpdateVertexData(Vertex* vp, unsigned int vcount, unsigned int* idx, unsigned int nidx, GLenum m) {
  // Delete old buffers
  glDeleteBuffers(N_BUFFERS, vertex_buffers);
  glDeleteVertexArrays(1, &vertex_buffer_object);

  // Create a new buffer with the updated vertex data
  IndexedModel model;
  for(unsigned int i = 0; i < vcount; i++) {
    model.positions.push_back(*vp[i].GetPos());
    model.texCoords.push_back(*vp[i].GetTexCoord());
    model.normals.push_back(*vp[i].GetNormal());
  }
  for(unsigned int i = 0; i < nidx; i++) {
    model.indices.push_back(idx[i]);
  }
  mode = m;
  InitMesh(model);
}

void Mesh::InitMesh(const IndexedModel& model) {
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
