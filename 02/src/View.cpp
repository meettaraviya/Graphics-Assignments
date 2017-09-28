#include "View.hpp"

namespace View{
	glm::mat4 mat_view = id;
	glm::vec3 eye, lookat, up;
	GLfloat l,r,t,b,n,f;
	
	glm::vec3 getN(){
		return (eye-lookat)/glm::length(eye-lookat);
	}
	glm::vec3 getU(){
		glm::vec3 u = glm::cross(up, getN());
		glm::normalize(u);
		return u;
	}
	glm::vec3 getV(){
		return glm::cross(getN(),getU());
	}

	void reset(){
		mat_view = id;
	}

	void WCStoVCS(){
		glm::mat4 eyeToOrigin({
			{1.0, 0.0, 0.0, 0.0},
			{0.0, 1.0, 0.0, 0.0},
			{0.0, 0.0, 1.0, 0.0},
			{-eye[0], -eye[1], -eye[2], 1.0},
		});
		glm::vec3 n = getN(), v = getV(), u = getU();
		glm::mat4 rotate({
			{u[0],u[1],u[2],0.0},
			{v[0],v[1],v[2],0.0},
			{n[0],n[1],n[2],0.0},
			{ 0.0, 0.0, 0.0,1.0},
		});
		mat_view = eyeToOrigin*mat_view;
	}

	void VCStoCCS(){

	}

	void CCStoNDCS(){

	}

	void NDCStoDCS(){

	}

};