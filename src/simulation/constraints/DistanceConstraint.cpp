#include "constraint.hpp"
#include <glm/gtx/norm.hpp> 

DistanceConstraint::DistanceConstraint(Entity* current, size_t x1, size_t x2, float distance) {
	this->current = current;
	this->next = nullptr;
	this->x1 = x1;
	this->x2 = x2;
	// rest
	this->distance = distance;
}

void DistanceConstraint::project() {
	auto object = current->getObject();
	// auto p2 = current->getVelocities()->at(x2);

	// float a = glm::l2Norm(p1 - p2) - this->distance;

}
