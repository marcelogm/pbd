#include "constraint.hpp"

BendConstraint::BendConstraint(Entity* entity, size_t x1, size_t x2, size_t x3, size_t x4, float dihedralAngle) {
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->x4 = x4;
	this->dihedralAngle = dihedralAngle;
}

void BendConstraint::project() {
}
