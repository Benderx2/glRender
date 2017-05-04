#include <iostream>
#include <render.h>

void monkey_predraw(mesh& msh, shader& shdr, texture& tex, transform& t);

display dp(640, 480, "glRender example");

int main(void) {
  dp.culling(true);

  camera cam(glm::vec3(0,0,3), glm::vec3(0,0,-1), glm::vec3(0,1,0), 70.0f, dp.get_aspect(), 0.01f, 1000.0f);

  gameobject monkey("obj_monkey");
  textrender text("data/glfont.png");
  shader shdr("shaders/shader3d", true);
  mesh msh("data/monkey.obj");
  texture tex("data/bricks.jpg");
  transform t;

  // Set Mesh, Shader, Texture, and Transformation for the model..
  monkey.set_property(msh);
  monkey.set_property(shdr);
  monkey.set_property(tex);
  monkey.set_property(t);

  // Also our "predraw" function which is called every frame before drawing...
  monkey.set_property(monkey_predraw);

  // Create a scene with 1 object
  scene monkey_scene(1);

  monkey_scene.add_camera(&cam);
  monkey_scene.add_object(&monkey);

  while(!dp.closed()) {
    dp.update();
    dp.clear(color::BLACK, 1.0f);

    // 3D Drawing Code goes here..
    monkey_scene.draw();

    engine_set_mode(dp, ENGINE_2D);

    text.render("Hello, World! FPS: " + std::to_string(dp.get_fps()), 0, 0, 2.0f);
    // Do not forget to reset to 3D! (or just see what happens if you dont)
    engine_set_mode(dp, ENGINE_3D);

    dp.swap();
  }
  return 0;
}

void monkey_predraw(mesh& msh, shader& shdr, texture& tex, transform& t) {
  t.get_rotation().x = sinf(dp.ticks() / 1000.0f);
  t.get_rotation().y = sinf(dp.ticks() / 1000.0f);
  t.get_rotation().z = (dp.ticks() / 1000.0f);
  shdr.set_uniform("lightdir", glm::vec3(0,0,1));
}
