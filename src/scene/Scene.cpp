#include "scene.hpp"

Scene::Scene(vector<Entity> entities) {
	this->entities = entities;
    this->renderer = new Renderer();
	this->camera = new Camera(vec3(0.0f, 0.0f, 2.0f));
}

void Scene::render() {
	this->renderer->clear();
    this->renderer->prepare();
	for (Entity entity : this->entities) {
        this->renderer->render(
			&entity, 
			this->camera, 
			Configuration::getInstance()->getLight()
		);
	}
}

Camera* Scene::getCamera() {
	return camera;
}

