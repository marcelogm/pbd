#include "constraint.hpp"
#include <glm/ext/scalar_common.hpp>

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

	const auto p1 = object->getEstimate()->at(i1);
	const auto p2 = object->getEstimate()->at(i2);
	const auto p3 = object->getEstimate()->at(i3);
	const auto p4 = object->getEstimate()->at(i4);

	const auto w1 = object->getMasses()->at(i1).inverse;
	const auto w2 = object->getMasses()->at(i1).inverse;
	const auto w3 = object->getMasses()->at(i1).inverse;
	const auto w4 = object->getMasses()->at(i1).inverse;

	// triangle norms
	const auto p2p3 = glm::cross(p2, p3);
	const auto p2p4 = glm::cross(p2, p4);
	const auto norm1 = p2p3 / l2Norm(p2p3);
	const auto norm2 = p2p4 / l2Norm(p2p4);
	const auto dot = glm::dot(norm1, norm2);

	// partial derivatives (gradient)
	const auto derivative3 = (glm::cross(p2, norm2) + dot * glm::cross(norm1, p2)) / (l2Norm(p2p3));
	const auto derivative4 = (glm::cross(p2, norm1) + dot * glm::cross(norm2, p2)) / (l2Norm(p2p4));
	const auto derivative2 = -(glm::cross(p3, norm2) + dot * glm::cross(norm1, p3)) /
		(l2Norm(p2p3)) - (glm::cross(p4, norm1) + dot * glm::cross(norm2, p4)) / (l2Norm(p2p4));
	const auto derivative1 = -derivative2 - derivative3 - derivative4;

	// squared norm
	const auto Q = glm::length2(derivative1) + glm::length2(derivative2) + 
		glm::length2(derivative3) + glm::length2(derivative4);

	// weighting
	const auto weight_sum = (w1 * Q) + (w2 * Q) + (w3 * Q) + (w4 * Q);
	const auto scalar1 = 1.0f / (w1 / weight_sum);
	const auto scalar2 = 1.0f / (w2 / weight_sum);
	const auto scalar3 = 1.0f / (w3 / weight_sum);
	const auto scalar4 = 1.0f / (w4 / weight_sum);
	
	const auto clamped_dot = glm::fclamp(dot, -1.f, 1.f);
	const auto angle = glm::sqrt(1.0f - clamped_dot * clamped_dot) * (glm::acos(clamped_dot) - dihedralAngle);

	// add deltas
	const auto k = 1.0f - glm::pow(1.0f - bendability, 1.0f / iterations);
	object->getEstimate()->at(i1) += k * ((-angle * derivative1) * (1.f / scalar1));
	object->getEstimate()->at(i2) += k * ((-angle * derivative2) * (1.f / scalar2));
	object->getEstimate()->at(i3) += k * ((-angle * derivative3) * (1.f / scalar3));
	object->getEstimate()->at(i4) += k * ((-angle * derivative4) * (1.f / scalar4));
}
