#pragma once
#include "../../entity/entity.hpp"
#include "../../configuration/config.hpp"
#include <glm/gtx/norm.hpp> 
#include <Eigen/Eigen>

using glm::cross;
using glm::normalize;
using glm::dot;
using glm::acos;
using glm::l2Norm;
using Eigen::MatrixXf;
using Eigen::Vector3f;

struct ConstraintConfiguration {};

class Constraint {
public:
	virtual void project() = 0;
};

class AnchorConstraint :public Constraint {
private:
	Entity* entity;
	size_t x1;
	vec3 fixed;
public:
	AnchorConstraint(Entity*, size_t, vec3);
	void project();
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
	float stiffness;
	MatrixXf coeff;
public:
	DistanceConstraint(Entity* current, size_t x1, size_t x2, float distance, float stiffness);
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