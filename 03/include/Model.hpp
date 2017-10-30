#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "Include.hpp"

class Part{
  glm::mat4 mat_rotation;
  vector<glm::vec4> vertices;
  vector<glm::vec4> colors;
  vector<Part*> joined_parts;
  GLuint vbo;

  glm::vec3 attach_point;

public:
  GLuint attrib_col, attrib_pos;
  Part(){}
  Part(GLuint vPosition, GLuint vColor);
  void draw(glm::mat4);
  void joinTo(Part* part, glm::vec3 attach_point);
  void fromFile(char *filename);

};

class Model{
  GLuint vao, attrib_col, attrib_pos;

public:
  Part* root;
  Model(){}
  Model(GLuint vPosition, GLuint vColor);
  void draw();
  void fromFile(char* filename);
};

#endif