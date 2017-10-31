#include "main.hpp"

GLFWwindow* window;

GLuint shaderProgram, vPosition, vColor, uModelViewMatrix, uPartMatrix;

glm::mat4 modelview_matrix;

<<<<<<< HEAD
Scene* scene, *scene2;
Model* model;
=======
Model model;
Character character;
>>>>>>> d95e54389d24f980f7e8dea61f115a16b1699a64

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

  uModelViewMatrix = glGetUniformLocation(shaderProgram, "uModelViewMatrix");
  uPartMatrix = glGetUniformLocation(shaderProgram, "uPartMatrix");

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

<<<<<<< HEAD
  model->draw();
  scene->render();
  scene2->render();
=======
  modelview_matrix = RealView::mat_proj * 
                      RealView::mat_lookat *
                      World::mat_translation *
                      World::mat_rotation;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  // model.render();
  character.render();
>>>>>>> d95e54389d24f980f7e8dea61f115a16b1699a64

}


void loadScene(char* modelFileName){
  FILE *modelFile = fopen(modelFileName, "r");
  char rawFileName[20];
  glm::vec4 scale(0.0,0.0,0.0,1.0), rot(0.0,0.0,0.0,1.0), translate(0.0,0.0,0.0,1.0);
<<<<<<< HEAD
  for(int i=0;i<3;i++){
    fscanf(sceneFile,"%s",rawFileName);
    fscanf(sceneFile,"%f %f %f",&scale[0],&scale[1],&scale[2]);
    fscanf(sceneFile,"%f %f %f",&rot[0],&rot[1],&rot[2]);
    fscanf(sceneFile,"%f %f %f",&translate[0],&translate[1],&translate[2]);
    scene->fromFile(rawFileName);
    scene->scale(i,scale[0],scale[1],scale[2]);
    scene->rotate(i,rot[0],rot[1],rot[2]);
    scene->translate(i,translate[0],translate[1],translate[2]);
    scene->loadBuffers(i);
=======
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
>>>>>>> d95e54389d24f980f7e8dea61f115a16b1699a64
  }
  fclose(sceneFile);
}

void loadScene2(char* sceneFileName){
  FILE *sceneFile = fopen(sceneFileName, "r");
  char rawFileName[20];
  glm::vec4 scale(0.0,0.0,0.0,1.0), rot(0.0,0.0,0.0,1.0), translate(0.0,0.0,0.0,1.0);
  for(int i=0;i<3;i++){
    fscanf(sceneFile,"%s",rawFileName);
    fscanf(sceneFile,"%f %f %f",&scale[0],&scale[1],&scale[2]);
    fscanf(sceneFile,"%f %f %f",&rot[0],&rot[1],&rot[2]);
    fscanf(sceneFile,"%f %f %f",&translate[0],&translate[1],&translate[2]);
    scene2->fromFile(rawFileName);
    scene2->scale(i,scale[0],scale[1],scale[2]);
    scene2->rotate(i,rot[0],rot[1],rot[2]);
    scene2->translate(i,translate[0],translate[1],translate[2]);
    scene2->loadBuffers(i);
  }
  fclose(sceneFile);
}

int main(int argc, char** argv)
{
  window = csX75::getWindow();
  initShadersGL();
<<<<<<< HEAD

  scene = new Scene(GL_TRIANGLES);
  scene2 = new Scene(GL_TRIANGLES);
  model = new Model();

  loadScene((char*) "scenes/myscene.scn");
  loadScene2((char*) "scenes/myscene2.scn");
  model->fromFile((char*) "characters/test.char");
=======
  model = Model(vPosition,vColor, GL_TRIANGLES);
  character = Character(vPosition,vColor, GL_TRIANGLES);

  loadScene( (char*) "scenes/myscene.scn");
  loadCharacter( (char*) "characters/1.char");
>>>>>>> d95e54389d24f980f7e8dea61f115a16b1699a64

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