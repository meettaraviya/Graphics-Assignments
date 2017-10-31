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
  Part(){}
  void draw(glm::mat4);
  void joinTo(Part* part, glm::vec3 attach_point);
  void fromFile(char *filename);
  void loadBuffers();
};

class Model{
  GLuint vao;

public:
  Part* root;
  // Model();
  void draw();
  void fromFile(char* filename);
};

#endif