#include "ObjectLoader.h"


// String split method: https://www.javatpoint.com/how-to-split-strings-in-cpp
ObjectLoader::ObjectLoader(const char* objFilePath) : indicesSize{ 0 }, verticesSize{ 0 } {
	std::string line;
	std::ifstream objectFile;
	std::string token;
	//objectFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		objectFile.open(objFilePath);
		if (objectFile.is_open()) {
			while (getline(objectFile, line)) {
				if (line[0] == 'v' && line[1] != 'n') {
					/*int found = line.find(' ', 2);
					int found2 = found + 1;
					std::string xVal = line.substr(2, found - 2);
					found = line.find(' ', found2);
					std::string yVal = line.substr(found2, found - found2);
					found2 = found + 1;
					found = line.find(' ', found2);
					std::string zVal = line.substr(found2, found - found2);*/
					std::stringstream lineStream(line);
					while (getline(lineStream, token, ' ')) {
						if (token != "v") {
							vertices.push_back(std::stof(token));
						}
					}
					
				}
				else if (line[0] == 'f') {
					/*std::string vertOne = line.substr(2, 1);
					int found = line.find(' ', 2);
					std::string vertTwo = line.substr(found + 1, 1);
					found = line.find(' ', found + 1);
					std::string vertThree = line.substr(found + 1, 1);
					indices.push_back(std::stoi(vertOne));
					indices.push_back(std::stoi(vertTwo));
					indices.push_back(std::stoi(vertThree));*/
					std::stringstream lineStream(line);
					while (getline(lineStream, token, ' ')) {
						if (token != "f") {
							indices.push_back(std::stoi(token) - 1);
						}
					}
				}
			}
			objectFile.close();
			verticesSize = vertices.size();
			indicesSize = indices.size();
		}
	}
	catch (std::invalid_argument e){
		std::cout << "invalid argument: " << e.what() << std::endl;
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