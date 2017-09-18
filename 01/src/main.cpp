#include "main.hpp"

#define WINDOW_WIDTH 768
#define WINDOW_HEIGHT 512

#define GRID_N 32
#define GRID_M 48
GLuint shaderProgram;
GLuint vbo_triangles, vao_triangles, vao_grid, vbo_grid;

// glm::mat4 rotation_matrix;
glm::mat4 mat_rotation;
glm::mat4 mat_view;
glm::mat4 mat_translation;
glm::mat4 mat_ortho_proj;
glm::mat4 mat_persp_proj;
glm::mat4 modelview_matrix;
GLuint uModelViewMatrix;

vector<glm::vec4> v_positions;
vector<glm::vec4> v_positions_loose;
vector<glm::vec4> v_grid_lines;
vector<glm::vec4> v_grid_line_colors;
glm::vec4 positions_sum;
vector<glm::vec4> v_colors;

glm::vec3 pos_camera(0.0,0.0, -50.0);
glm::vec4 bg_color(0.53, 0.80, 0.98, 1.0);

const GLfloat y_min = -50.0;
const GLfloat y_max = 50.0;
const GLfloat z_min_ortho = -2.0;
const GLfloat z_min_persp = 0.1;
const GLfloat z_max = 1e10;
const GLfloat aspect_ratio = (GLfloat) WINDOW_WIDTH / WINDOW_HEIGHT;
const glm::mat4 id(1.0);

enum Mode mode;

void generateGrid(){
  GLfloat y_gap = (y_max-y_min)/GRID_M;
  for(int i=1; i<GRID_M; i++){
    // v_grid_lines.push_back(glm::vec4(y_min*aspect_ratio, y_min+i*y_gap,100.0,0.0));
    // v_grid_lines.push_back(glm::vec4(y_max*aspect_ratio, y_min+i*y_gap,100.0,0.0));
    v_grid_lines.push_back(glm::vec4(-1.0, y_min+i*y_gap,0.0,0.0));
    v_grid_lines.push_back(glm::vec4(1.0, y_min+i*y_gap,0.0,0.0));
  }
  GLfloat x_gap = (y_max-y_min)*aspect_ratio/GRID_N;
  for(int i=1; i<GRID_N; i++){
    v_grid_lines.push_back(glm::vec4(y_min*aspect_ratio + i*x_gap, y_min,0.0,0.0));
    v_grid_lines.push_back(glm::vec4(y_min*aspect_ratio + i*x_gap, y_max,0.0,0.0));
  }
  v_grid_line_colors.resize(2*(GRID_N+GRID_M-2), glm::vec4(0.0,0.0,1.0,1.0));
}

void initBuffersGL(void)
{

  // glGenVertexArrays (1, &vao_grid);
  // glBindVertexArray (vao_grid);

  // glGenBuffers (1, &vbo_grid);
  // glBindBuffer (GL_ARRAY_BUFFER, vbo_grid);
  // glBufferData (GL_ARRAY_BUFFER, (v_grid_lines.size() + v_grid_line_colors.size()) * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
  // glBufferSubData( GL_ARRAY_BUFFER, 0, v_grid_lines.size() * sizeof(glm::vec4), v_grid_lines.data() );
  // glBufferSubData( GL_ARRAY_BUFFER, v_grid_lines.size() * sizeof(glm::vec4), v_grid_line_colors.size() * sizeof(glm::vec4), v_grid_line_colors.data() );

  // GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  // glEnableVertexAttribArray( vPosition );
  // GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
  // glEnableVertexAttribArray( vColor );
  // uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  // glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  // glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_grid_lines.size()*sizeof(glm::vec4)) );


////////////////////////////////////////////////////
  
  glGenVertexArrays (1, &vao_triangles);
  glBindVertexArray (vao_triangles);

  glGenBuffers (1, &vbo_triangles);
  glBindBuffer (GL_ARRAY_BUFFER, vbo_triangles);
  // cout << (v_positions.size() + v_colors.size()) * sizeof(glm::vec4) << endl;
  glBufferData (GL_ARRAY_BUFFER, (v_positions.size() + v_colors.size()) * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, v_positions.size() * sizeof(glm::vec4), v_positions.data() );
  glBufferSubData( GL_ARRAY_BUFFER, v_positions.size() * sizeof(glm::vec4), v_colors.size() * sizeof(glm::vec4), v_colors.data() );

  GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  glEnableVertexAttribArray( vPosition );
  GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
  glEnableVertexAttribArray( vColor );
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_positions.size()*sizeof(glm::vec4)) );


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

  mat_ortho_proj = glm::ortho(y_min*aspect_ratio,y_max*aspect_ratio, y_min, y_max, z_min_ortho, z_max);
  mat_persp_proj = glm::perspective((GLfloat) 45.0, aspect_ratio, z_min_persp, z_max);
  mat_view = glm::lookAt(pos_camera, glm::vec3(0.0,0.0,1.0), glm::vec3(0.0,1.0,0.0));
}

void loadModel(std::string file_name) {
  std::ifstream in_file;
  in_file.open(file_name.c_str());
  if (in_file.is_open()) {

    v_positions.clear();
    v_colors.clear();
    positions_sum = glm::vec4(0.0,0.0,0.0,0.0);

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

    // for (int i = 0; i < v_positions.size(); i++) {
    //   std::cout << v_positions[i][0] << " " << v_positions[i][1] << " " << v_positions[i][2] << std::endl;
    // }
    // std::cout << std::endl;
    // for (int i = 0; i < v_positions.size(); i++) {
    //   std::cout << v_colors[i][0] << " " << v_colors[i][1] << " " << v_colors[i][2] << std::endl;
    // }

    initBuffersGL();
    initShadersGL();

    glLoadMatrixf(glm::value_ptr(mat_rotation));
    glLoadIdentity();
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

void removePoint(){
  // cout << "remove" << endl;
  if(v_positions_loose.empty()){
    v_positions_loose.push_back(v_positions[v_positions.size()-3]);
    v_positions_loose.push_back(v_positions[v_positions.size()-2]);
    for(int i=0; i<3; i++){
      positions_sum = positions_sum - v_positions.back();
      v_positions.pop_back();
      v_colors.pop_back();
    }

  }
  else{
    v_positions_loose.pop_back();
  }
}

extern GLfloat modellingModeZ;

void drawPoint(double x, double y) {
  // cout << v_positions.size() << endl;
  // cout << x<< " "<<y<<endl;
  // cout << "draw" << endl;
  GLfloat y_actual = ((y-0)/WINDOW_HEIGHT)*(y_min-y_max) + y_max;
  GLfloat x_actual = ((x-0)/WINDOW_WIDTH)*(y_min-y_max)*aspect_ratio + y_max*aspect_ratio;
  glm::vec4 vec(x_actual, y_actual, modellingModeZ, 1.0);
  v_positions_loose.push_back(vec);
  if(v_positions_loose.size()==3){

    glm::vec4 color(0.0, 0.0, 0.0, 1.0);
    cout<<"Enter RGB color value"<<endl;
    for(int i=0;i<3;i++){
        cin>>color[i];
    }

    for(int j=0;j<3;j++){   
      positions_sum += v_positions_loose[j];
      v_positions.push_back(v_positions_loose[j]);
      v_colors.push_back(color);
    }

    v_positions_loose.clear();
    initBuffersGL();
  }
  
}

//-----------------------------------------------------------------

// void drawGrid(){
//   glBindBuffer (GL_ARRAY_BUFFER, 0);
//   glBindVertexArray(0);
//   glBindVertexArray(vao_grid);
//   glBindBuffer (GL_ARRAY_BUFFER, vbo_grid);
//   glDrawArrays(GL_LINES, 0, v_grid_lines.size());
//   glBindBuffer (GL_ARRAY_BUFFER, 0);
//   glBindVertexArray(0);
//   glBindBuffer (GL_ARRAY_BUFFER, vbo_triangles);
//   glBindVertexArray(vao_triangles);
// }


GLfloat unit_rotation = 3.14e-2;
GLfloat unit_translation = 1.0;

void renderModellingMode(GLFWwindow *window){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // drawGrid();

  modelview_matrix = mat_ortho_proj * mat_view;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  glDrawArrays(GL_TRIANGLES, 0, v_positions.size());
}

void renderInspectionMode(GLFWwindow *window)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(bg_color[0], bg_color[1], bg_color[2], bg_color[3]);
  modelview_matrix = glm::translate(id, (glm::vec3) -positions_sum/(GLfloat) v_positions.size());

  if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3(0.0, -1.0, 0.00))*mat_rotation;
  }
  if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3( 0.0, 1.0, 0.0))*mat_rotation;
  }
  if(glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3( -1.0, 0.0, 0.00))*mat_rotation;
  }
  if(glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3(1.0, 0.0, 0.0))*mat_rotation;
  }
  if(glfwGetKey(window, GLFW_KEY_PAGE_DOWN)==GLFW_PRESS){
    mat_rotation = glm::rotate(id,unit_rotation, glm::vec3(0.0, 0.0, 1.0))*mat_rotation;
  }
  if(glfwGetKey(window, GLFW_KEY_PAGE_UP)==GLFW_PRESS){
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
  glm::vec4 temp = modelview_matrix * positions_sum/(GLfloat) v_positions.size();
  for(int i=0; i<3; i++)
    cout << (positions_sum/(GLfloat) v_positions.size())[i] << " " << temp[i] << " ";
  cout << endl;
  modelview_matrix = mat_translation * modelview_matrix;
  modelview_matrix = mat_view * modelview_matrix;
  modelview_matrix = mat_persp_proj * modelview_matrix;

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  glDrawArrays(GL_TRIANGLES, 0, v_positions.size());

}

void centreToCentroid(){
  mat_translation = glm::translate(id, (glm::vec3) -positions_sum/(GLfloat) v_positions.size());
}

int main(int argc, char** argv)
{
  GLFWwindow* window;

  glfwSetErrorCallback(csX75::error_callback);

  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Computer graphics - Assignment 1", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    cerr<<"GLEW Init Failed : %s"<<endl;
  }

  cout<<"Vendor: "<<glGetString (GL_VENDOR)<<endl;
  cout<<"Renderer: "<<glGetString (GL_RENDERER)<<endl;
  cout<<"Version: "<<glGetString (GL_VERSION)<<endl;
  cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<endl;

  glfwSetKeyCallback(window, csX75::key_callback);
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
  glfwSetMouseButtonCallback(window, csX75::mouse_button_callback);
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  csX75::initGL();
  initShadersGL();
  generateGrid();
  loadModel("file.raw");

  mode = MODE_INSPECTION;
  cout<< "Inspection Mode" <<endl;

  while (glfwWindowShouldClose(window) == 0)
  { 
    if(mode==MODE_INSPECTION){
      renderInspectionMode(window);
    }
    else{
      renderModellingMode(window);
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
