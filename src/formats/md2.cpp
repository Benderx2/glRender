#include <formats/md2.h>
#include <stdio_nowarn.h>

vector3 md2_normals_table[162] {
  #include "md2_normals.h"
};

MD2Loader::MD2Loader(const std::string& file) {
  FILE* fp;
  std::cout << "Loading MD2 file: " << file << std::endl;

  fp = fopen(file.c_str(), "rb");
  if(fp == NULL) {
    std::cout << "-- unable to open file for reading" << std::endl;
    return;
  }
  fread_nowarn(&header, 1, sizeof(md2_header_t), fp);
  if(header.magic != 844121161 || header.version != 8) {
    std::cout << "-- bad header or version" << std::endl;
  }

  skins = new md2_skin_t[header.n_skins];
  texcoords = new md2_texcoord_t[header.n_texcoords];
  frames = new md2_frame_t[header.n_frames];
  triangles = new md2_triangle_t[header.n_triangles];
  glcmds = new u32[header.n_glcmds];

  // Read skins
  fseek(fp, header.skins_ptr, SEEK_SET);
  fread_nowarn(skins, sizeof(md2_skin_t), header.n_skins, fp);
  // Read texcoords
  fseek(fp, header.texcoords_ptr, SEEK_SET);
  fread_nowarn(texcoords, sizeof(md2_texcoord_t), header.n_texcoords, fp);
  // Read triangles
  fseek(fp, header.triangles_ptr, SEEK_SET);
  fread_nowarn(triangles, sizeof(md2_triangle_t), header.n_triangles, fp);
  // Read Frames
  fseek(fp, header.frames_ptr, SEEK_SET);
  for(int i = 0; i < header.n_frames; i++) {
    frames[i].vertices = new md2_vertex_t[header.n_vertices];
    fread_nowarn(frames[i].scale, sizeof(md2_vec3_t), 1, fp);
    fread_nowarn(frames[i].translate, sizeof(md2_vec3_t), 1, fp);
    fread_nowarn(frames[i].name, sizeof(i8), 16, fp);
    fread_nowarn(frames[i].vertices, sizeof(md2_vertex_t), header.n_vertices, fp);
    //std::cout << "-- read frame: '" << frames[i].name << "'" << std::endl;
  }
  // Read glcmds
  fseek(fp, header.glcmds_ptr, SEEK_SET);
  fread_nowarn(glcmds, sizeof(u32), header.n_glcmds, fp);
  // free file pointer
  fclose(fp);
}

MD2Model MD2Loader::GetFrameData(int n) {
  float s, t;

  MD2Model model;

  md2_frame_t* current_frame = NULL;
  md2_vertex_t* current_vertex = NULL;

  if(n < 0 || n >= header.n_vertices)
    return model;

  for(int i = 0; i < header.n_triangles; i++) {
    for(int j = 0; j < 3; j++) {
      current_frame = &frames[n];
      // The current vertex is obtained by accessing the current frame's vertices, which
      // is accessed by obtaining the vertex index from the current triangle being drawn
      current_vertex = &current_frame->vertices[triangles[i].vertex_indices[j]];
      // texture coordinates
      s = (float)texcoords[triangles[i].texcoord_indices[j]].s / (float)header.skin_w;
      t = (float)texcoords[triangles[i].texcoord_indices[j]].t / (float)header.skin_h;
      model.vertices.push_back(Vertex(
        vector3(
          current_frame->scale[0] * current_vertex->v[0] + current_frame->translate[0],
          current_frame->scale[1] * current_vertex->v[1] + current_frame->translate[1],
          current_frame->scale[2] * current_vertex->v[2] + current_frame->translate[2]
        ),
        vector2(s, t),
        md2_normals_table[current_vertex->normal_index]
        )
      );
      model.indices.push_back(i * 3 + j);
    }
  }
  return model;
}
MD2Loader::~MD2Loader() {
  for(int i = 0; i < header.n_frames; i++) {
    delete frames[i].vertices;
  }
  delete frames;
  delete triangles;
  delete glcmds;
  delete texcoords;
  delete skins;
}
