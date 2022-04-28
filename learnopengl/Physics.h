#pragma once
#include <iostream>

#include "btBulletDynamicsCommon.h"
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include "Bullet3Common/b3FileUtils.h"
#include "Model.h"


class Physics {
private:
	btDiscreteDynamicsWorld* dynamicsWorld;
	
public:
	Physics();
	void LoadMesh(Model * model);
};


