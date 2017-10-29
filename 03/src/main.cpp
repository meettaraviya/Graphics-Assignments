#include "main.hpp"

GLFWwindow* window;

GLuint shaderProgram, vPosition, vColor, uModelViewMatrix;

glm::mat4 modelview_matrix;

Scene scene;
PointArray viewEye;
// LineArray viewFrustum, viewAxes;

const glm::vec4 bg_color(0.95, 0.95, 0.95, 1.0);

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
  RealView::update();

  modelview_matrix = RealView::mat_ortho_proj * 
                      RealView::mat_lookat *
                      World::mat_translation *
                      World::mat_rotation;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  modelview_matrix = RealView::mat_ortho_proj * 
                      RealView::mat_lookat *
                      World::mat_translation *
                      World::mat_rotation;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  scene.render();

}


void loadScene(char* sceneFileName){
  FILE *sceneFile = fopen(sceneFileName, "r");
  char rawFileName[20];
  glm::vec4 scale(0.0,0.0,0.0,1.0), rot(0.0,0.0,0.0,1.0), translate(0.0,0.0,0.0,1.0);
  for(int i=0;i<3;i++){
    fscanf(sceneFile,"%s",rawFileName);
    fscanf(sceneFile,"%f %f %f",&scale[0],&scale[1],&scale[2]);
    fscanf(sceneFile,"%f %f %f",&rot[0],&rot[1],&rot[2]);
    fscanf(sceneFile,"%f %f %f",&translate[0],&translate[1],&translate[2]);
    scene.fromFile(rawFileName);
    scene.scale(i,scale[0],scale[1],scale[2]);
    scene.rotate(i,rot[0],rot[1],rot[2]);
    scene.translate(i,translate[0],translate[1],translate[2]);
    scene.loadBuffers(i);
  }

}

int main(int argc, char** argv)
{
  window = csX75::getWindow();

  initShadersGL();
  scene = Scene(vPosition,vColor, GL_TRIANGLES);

  loadScene( (char*) "scenes/myscene.scn");

  while (glfwWindowShouldClose(window) == 0)
  { 
    renderScene(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}