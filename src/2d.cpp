#include <GL/glut.h>
#include <iostream>

void display() {
  glClear(GL_COLOR_BUFFER_BIT); // clear color buffer
  glColor3f(1.0f, 0.0f, 0.0f);  // set red color
  glBegin(GL_TRIANGLES);        // display vertices
  glVertex2f(-0.5f, -0.5f);
  glVertex2f(0.5f, -0.5f);
  glVertex2f(0.0f, 0.5f);
  glEnd();
  glFlush(); // execute on GPU
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

void init() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // black color of screen
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);                       // initialize GLUT
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set single buffering and RGB
  glutInitWindowSize(500, 500);                // set window size
  glutCreateWindow("2D Triangle - OpenGL example"); // create window
  glutDisplayFunc(display);                         // set our display function
  glutKeyboardFunc(keyboard);                       // set keyboard callback
  init();                                           // initialize OpenGL
  glutMainLoop();                                   // main loop of GLUT
  return 0;
}
