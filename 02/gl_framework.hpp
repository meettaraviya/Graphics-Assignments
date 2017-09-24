#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

using namespace std;

void centreToCentroid();

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))
#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 512

#define GRID_N 32
#define GRID_M 48

namespace csX75
{
  //! Initialize GL State
  void initGL(void);
  //! Creates and returns a window
  GLFWwindow * getWindow();
 
  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

};

#endif
