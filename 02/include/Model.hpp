#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "Include.hpp"

class Model{

	struct Part{
		vector<glm::vec4> vertices;
		vector<glm::vec4> colors;
		GLuint vbo;
	};

	GLuint vao, attrib_col, attrib_pos;
	int draw_mode;
	vector<struct Part*> parts;

public:
	Model(){}
	Model(GLuint vPosition, GLuint vColor, int shape);
	void fromFile(string inFileName);
	void render();

	// defined in Transformation.cpp
	void scale(int index, GLfloat sx, GLfloat sy, GLfloat sz);
	void rotate(int index, GLfloat rx, GLfloat ry, GLfloat rz);
	void translate(int index, GLfloat tx, GLfloat ty, GLfloat tz);
	void centre(int index);

};

#endif