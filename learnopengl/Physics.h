#pragma once
#include <iostream>

#include "btBulletDynamicsCommon.h"
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include "Bullet3Common/b3FileUtils.h"
#include "Model.h"

struct RigidBodyInfo {
	btVector3 position;
	btScalar mass;
	btVector3 fallInertia;
};

enum class ShapeType {
	normal, sphere, plane
};

class Physics {
private:
	btDiscreteDynamicsWorld* dynamicsWorld;
	std::vector<btCollisionShape*> collisionShapes;
	std::vector<btRigidBody*> rigidBodies;

	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	
public:
	Physics();
	void LoadMesh(Model * model, std::vector<int> params, ShapeType shapeType = ShapeType::normal);
	void AddBody(RigidBodyInfo RBI, int index);
	void Update(float deltaTime, int maxSubSteps);
	btVector3 getPos(int index);
	void Delete();
};


