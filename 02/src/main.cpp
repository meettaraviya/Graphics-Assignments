#include "main.hpp"

GLFWwindow* window;

GLuint shaderProgram, vPosition, vColor, uModelViewMatrix;

glm::mat4 modelview_matrix;

Model model;
PointArray viewEye;
LineArray viewFrustum, viewAxes;

const glm::vec4 bg_color(0.2, 1.0, 0.2, 1.0);
const glm::vec4 eye_color(1.0, 0.0, 0.0, 1.0);

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

  // viewAxes.render();

  modelview_matrix = modelview_matrix *
                      View::mat_view;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  model.render();
  viewFrustum.render();
  viewEye.render();

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
    model.fromFile(rawFileName);
    model.scale(i,scale[0],scale[1],scale[2]);
    model.rotate(i,rot[0],rot[1],rot[2]);
    model.translate(i,translate[0],translate[1],translate[2]);
    model.loadBuffers(i);
  }

  fscanf(sceneFile,"%f %f %f",&View::eye[0],&View::eye[1],&View::eye[2]);
  fscanf(sceneFile,"%f %f %f",&View::lookat[0],&View::lookat[1],&View::lookat[2]);
  fscanf(sceneFile,"%f %f %f",&View::up[0],&View::up[1],&View::up[2]);
  fscanf(sceneFile,"%f %f %f %f %f %f",&View::l,&View::r,&View::t,&View::b,&View::n,&View::f);

  viewEye = PointArray(vPosition, vColor);
  viewEye.fromPoint(View::eye, eye_color);
  viewEye.loadBuffers(0);

  viewFrustum.loadFrustum();
  viewFrustum.loadBuffers(0);

  // viewAxes.loadAxes();
  // viewAxes.loadBuffers(0);

  cout << View::eye[0] << " " << View::eye[1] << " " << View::eye[2] << " " << endl;

}

int main(int argc, char** argv)
{
  window = csX75::getWindow();

  initShadersGL();
  model = Model(vPosition,vColor, GL_TRIANGLES);
  viewFrustum = LineArray(vPosition,vColor);
  viewAxes = LineArray(vPosition,vColor);

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