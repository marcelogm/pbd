#include "constraint.hpp"

vector<Constraint*> RidigBodyConstraintFactory::create(Entity* entity) {
	vector<Constraint*> constraints;
	const auto object = entity->getObject();
	const auto vertices = object->getVertices();
	const auto size = vertices->size();
	for (size_t i = 0; i < size; i++) {
		for (size_t j = i + 1; j < size; j++) {
			const auto distance = glm::distance(vertices->at(i), vertices->at(j));
			auto constraint = new DistanceConstraint(entity, i, j, distance, 0.1);
			constraints.push_back(constraint);
		}
	}
	return constraints;
}