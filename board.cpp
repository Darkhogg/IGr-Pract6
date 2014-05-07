#include "board.hpp"

igr::board::board () {
  
  /* Generate the pool table */
  color brown {0.7f, 0.1f, 0.f};
  color green {0.f, 0.3f, 0.f};

  /* Green cube asthe board */
  auto green_board = std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_box(green)),
    matr<double>::make_translation({0.0, 0.01, 0.0})
    * matr<double>::make_scalation({2.0, 0.1, 1.0})
  );

  /* Brown top-left leg */
  auto tl_leg = std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_cylinder(brown, 64)),
    matr<double>::make_translation({0.94, -0.5, 0.44})
    * matr<double>::make_scalation({0.15, 1.0, 0.15})
    * matr<double>::make_rotation_x(M_PI_2)
  );

  /* Brown top-right leg */
  auto tr_leg = std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_cylinder(brown, 64)),
    matr<double>::make_translation({-0.94, -0.5, 0.44})
    * matr<double>::make_scalation({0.15, 1.0, 0.15})
    * matr<double>::make_rotation_x(M_PI_2)
  );

  /* Brown bottom-left leg */
  auto bl_leg = std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_cylinder(brown, 64)),
    matr<double>::make_translation({0.94, -0.5, -0.44})
    * matr<double>::make_scalation({0.15, 1.0, 0.15})
    * matr<double>::make_rotation_x(M_PI_2)
  );

  /* Brown bottom-right leg */
  auto br_leg = std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_cylinder(brown, 64)),
    matr<double>::make_translation({-0.94, -0.5, -0.44})
    * matr<double>::make_scalation({0.15, 1.0, 0.15})
    * matr<double>::make_rotation_x(M_PI_2)
  );

  /* Frame (5 pieces!) */
  auto frame = std::make_shared<composite_scene_object>();

  /* Under wood */
  frame->add_object(std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_box(brown)),
    matr<double>::make_translation({0.0, 0.0, 0.0})
    * matr<double>::make_scalation({2.0, 0.1, 1.0})
  ));

  /* Top wood */
  frame->add_object(std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_box(brown)),
    matr<double>::make_translation({1.05, 0.04, 0.0})
    * matr<double>::make_scalation({0.1, 0.18, 1.0})
  ));

  /* Bottom wood */
  frame->add_object(std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_box(brown)),
    matr<double>::make_translation({-1.05, 0.04, 0.0})
    * matr<double>::make_scalation({0.1, 0.18, 1.0})
  ));

  /* Left wood */
  frame->add_object(std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_box(brown)),
    matr<double>::make_translation({0.0, 0.04, 0.55})
    * matr<double>::make_scalation({2.2, 0.18, 0.1})
  ));

  /* Left wood */
  frame->add_object(std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_box(brown)),
    matr<double>::make_translation({0.0, 0.04, -0.55})
    * matr<double>::make_scalation({2.2, 0.18, 0.1})
  ));

  /* Stick (2 pieces!) */
  auto stick = std::make_shared<composite_scene_object>();

  stick->add_object(std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_cylinder(brown, 64)),
    matr<double>{}
  ));

  stick->add_object(std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_cylinder(colors::white, 64)),
    matr<double>::make_translation({0.0, 0.0, -0.51})
    * matr<double>::make_scalation({1.0, 1.0, 0.02})
  ));

  auto stickt = std::make_shared<transformed_scene_object>(
    stick,
    matr<double>::make_translation({0.9, 0.15, 0.5})
    * matr<double>::make_rotation_x(0.1)
    * matr<double>::make_scalation({0.02, 0.02, 1.7})
  );

  /* Balls (16 pieces!) */
  auto balls = std::make_shared<composite_scene_object>();
  double dx = 0.05 * sin(M_PI / 3);
  double dz = 0.05;

  balls->add_object(std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_sphere(colors::white, 32, 32)),
    matr<double>::make_translation({0.5, 0.1, 0.0})
    * matr<double>::make_scalation({0.08, 0.08, 0.08})
  ));

  balls->add_object(std::make_shared<transformed_scene_object>(
    std::make_shared<mesh_scene_object>(mesh::make_aligned_sphere({0.1f, 0.1f, 0.1f}, 32, 32)),
    matr<double>::make_translation({-0.3 - dx * 4, 0.1, 0.0})
    * matr<double>::make_scalation({0.08, 0.08, 0.08})
  ));

  std::vector<vec<double>> vecs = {
    {0.0, 0.0, 0.0},
    {-dx * 2, 0.0, -dz},
    {-dx * 2, 0.0, +dz},
    {-dx * 4, 0.0, -dz * 2},
    //{-dx * 4, 0.0, 0.0},
    {-dx * 4, 0.0, +dx * 2},
    {-dx * 6, 0.0, -dz * 3},
    {-dx * 6, 0.0, -dz},
    {-dx * 6, 0.0, +dz},
    {-dx * 6, 0.0, +dz * 3},
    {-dx * 8, 0.0, -dz * 4},
    {-dx * 8, 0.0, -dz * 2},
    {-dx * 8, 0.0, 0.0},
    {-dx * 8, 0.0, +dz * 2},
    {-dx * 8, 0.0, +dz * 4},
  };

  for (auto v : vecs) {
    balls->add_object(std::make_shared<transformed_scene_object>(
      std::make_shared<mesh_scene_object>(mesh::make_aligned_sphere({0.2f, 0.2f, 0.3f}, 32, 32)),
      matr<double>::make_translation(v + vec<double>{-0.3, 0.1, 0.0})
      * matr<double>::make_scalation({0.08, 0.08, 0.08})
    ));
  }

  /* Table */
  auto table = std::make_shared<composite_scene_object>();
  table->add_object(green_board);
  table->add_object(frame);
  table->add_object(tl_leg);
  table->add_object(tr_leg);
  table->add_object(bl_leg);
  table->add_object(br_leg);
  table->add_object(stickt);
  table->add_object(balls);

  obj = std::make_shared<transformed_scene_object>(table, matr<double>{});
}