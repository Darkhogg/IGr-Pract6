#include "scene_object.hpp"

#include "engine/mesh.hpp"

namespace igr {

  class mesh_scene_object : public scene_object {
      mesh obj_mesh;

    public:
      mesh_scene_object (mesh m)
        : obj_mesh{m}
        {}

      void draw_object ();
  };

}