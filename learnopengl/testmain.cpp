#include <iostream>
#include "ObjectLoader.h"

int main(void) {
	ObjectLoader obj("cube.obj");
	float * vertices = obj.getVertices();
	unsigned int* indices = obj.getIndices();
	int verticesSize = obj.getVerticesSize();
	int indicesSize = obj.getIndicesSize();
	std::cout << "vertices: " << std::endl;
	for (int i = 0; i < verticesSize; i++) {
		std::cout << *(vertices + i) << " ";
	}
	std::cout << std::endl;
	std::cout << "indices: " << std::endl;
	for (int j = 0; j < indicesSize; j++) {
		std::cout << *(indices + j) << " ";
	}
	std::cout << std::endl;


	return 0;
}