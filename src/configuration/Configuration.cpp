#include "config.hpp"

Configuration::Configuration() {
	this->viewport = { 1200.0f, 800.0f };
	this->light = { vec4(0.0f, 0.0f, 10.0f, 1.0f), 0.5f, 0.5f };
};

Configuration* Configuration::getInstance() {
	if (instance == nullptr) {
		instance = new Configuration();
	}
	return instance;
}

Configuration* Configuration::instance = nullptr;

ViewportDimension* Configuration::getViewport() {
	return &this->viewport;
}

LightConfiguration* Configuration::getLight() {
	return &this->light;
}