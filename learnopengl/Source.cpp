#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "ObjectLoader.h"
#include "Model.h"
#include "Physics.h"
#include <cmath>

#include <Windows.h> // TODO change this
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"


// Callback function for handling resizing window.
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Function for key input in window

int processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        return 0;
    }
    else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        return 1;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        return 2;
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        return 3;
    }
    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        return 4;
    }
    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        return 5;
    }
    else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        return 6;
    }
    else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        return 7;
    }
    else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        return 8;
    }
    else if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        return 9;
    }
    else if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
        return 10;
    }
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        return 11;
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        return 12;
    }
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        return 13;
    }
    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        return 14;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        return 15;
    }
    else if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        return 16;
    }
    return 0;
}

btBroadphaseInterface* broadphase;
btDefaultCollisionConfiguration* collisionConfiguration;
btCollisionDispatcher* dispatcher;
btSequentialImpulseConstraintSolver* solver;
// Init physics
btDiscreteDynamicsWorld* initPhysics() {
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
    solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));
    return dynamicsWorld;
}


btRigidBody* createBall(btDiscreteDynamicsWorld* dynamicsWorld) {
    btCollisionShape* fallShape = new btSphereShape(1);
    // Create info for sphere and add to world
    // 50m above ground
    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 30, 0)));
    btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    fallShape->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
    dynamicsWorld->addRigidBody(fallRigidBody);
    return fallRigidBody;
}

void deleteBall(btDiscreteDynamicsWorld* dynamicsWorld, btRigidBody* fallRigidBody) {

    dynamicsWorld->removeRigidBody(fallRigidBody);
    delete fallRigidBody->getMotionState();
    delete fallRigidBody;
}



int main(void)
{
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Tell glfw to use opengl 3.3 with only core features.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Learn Opengl", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to make window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current, 
    set viewport coords
    register callback for window resize*/
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Initialize glew */
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "glew init err: " << glewGetErrorString(err) << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    Shader ourShader("shader.vs", "shader.fs");

    std::string modelFile = "sphere.obj";
    Model ourModel(&modelFile[0]);

    std::string modelFile2 = "sphere2.obj";
    Model ourModel2(&modelFile2[0]);

    std::string modelFile3 = "plane.obj";
    Model ourModel3(&modelFile3[0]);

    std::string modelFile4 = "wedge.obj";
    Model wedgeModel1(&modelFile4[0]);

    std::string modelFile5 = "wedge2.obj";
    Model wedgeModel2(&modelFile5[0]);

    btDiscreteDynamicsWorld* dynamicsWorld = initPhysics();
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    btCollisionShape* fallShape2 = new btSphereShape(2);
    btConvexHullShape* wedgeShape = new btConvexHullShape;
    Mesh mesh = wedgeModel1.getMesh();
    for (std::vector<Vertex>::iterator it = mesh.vertices.begin(); it != mesh.vertices.end(); it++) {
        wedgeShape->addPoint(btVector3((*it).Position[0], (*it).Position[1], (*it).Position[2]));
    }
    wedgeShape->optimizeConvexHull();
    btConvexHullShape* wedgeShape2 = new btConvexHullShape;
    Mesh mesh2 = wedgeModel2.getMesh();
    for (std::vector<Vertex>::iterator it = mesh2.vertices.begin(); it != mesh2.vertices.end(); it++) {
        wedgeShape2->addPoint(btVector3((*it).Position[0], (*it).Position[1], (*it).Position[2]));
    }
    wedgeShape2->optimizeConvexHull();

    // Create info for ground and add to world
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);

    // First ball
    btRigidBody* fallRigidBody = createBall(dynamicsWorld);

    // Sphere 2
    btDefaultMotionState* fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0.1f, 40, 0)));
    btScalar mass2 = 2;
    btVector3 fallInertia2(0, 0, 0);
    fallShape2->calculateLocalInertia(mass2, fallInertia2);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI2(mass2, fallMotionState2, fallShape2, fallInertia2);
    btRigidBody* fallRigidBody2 = new btRigidBody(fallRigidBodyCI2);
    dynamicsWorld->addRigidBody(fallRigidBody2);

    // Wedge 1
    btDefaultMotionState* wedgeMotionState1 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 20, 0)));
    btScalar massWedge = 0;
    btVector3 fallInertiaWedge(0, 0, 0);
    wedgeShape->calculateLocalInertia(massWedge, fallInertiaWedge);
    btRigidBody::btRigidBodyConstructionInfo wedgeRigidBodyCI(massWedge, wedgeMotionState1, wedgeShape, fallInertiaWedge);
    btRigidBody* wedgeRigidBody = new btRigidBody(wedgeRigidBodyCI);
    dynamicsWorld->addRigidBody(wedgeRigidBody);

    // Wedge 2
    btDefaultMotionState* wedgeMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 7)));
    btRigidBody::btRigidBodyConstructionInfo wedgeRigidBodyCI2(massWedge, wedgeMotionState2, wedgeShape2, fallInertiaWedge);
    btRigidBody* wedgeRigidBody2 = new btRigidBody(wedgeRigidBodyCI2);
    dynamicsWorld->addRigidBody(wedgeRigidBody2);



 /*   Physics * physics = new Physics();
    RigidBodyInfo RBI;
    RBI.position = btVector3(0, -1, 0);
    RBI.mass = 0;
    RBI.fallInertia = btVector3(0, 0, 0);
    std::vector<int>params = { 0, 1, 0, 1 };
    physics->LoadMesh(&ourModel3, params, ShapeType::plane);
    int groundIndex = 0;
    physics->AddBody(RBI, groundIndex);

    RBI.position = btVector3(0, 50, 0);
    RBI.mass = 1;
    params = { 1 };
    physics->LoadMesh(&ourModel, params, ShapeType::sphere);
    int sphere1Index = 1;
    physics->AddBody(RBI, sphere1Index);*/



    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 groundModel = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    view = glm::translate(view, glm::vec3(0.0f, -20.0f, -50.0f));
    view = glm::rotate(view, 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 translationA(200.0f, 200.0f, 0.0f);
    glm::vec3 translationB(400.0f, 200.0f, 0.0f);

    ourShader.setInt("shaderType", 0);
    float ballLapse = 0.0f; // Lapsed time for balls.

    bool showDepthOff = false;  // Initialize false so program automatically sets bool.
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        ballLapse = ballLapse + deltaTime;
        float rotationSpeed = 0.7f;
        // Input
        int input = processInput(window);
        
        /* Render here */
        glClearColor(0.1f, 0.15f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Translations for viewing
        
        
        switch (input) {
        case 0:  // Set defaults for rendering.
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            if (!showDepthOff) {  // Optimization so we don't send a uniform to gpu every frame.
                ourShader.setBool("showDepth", false);
                showDepthOff = true;
            }
            break;
        case 1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
        case 2: // s
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -15.0f * deltaTime)); break;
        case 3: // w
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, 6.0f * deltaTime)); break;
        case 4: // k
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(rotationSpeed * deltaTime, 0.0f, 0.0f)); break;
        case 5: // l
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(0.0f, rotationSpeed * deltaTime, 0.0f)); break;
        case 6: // i
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(-rotationSpeed * deltaTime, 0.0f, 0.0f)); break;
        case 7: // j
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(0.0f, -rotationSpeed * deltaTime, 0.0f)); break;
        case 8: // o
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(0.0f, 0.0f, -rotationSpeed * deltaTime)); break;
        case 9: // u
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(0.0f, 0.0f, rotationSpeed * deltaTime)); break;
        case 10: // 9
            ourShader.setBool("showDepth", true); showDepthOff = false; break;
        case 11: // no shader, key 1
            ourShader.setInt("shaderType", 0); break;
        case 12: // gouraud shader, key 2
            ourShader.setInt("shaderType", 1); break;
        case 13: // phong shader, key 3
            ourShader.setInt("shaderType", 2); break;
        case 14: // key e, scale object bigger
            model = glm::scale(model, glm::vec3(1.01f));
        case 15: // key d, scale object smaller
            model = glm::scale(model, glm::vec3(0.99f));
        case 16: // key b, make new ball/ delete old one
            if (ballLapse > 1) {
                deleteBall(dynamicsWorld, fallRigidBody);
                fallRigidBody = createBall(dynamicsWorld);
                ballLapse = 0.0f;
            }
        }


        dynamicsWorld->stepSimulation(deltaTime, 10);
        btTransform trans;
        btTransform trans2;
        btTransform trans3;
        btTransform trans4;
        fallRigidBody->getMotionState()->getWorldTransform(trans);
        fallRigidBody2->getMotionState()->getWorldTransform(trans2);
        wedgeRigidBody->getMotionState()->getWorldTransform(trans3);
        wedgeRigidBody2->getMotionState()->getWorldTransform(trans4);

        //physics->Update(deltaTime, 10);

        //btVector3 pos = physics->getPos(sphere1Index);
        //ourShader.setMatrix4fv("model", glm::translate(model, glm::vec3(pos[0], pos[1], pos[2])));
        ourShader.setMatrix4fv("model", glm::translate(model,
            glm::vec3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ())));
        ourShader.setMatrix4fv("view", view);
        ourShader.setMatrix4fv("projection", projection);

        ourShader.setVec3("viewPos", glm::vec3(view * glm::vec4(1.0, 1.0, 1.0, 1.0)));

        ourShader.use();

        ourModel.Draw(ourShader);

        ourShader.setMatrix4fv("model", glm::translate(model,
            glm::vec3(trans2.getOrigin().getX(), trans2.getOrigin().getY(), trans2.getOrigin().getZ())));

        ourModel2.Draw(ourShader);

        ourShader.setMatrix4fv("model", glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)));

        ourModel3.Draw(ourShader);

        ourShader.setMatrix4fv("model", glm::translate(model,
            glm::vec3(trans3.getOrigin().getX(), trans3.getOrigin().getY(), trans3.getOrigin().getZ())));

        wedgeModel1.Draw(ourShader);

        ourShader.setMatrix4fv("model", glm::translate(model,
            glm::vec3(trans4.getOrigin().getX(), trans4.getOrigin().getY(), trans4.getOrigin().getZ())));

        wedgeModel2.Draw(ourShader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // Deallocation
    ourModel.Delete();
    ourShader.deleteProgram();

 /*   physics->Delete();*/

    dynamicsWorld->removeRigidBody(wedgeRigidBody2);
    delete wedgeRigidBody2->getMotionState();
    delete wedgeRigidBody2;

    dynamicsWorld->removeRigidBody(wedgeRigidBody);
    delete wedgeRigidBody->getMotionState();
    delete wedgeRigidBody;

    dynamicsWorld->removeRigidBody(fallRigidBody2);
    delete fallRigidBody2->getMotionState();
    delete fallRigidBody2;


    dynamicsWorld->removeRigidBody(groundRigidBody);
    delete groundRigidBody->getMotionState();
    delete groundRigidBody;

    delete fallShape2;
    delete wedgeShape;
    delete wedgeShape2;
    delete groundShape;
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;

    glfwTerminate();
    return 0;
}