#ifndef _TRANSFORMATION_HPP_
#define _TRANSFORMATION_HPP_

#include "Include.hpp"
#include "Model.hpp"

extern GLFWwindow* window;

namespace RealView{
	const GLfloat y_min = -50.0, y_max = 50.0, z_min = -2.0, z_max = 10000;
	const GLfloat aspect_ratio = (GLfloat) WINDOW_WIDTH / WINDOW_HEIGHT;
	const glm::vec3 pos_camera(0.0,0.0, -50.0);
	const glm::mat4 mat_lookat = glm::lookAt(pos_camera, glm::vec3(0.0,0.0,1.0), glm::vec3(0.0,1.0,0.0));
	glm::mat4 mat_ortho_proj = glm::ortho(y_min*aspect_ratio,y_max*aspect_ratio, y_min, y_max, z_min, z_max);
	const GLuint zoom_in_key = GLFW_KEY_X, zoom_out_key = GLFW_KEY_Z;
};

namespace World{
	glm::mat4 mat_rotation, mat_translation;
	const GLfloat unit_rotation = 3.14e-2, unit_translation = 1.0;
	const glm::vec3 axes[6] = {
	  glm::vec3(1.0, 0.0, 0.0),
	  glm::vec3(-1.0, 0.0, 0.0),
	  glm::vec3(0.0, 1.0, 0.0),
	  glm::vec3(0.0, -1.0, 0.0),
	  glm::vec3(0.0, 0.0, 1.0),
	  glm::vec3(0.0, 0.0, -1.0),
	};
	const GLuint rotation_keys[6] = {
	  GLFW_KEY_UP,
	  GLFW_KEY_DOWN,
	  GLFW_KEY_RIGHT,
	  GLFW_KEY_LEFT,
	  GLFW_KEY_PAGE_DOWN,
	  GLFW_KEY_PAGE_UP,
	};
	const GLuint translation_keys[6] = {
	  GLFW_KEY_A,
	  GLFW_KEY_D,
	  GLFW_KEY_W,
	  GLFW_KEY_S,
	  GLFW_KEY_X,
	  GLFW_KEY_Z,
	};
	void rotate();
	void translate();
	void centre();
	void update();
};

#endif