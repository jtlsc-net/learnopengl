#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

class ObjectLoader {
private:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	int verticesSize;
	int indicesSize;
public:
	ObjectLoader(const char* objFilePath);
	float* getVertices();
	unsigned int* getIndices();
	int getVerticesSize() const;
	int getIndicesSize() const;
};