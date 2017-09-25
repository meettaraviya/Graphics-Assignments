#include "main.hpp"

GLFWwindow* window;

GLuint shaderProgram, vPosition, vColor, uModelViewMatrix;

glm::mat4 modelview_matrix;

Model model;

const glm::vec4 bg_color(0.53, 0.80, 0.98, 1.0);

void initShadersGL(void)
{
  string vertex_shader_file("shaders/vshader.glsl");
  string fragment_shader_file("shaders/fshader.glsl");

  vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" );

}

void renderScene(GLFWwindow *window)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);

  World::update();

  modelview_matrix = RealView::mat_ortho_proj * 
                      RealView::mat_lookat *
                      World::mat_translation *
                      World::mat_rotation;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  model.render();

}

int main(int argc, char** argv)
{
  window = csX75::getWindow();

  initShadersGL();
  model = Model(vPosition,vColor, GL_TRIANGLES);
  
  model.fromFile("models/ham.raw");
  model.fromFile("models/capt.raw");
  model.fromFile("models/arrow.raw");
  model.scale(1,2,3,4);

  while (glfwWindowShouldClose(window) == 0)
  { 
    renderScene(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}