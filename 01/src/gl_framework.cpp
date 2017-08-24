#include "gl_framework.hpp"
using namespace std;

extern GLfloat xrot, yrot, zrot;

namespace csX75
{
//! Initialize GL State
void initGL(void)
{
  //Set framebuffer clear color
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  //Set depth buffer furthest depth
  glClearDepth(1.0);
  //Set depth test to less-than
  glDepthFunc(GL_LESS);
  //Enable depth testing
  glEnable(GL_DEPTH_TEST);
}

//!GLFW Error Callback
void error_callback(int error, const char* description)
{
  std::cerr << description << std::endl;
}

//!GLFW framebuffer resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  //!Resize the viewport to fit the window size - draw to entire window
  glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
    double posX, posY;
    glfwGetCursorPos(window, &posX, &posY);
    // std::cout << "(x,y) coordinates are: " << posX << " " << posY << std::endl;
    drawPoint(posX,posY);
  }
}

//!GLFW keyboard callback
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  //!Close the window if the ESC key was pressed
  if (key == GLFW_KEY_L && action == GLFW_PRESS) {
    string filename;
    cout << "Enter file name: ";
    cin >> filename;
    loadModel(filename);
  }
  if (key == GLFW_KEY_K && action == GLFW_PRESS) {
    string filename;
    cout << "Enter file name: ";
    cin >> filename;
    saveModel(filename);
  }
  else if (key == GLFW_KEY_LEFT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    yrot -= 0.314159;
  else if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    yrot += 0.314159;
  else if (key == GLFW_KEY_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
    xrot += 0.314159;
  else if (key == GLFW_KEY_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
    xrot -= 0.314159;
  else if (key == GLFW_KEY_PAGE_UP && (action == GLFW_REPEAT || action == GLFW_PRESS))
    zrot += 0.314159;
  else if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_REPEAT || action == GLFW_PRESS))
    zrot -= 0.314159;
}
};



