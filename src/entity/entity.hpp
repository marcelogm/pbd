#pragma once

#include <vgl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <LoadShaders.h>
#include <algorithm>

using std::string;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::value_ptr;
using std::vector;
using std::set;
using std::map;
using std::ifstream;

typedef struct {
	size_t position;
	size_t normal;
} Vertex;

typedef struct {
	Vertex vertices[2];
} Edge;

typedef struct {
	Vertex vertices[3];
} Triangle;

typedef struct {
	bool operator() (const Edge& a, const Edge& b) const {
		const std::less<std::pair<int, int>> comparator;
		return comparator(
			std::minmax(a.vertices[0].position, a.vertices[1].position),
			std::minmax(b.vertices[0].position, b.vertices[1].position)
		);
	}
} EdgeComparator;

class Object {
private:
	vector<vec3> vertices;
	vector<vec3> normals;
	vector<Triangle> triangles;
	set<Edge, EdgeComparator> edges;
	map<Edge, vector<Triangle>, EdgeComparator> adjacents;
	void updateEdges();
public:
	Object();
	Object(vector<vec3>, vector<vec3>, vector<Triangle>);
	vector<vec3>* getVertices();
	vector<vec3>* getNormals();
	vector<Triangle>* getTriangles();
	size_t getVerticesCount();
};

class ObjectProvider {
public:
	Object get(string path);
};

typedef struct {
	GLuint VAO;
	GLuint positionVBO;
	GLuint normalVBO;
	GLuint shader;
} OpenGLObjectInformation;

class Entity {
private:
	Object original;
	Object actual;
	vector<vec3> vertices;
	vector<vec3> estimate;
	vector<vec3> normals;
	mat4 model;
	vec4 color;
	bool gravity;
	float inverseMass;
	OpenGLObjectInformation info;
public:
	Entity(Object object, vector<ShaderInfo> shaders, vec4 color, mat4 model, bool gravity, float mass);
	void update();
	OpenGLObjectInformation getOpenGLInformation();
	mat4* getModel();
	vector<vec3>* getVertices();
	vector<vec3>* getNormals();
	vec4* getColor();
	bool isAffectedByGravity();
};