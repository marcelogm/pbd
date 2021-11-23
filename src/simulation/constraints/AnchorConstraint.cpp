#include "constraint.hpp"

AnchorConstraint::AnchorConstraint(Entity* entity, size_t i, vec3 fixed) {
	this->entity = entity;
	this->i = i;
	this->fixed = fixed;
}

void AnchorConstraint::project() {
	entity->getObject()->getEstimate()->at(i) = fixed;
}