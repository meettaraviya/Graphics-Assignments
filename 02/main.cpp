#include "main.hpp"

GLuint shaderProgram, vPosition, vColor, uModelViewMatrix;

glm::mat4 mat_rotation, mat_translation, mat_ortho_proj, modelview_matrix, mat_view;

Model model;

const glm::vec3 pos_camera(0.0,0.0, -50.0);
const glm::vec4 bg_color(0.53, 0.80, 0.98, 1.0);

const GLfloat y_min = -50.0, y_max = 50.0, z_min_ortho = -2.0, z_min_persp = 0.1, z_max = 10000, unit_rotation = 3.14e-2, unit_translation = 1.0;
const GLfloat aspect_ratio = (GLfloat) WINDOW_WIDTH / WINDOW_HEIGHT;

const glm::mat4 id(1.0);

void initShadersGL(void)
{
  string vertex_shader_file("vshader.glsl");
  string fragment_shader_file("fshader.glsl");

  vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" );

  mat_ortho_proj = glm::ortho(y_min*aspect_ratio,y_max*aspect_ratio, y_min, y_max, z_min_ortho, z_max);
  mat_view = glm::lookAt(pos_camera, glm::vec3(0.0,0.0,1.0), glm::vec3(0.0,1.0,0.0));
}

void renderScene(GLFWwindow *window)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
  modelview_matrix = id;

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
  modelview_matrix = mat_translation * modelview_matrix;
  modelview_matrix = mat_view * modelview_matrix;
  modelview_matrix = mat_ortho_proj * modelview_matrix;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  model.render();

}

void centreToCentroid(){
  mat_translation = id;
}

GLuint getVao(){
  GLuint vao;
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray(vPosition);
  glEnableVertexAttribArray(vColor);
  return vao;
}


int main(int argc, char** argv)
{
  GLFWwindow* window = csX75::getWindow();

  initShadersGL();
  model = Model(vPosition,vColor,getVao(), GL_TRIANGLES);
  
  model.fromFile("ham.raw");
  model.fromFile("capt.raw");
  model.fromFile("arrow.raw");

  while (glfwWindowShouldClose(window) == 0)
  { 
    renderScene(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
