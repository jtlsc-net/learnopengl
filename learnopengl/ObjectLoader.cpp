#include "ObjectLoader.h"
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"

// String split method: https://www.javatpoint.com/how-to-split-strings-in-cpp
ObjectLoader::ObjectLoader(const char* objFilePath) : indicesSize{ 0 }, verticesSize{ 0 }, highestFloat{ 0.0 } {
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
							intermediateVertices.push_back(std::stof(token));
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
			// Add vertex normals to array.
			if (hasVertexNormals) {
				/*vertices.resize(vertices.size() + vertexNormals.size());
				std::vector<float>::iterator verticesIt = vertices.begin();
				for (std::vector<float>::iterator vertexNormalsIt = vertexNormals.begin(); vertexNormalsIt != vertexNormals.end(); vertexNormalsIt++) {
					vertices.insert(verticesIt, *vertexNormalsIt);
					verticesIt++;
					if ((verticesIt - vertices.begin()) % 3 == 0) {
						verticesIt = verticesIt + 3;
					}
				}*/
				numVertices = intermediateVertices.size();
				std::vector<float>::iterator intVertIt = intermediateVertices.begin();
				std::vector<float>::iterator vertNormIt = vertexNormals.begin();
				for (int i = 0; i < (intermediateVertices.size() + vertexNormals.size()); i++) {
					if (((i % 6) == 0) || ((i - 1) % 6 == 0) || ((i - 2) % 6 == 0)) {
						/*std::cout << " vert: " << *intVertIt;*/
						vertices.push_back(*intVertIt);
						intVertIt++;
					}
					else if (((i - 3) % 6 == 0) || ((i - 4) % 6 == 0) || ((i - 5) % 6 == 0)) {
						/*std::cout << " norm: " << *vertNormIt;*/
						vertices.push_back(*vertNormIt);
						vertNormIt++;
					}
					/*if (i - 1 % 3 == 0) {
						std::cout << std::endl;
					}*/
				}
			}
			// Calculate vector normals from face norms
			else {
				for (std::vector<float>::iterator it = intermediateVertices.begin(); it != intermediateVertices.end(); it++) {
					vertices.push_back(*it);
				}
				//hasVertexNormals = false;
				//std::vector<unsigned int>::iterator indicesIt = indices.begin();
				//std::vector<std::vector<glm::vec3>> referenceVec(intermediateVertices.size()/3); // Vector access time at given index is constant, I think faster than map for this case.
				//// Normal vector calculations here: https://stackoverflow.com/questions/1966587/given-3-points-how-do-i-calculate-the-normal-vector
				//while (indicesIt != indices.end()) {
				//	int a = *indicesIt;
				//	indicesIt++;
				//	int b = *indicesIt;
				//	indicesIt++;
				//	int c = *indicesIt;
				//	indicesIt++;
				//	glm::vec3 vector1 = glm::vec3(intermediateVertices.at(3 * b) - intermediateVertices.at(3 * a),
				//		intermediateVertices.at(3 * b + 1) - intermediateVertices.at(3 * a + 1),
				//		intermediateVertices.at(3 * b + 2) - intermediateVertices.at(3 * a + 2));
				//	glm::vec3 vector2 = glm::vec3(intermediateVertices.at(3 * c) - intermediateVertices.at(3 * a),
				//		intermediateVertices.at(3 * c + 1) - intermediateVertices.at(3 * a + 1),
				//		intermediateVertices.at(3 * c + 2) - intermediateVertices.at(3 * a + 2));
				//	glm::vec3 pushVector = glm::cross(vector1, vector2);
				//	referenceVec.at(a).push_back(pushVector);
				//	referenceVec.at(b).push_back(pushVector);
				//	referenceVec.at(c).push_back(pushVector);
				//}
				//for (std::vector<std::vector<glm::vec3>>::iterator refIt = referenceVec.begin(); refIt != referenceVec.end(); refIt++) {
				//	float xsum = 0.0;
				//	float ysum = 0.0;
				//	float zsum = 0.0;
				//	for (std::vector<glm::vec3>::iterator normIt = (*refIt).begin(); normIt != (*refIt).end(); normIt++) {
				//		xsum = xsum + (*normIt)[0];
				//		ysum = ysum + (*normIt)[1];
				//		zsum = zsum + (*normIt)[2];
				//	}
				//	vertexNormals.push_back(glm::normalize(glm::vec3(xsum, ysum, zsum))[0]);
				//	vertexNormals.push_back(glm::normalize(glm::vec3(xsum, ysum, zsum))[1]);
				//	vertexNormals.push_back(glm::normalize(glm::vec3(xsum, ysum, zsum))[2]);
				//}
				//std::vector<float>::iterator intVertIt = intermediateVertices.begin();
				//std::vector<float>::iterator vertNormIt = vertexNormals.begin();
				//for (int i = 0; i < (intermediateVertices.size() + vertexNormals.size()); i++) {
				//	if (((i % 6) == 0) || ((i - 1) % 6 == 0) || ((i - 2) % 6 == 0)) {
				//		std::cout << " vert: " << *intVertIt;
				//		vertices.push_back(*intVertIt);
				//		intVertIt++;
				//	}
				//	else if (((i - 3) % 6 == 0) || ((i - 4) % 6 == 0) || ((i - 5) % 6 == 0)) {
				//		std::cout << " norm: " << *vertNormIt;
				//		vertices.push_back(*vertNormIt);
				//		vertNormIt++;
				//	}
				//	if ((i + 1) % 3 == 0) {
				//		std::cout << std::endl;
				//	}
				//}
			}
			objectFile.close();
			verticesSize = vertices.size();
			indicesSize = indices.size();
			double logFloat = log10(static_cast<float>(highestFloat));
			int highestFloatMag = static_cast<int>(logFloat);
			highestFloat = static_cast<float>(pow(10, highestFloatMag));
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

unsigned int* ObjectLoader::getIndices() {
	return indices.data();
}

int ObjectLoader::getVerticesSize() const {
	return verticesSize;
}

int ObjectLoader::getIndicesSize() const {
	return indicesSize;
}

int ObjectLoader::getNumVertices() const {
	return numVertices;
}

float ObjectLoader::getHighestFloat() const {
	return highestFloat;
}

bool ObjectLoader::getHasVertexNormals() const {
	return hasVertexNormals;
}
