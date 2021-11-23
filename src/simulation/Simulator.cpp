#include "simulation.hpp"

void Simulator::update(Scene* scene) {
	const auto params = Configuration::getInstance()->getSimulationParams();
	auto iterations = params->iterations;
	const float delta_t = params->step / params->substeps;
	auto entities = scene->getEntities();

	this->gravity->apply(&scene->getEntities(), delta_t);

	for (int i = 0; i < entities.size(); i++) {
		auto object = entities.at(i)->getObject();
		for (int j = 0; j < object->getVertices()->size(); j++) {
			object->getVelocities()->at(j) *= 0.998f;
		}
	}

	// time step integration
	for (size_t step = 0; step < params->substeps; step++) {
		auto entities = scene->getEntities();
		for (int i = 0; i < entities.size(); i++) {
			this->semiImplicitEuler(entities.at(i), delta_t);
		}
	}

	
	for (int i = 0; i < iterations; i++) {
		for (auto constraint : scene->getConstraints()) {
			constraint->project();
		}
		/*
		std::ofstream myfile;
		myfile.open("test.csv", std::ios_base::app);
		auto x1 = scene->getEntities().at(0)->getObject()->getEstimate()->at(0);
		auto x2 = scene->getEntities().at(0)->getObject()->getEstimate()->at(1);
		auto x3 = scene->getEntities().at(0)->getObject()->getEstimate()->at(2);
		myfile << 0 << "," << x1.x << "," << x1.y << "," << x1.z << "\n";
		myfile << 1 << "," << x2.x << "," << x2.y << "," << x2.z << "\n";
		myfile << 2 << "," << x3.x << "," << x3.y << "," << x3.z << "\n";
		myfile.close();*/
	}

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
	for (int i = 0; i < positions->size(); i++) {
		const auto x = positions->at(i);
		const auto v = velocities->at(i);
		p->at(i) = x + delta_t * v;
	}
}

void Simulator::updatePositionsAndVelocities(Entity* entity, const float delta_t) {
	const auto object = entity->getObject();
	// #pragma omp parallel for
	for (int j = 0; j < object->getVertices()->size(); j++) {
		const auto p = object->getEstimate()->at(j);
		const auto x = object->getVertices()->at(j);
		// first order
		object->getVelocities()->at(j) = (p - x) / delta_t;
		object->getVertices()->at(j) = p;
	}
}

Simulator::Simulator() {
	this->gravity = new Gravity();
}