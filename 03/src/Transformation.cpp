#include "Transformation.hpp"

const glm::mat4 id(1.0);

void Model::scale(int index, GLfloat sx, GLfloat sy, GLfloat sz){
	Part* part = parts[index];
	glm::mat4 mat_scale = glm::scale(id,{sx,sy,sz});
	for(int i=0; i < part->vertices.size(); i++){
		part->vertices[i] = mat_scale*part->vertices[i];
	}
}

void Model::rotate(int index, GLfloat rx, GLfloat ry, GLfloat rz){
	Part* part = parts[index];
	glm::mat4 mat_rotate = id;
	mat_rotate = glm::rotate(id,glm::radians(rx), glm::vec3(1.0, 0.0, 0.0))*mat_rotate;
	mat_rotate = glm::rotate(id,glm::radians(ry), glm::vec3(0.0, 1.0, 0.0))*mat_rotate;
	mat_rotate = glm::rotate(id,glm::radians(rz), glm::vec3(0.0, 0.0, 1.0))*mat_rotate;
	for(int i=0; i < part->vertices.size(); i++){
		part->vertices[i] = mat_rotate*part->vertices[i];
	}
}

void Model::translate(int index, GLfloat tx, GLfloat ty, GLfloat tz){
	Part* part = parts[index];
	glm::mat4 mat_translate = glm::translate(id,{tx,ty,tz});
	for(int i=0; i < part->vertices.size(); i++){
		part->vertices[i] = mat_translate*part->vertices[i];
	}
}

void Model::centre(int index){
	Part* part = parts[index];
	glm::vec4 vertices_sum({0.0,0.0,0.0,0.0});
	for(int i=0; i < part->vertices.size(); i++){
		vertices_sum += part->vertices[i];
	}
	glm::mat4 mat_centre = glm::translate(id, (glm::vec3) -vertices_sum/(GLfloat) part->vertices.size());;
	for(int i=0; i < part->vertices.size(); i++){
		part->vertices[i] = mat_centre*part->vertices[i];
	}
}
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
	
	void rotate(){
		for(int i=0; i<6; i++){
		    if(glfwGetKey(window, rotation_keys[i])==GLFW_PRESS){
		      mat_rotation = glm::rotate(id,unit_rotation, axes[i])*mat_rotation;
		    }
		}
	}

	void translate(){
		for(int i=0; i<4; i++){
		    if(glfwGetKey(window, translation_keys[i])==GLFW_PRESS){
		      mat_translation = glm::translate(mat_translation, unit_translation*axes[i]);
		    }
		}
	}

	void centre(){
		mat_translation = id;
	}

	void update(){
		rotate();
		translate();
	}
};