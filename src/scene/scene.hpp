#pragma once

#include <vgl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <LoadShaders.h>
#include "../configuration/config.hpp"
#include "../camera/camera.hpp"

using std::string;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::value_ptr;
using std::vector;
using std::ifstream;

class Object {
private:
	vector<vec3> vertices;
	vector<vec3> normals;
public:
	Object();
	Object(vector<vec3>, vector<vec3>);
	vector<vec3>* getVertices();
	vector<vec3>* getNormals();
};

class ObjectProvider {
public:
	Object get(string path);
};

class Entity {
private:
	Object original;
	Object actual;
	mat4 model;
	vec4 color;
	GLuint VAO;
	GLuint positionVBO;
	GLuint normalVBO;
	GLuint shader;
public:
	Entity(Object object, vector<ShaderInfo> shaders, vec4 color, mat4 model);
	void update();
	GLuint getPositionVBO();
	GLuint getNormalVBO();
	GLuint getShader();
	GLuint getVAO();
	mat4* getModel();
	vector<vec3>* getVertices();
	vector<vec3>* getNormals();
	vec4* getColor();
};

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
	vector<Entity> entities;
	Renderer* renderer;
	Camera* camera;
public:
	Scene(vector<Entity> entities);
	void render();
	Camera* getCamera();
};