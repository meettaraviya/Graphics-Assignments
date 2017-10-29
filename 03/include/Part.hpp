#ifndef _PART_HPP_
#define _PART_HPP_

#include "Include.hpp"
#include "Joint.hpp"

class Part{
  vector<glm::vec4> vertices;
  vector<glm::vec4> colors;
  vector<class Joint*> joints;
  GLuint vbo;

public:
  GLuint attrib_col, attrib_pos;
  Part(){}
  Part(GLuint vPosition, GLuint vColor);
  void draw(glm::mat4);
  void addJoint(Joint* joint);
  void fromFile(char *filename);

};

#endif