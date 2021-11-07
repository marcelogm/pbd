#include "entity.hpp"

Entity::Entity(Object object, vector<ShaderInfo> shaders, vec4 color, mat4 model, bool gravity, float mass) {
	this->original = object;
	this->actual = object;
	this->color = color;
	this->model = model;
	this->gravity = gravity;
	// Isso deve virar um vetor
	this->inverseMass = 1.0f / mass;
	this->vertices = vector<vec3>(this->actual.getVerticesCount());
	this->normals = vector<vec3>(this->actual.getVerticesCount());

	this->info = {};
	this->info.shader = LoadShaders(&shaders.front());
	glGenVertexArrays(1, &this->info.VAO);
	glGenBuffers(1, &this->info.positionVBO);
	glGenBuffers(1, &this->info.normalVBO);
	glBindVertexArray(this->info.VAO);
}

void Entity::update() {
	const vector<vec3>* rawVertices = this->actual.getVertices();
	const vector<vec3>* rawNormals = this->actual.getNormals();
	for (size_t i = 0; i < this->actual.getTriangles()->size(); i++) {
		const Triangle triangle = this->actual.getTriangles()->at(i);
		#pragma unroll
		for (size_t j = 0; j < 3; j++) {
			vertices[(i * 3) + j] = rawVertices->at(triangle.vertices[j].position);
			normals[(i * 3) + j] = rawNormals->at(triangle.vertices[j].normal);
		}
	}
}

OpenGLObjectInformation Entity::getOpenGLInformation() {
	return this->info;
}

mat4* Entity::getModel() {
	return &this->model;
}

vector<vec3>* Entity::getVertices() {
	return &this->vertices;
}

vector<vec3>* Entity::getNormals() {
	return &this->normals;
}

vec4* Entity::getColor() {
	return &this->color;
}

bool Entity::isAffectedByGravity() {
	return gravity;
}