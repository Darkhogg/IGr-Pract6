#include "mesh_scene_object.hpp"

#include <ostream>

void igr::mesh_scene_object::draw_object () {
  matr<double> m;
  m.gl_load(GL_MODELVIEW_MATRIX);
  std::cout << m << std::endl;

  obj_mesh.gl_draw_immediate();
}