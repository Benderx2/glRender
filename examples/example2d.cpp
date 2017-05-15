#include <render.h>

// Rendering a 2D Sprite Animation in glRender
int main(void) {
  Display screen(640, 480, "glRender sprite example");
  Texture sprite_sheet("data/sprites.png", 256, 256, 6);

  screen.Culling(true);
  int current_frame = 0;
  int max_frames = 6;
  // Get time in 1/10th of a second.
  double now = screen.Ticks() / 100.0f;
  double then = 0;
  while(!screen.Closed()) {
    screen.Clear(Color::BLACK, 1.0f);
    screen.Update();
    EngineSetMode(screen, ENGINE_2D);
    sprite_sheet.DrawBlock(100, 100, 256, 256, current_frame);
    now = screen.Ticks() / 100.0f;
    if(now - then >= 1.0f) {
    // every 1/10th of a second
      current_frame += 1;
      then = now;
    }

    if(current_frame >= max_frames) current_frame = 0;
    EngineSetMode(screen, ENGINE_3D);
    screen.Flush();
  }
}
