#ifndef __BOARD__HPP__
#define __BOARD__HPP__

#include <memory>

#include "scene_object.hpp"
#include "composite_scene_object.hpp"
#include "mesh_scene_object.hpp"
#include "transformed_scene_object.hpp"

/* Made against my will -- inheritance abuse follows */
namespace igr {
  class board : public scene_object {
      std::shared_ptr<scene_object> obj;

    public:
      board ();

      void draw_object () {obj->draw_object();}
  };
}

#endif