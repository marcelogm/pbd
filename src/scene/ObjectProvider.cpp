#include "scene.hpp"

Object ObjectProvider::get(string path) {
	vector<vec3> tempVertices = vector<vec3>();
	vector<vec3> tempNormals = vector<vec3>();
	vector<int> verticesIndex = vector<int>();
	vector<int> normalsIndex = vector<int>();

	vector<vec3> vertices = vector<vec3>();
	vector<vec3> normals = vector<vec3>();
	
	FILE* file = fopen(path.c_str(), "r");
	if (file == NULL) {
		return Object({}, {});
	}
	
	while (true) {
		char line[128];
		int res = fscanf(file, "%s", line);
		if (res == EOF) break;

		if (strcmp(line, "v") == 0) {
			vec3 vertex;
			(void) fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		}
		else if (strcmp(line, "vn") == 0) {
			glm::vec3 normal;
			(void) fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if (strcmp(line, "f") == 0) {
			unsigned int vertexIndex[3], normalIndex[3];
			(void) fscanf(file, "%d//%d %d//%d %d//%d\n",
				&vertexIndex[0], &normalIndex[0],
				&vertexIndex[1], &normalIndex[1], 
				&vertexIndex[2], &normalIndex[2]);
			verticesIndex.push_back(vertexIndex[0]);
			verticesIndex.push_back(vertexIndex[1]);
			verticesIndex.push_back(vertexIndex[2]);
			normalsIndex.push_back(normalIndex[0]);
			normalsIndex.push_back(normalIndex[1]);
			normalsIndex.push_back(normalIndex[2]);
		}
	}

	for (size_t i = 0; i < verticesIndex.size(); i++) {
		vertices.push_back(tempVertices.at(verticesIndex.at(i) - 1));
		normals.push_back(tempNormals.at(normalsIndex.at(i) - 1));
	}

	return Object(vertices, normals);
}

