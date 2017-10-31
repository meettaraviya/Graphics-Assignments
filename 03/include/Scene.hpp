#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include "Include.hpp"

class Scene{
protected:
	struct Scene_Element{
		vector<glm::vec4> vertices;
		vector<glm::vec4> colors;
		GLuint vbo;
	};

	GLuint vao;
	int draw_mode;

public:
	vector<struct Scene_Element*> scene_elements;
	Scene(){}
	Scene(int shape);
	void fromFile(char* inFileName);
	void loadBuffers(int index);
	void render();

	void scale(int index, GLfloat sx, GLfloat sy, GLfloat sz);
	void rotate(int index, GLfloat rx, GLfloat ry, GLfloat rz);
	void translate(int index, GLfloat tx, GLfloat ty, GLfloat tz);
	void centre(int index);


};

#endif