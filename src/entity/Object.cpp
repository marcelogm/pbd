#include "entity.hpp"

Object::Object() {
	this->vertices = vector<vec3>();
	this->normals = vector<vec3>();
	this->triangles = vector<Triangle>();
	this->estimate = vector<vec3>();
	this->velocities = vector<vec3>();
	this->updateEdges();
}

Object::Object(vector<vec3> vertices, vector<vec3> normals, vector<Triangle> triangles, float particleMass) {
	this->vertices = vertices;
	this->estimate = vertices;
	this->normals = normals;
	this->triangles = triangles;
	this->velocities = vector<vec3>(vertices.size());
	this->masses = vector<Mass>(vertices.size());
	for (size_t i = 0; i < vertices.size(); i++) {
		this->velocities.at(i) = vec3(0.0f);
		this->masses.at(i) = { particleMass, 1.f / particleMass };
	}
	this->updateEdges();
}

void Object::updateEdges() {
	this->edges = {};
	this->adjacents = {};
	for (size_t i = 0; i < triangles.size(); i++) {
		const Triangle triangle = triangles[i];

		const Edge first = { triangle.vertices[0], triangle.vertices[1] };
		const Edge second = { triangle.vertices[0], triangle.vertices[2] };
		const Edge third = { triangle.vertices[1], triangle.vertices[2] };

		this->edges.insert(first);
		this->edges.insert(second);
		this->edges.insert(third);

		this->adjacents[first].push_back(triangle);
		this->adjacents[second].push_back(triangle);
		this->adjacents[third].push_back(triangle);
	}
}

vector<vec3>* Object::getVertices() {
	return &vertices;
}

vector<vec3>* Object::getNormals() {
	return &normals;
}

vector<vec3>* Object::getEstimate() {
	return &estimate;
}

vector<vec3>* Object::getVelocities() {
	return &velocities;
}

vector<Mass>* Object::getMasses() {
	return &masses;
}

vector<Triangle>* Object::getTriangles() {
	return &triangles;
}

set<Edge, EdgeComparator>* Object::getEdges() {
	return &edges;
}

map<Edge, vector<Triangle>, EdgeComparator>* Object::getAdjacentTriangles() {
	return &adjacents;
}

size_t Object::getVerticesCount() {
	return triangles.size() * 3;
}
