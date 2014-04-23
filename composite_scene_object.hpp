#ifndef __COMPOSITE_SCENE_OBJECT__HPP__
#define __COMPOSITE_SCENE_OBJECT__HPP__

#include <vector>
#include <memory>

#include "scene_object.hpp"

namespace igr {
  class composite_scene_object : public scene_object {
      std::vector<std::shared_ptr<scene_object>> objs;

    public:
      composite_scene_object ()
        {}

      void clear ();
      void add_object (std::shared_ptr<scene_object> obj);

      void draw_object ();
  };
}

#endif