#include "Joint.hpp"

void Joint::draw(glm::mat4 parent_transform){
	glm::mat4 child_transform = glm::translate(id, attach_point) * mat_rotation * glm::translate(id, -attach_point);
	child->draw(child_transform);
}

Joint::Joint(Part* parent, Part* child, glm::vec3 attach_point){
	this->parent = parent;
	this->child = child;
	this->attach_point = attach_point;
}