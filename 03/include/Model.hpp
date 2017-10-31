#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "Include.hpp"
<<<<<<< HEAD

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
=======
#include "RealView.hpp"
#include "Transformation.hpp"

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

class Character: public Model{
	vector<glm::mat4> mats_relative_rot;
	vector<glm::vec4> attach_points; 
	vector<vector<int>> tree;
	void renderOne(int i, glm::mat4 parent_transform);

	GLfloat relative_rot_speed = 15.7e-2;
	GLuint relative_rot_keys[6] = {
	  GLFW_KEY_R,
	  GLFW_KEY_F,
	  GLFW_KEY_T,
	  GLFW_KEY_G,
	  GLFW_KEY_Y,
	  GLFW_KEY_H,
	};
public:
	Character(){}
	Character(GLuint vPosition, GLuint vColor, int shape);
	void render();
	void update();
	void fromFile(char* inFileName);
	void addJoint(int, int, glm::vec3);
>>>>>>> d95e54389d24f980f7e8dea61f115a16b1699a64
};

#endif