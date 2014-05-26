#include "engine/common.h"
#include "engine/scene.hpp"
#include "engine/camera.hpp"
#include "engine/mesh.hpp"
#include "engine/matr.hpp"
#include "engine/gl_light.hpp"

#include <ostream>
#include <memory>

#include "board.hpp"
#include "transformed_scene_object.hpp"

namespace igr {
  enum class projection {
    orthogonal, perspective, oblique
  };

  class lighting_scene : public scene<lighting_scene> {
      double time;

      camera cam;
      std::shared_ptr<transformed_scene_object> obj;
      projection proj;

      gl_light lamp_light, sun_light;
      bool lamp_on, sun_on, ambient_on;
      double lamp_scale;

      matr<double> lamptrans;

    public:
      lighting_scene()
        : scene {"Práctica 7 - Daniel Escoz Solana"},
          cam{{2.0, 2.0, 2.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}},
          proj{projection::orthogonal}
      {}

      void on_begin ();
      bool on_event (event_t event);
      void on_update (float delta);
      void on_draw ();
      void on_end ();
  };

  mesh make_aligned_lamp (color col, std::size_t sides);
}