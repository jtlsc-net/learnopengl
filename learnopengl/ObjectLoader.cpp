#include "ObjectLoader.h"

// String split method: https://www.javatpoint.com/how-to-split-strings-in-cpp
ObjectLoader::ObjectLoader(const char* objFilePath) : indicesSize{ 0 }, verticesSize{ 0 } {
	std::string line;
	std::ifstream objectFile;
	std::string token;
	float tokenFloat;
	float absFloat;
	int lineCount = 0;
	//objectFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//  add string trim method
	try
	{
		objectFile.open(objFilePath);
		if (objectFile.is_open()) {
			while (getline(objectFile, line)) {
				if (line[0] == 'v' && line[1] == ' ') {
					std::stringstream lineStream(line);
					while (getline(lineStream, token, ' ')) {
						if (token != "v") {
							if (token == "" || token == " ") {
								// TODO this doesn't technically work correctly.  Remove or fix.
								throw "error on line %d, likely whitespace at end", lineCount;
							}
							absFloat = abs(std::stof(token));
							if (absFloat > highestFloat) {
								highestFloat = absFloat;
							}
							vertices.push_back(std::stof(token));
						}
					}
				}

				else if (line[0] == 'v' && line[1] == 'n') {
					hasVertexNormals = true;
					std::stringstream lineStream(line);
					while (getline(lineStream, token, ' ')) {
						if (token != "vn") {
							if (token == "" || token == " ") {
								throw "error on line %d, likely whitespace at end", lineCount;
							}
							vertexNormals.push_back(std::stof(token));
						}
					}
				}

				else if (line[0] == 'f') {
					std::stringstream lineStream(line);
					std::vector<float> tokenArr;
					while (getline(lineStream, token, ' ')) {
						if (token != "f") {
							if (token == "" || token == " ") {
								throw "error on line %d, likely whitespace at end", lineCount;
							}
							//indices.push_back(std::stoi(token) - 1);
							tokenArr.push_back(std::stoi(token) - 1);
						}
					}
					int prev = 1;
					for (int i = 2; i < tokenArr.size(); i++) {
						indices.push_back(tokenArr.at(0));
						indices.push_back(tokenArr.at(prev));
						indices.push_back(tokenArr.at(i));
						prev = i;
					}
				}
				lineCount++;
			}
			objectFile.close();
			verticesSize = vertices.size();
			vertexNormalsSize = vertexNormals.size();
			indicesSize = indices.size();
		}
	}
	catch (char* c) {
		std::cout << c << std::endl;
	}
	catch (std::invalid_argument e){
		std::cout << "invalid argument: " << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "unkown error, likely whitespace at end of line " << lineCount << std::endl;
	}
}

float* ObjectLoader::getVertices() {
	return vertices.data();
}

float* ObjectLoader::getVertexNormals() {
	return vertexNormals.data();
}

unsigned int* ObjectLoader::getIndices() {
	return indices.data();
}

int ObjectLoader::getVerticesSize() const {
	return verticesSize;
}

int ObjectLoader::getVertexNormalsSize() const {
	return vertexNormalsSize;
}

int ObjectLoader::getIndicesSize() const {
	return indicesSize;
}

float ObjectLoader::getHighestFloat() const {
	return highestFloat;
}

bool ObjectLoader::getHasVertexNormals() const {
	return hasVertexNormals;
}