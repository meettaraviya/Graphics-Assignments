#include "main.hpp"

#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 512

GLuint shaderProgram;
GLuint vbo, vao;

// glm::mat4 rotation_matrix;
glm::mat4 mat_rotation;
glm::mat4 mat_translation;
glm::mat4 mat_ortho_proj;
glm::mat4 mat_persp_proj;
glm::mat4 modelview_matrix;
GLuint uModelViewMatrix;

vector<glm::vec4> v_positions;
glm::vec4 positions_sum;
vector<glm::vec4> v_colors;

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

  GLdouble aspect_ratio = (GLfloat) WINDOW_WIDTH / WINDOW_HEIGHT;
  mat_ortho_proj = glm::ortho(-2.0*aspect_ratio, 2.0*aspect_ratio, -2.0, 2.0, -2.0, 2.0);
  mat_persp_proj = glm::perspective(45.0, aspect_ratio, 0.1, 10.0);
}

void loadModel(string file_name){
  ifstream in_file;
  in_file.open(file_name);

  if (in_file.is_open()){

    v_positions.clear();
    v_colors.clear();

    GLfloat tmp;
    glm::vec4 vec(0.0,0.0,0.0,1.0);
    int i = 0;

    while (in_file >> tmp){
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

    for(int i=0; i<v_positions.size(); i++){
      cout << v_positions[i][0] << " " << v_positions[i][1] << " " << v_positions[i][2] << endl;
    }
    cout << endl;
    for(int i=0; i<v_positions.size(); i++){
      cout << v_colors[i][0] << " " << v_colors[i][1] << " " << v_colors[i][2] << endl; 
    }

    initBuffersGL();
    initShadersGL();

    glLoadMatrixf(glm::value_ptr(mat_rotation));
    glLoadIdentity();
  }
  else {
    cerr << "Bad file name" << endl;
  }
}

void saveModel(string file_name){
  ofstream out_file;
  out_file.open(file_name);

  if (out_file.is_open()){

    GLfloat tmp;
    glm::vec4 vec(0.0,0.0,0.0,1.0);

    for(size_t i=0; i<v_positions.size(); i++){
      out_file << v_positions[i][0] << " " << v_positions[i][1] << " " << v_positions[i][2] << " "
               << v_colors[i][0] << " " << v_colors[i][1] << " " << v_colors[i][2] << endl;
    }

    out_file.close();
  }
  else {
    cerr << "Failed to write to file" << endl;
  }
}
//-----------------------------------------------------------------


float unit_rotation = 5e-2;
float unit_translation = 0.1;

void renderGL(GLFWwindow *window)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  // // Draw 
  
  glm::mat4 id(1.0);

  modelview_matrix = glm::translate(id, (glm::vec3) -positions_sum/(GLfloat) v_positions.size());

  if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3(0.0, -1.0, 0.00))*mat_rotation;
  }
  if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3( 0.0, 1.0, 0.0))*mat_rotation;
  }
  if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3( -1.0, 0.0, 0.00))*mat_rotation;
  }
  if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3(1.0, 0.0, 0.0))*mat_rotation;
  }
  if(glfwGetKey(window, GLFW_KEY_PAGE_UP)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3(0.0, 0.0, 1.0))*mat_rotation;
  }
  if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3(0.0, 0.0, -1.0))*mat_rotation;
  }


  if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){
    mat_translation = glm::translate(mat_translation, glm::vec3(0.0, +unit_translation * 1.0, 0.0));
  }
  if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){
    mat_translation = glm::translate(mat_translation, glm::vec3(0.0, -unit_translation * 1.0, 0.0));
  }
  if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS){
    mat_translation = glm::translate(mat_translation, glm::vec3(+unit_translation * 1.0, 0.0, 0.0));
  }
  if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS){
    mat_translation = glm::translate(mat_translation, glm::vec3(-unit_translation * 1.0, 0.0, 0.0));
  }
  if(glfwGetKey(window, GLFW_KEY_X)==GLFW_PRESS){
    mat_translation = glm::translate(mat_translation, glm::vec3(0.0, 0.0, +unit_translation * 1.0));
  }
  if(glfwGetKey(window, GLFW_KEY_Z)==GLFW_PRESS){
    mat_translation = glm::translate(mat_translation, glm::vec3(0.0, 0.0, -unit_translation * 1.0));
  }


  modelview_matrix = mat_rotation * modelview_matrix;
  modelview_matrix = glm::translate(id, (glm::vec3) positions_sum/(GLfloat) v_positions.size()) * modelview_matrix;
  modelview_matrix = mat_translation * modelview_matrix;
  modelview_matrix = mat_ortho_proj * modelview_matrix;

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
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CS475/CS675 Tutorial 3: Rotating  Colorcube", NULL, NULL);
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
      renderGL(window);

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

