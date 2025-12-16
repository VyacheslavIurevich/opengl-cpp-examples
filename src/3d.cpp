#include <GL/glut.h>
#include <cmath>
#include <iostream>

float angle = 0.0f; // rotation angle

GLfloat vertices[] = {  // cube vertices (8 vertices, each with 3 coordinates)
    -0.5f, -0.5f, 0.5f, // front face
    0.5f,  -0.5f, 0.5f,  0.5f, 0.5f, 0.5f,  -0.5f, 0.5f, 0.5f,

    -0.5f, -0.5f, -0.5f, // back face
    0.5f,  -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f};

GLfloat colors[] = {
    // vertex colors (RGBA)
    1.0f, 0.0f, 0.0f, 1.0f, // red
    0.0f, 1.0f, 0.0f, 1.0f, // green
    0.0f, 0.0f, 1.0f, 1.0f, // blue
    1.0f, 1.0f, 0.0f, 1.0f, // yellow
    1.0f, 0.0f, 1.0f, 1.0f, // purple
    0.0f, 1.0f, 1.0f, 1.0f, // cyan
    0.5f, 0.5f, 0.5f, 1.0f, // gray
    1.0f, 0.5f, 0.0f, 1.0f  // orange
};

GLubyte indices[] = {
    // indices for drawing squares (6 faces, 4 vertices in each one)
    0, 1, 2, 3, // front face
    4, 5, 6, 7, // back face
    3, 2, 6, 7, // top face
    0, 1, 5, 4, // bottom face
    1, 5, 6, 2, // right face
    0, 4, 7, 3  // left face
};

void init() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // dark gray background

  glEnable(GL_DEPTH_TEST); // enable depth buffer

  glEnable(GL_LIGHTING); // enable lighting
  glEnable(GL_LIGHT0);   // enable light source 0

  GLfloat light_position[] = {1.0f, 1.0f, 1.0f, 0.0f}; // light position
  GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};  // ambient light
  GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  // diffuse light

  glLightfv(GL_LIGHT0, GL_POSITION, light_position); // set light position
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);   // set ambient light
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);   // set diffuse light

  glEnable(GL_COLOR_MATERIAL); // enable color material
  glColorMaterial(GL_FRONT_AND_BACK,
                  GL_AMBIENT_AND_DIFFUSE); // set material properties
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers

  glMatrixMode(GL_MODELVIEW); // switch to modelview matrix
  glLoadIdentity();           // reset modelview matrix

  gluLookAt(2.0f, 2.0f, 2.0f,  // camera position
            0.0f, 0.0f, 0.0f,  // look at point
            0.0f, 1.0f, 0.0f); // up vector

  glRotatef(angle, 1.0f, 1.0f, 0.5f); // rotate cube

  glEnableClientState(GL_VERTEX_ARRAY); // enable vertex array
  glEnableClientState(GL_COLOR_ARRAY);  // enable color array

  glVertexPointer(3, GL_FLOAT, 0, vertices); // set vertex pointer
  glColorPointer(4, GL_FLOAT, 0, colors);    // set color pointer

  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices); // draw cube

  glDisableClientState(GL_COLOR_ARRAY);  // disable color array
  glDisableClientState(GL_VERTEX_ARRAY); // disable vertex array

  glutSwapBuffers(); // swap buffers (double buffering)
}

void update(int value) {
  angle += 1.0f; // increment rotation angle
  if (angle > 360) {
    angle -= 360; // keep angle in 0-360 range
  }

  glutPostRedisplay();          // request redisplay
  glutTimerFunc(16, update, 0); // call update every 16ms (~60 FPS)
}

void reshape(int width, int height) {
  if (height == 0)
    height = 1; // prevent division by zero

  glViewport(0, 0, width, height); // set viewport to window size

  glMatrixMode(GL_PROJECTION); // switch to projection matrix
  glLoadIdentity();            // reset projection matrix

  gluPerspective(45.0f, (float)width / (float)height, 0.1f,
                 100.0f); // set perspective projection

  glMatrixMode(GL_MODELVIEW); // switch back to modelview matrix
}

void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 27:   // ESC key
    exit(0); // exit program
    break;
  case ' ':                                     // space key
    std::cout << "Space pressed!" << std::endl; // print message
    break;
  }
}

int main(int argc, char **argv) {
  glutInit(&argc, argv); // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
                      GLUT_DEPTH); // set double buffering, RGB and depth
  glutInitWindowSize(800, 600);    // set window size
  glutCreateWindow("3D Cube - OpenGL Example"); // create window

  init(); // initialize OpenGL settings

  glutDisplayFunc(display);     // set display callback
  glutReshapeFunc(reshape);     // set reshape callback
  glutKeyboardFunc(keyboard);   // set keyboard callback
  glutTimerFunc(16, update, 0); // start timer for animation

  glutMainLoop(); // start main loop

  return 0;
}
