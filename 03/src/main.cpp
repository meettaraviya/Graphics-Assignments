#include "main.hpp"

GLFWwindow* window;

GLuint shaderProgram, vPosition, vColor, vUV, uModelViewMatrix;

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
  vUV = glGetAttribLocation( shaderProgram, "uv" );

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
  fclose(modelFile);
}

GLuint loadTexture( const char * filename)
{
    GLuint texture;
    unsigned char header[54];// 54 Byte header of BMP
    int pos;
    unsigned int w,h;
    unsigned int size; //w*h*3
    unsigned char * data; // Data in RGB FORMAT
    FILE * file;
    
    file = fopen( filename, "rb" ); 
    if ( file == NULL ) return 0;  // if file is empty 
    if (fread(header,1,54,file)!=54)
      {
  printf("Incorrect BMP file\n");
  return 0;
      }

    // Read  MetaData
    pos = *(int*)&(header[0x0A]);
    size = *(int*)&(header[0x22]);
    w = *(int*)&(header[0x12]);
    h = *(int*)&(header[0x16]);

    //Just in case metadata is missing
    if(size == 0) 
      size = w*h*3;
    if(pos == 0)
      pos = 54;

    data = new unsigned char [size];

    fread( data, size, 1, file ); // read the file
    fclose( file );
    //////////////////////////

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
   

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    free( data );
    return texture;// return the texture id
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

  char textureFile[100];
  fscanf(charFile, "%s" , textureFile);

  GLuint texture = loadTexture(textureFile);

  fclose(charFile);

}

int main(int argc, char** argv)
{
  window = csX75::getWindow();

  initShadersGL();
  model = Model(GL_TRIANGLES);
  character = Character(GL_TRIANGLES);

  loadScene( (char*) "scenes/myscene.scn");
  loadCharacter( (char*) "characters/robot.char");

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