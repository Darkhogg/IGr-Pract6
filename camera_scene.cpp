#include "camera_scene.hpp"

#define SPHERE 64

void igr::camera_scene::on_begin () {
  proj = projection::perspective;

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

  obj = table;
}

bool igr::camera_scene::on_event (event_t event) {
  return false;
}

void igr::camera_scene::on_update (float delta) {
  double rotX = 0.0;
  double rotY = 0.0;
  double rotZ = 0.0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
    rotX += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    rotX -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    rotY += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    rotY -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
    rotZ += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
    rotZ -= delta * 3.0;
  }

  auto oldUp = cam.up;
  cam.transform(matr<double>::make_rotation_x(rotX));
  cam.transform(matr<double>::make_rotation_y(rotY));
  cam.transform(matr<double>::make_rotation_z(rotZ));
  cam.up = oldUp;
  //cam.normalize();

  double yaw   = 0.0;
  double pitch = 0.0;
  double roll  = 0.0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
    yaw += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
    yaw -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    pitch += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
    pitch -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
    roll += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::V)) {
    roll -= delta * 3.0;
  }

  cam.yaw(yaw);
  cam.pitch(pitch);
  cam.roll(roll);
  

  double mX = 0.0;
  double mY = 0.0;
  double mZ = 0.0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {
    mX += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
    mX -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) {
    mY += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
    mY -= delta * 3.0;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B)) {
    mZ += delta * 3.0;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
    mZ -= delta * 3.0;
  }

  cam.eye  = cam.eye + vec<double>{mX, mY, mZ, category::vector};
  //cam.look = cam.look + vec<double>{mX, mY, mZ, category::vector};


  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
    proj = projection::orthogonal;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
    proj = projection::perspective;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
    proj = projection::oblique;
  }


  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    cam.eye  = {3.0, 3.0, 3.0};
    cam.look = {0.0, 0.0, 0.0};
    cam.up   = {0.0, 1.0, 0.0};
    //cam.normalize();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
    cam.eye  = {3.0, 0.0, 0.0};
    cam.look = {0.0, 0.0, 0.0};
    cam.up   = {0.0, 1.0, 0.0};
    //cam.normalize();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
    cam.eye  = {0.0, 3.0, 0.0001};
    cam.look = {0.0, 0.0, 0.0};
    cam.up   = {0.0, 1.0, 0.0};
    //cam.normalize();
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)) {
    cam.eye  = {0.0, 0.0, 3.0};
    cam.look = {0.0, 0.0, 0.0};
    cam.up   = {0.0, 1.0, 0.0};
    //cam.normalize();
  }
}

void igr::camera_scene::on_draw () {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* Clear the scene */
  glClearColor(0.15f, 0.175f, 0.2f, 1.f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Set up lighting */
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);

  glEnable(GL_LIGHT0);
  GLfloat lgtd[] = {0.3f, 0.3f, 0.3f, 1.f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lgtd);
  GLfloat lgta[] = {0.1f, 0.1f, 0.1f, 1.f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, lgta);
  GLfloat lgtp[] = {25.f, 25.f, 0.f, 1.f};
  glLightfv(GL_LIGHT0, GL_POSITION, lgtp);
  GLfloat lgts[] = {0.f, 0.f, 0.f, 1.f};
  glLightfv(GL_LIGHT0, GL_SPECULAR, lgts);

  glEnable(GL_COLOR_MATERIAL);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.1f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_FRONT);

  glEnable(GL_MULTISAMPLE);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(0.0f, 1.0f);

  /* Update the projection */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();


  auto aspect = (float) window.getSize().x / (float) window.getSize().y;

  switch (proj) {
    case projection::orthogonal: {
      glOrtho(-aspect, aspect, -1.0, 1.0, 0.1, 1000.0);

      break;
    }

    case projection::perspective: {
      gluPerspective(45.0, aspect, 0.1, 1000.0);

      break;
    }

    case projection::oblique: {
      vec<double> oblique_vector {0.1, 0.1, 1, category::vector};
      auto d = oblique_vector.normalized();

      double N = 0.1;
      float m[] = { // COLUMN MAJOR!!
                    1.f,               0.f,   0.f,   0.f,
                    0.f,               1.f,   0.f,   0.f,
            - d.x / d.z,       - d.y / d.z,   1.f,   0.f,
        - N * d.x / d.z,   - N * d.y / d.z,   0.f,   1.f
      };

      glOrtho(-aspect, aspect, -1.0, 1.0, 0.1, 1000.0);
      glMultMatrixf(m);

      break;
    }
  }

  /* Update the camera */
  cam.gl_update();

  /* Draw axis */
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-100.f, 0.f, 0.f);
    glVertex3f(+100.f, 0.f, 0.f);

    glColor3f(0.f, 0.8f, 0.f);
    glVertex3f(0.f, -100.f, 0.f);
    glVertex3f(0.f, +100.f, 0.f);

    glColor3f(0.f, 0.5f, 1.f);
    glVertex3f(0.f, 0.f, -100.f);
    glVertex3f(0.f, 0.f, +100.f);
  glEnd();
  glEnable(GL_LIGHTING);

  /* Draw box */
  obj->draw_object();
}

void igr::camera_scene::on_end () {

}



/** Main method */
int main () {
  igr::camera_scene{}.run();
}