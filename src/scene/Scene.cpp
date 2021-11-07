#include "scene.hpp"

Scene::Scene(vector<Entity*> entities, Camera* camera, vector<Constraint*> constrains) {
	this->entities = entities;
	this->camera = camera;
	this->renderer = new Renderer();
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

