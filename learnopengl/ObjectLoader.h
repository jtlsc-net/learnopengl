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
	std::vector<float> intermediateVertices;
	int verticesSize;
	int numVertices;
	int indicesSize;
	float highestFloat;
	bool hasVertexNormals = false;
public:
	ObjectLoader(const char* objFilePath);
	float* getVertices();
	unsigned int* getIndices();
	int getVerticesSize() const;
	int getNumVertices() const;
	int getIndicesSize() const;
	float getHighestFloat() const;
	bool getHasVertexNormals() const;
};