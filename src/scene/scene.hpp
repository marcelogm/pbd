#pragma once

#include "../configuration/config.hpp"
#include "../camera/camera.hpp"
#include "../entity/entity.hpp"
#include "../simulation/constraints/constraint.hpp"

using glm::mat4;
using std::vector;

class Renderer {
private:
	float aspect;
	mat4 projection;
	float lightPosition;
	float ambientLightStrength;
	float diffuseLightStrength;
public:
	void clear();
	void prepare();
	void render(Entity*, Camera*, LightConfiguration*);
};

class Scene {
private:
	vector<Entity*> entities;
	vector<Constraint*> constraints;
	Renderer* renderer;
	Camera* camera;
public:
	Scene(vector<Entity*> entities, Camera* camera, vector<Constraint*> constraints);
	void render();
	Camera* getCamera();
	vector<Constraint*> getConstraints();
	vector<Entity*> getEntities();
};

class ClothSceneFactory {
public:
	Scene* build();
};