#ifndef __TRANSFORMED_SCENE_OBJECT__HPP__
#define __TRANSFORMED_SCENE_OBJECT__HPP__

#include <memory>

#include "scene_object.hpp"
#include "engine/matr.hpp"

namespace igr {

  class transformed_scene_object : public scene_object {
      std::shared_ptr<scene_object> obj;

    public:
      matr<double> trans;
      transformed_scene_object (std::shared_ptr<scene_object> obj, matr<double> trans)
        : obj{obj}, trans{trans}
        {}

      void draw_object ();
  };

}

#endif