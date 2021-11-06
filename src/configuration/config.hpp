#pragma once
#include <glm/glm.hpp>

using glm::vec4;

typedef struct {
	float width;
	float height;
} ViewportDimension;

typedef struct {
	vec4 lightPosition;
	float ambientLightStrength;
	float diffuseLightStrength;
} LightConfiguration;

class Configuration {
private:
	Configuration();
	static Configuration* instance;
	LightConfiguration light;
	ViewportDimension viewport;
public:
	static Configuration* getInstance();
	ViewportDimension* getViewport();
	LightConfiguration* getLight();
};