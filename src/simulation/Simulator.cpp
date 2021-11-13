#include "simulation.hpp"

void Simulator::update(Scene* scene) {
	auto iterations = Configuration::getInstance()->getSimulationParams()->iterations;
	const size_t subSteps = 5;
	const float delta_t = 0.005f / subSteps;
	auto entities = scene->getEntities();

	// semi implicit euler 
	for (size_t step = 0; step < subSteps; step++) {
		auto entities = scene->getEntities();
		for (size_t i = 0; i < entities.size(); i++) {
			this->semiImplicitEuler(entities.at(i), delta_t);
		}
	}

	// collision constraints
	for (int i = 0; i < iterations; i++) {
		for (auto constraint : scene->getConstraints()) {
			constraint->project();
		}
	}

	// update positions and velocities
	for (size_t i = 0; i < entities.size(); i++) {
		auto entity = entities.at(i);
		this->updatePositionsAndVelocities(entity, delta_t);
	}
}

void Simulator::semiImplicitEuler(Entity* entity, const float delta_t) {
	const auto object = entity->getObject();
	const auto positions = object->getVertices();
	const auto velocities = object->getVelocities();
	auto p = object->getEstimate();
	for (size_t i = 0; i < positions->size(); i++) {
		const auto x = positions->at(i);
		const auto v = velocities->at(i);
		p->at(i) = x + delta_t * v;
	}
}

void Simulator::updatePositionsAndVelocities(Entity* entity, const float delta_t) {
	const auto object = entity->getObject();
	for (size_t j = 0; j < object->getVertices()->size(); j++) {
		const auto p = object->getEstimate()->at(j);
		const auto x = object->getVertices()->at(j);
		// first order
		object->getVelocities()->at(j) = (p - x) / delta_t;
		object->getVertices()->at(j) = p;
	}
}