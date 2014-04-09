#include "engine/common.h"
#include "engine/scene.hpp"
#include "engine/camera.hpp"
#include "engine/mesh.hpp"
#include "engine/matr.hpp"


namespace igr {
  enum class projection {
    orthogonal, perspective, oblique
  };

  class camera_scene : public scene<camera_scene> {
      camera cam;
      std::array<mesh, 4> spheres;
      projection proj;

    public:
      camera_scene()
        : scene {"Práctica 6 - Daniel Escoz Solana"},
          cam{{3.0, 3.0, 3.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}},
          proj{projection::orthogonal}
      {}

      void on_begin ();
      bool on_event (event_t event);
      void on_update (float delta);
      void on_draw ();
      void on_end ();
  };
}