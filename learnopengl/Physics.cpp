#include "Physics.h"
#include <iostream>
#include <vector>
#include "Mesh.h"
#include "BulletCollision/CollisionShapes/btConvexHullShape.h"


Physics::Physics() {
    // Set up world
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void Physics::LoadMesh(Model * model) {
    Mesh mesh = model->getMesh();
    btConvexHullShape* shape = new btConvexHullShape;
    for (std::vector<Vertex>::iterator it = mesh.vertices.begin(); it != mesh.vertices.end(); it++) {
        shape->addPoint(btVector3((*it).Position[0], (*it).Position[1], (*it).Position[2]));
    }
}