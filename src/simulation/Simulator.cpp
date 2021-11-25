#include "simulation.hpp"

void Simulator::update(Scene* scene) {
	const auto params = Configuration::getInstance()->getSimulationParams();
	const auto iterations = params->iterations;
	const auto delta_t = params->step / params->substeps;
	auto entities = scene->getEntities();

	// apply external forces
	this->externalForces->apply(&scene->getEntities(), delta_t);


	// integrate
	for (size_t step = 0; step < params->substeps; step++) {
		auto entities = scene->getEntities();
		for (int i = 0; i < entities.size(); i++) {
			this->semiImplicitEuler(entities.at(i), delta_t);
		}
	}
	
	// solve 
	for (int i = 0; i < iterations; i++) {
		for (auto constraint : scene->getConstraints()) {
			constraint->project();
		}

#ifdef DEBUG
		auto to_debug = entities.at(0)->getObject();
		std::ofstream outfile("k_0_10_30_it.csv", std::ios_base::app);
		outfile << "0" << ","
			<< to_debug->getEstimate()->at(0).x << ","
			<< to_debug->getEstimate()->at(0).y << ","
			<< to_debug->getEstimate()->at(0).z << "\n";
		outfile << "1" << ","
			<< to_debug->getEstimate()->at(1).x << ","
			<< to_debug->getEstimate()->at(1).y << ","
			<< to_debug->getEstimate()->at(1).z << "\n";
		outfile << "2" << ","
			<< to_debug->getEstimate()->at(2).x << ","
			<< to_debug->getEstimate()->at(2).y << ","
			<< to_debug->getEstimate()->at(2).z << "\n";
		outfile.close();
#endif
	}

	// update vertices and velocities (momentum)
	for (size_t i = 0; i < entities.size(); i++) {
		auto entity = entities.at(i);
		this->updatePositionsAndVelocities(entity, delta_t);
	}

	// velocity update: dump velocities 
	for (int i = 0; i < entities.size(); i++) {
		auto object = entities.at(i)->getObject();
		for (int j = 0; j < object->getVertices()->size(); j++) {
			object->getVelocities()->at(j) *= 0.998f;
		}
	}
}

void Simulator::semiImplicitEuler(Entity* entity, const float delta_t) {
	const auto object = entity->getObject();
	const auto positions = object->getVertices();
	const auto velocities = object->getVelocities();
	auto p = object->getEstimate();
	for (int i = 0; i < positions->size(); i++) {
		const auto x = positions->at(i);
		const auto v = velocities->at(i);
		p->at(i) = x + delta_t * v;
	}
}

void Simulator::updatePositionsAndVelocities(Entity* entity, const float delta_t) {
	const auto object = entity->getObject();
	for (int j = 0; j < object->getVertices()->size(); j++) {
		const auto p = object->getEstimate()->at(j);
		const auto x = object->getVertices()->at(j);
		object->getVelocities()->at(j) = (p - x) / delta_t;
		object->getVertices()->at(j) = p;
	}
}

Simulator::Simulator() {
	this->externalForces = new ExternalForce();
}