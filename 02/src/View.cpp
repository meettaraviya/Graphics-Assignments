#include "View.hpp"
#include "Model.hpp"

namespace View{
	glm::mat4 mat_view = id;
	glm::vec3 eye, lookat, up;
	GLfloat l,r,t,b,n,f;
	GLfloat L=0,R=WINDOW_WIDTH,T=WINDOW_HEIGHT,B=0;

	glm::vec3 getN(){
		return glm::normalize(eye-lookat);
	}
	glm::vec3 getU(){
		return glm::normalize(glm::cross(up, eye-lookat));
	}
	glm::vec3 getV(){
		return glm::normalize(glm::cross(eye-lookat, glm::cross(up, eye-lookat)));
	}
	void reset(){
		mat_view = id;

		glm::vec3 n=getN(), v=getV(), u=getU();
		for(int i=0; i<3; i++){
			cout << n[i] << " " << u[i] << " " << v[i] << endl; 
		}

		cout << endl << "Reset" << endl;
		int vert[9] = {0,1,5,4,8,9,13,12,24};
		for(int i=0; i<9; i++){
			glm::vec4 out = mat_view* viewFrustum.parts[0]->vertices[vert[i]];
			cout << out[0] << " " << out[1] << " " << out[2] << endl;	
		}
		cout << endl;
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

		cout << "WCStoVCS" << endl;
		int vert[9] = {0,1,5,4,8,9,13,12,24};
		for(int i=0; i<9; i++){
			glm::vec4 out = mat_view* viewFrustum.parts[0]->vertices[vert[i]];
			cout << out[0] << " " << out[1] << " " << out[2] << endl;	
		}
		cout << endl;
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


		cout << "VCStoCCS" << endl;
		int vert[9] = {0,1,5,4,8,9,13,12,24};
		for(int i=0; i<9; i++){
			glm::vec4 out = mat_view* viewFrustum.parts[0]->vertices[vert[i]];
			cout << out[0] << " " << out[1] << " " << out[2] << endl;	
		}
		cout << endl;

	}

	void CCStoNDCS(){

		cout << "CCStoNDCS" << endl;
		int vert[9] = {0,1,5,4,8,9,13,12,24};
		for(int i=0; i<9; i++){
			glm::vec4 out = mat_view* viewFrustum.parts[0]->vertices[vert[i]];
			cout << out[0] << " " << out[1] << " " << out[2] << endl;	
		}
		cout << endl;
	}

	void NDCStoDCS(){
		glm::mat4 fitToWindow({
			{(R-L)/2, 0.0, 0.0, 0.0},
			{0.0, (T-B)/2, 0.0, 0.0},
			{0.0, 0.0, 0.5, 0.0},
			{(R+L)/2, (T+B)/2, 0.5, 1.0},
		});
		mat_view = fitToWindow*mat_view;


		cout << "NDCStoDCS" << endl;
		int vert[9] = {0,1,5,4,8,9,13,12,24};
		for(int i=0; i<9; i++){
			glm::vec4 out = mat_view* viewFrustum.parts[0]->vertices[vert[i]];
			cout << out[0] << " " << out[1] << " " << out[2] << endl;	
		}
		cout << endl;
	}

};