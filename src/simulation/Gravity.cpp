#include "simulation.hpp"

void Gravity::apply(vector<Entity*>* entities) {
	const auto delta = (float)Frametime::getInstance()->getDelta();
	const auto params = Configuration::getInstance()->getSimulationParams();

	for (size_t i = 0; i < entities->size(); i++) {
		Entity* entity = entities->at(i);
		for (size_t j = 0; j < entity->getVertices()->size() && entity->isAffectedByGravity(); j++) {
			vector<vec3>* vertices = entity->getVertices();
			vertices->at(j) = vertices->at(j) + ((delta * vec3(0.f, -this->ACCELERATION, 0.f)) * params->gravityModifier);
		}
	}
}