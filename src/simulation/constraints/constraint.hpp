#pragma once
#include "../../entity/entity.hpp"

struct ConstraintConfiguration {};

class Constraint {
public:
	virtual void project() = 0;
};

class BendConstraint : public Constraint {
public:
	void project();
};

class BendConstraintFactory {
public:
	vector<Constraint*> create(Entity*, ConstraintConfiguration);
};