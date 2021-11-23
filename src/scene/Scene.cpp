#include "scene.hpp"

Scene::Scene(vector<Entity*> entities, Camera* camera, vector<Constraint*> constrains) {
	this->entities = entities;
	this->camera = camera;
	this->renderer = new Renderer();
	this->constraints = constrains;
	this->collisionContraints = vector<Constraint*>();
}

void Scene::render() {
	this->renderer->clear();
    this->renderer->prepare();
	for (Entity* entity : this->entities) {
		entity->update();
        this->renderer->render(entity, this->camera, Configuration::getInstance()->getLight());
	}
}

Camera* Scene::getCamera() {
	return camera;
}

vector<Constraint*> Scene::getConstraints() {
	return this->constraints;
}

vector<Constraint*> Scene::getCollisionConstraints() {
	return this->collisionContraints;
}

vector<Entity*> Scene::getEntities() {
	return this->entities;
}

