#include <iostream>
#include <render.h>

void monkey_predraw(mesh& msh, shader& shdr, texture& tex, transform& t);

void controller_process(scene* s, controller_key k, float x, float y);

bool start_rendering = false;

int main(void) {

  display screen(640, 480, "glRender example");

  screen.culling(true);

  camera cam(glm::vec3(0,0,3), glm::vec3(0,0,-1), glm::vec3(0,1,0), 70.0f, screen.get_aspect(), 0.01f, 1000.0f);

  // Create gameobject called "obj_monkey"
  gameobject monkey("obj_monkey");
  // Shader, mesh, transformation and texture objects for our monkey
  shader shdr("shaders/shader3d", true);
  mesh msh("data/monkey.obj");
  texture tex("data/bricks.jpg");
  transform t;
  // Our glrender logo
  texture tex02("data/glrender.png");
  // Load up a basic textrenderer
  textrender text("data/glfont.png");

  // Set Mesh, Shader, Texture, and Transformation for the model..
  monkey.set_property(msh);
  monkey.set_property(shdr);
  monkey.set_property(tex);
  monkey.set_property(t);

  // Also our "predraw" function which is called every frame before drawing...
  monkey.set_property(monkey_predraw);

  // Create a scene with 1 object
  scene monkey_scene(1);
  // Add the camera and the only object
  monkey_scene.add_camera(&cam);
  monkey_scene.add_object(&monkey);

  // Create a controller for the scene
  controller sample_controller(&monkey_scene);
  // Set our callback
  sample_controller.set_callback(controller_process);
  // Finally register the controller
  screen.register_controller(&sample_controller);

  while(!screen.closed()) {
    // Update our display module
    screen.update();

    // Clear the screen
    screen.clear(color::BLACK, 1.0f);

    // 3D Drawing Code goes here..
    // Draw our scene
    if(start_rendering == true)
      monkey_scene.draw();
    // Switch to 2D rendering mode now
    engine_set_mode(screen, ENGINE_2D);
    // 2D Drawing Code goes here...
    if(start_rendering == false)
      text.render("Press Z to start rendering. Use arrow keys to rotate.", 150, 200, 1.0f);
    else
      text.render("FPS: " + std::to_string(screen.get_fps()), 0, 0, 1.0f);
    // Render our logo!
    tex02.draw_block(screen.get_width() - 64, screen.get_height() - 64, 64, 64);
    // Do not forget to reset to 3D! (or just see what happens if you dont)
    engine_set_mode(screen, ENGINE_3D);
    // Finally, flush the output.
    screen.flush();
  }
  return 0;
}

void monkey_predraw(mesh& msh, shader& shdr, texture& tex, transform& t) {
  shdr.set_uniform("lightdir", glm::vec3(0,0,1));
}

void controller_process(scene* s, controller_key k, float x, float y) {
  gameobject* obj_monkey = (*s).get_object_ptr("obj_monkey");
  if(k == CONTROLLER_LEFT) {
    obj_monkey->get_transform().get_rotation().y -= 0.1f;
  }
  if(k == CONTROLLER_RIGHT) {
    obj_monkey->get_transform().get_rotation().y += 0.1f;
  }
  if(k == CONTROLLER_UP) {
    obj_monkey->get_transform().get_rotation().x -= 0.1f;
  }
  if(k == CONTROLLER_DOWN) {
    obj_monkey->get_transform().get_rotation().x += 0.1f;
  }
  if(k == CONTROLLER_Z) {
    start_rendering = true;
  }
}
