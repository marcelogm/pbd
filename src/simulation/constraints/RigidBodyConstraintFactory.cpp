#include "constraint.hpp"

vector<Constraint*> RidigBodyConstraintFactory::createWithFixedStiffness(Entity* entity, float stiffness) {
	vector<Constraint*> constraints;
	const auto object = entity->getObject();
	const auto vertices = object->getVertices();
	const auto size = vertices->size();
	for (size_t i = 0; i < size; i++) {
		for (size_t j = i + 1; j < size; j++) {
			const auto distance = glm::l2Norm(vertices->at(i), vertices->at(j));
			auto constraint = new DistanceConstraint(entity, i, j, distance, stiffness);
			constraints.push_back(constraint);
		}
	}
	return constraints;
}

vector<Constraint*> RidigBodyConstraintFactory::create(Entity* entity) {
	vector<Constraint*> constraints;
	const auto object = entity->getObject();
	const auto vertices = object->getVertices();
	const auto size = vertices->size();
	for (size_t i = 0; i < size; i++) {
		for (size_t j = i + 1; j < size; j++) {
			const auto distance = glm::l2Norm(vertices->at(i), vertices->at(j));
			auto constraint = new DistanceConstraint(entity, i, j, distance);
			constraints.push_back(constraint);
		}
	}
	return constraints;
}

