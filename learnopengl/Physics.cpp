#include "Physics.h"


//void PhysicsWorld::AddObject(Object* object) {
//	objectList.push_back(object);
//}
//
//void PhysicsWorld::RemoveObject(Object* object) {
//	if (!object) return;
//	std::vector<Object*>::iterator it = std::find(objectList.begin(), objectList.end(), object);
//	if (it == objectList.end()) return;
//	objectList.erase(it);
//}
//
//// Currently steps through and applies gravity
//Object* PhysicsWorld::Step(float deltaT) {
//	for (Object* object : objectList) {
//		object->Force += object->Mass * gravity;  // F = MA
//		object->Vel += object->Force / object->Mass * deltaT;
//		object->Pos += object->Vel * deltaT;
//
//		object->Force = glm::vec3(0.0f, 0.0f, 0.0f);
//		return object;
//	}
//}