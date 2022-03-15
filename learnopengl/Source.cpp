#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "ObjectLoader.h"
#include <Windows.h> // TODO change this

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
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        return 2;
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        return 3;
    }
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        return 4;
    }
    else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
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
    return 0;
}

int main(void)
{
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

    ObjectLoader ourObj("cube.obj");
    float* vertices = ourObj.getVertices();
    unsigned int* indices = ourObj.getIndices();

    // Array for the triangle
    /*float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2
    };*/

    // Arrays for rectangle
    //float vertices[] = {
    //    0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // top right
    //    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f   // top left 
    //};
    //unsigned int indices[] = {
    //    0, 1, 3,
    //    1, 2, 3
    //};

    // Arrays for cube
    //float vertices[] = {
    //    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,  // top right front
    //    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // top left front
    //    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // bottom right front
    //    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, // bottom left front

    //    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // top right back
    //    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top left back
    //    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom right back
    //    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f // bottom left back
    //};
    //unsigned int indices[] = {
    //    0, 1, 2, //front
    //    1, 2, 3,
    //    0, 1, 4, //top
    //    1, 5, 4,
    //    0, 4, 6,  //right
    //    0, 2, 6,
    //    1, 5, 7,  //left
    //    1, 3, 7,
    //    2, 3, 6, //bottom
    //    3, 7, 6,
    //    4, 5, 6, //back
    //    5, 6, 7
    //};



    // Buffer object
    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);  // generates buffer
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // binds buffer to array buffer target (all calls to GL_ARRAY_BUFFER will be to VBO
    glBufferData(GL_ARRAY_BUFFER, ourObj.getVerticesSize() * sizeof(float), vertices, GL_STATIC_DRAW); // sizeof = full byte storage for array
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // for triangles example
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ourObj.getIndicesSize() * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // for triangles example

    // Sending data to shaderProgram
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);

    // Translations for viewing
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0, 0.0f, 0.0f));
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f));
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Input
        int input = processInput(window);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (input == 0) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        if (input == 1) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        if (input == 2) {
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -0.01f));
        }
        if (input == 3) {
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.01f));
        }
        if (input == 4) {
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(0.5f, 0.0f, 0.0f));
        }
        if (input == 5) {
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(0.0f, 0.0f, 0.5f));
        }
        if (input == 6) {
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(-0.5f, 0.0f, 0.0f));
        }
        if (input == 7) {
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(0.0f, 0.0f, -0.5f));
        }
        if (input == 8) {
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(0.0f, 0.5f, 0.0f));
        }
        if (input == 9) {
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(0.005f), glm::vec3(0.0f, -0.5f, 0.0f));
        }

        ourShader.use();

        // Draw stuff
        /*float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");*/
        int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // Render squares
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        glDrawElements(GL_TRIANGLES, ourObj.getIndicesSize(), GL_UNSIGNED_INT, 0);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // Deallocation
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    ourShader.deleteProgram();

    glfwTerminate();
    return 0;
}