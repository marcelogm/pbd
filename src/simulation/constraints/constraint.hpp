#pragma once
#include "../../entity/entity.hpp"

using glm::cross;
using glm::normalize;
using glm::dot;
using glm::acos;

struct ConstraintConfiguration {};

class Constraint {
public:
	virtual void project() = 0;
};

class BendConstraint : public Constraint {
private:
	Entity* entity;
	size_t x1;
	size_t x2;
	size_t x3;
	size_t x4;
	float dihedralAngle;
public:
	BendConstraint(Entity*, size_t, size_t, size_t, size_t, float angle);
	void project();
};

class DistanceConstraint : public Constraint {
private:
	Entity* current;
	Entity* next;
	size_t x1;
	size_t x2;
	float distance;
public:
	DistanceConstraint(Entity* current, size_t x1, size_t x2, float distance);
	void project();
};

class BendConstraintFactory {
private:
	size_t getRemainingVertex(Triangle* triangle, size_t p1, size_t p2);
public:
	vector<Constraint*> create(Entity*, ConstraintConfiguration);
};

class RidigBodyConstraintFactory {
public:
	vector<Constraint*> create(Entity*);
};