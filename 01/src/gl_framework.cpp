#include "gl_framework.hpp"
using namespace std;

extern GLfloat xrot, yrot, zrot;
extern enum Mode mode;

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
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mode == MODE_MODELLING) {
    if(GLFW_MOD_SHIFT & mods){
      removePoint();
    }
    else{
      double posX, posY;
      glfwGetCursorPos(window, &posX, &posY);
      drawPoint(posX, posY);
    }
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
  if (key == GLFW_KEY_M && action == GLFW_PRESS) {
    cout<< "Modelling Mode" <<endl;
    mode = MODE_MODELLING;
  }
  if (key == GLFW_KEY_I && action == GLFW_PRESS) {
    cout<<"Inspection Mode"<<endl;
    mode = MODE_INSPECTION;
  }
  if(key == GLFW_KEY_R && action == GLFW_PRESS && mode == MODE_INSPECTION){
    centreToCentroid();
  }
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    exit(0);
  }
}
};



