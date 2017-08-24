#include "main.hpp"
using namespace std;
GLuint shaderProgram;
GLuint vbo, vao;

// glm::mat4 rotation_matrix;
glm::mat4 transformation_matrix;
glm::mat4 ortho_matrix;
glm::mat4 modelview_matrix;
GLuint uModelViewMatrix;

std::vector<glm::vec4> v_positions;
std::vector<glm::vec4> v_colors;
glm::vec4 positions_sum;

void initBuffersGL(void)
{

  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);

  glGenBuffers (1, &vbo);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);
  cout << (v_positions.size() + v_colors.size()) * sizeof(glm::vec4) << endl;
  glBufferData (GL_ARRAY_BUFFER, (v_positions.size() + v_colors.size()) * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, v_positions.size() * sizeof(glm::vec4), v_positions.data() );
  glBufferSubData( GL_ARRAY_BUFFER, v_positions.size() * sizeof(glm::vec4), v_colors.size() * sizeof(glm::vec4), v_colors.data() );
}

void initShadersGL(void)
{
  string vertex_shader_file("vshader.glsl");
  string fragment_shader_file("fshader.glsl");

  vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

  GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_positions.size()*sizeof(glm::vec4)) );

  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
}

void loadModel(std::string file_name) {
  std::ifstream in_file;
  in_file.open(file_name.c_str());
  if (in_file.is_open()) {

    v_positions.clear();
    v_colors.clear();

    GLfloat tmp;
    glm::vec4 vec(0.0, 0.0, 0.0, 1.0);
    int i = 0;

    while (in_file >> tmp){
      // cout << tmp << endl;
      i = (i+1)%6;

      switch(i){
        case 1:
        case 2:
          vec[i-1] = tmp;
          break;
        case 3:
          vec[2] = tmp;
          v_positions.push_back(vec);
          positions_sum += vec;
          break;
        case 4:
        case 5:
          vec[i-4] = tmp;
          break;
        case 0:
          vec[2] = tmp;
          v_colors.push_back(vec);
          break;
      }

    }

    in_file.close();

    for (int i = 0; i < v_positions.size(); i++) {
      std::cout << v_positions[i][0] << " " << v_positions[i][1] << " " << v_positions[i][2] << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < v_positions.size(); i++) {
      std::cout << v_colors[i][0] << " " << v_colors[i][1] << " " << v_colors[i][2] << std::endl;
    }

    initBuffersGL();
    initShadersGL();
  }
  else {
    cerr << "Bad file name" << endl;
  }
}

void saveModel(std::string file_name) {
  std::ofstream out_file;
  out_file.open(file_name.c_str());

  if (out_file.is_open()) {

    GLfloat tmp;
    glm::vec4 vec(0.0, 0.0, 0.0, 1.0);

    for (size_t i = 0; i < v_positions.size(); i++) {
      out_file << v_positions[i][0] << " " << v_positions[i][1] << " " << v_positions[i][2] << " "
               << v_colors[i][0] << " " << v_colors[i][1] << " " << v_colors[i][2] << endl;
    }

    out_file.close();
  }
  else {
    cerr << "Failed to write to file" << endl;
  }
}

void drawPoint(double x, double y) {
  y = 512 - y;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
  glPointSize(50);
  glBegin(GL_POINTS);
  glVertex2f(x , y);
  cout << x<< " "<<y<<endl;
  glEnd();
  glm::vec4 vec(x, y, 0.1, 1.0);
  v_positions.push_back(vec);
  if(v_positions.size()%3 == 0){
    glm::vec4 vec1(0.0, 0.0, 0.0, 1.0);
    cout<<"Enter RGB color value"<<endl;
    for(int j=0;j<2;j++){   
      for(int i=0;i<2;i++){
        cin>>vec1[i];
      }
      v_colors.push_back(vec1);
    }
    positions_sum += (v_positions[v_positions.size()-3] + v_positions[v_positions.size()-2] + v_positions[v_positions.size()-1]);
  }
  glFlush();
  
}

//-----------------------------------------------------------------


void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  transformation_matrix = glm::rotate(glm::mat4(1.0f), xrot, glm::vec3(1.0f,0.0f,0.0f));
  transformation_matrix = glm::rotate(transformation_matrix, yrot, glm::vec3(0.0f,1.0f,0.0f));
  transformation_matrix = glm::rotate(transformation_matrix, zrot, glm::vec3(0.0f,0.0f,1.0f));
  ortho_matrix = glm::ortho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
  modelview_matrix = ortho_matrix * transformation_matrix;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glDrawArrays(GL_TRIANGLES, 0, v_positions.size());

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //We don't want the old OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(512, 512, "CS475/CS675 Tutorial 3: Rotating  Colorcube", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  //! Make the window's context current
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      cerr<<"GLEW Init Failed : %s"<<endl;
    }

  //Print and see what context got enabled
  cout<<"Vendor: "<<glGetString (GL_VENDOR)<<endl;
  cout<<"Renderer: "<<glGetString (GL_RENDERER)<<endl;
  cout<<"Version: "<<glGetString (GL_VERSION)<<endl;
  cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
  //MouseClick Callback
  glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);
  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  
  csX75::initGL();
  loadModel("file.raw");
  initShadersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
  {

    // Render here
    renderGL();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

