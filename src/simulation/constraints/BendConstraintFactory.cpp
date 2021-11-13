#include "constraint.hpp"
#include <glm/gtx/norm.hpp>

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

vector<Constraint*> BendConstraintFactory::create(Entity* entity, ConstraintConfiguration config) {
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
		const auto x1 = it.vertices[0].position;
		const auto x2 = it.vertices[1].position;
		const auto x3 = this->getRemainingVertex(&t1, x1, x2);
		const auto x4 = this->getRemainingVertex(&t2, x1, x2);
		const auto n1 = cross(vertices->at(x2), vertices->at(x3)) / l2Norm(cross(vertices->at(x2), vertices->at(x3)));
		const auto n2 = cross(vertices->at(x2), vertices->at(x4)) / l2Norm(cross(vertices->at(x2), vertices->at(x4)));
		const float dihedralAngle = acos(dot(n1, n2));
		constraints.push_back(new BendConstraint(entity, x1, x2, x3, x4, dihedralAngle));
	}
	return constraints;
}

