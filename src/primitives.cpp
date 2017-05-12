#include <primitives.h>
#include <iostream>

primitive::primitive(primitive_type ptype) {
  type = ptype;
  switch(ptype) {
    case PRIMITIVE_CUBE:
      create_cube();
      break;
    case PRIMITIVE_SPHERE:
      create_sphere();
      break;
    case PRIMITIVE_FLOOR:
      create_floor();
      break;
    case PRIMITIVE_CUSTOM:
      break;
    default:
      std::cout << "warning: unknown primitive type passed. returning null primitive." << std::endl;
      break;
  }
}
// Create floor primitive
void primitive::create_floor(void) {
  vertex vertices[] = {
    vertex(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0, 1), glm::vec3(0.0f, -1.0f, 0.0f)),
    vertex(glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec2(0, 0), glm::vec3(0.0f, -1.0f, 0.0f)),
    vertex(glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec2(1, 0), glm::vec3(0.0f, -1.0f, 0.0f)),
    vertex(glm::vec3(1.0f, 0.0f, -1.0f), glm::vec2(1, 1), glm::vec3(0.0f, -1.0f, 0.0f))
  };
  unsigned int indices[] = {
    0, 1, 2, 3
  };
  primitive_mesh = new mesh(&vertices[0], 4, &indices[0], 4, GL_QUADS);
}
// Create a sphere primitive
void primitive::create_sphere(void) {
  // Sphere Primitive, thanks to darkenwolf for the implementation
  std::vector<vertex> vertices;
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

      vertex v;
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
  primitive_mesh =  new mesh(&vertices[0], vertices.size(), &indices[0], indices.size(), GL_QUADS);
}
// Create cube primitive
void primitive::create_cube(void) {
  // Cube Primitive
  vertex* vp = new vertex[8];

  vp[0].pos = glm::vec3(-1, -1, 1);
  vp[0].normal = glm::vec3(-1, -1, 1);
  vp[0].texcord = glm::vec2(0, 0);

  vp[1].pos = glm::vec3(1, -1, 1);
  vp[1].normal = glm::vec3(1, -1, 1);
  vp[1].texcord = glm::vec2(1, 0);

  vp[2].pos = glm::vec3(-1, 1, 1);
  vp[2].normal = glm::vec3(-1, 1, 1);
  vp[2].texcord = glm::vec2(0, 1);

  vp[3].pos = glm::vec3(1, 1, 1);
  vp[3].normal = glm::vec3(1, 1, 1);
  vp[3].texcord = glm::vec2(1, 1);

  vp[5].pos = glm::vec3(1, -1, -1);
  vp[5].normal = glm::vec3(1, -1, -1);
  vp[5].texcord = glm::vec2(0, 0);

  vp[6].pos = glm::vec3(-1, 1, -1);
  vp[6].normal = glm::vec3(-1, 1, -1);
  vp[6].texcord = glm::vec2(1, 1);

  vp[7].pos = glm::vec3(1, 1, -1);
  vp[7].normal = glm::vec3(1, 1, -1);
  vp[7].texcord = glm::vec2(0, 1);

  unsigned int indices[] = {
    0, 1, 3, 2,
    1, 5, 7, 3,
    5, 4, 6, 7,
    4, 0, 2, 6,
    4, 5, 1, 0,
    2, 3, 7, 6
  };

  primitive_mesh = new mesh(vp, 8, indices, sizeof(indices), GL_QUADS);
}
// The below functions are designed to build primitives directly from code,
// as loading data from a model might be costly as well as unavailable on systems with
// no proper filesystems.
void primitive::map_vertex(glm::vec3 v) {
  if(type != PRIMITIVE_CUSTOM) {
    std::cerr << "error: attempt to map vertex to a non-custom primitive! ignoring..." << std::endl;
    return;
  }
  custom_vertices.push_back(v);
}

void primitive::map_texcoord(glm::vec2 v) {
  if(type != PRIMITIVE_CUSTOM) {
    std::cerr << "error: attempt to map texcoord to a non-custom primitive! ignoring..." << std::endl;
    return;
  }
  custom_texcoords.push_back(v);
}

void primitive::map_face(unsigned int i1, unsigned int i2, unsigned int i3) {
  if(type != PRIMITIVE_CUSTOM) {
    std::cerr << "error: attempt to map face to a non-custom primitive! ignoring..." << std::endl;
    return;
  }
  custom_indices.push_back(i1);
  custom_indices.push_back(i2);
  custom_indices.push_back(i3);
}

void primitive::map_normal(glm::vec3 n) {
  if(type != PRIMITIVE_CUSTOM) {
    std::cerr << "error: attempt to map normal to a non-custom primitive! ignoring..." << std::endl;
    return;
  }
  custom_normals.push_back(n);
}

// Convert all data to mesh data
void primitive::build_mesh() {
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
  std::vector<vertex> mesh_vertices;
  for(unsigned int i = 0; i < custom_vertices.size(); i++) {
    vertex v;

    v.pos = custom_vertices[i];

    if(i < custom_texcoords.size())
      v.texcord = custom_texcoords[i];
    else
      v.texcord = glm::vec2(0.0f, 0.0f);

    if(i < custom_normals.size())
      v.normal = custom_normals[i];
    else
      v.normal = glm::vec3(0.0f, 0.0f, 0.0f);

    mesh_vertices.push_back(v);
  }
  primitive_mesh = new mesh(&mesh_vertices[0], mesh_vertices.size(), &custom_indices[0], custom_indices.size(), GL_TRIANGLES);
}
// Destructor
primitive::~primitive() {
  delete primitive_mesh;
}
