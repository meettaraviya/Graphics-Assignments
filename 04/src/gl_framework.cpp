#include "gl_framework.hpp"

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

  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    if(key == GLFW_KEY_R && action == GLFW_PRESS){
      World::centre();
    }
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
      exit(0);
    }
    if(key == GLFW_KEY_C && action == GLFW_PRESS){
      keyframe.push_back(Frame());
      keyframe[keyframe.size()-1].frame_capture();
    }
  }

  GLFWwindow * getWindow(){
    GLFWwindow* window;

    glfwSetErrorCallback(csX75::error_callback);

    if (!glfwInit())
      exit(-1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Computer graphics - Assignment 1", NULL, NULL);
    if (!window)
    {
      glfwTerminate();
      exit(-1);
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      cerr<<"GLEW Init Failed : %s"<<endl;
    }

    cout<<"Vendor: "<<glGetString (GL_VENDOR)<<endl;
    cout<<"Renderer: "<<glGetString (GL_RENDERER)<<endl;
    cout<<"Version: "<<glGetString (GL_VERSION)<<endl;
    cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<endl;

    glfwSetKeyCallback(window, csX75::key_callback);
    glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    csX75::initGL();

    return window;
  }
};



