#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>

class ObjectLoader {
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> vertexNormals;
	int verticesSize;
	int vertexNormalsSize;
	int indicesSize;
	float highestFloat;
	bool hasVertexNormals = false;
public:
	ObjectLoader(const char* objFilePath);
	float* getVertices();
	float* getVertexNormals();
	unsigned int* getIndices();
	int getVerticesSize() const;
	int getVertexNormalsSize() const;
	int getIndicesSize() const;
	float getHighestFloat() const;
	bool getHasVertexNormals() const;
};