#include "main.hpp"

GLFWwindow* window;

GLuint shaderProgram, vPosition, vColor, uModelViewMatrix;

glm::mat4 modelview_matrix;

Model model;
Character character;

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

void render(GLFWwindow *window)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);

  World::update();
  RealView::update();

  modelview_matrix = RealView::mat_proj * 
                      RealView::mat_lookat *
                      World::mat_translation *
                      World::mat_rotation;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  modelview_matrix = RealView::mat_proj * 
                      RealView::mat_lookat *
                      World::mat_translation *
                      World::mat_rotation;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  // model.render();
  character.render();

}


void loadScene(char* modelFileName){
  FILE *modelFile = fopen(modelFileName, "r");
  char rawFileName[20];
  glm::vec4 scale(0.0,0.0,0.0,1.0), rot(0.0,0.0,0.0,1.0), translate(0.0,0.0,0.0,1.0);
  int count;
  fscanf(modelFile, "%d", &count);
  for(int i=0;i<count;i++){
    fscanf(modelFile,"%s",rawFileName);
    fscanf(modelFile,"%f %f %f",&scale[0],&scale[1],&scale[2]);
    fscanf(modelFile,"%f %f %f",&rot[0],&rot[1],&rot[2]);
    fscanf(modelFile,"%f %f %f",&translate[0],&translate[1],&translate[2]);
    model.fromFile(rawFileName);
    model.scale(i,scale[0],scale[1],scale[2]);
    model.rotate(i,rot[0],rot[1],rot[2]);
    model.translate(i,translate[0],translate[1],translate[2]);
    model.loadBuffers(i);
  }

}

void loadCharacter(char* charFileName){
  FILE *charFile = fopen(charFileName, "r");
  char rawFileName[20];
  int count;
  fscanf(charFile, "%d", &count);
  for(int i=0;i<count;i++){
    fscanf(charFile,"%s",rawFileName);
    character.fromFile(rawFileName);
    character.loadBuffers(i);
  }
  int l, r;
  glm::vec3 pos;
  for(int i=0; i<count-1; i++){
    fscanf( charFile, "%d %d %f %f %f", &l, &r, &pos.x, &pos.y, &pos.z);
    character.addJoint(l, r, pos);
  }

}

int main(int argc, char** argv)
{
  window = csX75::getWindow();

  initShadersGL();
  model = Model(vPosition,vColor, GL_TRIANGLES);
  character = Character(vPosition,vColor, GL_TRIANGLES);

  loadScene( (char*) "scenes/myscene.scn");
  loadCharacter( (char*) "characters/1.char");

  while (glfwWindowShouldClose(window) == 0)
  { 
    character.update();
    render(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}