#include "View.hpp"

namespace View{
	glm::mat4 mat_view = id;
	glm::vec3 eye, lookat, up;
	GLfloat l,r,t,b,n,f;
	GLfloat L=0,R=1,T=1,B=0;

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
			{u[0],v[0],n[0],0.0},
			{u[1],v[1],n[1],0.0},
			{u[2],v[2],n[2],0.0},
			{0.0,0.0,0.0,1.0},
		});
		mat_view = rotate*eyeToOrigin*mat_view;
	}

	void VCStoCCS(){	
		glm::mat4 shear({
			{1.0, 0.0, 0.0, 0.0},
			{0.0, 1.0, 0.0, 0.0},
			{(r+l)/(2*n), (t+b)/(2*n), 1.0, 0.0},
			{0.0, 0.0, 0.0, 1.0},
		});

		glm::mat4 scale({
			{(2*n)/(r-l), 0.0, 0.0, 0.0},
			{0.0, (2*n)/(t-b), 0.0, 0.0},
			{0.0, 0.0, 1.0, 0.0},
			{0.0, 0.0, 0.0, 1.0}
		});

		glm::mat4 normalize({
			{1.0, 0.0, 0.0, 0.0},
			{0.0, 1.0, 0.0, 0.0},
			{0.0, 0.0, -(f+n)/(f-n), -1.0},
			{0.0, 0.0, -(2*f*n)/(f-n), 0.0},
		});
		mat_view = normalize*scale*shear*mat_view;

	}

	void CCStoNDCS(){

	}

	void NDCStoDCS(){
		glm::mat4 fittowindow({
			{(R-L)/2, 0.0, 0.0, 0.0},
			{0.0, (T-B)/2, 0.0, 0.0},
			{0.0, 0.0, 0.5, 0.0},
			{(R+L)/2, (T+B)/2, 0.5, 1.0},
		});
		mat_view = fittowindow*mat_view;
	}

};