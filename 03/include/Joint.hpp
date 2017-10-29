#ifndef _JOINT_HPP_
#define _JOINT_HPP_

#include "Include.hpp"
#include "Joint.hpp"
#include "Part.hpp"

class Joint
{
	glm::vec4 attach_point;
	Part *child, *parent;

public:
	Joint();
	virtual glm::mat4 getT() = 0;
	void draw();
};

class HingeJoint:Joint
{
	GLfloat rot_angle, min_rot_angle, max_rot_angle;
	glm::mat4 init_transform;
	glm::vec3 axis;

public:
	HingeJoint();
	glm::mat4 getT();
};

class BallJoint:Joint
{
	glm::mat4 init_transform;
	glm::vec3 axis;
	glm::mat4 rot_matrix;

public:
	HingeJoint();
	glm::mat4 getT();
};

#endif