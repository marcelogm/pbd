#include "constraint.hpp"

size_t BendConstraintFactory::getRemainingVertex(Triangle* triangle, size_t p1, size_t p2) {
	size_t out;
	for (auto &vertex : triangle->vertices) {
		size_t p = vertex.position;
		if (p1 != p && p2 != p) {
			out = p;
		}
	}
	return out;
}

vector<Constraint*> BendConstraintFactory::create(Entity* entity) {
	const auto object = entity->getObject();
	const auto edges = object->getEdges();
	const auto adjacents = object->getAdjacentTriangles();
	const auto vertices = object->getVertices();
	auto constraints = vector<Constraint*>();
	for (auto &it: *edges) {
		if (adjacents->at(it).size() != 2) {
			continue;
		}
		auto t1 = adjacents->at(it)[0];
		auto t2 = adjacents->at(it)[1];
		const auto i1 = it.vertices[0].position;
		const auto i2 = it.vertices[1].position;
		const auto i3 = this->getRemainingVertex(&t1, i1, i2);
		const auto i4 = this->getRemainingVertex(&t2, i1, i2);

		const auto normal1 = cross(vertices->at(i2), vertices->at(i3)) / glm::l2Norm(cross(vertices->at(i2), vertices->at(i3)));
		const auto normal2 = cross(vertices->at(i2), vertices->at(i4)) / glm::l2Norm(cross(vertices->at(i2), vertices->at(i4)));
		const float dihedralAngle = glm::acos(glm::dot(normal1, normal2));
		constraints.push_back(new BendConstraint(entity, i1, i2, i3, i4, dihedralAngle));
	}
	return constraints;
}

