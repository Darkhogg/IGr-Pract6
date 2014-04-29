#include <memory>

#include "scene_object.hpp"
#include "engine/matr.hpp"

namespace igr {

  class transformed_scene_object : public scene_object {
      std::shared_ptr<scene_object> obj;
      matr<double> trans;

    public:
      transformed_scene_object (std::shared_ptr<scene_object> obj, matr<double> trans)
        : obj{obj}, trans{trans}
        {}

      void draw_object ();
  };

}