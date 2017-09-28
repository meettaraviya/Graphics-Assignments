#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include "Include.hpp"
#include "Transformation.hpp"

namespace csX75
{
  void initGL(void);
  GLFWwindow * getWindow();
  void error_callback(int error, const char* description);
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif
