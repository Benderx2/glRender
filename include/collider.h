#ifndef collider_h
#define collider_h

// 3D Collision Detection, very basic for now
#include <render_type.h>
#include <transform.h>

class BoxCollider {

public:
  inline BoxCollider(vector3 pos, float lx, float ly, float lz) {
    center = pos;
    half_lx = lx/2.0f;
    half_ly = ly/2.0f;
    half_lz = lz/2.0f;
  }

  inline void ApplyTransform(Transform& t) {
    center = vector3(vector4(center, 1.0f) * t.GetMatrix());
    half_lx = half_lx * t.GetScale().x;
    half_ly = half_ly * t.GetScale().y;
    half_lz = half_lz * t.GetScale().z;
  }


  inline bool IsCollision(BoxCollider& a) {
    BoxCollider b = *this;
    // Difference of center X > the minimum distance between their centers?, then no collision
    if(abs(a.center.x - b.center.x) > (a.half_lx + b.half_lx)) return false;
    if(abs(a.center.y - b.center.y) > (a.half_ly + b.half_ly)) return false;
    if(abs(a.center.z - b.center.z) > (a.half_lz + b.half_lz)) return false;
    return true;
  }

  vector3 center;
  float half_lx, half_ly, half_lz;
};
#endif
