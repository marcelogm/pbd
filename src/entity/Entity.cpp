#include "entity.hpp"

Entity::Entity(Object object, vector<ShaderInfo> shaders, vec4 color, mat4 model, bool gravity, float mass) {
	this->original = object;
	this->actual = object;
	this->color = color;
	this->model = model;
	this->gravity = gravity;
	this->mass = { mass, (1.0f / mass) };
	this->normalBuffer = new vector<vec3>(this->actual.getTriangles()->size() * 3);
	this->vertexBuffer = new vector<vec3>(this->actual.getTriangles()->size() * 3);

	this->info = {};
	this->info.shader = LoadShaders(&shaders.front());
	glGenVertexArrays(1, &this->info.VAO);
	glGenBuffers(1, &this->info.positionVBO);
	glGenBuffers(1, &this->info.normalVBO);
	glBindVertexArray(this->info.VAO);
}

OpenGLObjectInformation Entity::getOpenGLInformation() {
	return this->info;
}

mat4* Entity::getModel() {
	return &this->model;
}

Object* Entity::getObject() {
	return &this->actual;
}

vec4* Entity::getColor() {
	return &this->color;
}

bool Entity::isAffectedByGravity() {
	return gravity;
}

Mass Entity::getMass() {
	return this->mass;
}

void Entity::update() {
	const vector<vec3>* vertices = this->actual.getVertices();
	const vector<vec3>* normals = this->actual.getNormals();
	for (size_t i = 0; i < this->actual.getTriangles()->size(); i++) {
		const Triangle triangle = this->actual.getTriangles()->at(i);
		#pragma unroll
		for (size_t j = 0; j < 3; j++) {
			vertexBuffer->at((i * 3) + j) = vertices->at(triangle.vertices[j].position);
			//vertexBuffer->at((i * 3) + j) = normals->at(triangle.vertices[j].position);
		}
	}
}

vector<vec3>* Entity::getRenderedVertices() {
	return vertexBuffer;
}

vector<vec3>* Entity::getRenderedNormals() {
	return normalBuffer;
}

