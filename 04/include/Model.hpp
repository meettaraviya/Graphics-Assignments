#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "Include.hpp"
#include "RealView.hpp"
#include "Transformation.hpp"

class Model{
protected:
	struct Part{
		vector<glm::vec4> vertices;
		vector<glm::vec4> colors;
		int num_textured;
		GLuint texture;
		unsigned int texture_width, texture_height;
		vector<glm::vec2> uvs;
		GLuint vbo;
		unsigned char* texture_data = NULL;
	};

	GLuint vao;
	int draw_mode;

public:
	vector<struct Part*> parts;
	Model(){}
	Model(int shape);
	void fromFile(char* inFileName);
	void loadBuffers(int index);
	void render();


	// defined in Transformation.cpp
	void scale(int index, GLfloat sx, GLfloat sy, GLfloat sz);
	void rotate(int index, GLfloat rx, GLfloat ry, GLfloat rz);
	void translate(int index, GLfloat tx, GLfloat ty, GLfloat tz);
	void centre(int index);


};

class Character: public Model{
	vector<glm::vec4> attach_points;
	vector<vector<int>> tree;
	void renderOne(int i, glm::mat4 parent_translate, glm::mat4 parent_rotate);

	GLfloat relative_rot_speed = 1.57e-2;
	GLuint relative_rot_keys[6] = {
	  GLFW_KEY_T,
	  GLFW_KEY_G,
	  GLFW_KEY_Y,
	  GLFW_KEY_H,
	  GLFW_KEY_U,
	  GLFW_KEY_J,
	};
public:
	vector<glm::vec3> val_rot;
	Character(){}
	Character(int shape);
	void render();
	void update();
	void fromFile(char* inFileName);
	void addJoint(int, int, glm::vec3);
	void loadCharacter(char* charFileName);

};

#endif