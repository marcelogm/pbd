#include "constraint.hpp"

vector<Constraint*> RidigBodyConstraintFactory::create(Entity* entity) {
	vector<Constraint*> constraints;
	const auto object = entity->getObject();
	const auto indexes = object->getVertices();
	const auto size = indexes->size();
	for (size_t i = 0; i < size; i++) {
		for (size_t j = i + 1; j < size; j++) {
			const auto distance = glm::distance(indexes->at(i), indexes->at(j));
			auto constraint = new DistanceConstraint(entity, i, j, distance);
			constraints.push_back(constraint);
		}
	}
	return constraints;
}