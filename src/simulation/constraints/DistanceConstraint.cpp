#include "constraint.hpp"

void DistanceConstraint::precomputeInverseMassCoeff() {
	// inverse masses precomputation
	auto w_1 = current->getObject()->getMasses()->at(i1).inverse;
	auto w_2 = current->getObject()->getMasses()->at(i2).inverse;
	this->scalarMatrix = MatrixXf::Zero(2, 2);
	this->scalar_1 = 1.f / (w_1 / (w_1 + w_2));
	this->scalar_2 = 1.f / (w_2 / (w_1 + w_2));
	this->scalarMatrix.coeffRef(0, 0) = this->scalar_1;
	this->scalarMatrix.coeffRef(1, 1) = this->scalar_2;
}

DistanceConstraint::DistanceConstraint(Entity* current, size_t i1, size_t i2, float distance) {
	this->current = current;
	this->next = nullptr;
	this->i1 = i1;
	this->i2 = i2;
	this->distance = distance;
	this->stiffness = NULL;
	this->precomputeInverseMassCoeff();
}

DistanceConstraint::DistanceConstraint(Entity* current, size_t i1, size_t i2, float distance, float stiffness) {
	this->current = current;
	this->next = nullptr;
	this->i1 = i1;
	this->i2 = i2;
	this->distance = distance;
	this->stiffness = stiffness;
	this->precomputeInverseMassCoeff();
}

void DistanceConstraint::project() {
	auto params = Configuration::getInstance()->getSimulationParams();
	auto iterations = params->iterations;
	auto stiffness = this->stiffness == NULL ? params->stiffness : this->stiffness;

	auto object = current->getObject();
	auto p1 = object->getEstimate()->at(i1);
	auto p2 = object->getEstimate()->at(i2);

	// distance_constraint = | x_{1,2} - d |
	auto error = glm::l2Norm(p1 - p2) - distance;

	// gradient_x_1 C(x_1, x_2) = n
	// gradient_x_2 C(x_1, x_2) = -n
	// n = x_{1,2} / | x_{1,2} |
	vec3 gradient = (p1 - p2) / (float)(glm::l2Norm(p1 - p2) + 0.1);

	vec3 delta_p_1; 
	vec3 delta_p_2;

	// Esse é um experimento que estou fazendo
	// utilizando a decomposição de cholesky para melhorar a convergência do modelo
	if (params->llt) {
		MatrixXf RHS = MatrixXf::Zero(2, 3);
		vec3 v1 = -error * gradient;
		vec3 v2 = error * gradient;
		RHS.row(0) = Vector3f(v1.x, v1.y, v1.z);
		RHS.row(1) = Vector3f(v2.x, v2.y, v2.z);
		MatrixXf deltas = this->scalarMatrix.llt().solve(RHS);
		delta_p_1 = vec3(deltas.row(0)[0], deltas.row(0)[1], deltas.row(0)[2]);
		delta_p_2 = vec3(deltas.row(1)[0], deltas.row(1)[1], deltas.row(1)[2]);
	} else {
		delta_p_1 = this->scalar_1 * -error * gradient;
		delta_p_2 = this->scalar_2 * error * gradient;
	}

	// k = 1 − (1 − k)^(1/ns)
	auto k = 1.f - pow(1.f - stiffness, 1.f / iterations);

	// delta_x_1 = - (w_1 / (w_1 + w_2)) * (| x_{1,2} - d |) * n
	object->getEstimate()->at(i1) += k * delta_p_1;
	object->getEstimate()->at(i2) += k * delta_p_2;
}
