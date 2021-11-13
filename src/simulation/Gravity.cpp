#include "simulation.hpp"

void Gravity::apply(vector<Entity*>* entities, float delta_t) {
	const auto params = Configuration::getInstance()->getSimulationParams();

	for (size_t i = 0; i < entities->size(); i++) {
		if (entities->at(i)->isAffectedByGravity()) {
			Object* object = entities->at(i)->getObject();
			for (size_t j = 0; j < object->getVelocities()->size(); j++) {
				vector<vec3>* velocities = object->getVelocities();
				velocities->at(j) += ((delta_t * vec3(0.f, -this->ACCELERATION, 0.f)) * params->gravityModifier * 10.f);
			}
		}
	}
}