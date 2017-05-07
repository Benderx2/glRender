#include <primitives.h>

primitive::primitive(primitive_type ptype) {
  if(ptype == PRIMITIVE_CUBE) {
    // Cube Primitive

    // I wanna fucking copyright this code, spent at least an hour on figuring the vertices, draw order,
    // and normals out.
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

    vp[4].pos = glm::vec3(-1, -1, -1);
    vp[4].normal = glm::vec3(-1, -1, -1);
    vp[4].texcord = glm::vec2(1, 0);

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

  } else if(ptype == PRIMITIVE_SPHERE) {

    // Sphere Primitive, thanks to daktenwolf for the implementation
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
  } else if(ptype == PRIMITIVE_CONE) {

  }
}

primitive::~primitive() {

}
