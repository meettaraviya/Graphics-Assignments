#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "Include.hpp"
#include "View.hpp"

class Model{
protected:
	struct Part{
		vector<glm::vec4> vertices;
		vector<glm::vec4> colors;
		GLuint vbo;
	};

	GLuint vao, attrib_col, attrib_pos;
	int draw_mode;

public:
	vector<struct Part*> parts;
	Model(){}
	Model(GLuint vPosition, GLuint vColor, int shape);
	void fromFile(char* inFileName);
	void loadBuffers(int index);
	void render();

	// defined in Transformation.cpp
	void scale(int index, GLfloat sx, GLfloat sy, GLfloat sz);
	void rotate(int index, GLfloat rx, GLfloat ry, GLfloat rz);
	void translate(int index, GLfloat tx, GLfloat ty, GLfloat tz);
	void centre(int index);


};

class LineArray: public Model{
	static constexpr GLfloat lineWidth = 10.0;
	static constexpr GLfloat lineLength = 1000.0;
	static glm::vec4 axesColors[6];
public:
	glm::vec4 frustumCenter;
	LineArray(){}
	LineArray(GLuint vPosition, GLuint vColor);
	void loadFrustum();
	void loadAxes();
};

class PointArray: public Model{
	static constexpr GLfloat pointSize = 10.0;
public:
	PointArray(){}
	PointArray(GLuint vPosition, GLuint vColor);
	void fromPoint(glm::vec3 point, glm::vec4 color);
};


extern LineArray viewFrustum, viewAxes;

#endif