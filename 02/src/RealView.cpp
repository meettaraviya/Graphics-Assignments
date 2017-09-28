#include "RealView.hpp"

namespace RealView{
	const GLfloat y_min = -50.0, y_max = 50.0, z_min = -1100.0, z_max = 1100.0, zoom_speed = 1.01;
	const GLfloat aspect_ratio = (GLfloat) WINDOW_WIDTH / WINDOW_HEIGHT;
	const glm::vec3 pos_camera(0.0,0.0, -50.0);
	const glm::mat4 mat_lookat = glm::lookAt(pos_camera, glm::vec3(0.0,0.0,1.0), glm::vec3(0.0,1.0,0.0));
	glm::mat4 mat_ortho_proj = glm::ortho(y_min*aspect_ratio,y_max*aspect_ratio, y_min, y_max, z_min, z_max);
	GLfloat zoom_scale = 1.0;
	const GLuint zoom_in_key = GLFW_KEY_X, zoom_out_key = GLFW_KEY_Z;
	void zoom(){
		if(glfwGetKey(window, zoom_in_key)==GLFW_PRESS){
		      zoom_scale *= zoom_speed;
		}
		if(glfwGetKey(window, zoom_out_key)==GLFW_PRESS){
		      zoom_scale /= zoom_speed;
		}
		mat_ortho_proj = glm::ortho(y_min*aspect_ratio/zoom_scale,y_max*aspect_ratio/zoom_scale, y_min/zoom_scale, y_max/zoom_scale, z_min, z_max);
	}
	void update(){
		zoom();
	}
};