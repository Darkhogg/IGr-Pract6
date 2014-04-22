#include "transformed_scene_object.hpp"

void igr::transformed_scene_object::draw_object () {
  glPushMatrix();
  trans.gl_mult();
  obj->draw_object();
  glPopMatrix();
}