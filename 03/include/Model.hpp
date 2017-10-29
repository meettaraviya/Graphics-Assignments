#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "Include.hpp"
#include "Part.hpp"

class Model{
protected:
  GLuint vao, attrib_col, attrib_pos;

public:
  Part* root;
  Model(){}
  Model(GLuint vPosition, GLuint vColor);
  void draw();
  void fromFile(char* filename);
};
#endif