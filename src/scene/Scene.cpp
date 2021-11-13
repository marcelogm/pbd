#include "scene.hpp"

Scene::Scene(vector<Entity*> entities, Camera* camera, vector<Constraint*> constrains) {
	this->entities = entities;
	this->camera = camera;
	this->renderer = new Renderer();
	this->constraints = constrains;
}

void Scene::render() {
	this->renderer->clear();
    this->renderer->prepare();
	for (Entity* entity : this->entities) {
        this->renderer->render(entity, this->camera, Configuration::getInstance()->getLight());
	}
}

Camera* Scene::getCamera() {
	return camera;
}

vector<Constraint*> Scene::getConstraints() {
	return this->constraints;
}

vector<Entity*> Scene::getEntities() {
	return this->entities;
}

