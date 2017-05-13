#include <primitives.h>
#include <render_type.h>
#include <iostream>

Primitive::Primitive(primitive_type ptype) {
  type = ptype;
  switch(ptype) {
    case PRIMITIVE_CUBE:
      CreateCube();
      break;
    case PRIMITIVE_SPHERE:
      CreateSphere();
      break;
    case PRIMITIVE_FLOOR:
      CreateFloor();
      break;
    case PRIMITIVE_CUSTOM:
      break;
    default:
      std::cout << "warning: unknown primitive type passed. returning null primitive." << std::endl;
      break;
  }
}
// Create floor primitive
void Primitive::CreateFloor(void) {
  Vertex vertices[] = {
    Vertex(vector3(1.0f, 0.0f, 1.0f), glm::vec2(0, 1), vector3(0.0f, -1.0f, 0.0f)),
    Vertex(vector3(-1.0f, 0.0f, 1.0f), glm::vec2(0, 0), vector3(0.0f, -1.0f, 0.0f)),
    Vertex(vector3(-1.0f, 0.0f, -1.0f), glm::vec2(1, 0), vector3(0.0f, -1.0f, 0.0f)),
    Vertex(vector3(1.0f, 0.0f, -1.0f), glm::vec2(1, 1), vector3(0.0f, -1.0f, 0.0f))
  };
  unsigned int indices[] = {
    0, 1, 2, 3
  };
  primitive_mesh = new Mesh(&vertices[0], 4, &indices[0], 4, GL_QUADS);
}
// Create a sphere primitive
void Primitive::CreateSphere(void) {
  // Sphere Primitive, thanks to darkenwolf for the implementation
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;

  float radius = 1.0f;
  float rings = 12;
  float sectors = 24;
  float const R = 1./(float)(rings-1);
  float const S = 1./(float)(sectors-1);
  int r, s;
  for(r = 0; r < rings; r++) {
    for(s = 0; s < sectors; s++) {

      float const y = sin(-M_PI_2 + M_PI * r * R);
      float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
      float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

      Vertex v;
      v.pos.x = x*radius;
      v.pos.y = y*radius;
      v.pos.z = z*radius;

      v.normal.x = -x;
      v.normal.y = -y;
      v.normal.z = -z;

      v.texcord.x = s*S;
      v.texcord.y = r*R;
      vertices.push_back(v);
    }
  }
  for(r = 0; r < rings-1; r++) {
    for(s = 0; s < sectors - 1; s++) {
      indices.push_back(r * sectors + s);
      indices.push_back(r * sectors + (s+1));
      indices.push_back((r+1) * sectors + (s + 1));
      indices.push_back((r+1)* sectors + s);
    }
  }
  primitive_mesh =  new Mesh(&vertices[0], vertices.size(), &indices[0], indices.size(), GL_QUADS);
}
// Create cube primitive
void Primitive::CreateCube(void) {
  // Cube Primitive
  Vertex* vp = new Vertex[8];

  vp[0].pos = vector3(-1, -1, 1);
  vp[0].normal = vector3(-1, -1, 1);
  vp[0].texcord = glm::vec2(0, 0);

  vp[1].pos = vector3(1, -1, 1);
  vp[1].normal = vector3(1, -1, 1);
  vp[1].texcord = glm::vec2(1, 0);

  vp[2].pos = vector3(-1, 1, 1);
  vp[2].normal = vector3(-1, 1, 1);
  vp[2].texcord = glm::vec2(0, 1);

  vp[3].pos = vector3(1, 1, 1);
  vp[3].normal = vector3(1, 1, 1);
  vp[3].texcord = glm::vec2(1, 1);

  vp[5].pos = vector3(1, -1, -1);
  vp[5].normal = vector3(1, -1, -1);
  vp[5].texcord = glm::vec2(0, 0);

  vp[6].pos = vector3(-1, 1, -1);
  vp[6].normal = vector3(-1, 1, -1);
  vp[6].texcord = glm::vec2(1, 1);

  vp[7].pos = vector3(1, 1, -1);
  vp[7].normal = vector3(1, 1, -1);
  vp[7].texcord = glm::vec2(0, 1);

  unsigned int indices[] = {
    0, 1, 3, 2,
    1, 5, 7, 3,
    5, 4, 6, 7,
    4, 0, 2, 6,
    4, 5, 1, 0,
    2, 3, 7, 6
  };

  primitive_mesh = new Mesh(vp, 8, indices, sizeof(indices), GL_QUADS);
}
// The below functions are designed to build primitives directly from code,
// as loading data from a model might be costly as well as unavailable on systems with
// no proper filesystems.
void Primitive::MapVertex(vector3 v) {
  if(type != PRIMITIVE_CUSTOM) {
    std::cerr << "error: attempt to map vertex to a non-custom primitive! ignoring..." << std::endl;
    return;
  }
  custom_vertices.push_back(v);
}

void Primitive::MapTexCoord(glm::vec2 v) {
  if(type != PRIMITIVE_CUSTOM) {
    std::cerr << "error: attempt to map texcoord to a non-custom primitive! ignoring..." << std::endl;
    return;
  }
  custom_texcoords.push_back(v);
}

void Primitive::MapFace(unsigned int i1, unsigned int i2, unsigned int i3) {
  if(type != PRIMITIVE_CUSTOM) {
    std::cerr << "error: attempt to map face to a non-custom primitive! ignoring..." << std::endl;
    return;
  }
  custom_indices.push_back(i1);
  custom_indices.push_back(i2);
  custom_indices.push_back(i3);
}

void Primitive::MapNormal(vector3 n) {
  if(type != PRIMITIVE_CUSTOM) {
    std::cerr << "error: attempt to map normal to a non-custom primitive! ignoring..." << std::endl;
    return;
  }
  custom_normals.push_back(n);
}

// Convert all data to mesh data
void Primitive::BuildMesh() {
  if(type != PRIMITIVE_CUSTOM) {
    std::cerr << "error: cannot build mesh for a non-custom primitive! ignoring..." << std::endl;
    return;
  }
  if(custom_vertices.size() != custom_texcoords.size()) {
    std::cout << "warning: not all vertices are mapped to a texcoord!" << std::endl;
  }
  if(custom_vertices.size() != custom_normals.size()) {
    std::cout << "warning: not all vertices have a normal!" << std::endl;
  }
  std::vector<Vertex> mesh_vertices;
  for(unsigned int i = 0; i < custom_vertices.size(); i++) {
    Vertex v;

    v.pos = custom_vertices[i];

    if(i < custom_texcoords.size())
      v.texcord = custom_texcoords[i];
    else
      v.texcord = glm::vec2(0.0f, 0.0f);

    if(i < custom_normals.size())
      v.normal = custom_normals[i];
    else
      v.normal = vector3(0.0f, 0.0f, 0.0f);

    mesh_vertices.push_back(v);
  }
  primitive_mesh = new Mesh(&mesh_vertices[0], mesh_vertices.size(), &custom_indices[0], custom_indices.size(), GL_TRIANGLES);
}
// Destructor
Primitive::~Primitive() {
  delete primitive_mesh;
}
