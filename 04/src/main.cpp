#include "main.hpp"

GLFWwindow* window;

GLuint shaderProgram, vPosition, vColor, vUV, uModelViewMatrix, vIsTextured;

glm::mat4 modelview_matrix;

Model model;
vector<Frame>keyframe;
vector<int>numframe;
vector<Character> characters(2);
unsigned char *pixels;

int mode = RECORD;

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
  vUV = glGetAttribLocation( shaderProgram, "uv" );

  vIsTextured = glGetUniformLocation( shaderProgram, "isTextured" );
  uModelViewMatrix = glGetUniformLocation(shaderProgram, "uModelViewMatrix");

}
int screenShot(int frame_num)
{
  FILE   *out = fopen(("images/"+std::to_string(frame_num)+".tga").c_str(),"wb");
      char   *pixel_data = new char[3*WINDOW_WIDTH*WINDOW_HEIGHT];
      short  TGAhead[] = { 0, 2, 0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 24 };
      glReadBuffer(GL_FRONT);
      glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_BGR, GL_UNSIGNED_BYTE, pixel_data);

      fwrite(TGAhead,sizeof(TGAhead),1,out);
      fwrite(pixel_data, 3*WINDOW_WIDTH*WINDOW_HEIGHT, 1, out);
      fclose(out);

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


  if(mode==PLAYBACK){
    static int frame_num = 0;
    static double prev_time;
    while(glfwGetTime()<prev_time+TPF);
    prev_time = glfwGetTime();
    allframes[frame_num].frame_set();
    frame_num = (frame_num+1)%(allframes.size());
  }

  if(mode==RENDER){
    static int frame_num = 0;
    allframes[frame_num].frame_set();
    frame_num = (frame_num+1)%(allframes.size());
    screenShot(frame_num);
  }

  characters[0].render();
  // characters[1].render();
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
  fclose(modelFile);
}

int main(int argc, char** argv)
{
  window = csX75::getWindow();

  initShadersGL();
  model = Model(GL_TRIANGLES);
  characters[0] = Character(GL_TRIANGLES);
  characters[1] = Character(GL_TRIANGLES);

  characters[0].loadCharacter( (char*) "characters/spongebob.char");
  characters[1].loadCharacter( (char*) "characters/robot.char");

  Frame::count_params();

  cout << "\n\t[0] Playback \n\t[1] Record\nEnter mode:  ";
  cin >> mode;

  if(mode==PLAYBACK || mode==RENDER){
    load_keyframes();
    interpolate_frames();
  }


  while (glfwWindowShouldClose(window) == 0)
  {
    characters[0].update();
    characters[1].update();
    render(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}