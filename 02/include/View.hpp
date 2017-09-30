#ifndef _VIEW_HPP_
#define _VIEW_HPP_

#include "Include.hpp"

namespace View{
	extern glm::mat4 mat_view;
	extern glm::vec3 eye, lookat, up;
	extern GLfloat l,r,t,b,n,f;
	extern GLfloat L,R,T,B;
	extern GLuint divideByW;

	glm::vec3 getV();
	glm::vec3 getU();
	glm::vec3 getN();

	void reset();
	void WCStoVCS();
	void VCStoCCS();
	void CCStoNDCS();
	void NDCStoDCS();

	inline void toVCS(){reset(); WCStoVCS();}
	inline void toCCS(){toVCS(); VCStoCCS();}
	inline void toNDCS(){toCCS(); CCStoNDCS();}
	inline void toDCS(){toNDCS(); NDCStoDCS();}
};

#endif