#ifndef plot_h
#define plot_h

#include <vector>
#include <render_type.h>

class Plot {
  Plot(const std::string& function, vector2& min, vector2& max, vector2& step);

private:
  // Vertices (as quads)
  std::vector<vector3> v;
  int grid_w;
  int grid_h;
};

#endif
