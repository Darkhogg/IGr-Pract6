#include "lighting_scene.hpp"

#define SPHERE 64

void igr::lighting_scene::on_begin () {
  proj = projection::perspective;
  obj = std::make_shared<transformed_scene_object>(
    std::make_shared<board>(),
    matr<double>{}
  );

  sun_light.position = {1.0, 1.0, 0.0, category::vector};
  sun_light.ambient  = {0.1, 0.1, 0.1};
  sun_light.diffuse  = {0.2, 0.2, 0.2};
  sun_light.specular = {0.2, 0.2, 0.2};

  //lamp_light.position  = {0.0, 1.0, 0.0, category::point};
  lamp_light.ambient   = {0.1, 0.1, 0.0};
  lamp_light.diffuse   = {0.8, 0.8, 0.4};
  lamp_light.specular  = {1.0, 1.0, 0.5};
  lamp_light.cutoff    = 30.0;
  lamp_light.exponent  = 48.0;
  //lamp_light.direction = {-2.0, -1.0, 0.0, category::vector};

  sun_on = true;
  lamp_on = true;
  ambient_on = true;

  lamp_scale = 1.0;

  glEnable(GL_TEXTURE_2D);
}

bool igr::lighting_scene::on_event (event_t event) {
  if (event.type == sf::Event::KeyPressed) {
    switch (event.key.code) {
      case sf::Keyboard::Key::O: {
        lamp_on = !lamp_on;
        break;
      }
      case sf::Keyboard::Key::P: {
        sun_on = !sun_on;
        break;
      }
      case sf::Keyboard::Key::L: {
        ambient_on = !ambient_on;
        break;
      }
      default: {}
    }
  }

  return false;
}

void igr::lighting_scene::on_update (float delta) {
  time += delta;
  lamp_light.position = {-0.3 * cos(time*3), 0.7, -0.3 * sin(time*3), category::point};
  lamp_light.direction = {1.1 * cos(time*3), -1.0, 1.1 * sin(time*3), category::vector};

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8)) {
    lamp_scale += delta;
  }  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9)) {
    lamp_scale -= delta;
  }

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
    cam.eye  = {1.5, 1.5, 1.5};
    cam.look = {0.0, 0.0, 0.0};
    cam.up   = {0.0, 1.0, 0.0};
    //cam.normalize();

    obj->trans = matr<double>{};
    lamp_scale = 1.0;
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


  /* Scene transforms */

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U)) {
    obj->trans = matr<double>::make_translation({delta, 0.0, 0.0}) * obj->trans;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
    obj->trans = matr<double>::make_scalation({1.0, 1.0 + delta, 1.0}) * obj->trans;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
    obj->trans = matr<double>::make_rotation_z(delta) * obj->trans;
  }
}

void igr::lighting_scene::on_draw () {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /* Clear the scene */
  glClearColor(0.f, 0.f, 0.f, 1.f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /* Set up lighting */
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);

  /*
  glEnable(GL_LIGHT0);
  GLfloat lgtd[] = {0.3f, 0.3f, 0.3f, 1.f};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lgtd);
  GLfloat lgta[] = {0.1f, 0.1f, 0.1f, 1.f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, lgta);
  GLfloat lgtp[] = {25.f, 25.f, 0.f, 1.f};
  glLightfv(GL_LIGHT0, GL_POSITION, lgtp);
  GLfloat lgts[] = {0.f, 0.f, 0.f, 1.f};
  glLightfv(GL_LIGHT0, GL_SPECULAR, lgts);
  */

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

  /* Fog */
  GLfloat fog[] = {0.f, 0.f, 0.f, 1.0};
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, fog);
  glFogf(GL_FOG_DENSITY, 0.2f);
  glFogf(GL_FOG_START, 2.f);
  glFogf(GL_FOG_END, 8.f);
  glEnable(GL_FOG);

  /* Update the lights */
  if (sun_on) {
    sun_light.gl_enable();
    sun_light.gl_update();
  } else {
    sun_light.gl_disable();
  }

  if (ambient_on) {
    set_ambient_light_color({0.2f, 0.2f, 0.2f});
  } else {
    set_ambient_light_color({0.f, 0.f, 0.f});
  }

  /* Scalation! */
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glScaled(1.0, lamp_scale, 1.0);

  if (lamp_on) {
    lamp_light.gl_enable();
    lamp_light.gl_update();
  } else {
    lamp_light.gl_disable();
  }

  auto cyl = mesh::make_aligned_cylinder(colors::white, 32);
  cyl.transform(matr<double>::make_scalation({0.15, 0.15, 0.1}));
  cyl.transform(matr<double>::make_translation({0, 0, 0.05}));
  cyl.transform(matr<double>::make_rotation_x(atan2(2, -1)));
  cyl.transform(matr<double>::make_rotation_y(-3 * time + M_PI_2));
  cyl.transform(matr<double>::make_translation(lamp_light.position));
  cyl.gl_draw_immediate();

  if (lamp_on) {
    GLfloat emw[] = {1.f, 1.f, 0.5f, 1.f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emw);
  }

  auto bulb = mesh::make_aligned_sphere(lamp_on ? color{1.0, 1.0, 0.5} : color{0.5, 0.5, 0.1}, 32, 32);
  bulb.transform(matr<double>::make_scalation({0.1, 0.1, 0.1}));
  bulb.transform(matr<double>::make_translation(lamp_light.position));
  bulb.gl_draw_immediate();

  glPopMatrix();

  /* Draw board */
  GLfloat emb[] = {0.f, 0.f, 0.f, 1.f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emb);
  glPolygonMode(GL_FRONT_AND_BACK, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I) ? GL_LINE : GL_FILL);
  obj->draw_object();



  /* Draw axis */
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
    glColor3f(0.3f, 0.f, 0.f);
    glVertex3f(-100.f, 0.f, 0.f);
    glVertex3f(+100.f, 0.f, 0.f);

    glColor3f(0.f, 0.24f, 0.f);
    glVertex3f(0.f, -100.f, 0.f);
    glVertex3f(0.f, +100.f, 0.f);

    glColor3f(0.f, 0.15f, 0.3f);
    glVertex3f(0.f, 0.f, -100.f);
    glVertex3f(0.f, 0.f, +100.f);
  glEnd();
  glEnable(GL_LIGHTING);

}

void igr::lighting_scene::on_end () {

}



/** Main method */
int main () {
  igr::lighting_scene{}.run();
}