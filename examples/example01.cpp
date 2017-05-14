#include <iostream>
#include <render.h>

void predraw(Mesh* msh, Shader* shdr, Texture* tex, Transform* t);

void controller_process(Scene* s, controller_key k, float x, float y);

bool start_rendering = false;

int main(void) {

  Display screen(640, 480, "glRender example");

  screen.Culling(true);
  screen.SetMouse(screen.GetWidth()/2, screen.GetHeight()/2);

  Camera cam(vector3(0,0,3), vector3(0,0,-1), vector3(0,1,0), 70.0f, screen.GetAspect(), 0.01f, 1000.0f);

  // Our glrender logo
  Texture tex_logo("data/glrender.png");
  // Load up a basic textrenderer
  TextRender text("data/glfont.png");

  // Create gameobject called "obj_terrain"
  // Set Mesh, Shader, Texture, and Transformation for the model..
  // Also our "predraw" function which is called every frame before drawing..
  GameObject terrain("obj_terrain", new Mesh("data/terrain.obj", MESH_OBJ), new Texture("data/grass.jpg"), new Shader("shaders/shader_lambert", true), new Transform(), predraw);
  GameObject knight("obj_knight", new Mesh("data/knight.md2", MESH_MD2), new Texture("data/knight.jpg"), new Shader("shaders/shader_basic", true), new Transform(), NULL);

  knight.GetMesh()->SetFrame(0);
  knight.GetTransform()->SetScale(0.01f, 0.01f, 0.01f);
  knight.GetTransform()->SetTranslation(0.0f, 0.0f, 2.2f);
  knight.GetTransform()->SetRotation(-1.6f, -0.5f, 0.0f);

  terrain.GetTransform()->SetScale(0.5f, 0.5f, 0.5f);
  terrain.GetTransform()->SetTranslation(0.0f, -0.5f, 1.0f);
  // Create skybox
  Skybox sky("shaders/shader_sky", "data/sky/siege_rt.tga", "data/sky/siege_lf.tga", "data/sky/siege_up.tga", "data/sky/siege_dn.tga", "data/sky/siege_bk.tga", "data/sky/siege_ft.tga", 10.0f);
  // Create a scene with 1 object
  Scene my_scene(2);
  // Add the camera and the only object and the skybox
  my_scene.AddCamera(&cam);
  my_scene.AddObject(&knight);
  my_scene.AddObject(&terrain);
  my_scene.AddSky(&sky);
  // Create a controller for the scene
  Controller sample_controller(&my_scene);
  // Set our callback
  sample_controller.SetCallBack(controller_process);
  // Finally register the controller
  screen.RegisterController(&sample_controller);

  while(!screen.Closed()) {

    // Update our display module
    screen.Update();

    // Clear the screen
    screen.Clear(Color::BLUE, 1.0f);
    // 3D Drawing Code goes here..
    // Draw our scene
    if(start_rendering == true) {
      // Cycle between 0 and 35 frames
      knight.GetMesh()->SetAnimationSpeed(60);
      knight.GetMesh()->CycleAnimation(0, 100);
      my_scene.Draw();
    }
    // Switch to 2D rendering mode now
    EngineSetMode(screen, ENGINE_2D);
    // 2D Drawing Code goes here...
    if(start_rendering == false)
      text.Render("Press Z to start rendering. Use arrow keys to rotate.", 150, 200, 1.0f);
    else
      text.Render("FPS: " + std::to_string(screen.GetFPS()), 0, 0, 1.0f);
    // Render our logo!
    tex_logo.DrawBlock(screen.GetWidth() - 64, screen.GetHeight() - 64, 64, 64);
    // Do not forget to reset to 3D! (or just see what happens if you dont)
    EngineSetMode(screen, ENGINE_3D);
    // Finally, flush the output.
    screen.Flush();
  }
  return 0;
}

void predraw(Mesh* msh, Shader* shdr, Texture* tex, Transform* t) {
  // Set our lightdir vector in our shader
  shdr->SetUniform("lightdir", vector3(0,-1,0));
}

void controller_process(Scene* s, controller_key k, float x, float y) {
  GameObject* obj01 = s->GetObjectPointer("obj_knight");
  if(k == CONTROLLER_LEFT) {
    obj01->GetTransform()->GetRotation().y -= 0.1f;
  }
  if(k == CONTROLLER_RIGHT) {
    obj01->GetTransform()->GetRotation().y += 0.1f;
  }
  if(k == CONTROLLER_UP) {
    obj01->GetTransform()->GetRotation().x -= 0.1f;
  }
  if(k == CONTROLLER_DOWN) {
    obj01->GetTransform()->GetRotation().x += 0.1f;
  }
  if(k == CONTROLLER_Z) {
    start_rendering = true;
  }
}
