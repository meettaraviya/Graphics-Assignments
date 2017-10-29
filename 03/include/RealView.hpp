#ifndef _REALVIEW_HPP_
#define _REALVIEW_HPP_

#include "Include.hpp"

extern GLFWwindow* window;

namespace RealView{
	extern const GLfloat y_min, y_max, z_min, z_max, zoom_speed;
	extern const GLfloat aspect_ratio;
	extern const glm::vec3 pos_camera;
	extern const glm::mat4 mat_lookat;
	extern glm::mat4 mat_ortho_proj;
	extern GLfloat zoom_scale;
	extern const GLuint zoom_in_key, zoom_out_key;
	void zoom();
	void update();
};

#endif