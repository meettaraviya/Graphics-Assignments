#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include "Include.hpp"
#include "Transformation.hpp"
#include "main.hpp"

extern class Character character;

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
