#include "scene.hpp"

Object::Object() {
	this->vertices = vector<vec3>();
	this->normals = vector<vec3>();
}

Object::Object(vector<vec3> vertices, vector<vec3> normals) {
	this->vertices = vertices;
	this->normals = normals;
}

vector<vec3>* Object::getVertices() {
	return &vertices;
}

vector<vec3>* Object::getNormals() {
	return &normals;
}
