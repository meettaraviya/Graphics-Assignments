#include "Model.cpp"

using namespace std;

Model::Model(GLuint vPosition, GLuint vColor){
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  glEnableVertexAttribArray(vPosition);
  glEnableVertexAttribArray(vColor);
  
  attrib_pos = vPosition;
  attrib_col = vColor;
}

void Model::draw(){
  glBindVertexArray (vao);
  Part::draw();
}