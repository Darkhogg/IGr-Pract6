#include "camera_scene.hpp"

void igr::camera_scene::on_begin () {
  /* Setup the projection */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (float) window.getSize().x / (float) window.getSize().y, 0.1, 1000);

  /* Set up lighting */
  //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);

  glEnable(GL_COLOR_MATERIAL);
  glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);


  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  glEnable(GL_MULTISAMPLE);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
  glDepthFunc(GL_LEQUAL);
  glDepthRange(0.0f, 1.0f);

   // Light0
  glEnable(GL_LIGHT0);
  GLfloat d[]={1.0, 1.0, 1.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
  GLfloat a[]={0.3f, 0.3f, 0.3f, 1.0};
  glLightfv(GL_LIGHT0, GL_AMBIENT, a);
  GLfloat p[]={25.0, 25.0, 0.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, p);

  // Box 
  box = mesh::make_aligned_box({1.f, 1.f, 1.f});
}

bool igr::camera_scene::on_event (event_t event) {
  return false;
}

void igr::camera_scene::on_update (float delta) {
  double rotX = 0;
  double rotY = 0;
  double rotZ = 0;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
    rotX += delta;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    rotX -= delta;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    rotY += delta;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    rotY -= delta;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
    rotZ += delta;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
    rotZ -= delta;
  }

  cam.transform(matr<double>::make_rotation_x(rotX));
  cam.transform(matr<double>::make_rotation_y(rotY));
  cam.transform(matr<double>::make_rotation_z(rotZ));
}

void igr::camera_scene::on_draw () {
  glClearColor(0.15f, 0.175f, 0.2f, 1.f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  cam.gl_update();

  /* Draw axis */
  glBegin(GL_LINES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-10.f, 0.f, 0.f);
    glVertex3f(+10.f, 0.f, 0.f);

    glColor3f(0.f, 0.8f, 0.f);
    glVertex3f(0.f, -10.f, 0.f);
    glVertex3f(0.f, +10.f, 0.f);

    glColor3f(0.f, 0.5f, 1.f);
    glVertex3f(0.f, 0.f, -10.f);
    glVertex3f(0.f, 0.f, +10.f);
  glEnd();

  /* Draw box */
  box.gl_draw_immediate();
}

void igr::camera_scene::on_end () {

}



/** Main method */
int main () {
  igr::camera_scene{}.run();
}