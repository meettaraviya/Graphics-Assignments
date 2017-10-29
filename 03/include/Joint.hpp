#ifndef _JOINT_HPP_
#define _JOINT_HPP_

#define HINGE_JOINT 0
#define BALL_JOINT 1

#include "Include.hpp"
#include "Part.hpp"

class Joint
{
	glm::mat4 init_transform;
	class Part *child, *parent;

public:
	Joint();
	virtual glm::mat4 getT() = 0;
	void draw(glm::mat4);
};

class HingeJoint:Joint
{
	GLfloat rot_angle, min_rot_angle, max_rot_angle;
	glm::vec3 axis;

public:
	HingeJoint();
	HingeJoint(GLfloat)
	glm::mat4 getT();
};

class BallJoint:Joint
{
	glm::vec3 axis;
	glm::mat4 rot_matrix;

public:
	BallJoint();
	glm::mat4 getT();
};

#endif