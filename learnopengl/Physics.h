#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <algorithm>

// https://www.youtube.com/watch?v=-_IspRG548E

//struct Object {
//	glm::mediump_vec3 Pos;
//	glm::vec3 Vel;
//	glm::vec3 Force;
//	float Mass;
//};
//
//class PhysicsWorld {
//private:
//	std::vector<Object*> objectList;
//	glm::vec3 gravity = glm::vec3(0.0f, -0.2f, 0.0f);
//public:
//	void AddObject(Object* object);
//	void RemoveObject(Object* object);
//	Object* Step(float deltaT);
//};