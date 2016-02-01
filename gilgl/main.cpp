//
//  main.c
//  gilgl
//
//  Created by frellica on 16/1/28.
//  Copyright © 2016年 frellica. All rights reserved.
//
#include "gilgl.h"

int main(int argc, char ** argv) {
    GLFWwindow* window = NULL;
    const GLubyte* renderer;
    const GLubyte* version;
    GLuint vbo;
    GLuint vao;
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(1024, 768, "gl demo 1", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
   
    
    // Dark blue background
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint programID = LoadShaders("fragment/SimpleVertexShader.vertexshader",
                                   "fragment/SimpleFragmentShader.fragmentshader");
    

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), g_vertex_buffer_data,
                 GL_STATIC_DRAW);
    
    /* get version info */
    renderer = glGetString(GL_RENDERER); /* get renderer string */
    version = glGetString(GL_VERSION); /* version as a string */
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
    
    do {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programID);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();


    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
             && glfwWindowShouldClose(window) == 0);
    
    // Cleanup VBO
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(programID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    return 0;
    
}