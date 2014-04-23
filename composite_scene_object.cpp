#include "composite_scene_object.hpp"

void igr::composite_scene_object::clear () {
  objs.clear();
}

void igr::composite_scene_object::add_object (std::shared_ptr<scene_object> obj) {
  objs.push_back(obj);
}

void igr::composite_scene_object::draw_object () {
  for (auto obj : objs) {
    obj->draw_object();
  }
}