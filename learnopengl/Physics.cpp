#include "Physics.h"
#include <iostream>
#include <vector>
#include "Mesh.h"
#include "BulletCollision/CollisionShapes/btConvexHullShape.h"


Physics::Physics() {
    // Set up world
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
    solver = new btSequentialImpulseConstraintSolver;
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void Physics::LoadMesh(Model * model, std::vector<int> params, ShapeType shapeType) {
    Mesh mesh = model->getMesh();
    switch (shapeType) {
    case ShapeType::normal:
        btConvexHullShape* shape;
        btCollisionShape* shapeCol;
        shape = new btConvexHullShape;
        for (std::vector<Vertex>::iterator it = mesh.vertices.begin(); it != mesh.vertices.end(); it++) {
            shape->addPoint(btVector3((*it).Position[0], (*it).Position[1], (*it).Position[2]));
        }
        shape->optimizeConvexHull();
        collisionShapes.push_back(shape);
        break;
    case ShapeType::sphere:
        shapeCol = new btSphereShape(params[0]);
        collisionShapes.push_back(shapeCol);
        break;
    case ShapeType::plane:
        shapeCol = new btStaticPlaneShape(btVector3(params[0], params[1], params[2]), params[3]);
        collisionShapes.push_back(shapeCol);
        break;
    default:
        std::cout << "ERROR CREATING COLLISION SHAPE" << std::endl;
    }
}

void Physics::AddBody(RigidBodyInfo RBI, int index) {
    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
    btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    collisionShapes[index]->calculateLocalInertia(RBI.mass, RBI.fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, collisionShapes[index], fallInertia);
    btRigidBody* rigidBody = new btRigidBody(fallRigidBodyCI);
    rigidBodies.push_back(rigidBody);
    dynamicsWorld->addRigidBody(rigidBody);
}

void Physics::Update(float deltaTime, int maxSubSteps) {
    dynamicsWorld->stepSimulation(deltaTime, maxSubSteps);
}

btVector3 Physics::getPos(int index) {
    btTransform trans;
    rigidBodies[index]->getMotionState()->getWorldTransform(trans);
    return btVector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ());
}

void Physics::Delete() {
    for (std::vector<btRigidBody*>::iterator it = rigidBodies.begin(); it != rigidBodies.end(); it++) {
        dynamicsWorld->removeRigidBody((*it));
        delete (*it)->getMotionState();
    }
    rigidBodies.clear();
    collisionShapes.clear();
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}