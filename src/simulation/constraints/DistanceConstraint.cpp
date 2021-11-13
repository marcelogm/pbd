#include "constraint.hpp"

DistanceConstraint::DistanceConstraint(Entity* current, size_t x1, size_t x2, float distance, float stiffness) {
	this->current = current;
	this->next = nullptr;
	this->x1 = x1;
	this->x2 = x2;
	// rest
	this->distance = distance;
	this->stiffness = stiffness;
	// inverse masses precomputation
	auto w_1 = current->getObject()->getMasses()->at(x1).inverse;
	auto w_2 = current->getObject()->getMasses()->at(x2).inverse;
	this->coeff = MatrixXf::Zero(2, 2);
	this->coeff.coeffRef(0, 0) = 1.f / (w_1 / (w_1 + w_2));
	this->coeff.coeffRef(1, 1) = 1.f / (w_2 / (w_1 + w_2));
}

void DistanceConstraint::project() {
	auto iterations = Configuration::getInstance()->getSimulationParams()->iterations;
	auto stiffness = Configuration::getInstance()->getSimulationParams()->stiffness;

	MatrixXf RHS = MatrixXf::Zero(2, 3);
	auto object = current->getObject();
	auto p1 = object->getEstimate()->at(x1);
	auto p2 = object->getEstimate()->at(x2);

	// distance_constraint = | x_{1,2} - d |
	auto distance_constraint = l2Norm(p1 - p2) - distance;

	// gradient_x_1 C(x_1, x_2) = n
	// gradient_x_2 C(x_1, x_2) = -n
	// n = x_{1,2} / | x_{1,2} |
	vec3 n = (p1 - p2) / (float)(l2Norm(p1 - p2) + 0.1);
	vec3 v1 = -distance_constraint * n;
	vec3 v2 = distance_constraint * n;

	// to matrix
	RHS.row(0) = Vector3f(v1.x, v1.y, v1.z);
	RHS.row(1) = Vector3f(v2.x, v2.y, v2.z);

	// delta_x_2 = + (w_2 / (w_1 + w_2)) * (| x_{1,2} - d |) * n
	MatrixXf correction = this->coeff.llt().solve(RHS);

	// k = 1 − (1 − k)^(1/ns)
	auto k = 1.f - pow(1.f - stiffness, 1.f / iterations);

	// delta_x_1 = - (w_1 / (w_1 + w_2)) * (| x_{1,2} - d |) * n
	vec3 delta_x1 = vec3(correction.row(0)[0], correction.row(0)[1], correction.row(0)[2]);
	object->getEstimate()->at(x1) += k * delta_x1;

	vec3 delta_x2 = vec3(correction.row(1)[0], correction.row(1)[1], correction.row(1)[2]);
	object->getEstimate()->at(x2) += k * delta_x2;
}
