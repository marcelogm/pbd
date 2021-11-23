#include "constraint.hpp"

BendConstraint::BendConstraint(Entity* entity, size_t i1, size_t i2, size_t i3, size_t i4, float dihedralAngle) {
	this->entity = entity;
	this->i1 = i1;
	this->i2 = i2;
	this->i3 = i3;
	this->i4 = i4;
	this->dihedralAngle = dihedralAngle;
}

void BendConstraint::project() {
	auto iterations = Configuration::getInstance()->getSimulationParams()->iterations;
	auto bendability = Configuration::getInstance()->getSimulationParams()->bendability;
	auto object = entity->getObject();

	auto p1 = object->getEstimate()->at(i1);
	auto p2 = object->getEstimate()->at(i2);
	auto p3 = object->getEstimate()->at(i3);
	auto p4 = object->getEstimate()->at(i4);

	auto p2p3 = glm::cross(p2, p3);
	auto p2p4 = glm::cross(p2, p4);

	auto n1 = p2p3 / l2Norm(p2p3);
	auto n2 = p2p4 / l2Norm(p2p4);
	float d = glm::dot(n1, n2);

	auto q3 = (glm::cross(p2, n2) + d * glm::cross(n1, p2)) / (l2Norm(p2p3));
	auto q4 = (glm::cross(p2, n1) + d * glm::cross(n2, p2)) / (l2Norm(p2p4));
	auto q2 = -(glm::cross(p3, n2) + d * glm::cross(n1, p3)) / 
		(l2Norm(p2p3)) - (glm::cross(p4, n1) + d * glm::cross(n2, p4)) / (l2Norm(p2p4));
	auto q1 = -q2 -q3 -q4;

	float qSum = glm::length2(q1) + glm::length2(q2) + glm::length2(q3) + glm::length2(q4);

	auto w1 = object->getMasses()->at(i1).inverse;
	auto w2 = object->getMasses()->at(i2).inverse;
	auto w3 = object->getMasses()->at(i3).inverse;
	auto w4 = object->getMasses()->at(i4).inverse;
	float denominator = (w1 * qSum) + (w2 * qSum) + (w3 * qSum) + (w4 * qSum);

	this->scalar_1 = 1.0f / (w1 / denominator);
	this->scalar_2 = 1.0f / (w2 / denominator);
	this->scalar_3 = 1.0f / (w3 / denominator);
	this->scalar_4 = 1.0f / (w4 / denominator);

	d = fmax(fmin(d, 1.0f), -1.0f);
	float a = sqrtf(1.0f - d * d) * (acosf(d) - dihedralAngle);
	auto delta_x1 = this->scalar_1 * -a * q1;
	auto delta_x2 = this->scalar_2 * -a * q2;
	auto delta_x3 = this->scalar_3 * -a * q3;
	auto delta_x4 = this->scalar_4 * -a * q4;

	auto k = 1.f - pow(1.f - bendability, 1.f / iterations);

	object->getEstimate()->at(i1) += k * delta_x1;
	object->getEstimate()->at(i2) += k * delta_x2;
	object->getEstimate()->at(i3) += k * delta_x3;
	object->getEstimate()->at(i4) += k * delta_x4;
}
