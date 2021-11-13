#include "constraint.hpp"

AnchorConstraint::AnchorConstraint(Entity* entity, size_t x1, vec3 fixed) {
	this->entity = entity;
	this->x1 = x1;
	this->fixed = fixed;
}

void AnchorConstraint::project() {
	entity->getObject()->getEstimate()->at(x1) = fixed;
}