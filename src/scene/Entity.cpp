#include "scene.hpp"
#include "scene.hpp"

Entity::Entity(Object object, vector<ShaderInfo> shaders, vec4 color, mat4 model) {
	this->original = object;
	this->actual = object;
	this->color = color;
	this->model = model;
	this->shader = LoadShaders(&shaders.front());

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->positionVBO);
	glGenBuffers(1, &this->normalVBO);
	glBindVertexArray(this->VAO);
}
void Entity::update() {
	auto vertices = this->actual.getVertices();
	auto normals = this->actual.getNormals();
}

GLuint Entity::getPositionVBO() {
	return this->positionVBO;
}

GLuint Entity::getNormalVBO() {
	return this->normalVBO;
}

GLuint Entity::getShader() {
	return this->shader;
}

GLuint Entity::getVAO() {
	return this->VAO;
}

mat4* Entity::getModel() {
	return &this->model;
}

vector<vec3>* Entity::getVertices() {
	return this->actual.getVertices();
}

vector<vec3>* Entity::getNormals() {
	return this->actual.getNormals();
}

vec4* Entity::getColor() {
	return &this->color;
}