#ifndef _JOINT_HPP_
#define _JOINT_HPP_

#define HINGE_JOINT 0
#define BALL_JOINT 1

#include "Include.hpp"
#include "Part.hpp"

class Joint
{
	class Part *child, *parent;
	glm::vec3 attach_point;
	glm::mat4 mat_rotation;

public:
	Joint();
	glm::mat4 getT();
	void draw(glm::mat4);
	Joint(Part* parent, Part* child, glm::vec3 attach_point);
};

// class HingeJoint:Joint
// {
// 	GLfloat rot_angle, min_rot_angle, max_rot_angle;
// 	glm::vec3 axis;

// public:
// 	HingeJoint();
// 	HingeJoint(GLfloat)
// 	glm::mat4 getT();
// };

// class BallJoint:Joint
// {
// 	glm::vec3 axis;
// 	glm::mat4 rot_matrix;

// public:
// 	BallJoint();
// 	glm::mat4 getT();
// };

#endif