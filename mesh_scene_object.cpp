#include "mesh_scene_object.hpp"

#include <ostream>

void igr::mesh_scene_object::draw_object () {
  obj_mesh.gl_draw_immediate();
}