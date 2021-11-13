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

typedef struct {
	float gravityModifier;
	int iterations;
} SimulationParams;

class Configuration {
private:
	Configuration();
	static Configuration* instance;
	LightConfiguration light;
	ViewportDimension viewport;
	SimulationParams params;
public:
	static Configuration* getInstance();
	ViewportDimension* getViewport();
	LightConfiguration* getLight();
	SimulationParams* getSimulationParams();
};