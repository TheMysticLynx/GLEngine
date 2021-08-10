#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <glm/glm.hpp>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Mesh.h"
#include <iostream>
#include "GLTFImporter.h"

int WIDTH = 800;
int HEIGHT = 600;

double oldX;
double oldY;


#pragma region Callbacks
void window_resize(GLFWwindow*, int, int);
void mouse_move(GLFWwindow*, double newx, double newy);
void keyboard_input(GLFWwindow* window, int key, int scancode, int action, int mod);
#pragma endregion

Camera cam;

Vertex vertices[] = {
    //Position                            //Normal                       //Color                        //TexCoords

    //Front Face

    Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec3(1,1 ,1), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec3(1,1,1), glm::vec2(0.0f, 1.0f)},
    Vertex{glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec3(1,1,1), glm::vec2(1.0f, 1.0f)},
    Vertex{glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec3(1,1,1), glm::vec2(1.0f, 0.0f)},

    Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec3(1,1,1), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec3(1,1,1), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec3(1,1,1), glm::vec2(0.5f, 1.0f)},

    Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3( 0.0f, 0.5f, -0.8f), glm::vec3(1,1,1), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3( 0.0f, 0.5f, -0.8f), glm::vec3(1,1,1), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.5f, -0.8f), glm::vec3(1,1,1), glm::vec2(0.5f, 1.0f)},

    Vertex{glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3( 0.8f, 0.5f,  0.0f), glm::vec3(1,1,1), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3( 0.8f, 0.5f,  0.0f), glm::vec3(1,1,1), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.8f, 0.5f,  0.0f), glm::vec3(1,1,1), glm::vec2(0.5f, 1.0f)},

    Vertex{glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3( 0.0f, 0.5f,  0.8f), glm::vec3(1,1,1), glm::vec2(1.0f, 0.0f)},
    Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3( 0.0f, 0.5f,  0.8f), glm::vec3(1,1,1), glm::vec2(0.0f, 0.0f)},
    Vertex{glm::vec3( 0.0f, 0.8f,  0.0f), glm::vec3( 0.0f, 0.5f,  0.8f), glm::vec3(1,1,1), glm::vec2(0.5f, 1.0f)},

    
};

unsigned int indices[] = {
    0, 1, 2, // Bottom side
    0, 2, 3, // Bottom side
    4, 6, 5, // Left side
    7, 9, 8, // Non-facing side
    10, 12, 11, // Right side
    13, 15, 14 // Facing side
};



int main(void)
{
#pragma region Init
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "GL ENGINE", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress))) {
        return -1;
    }


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
#pragma endregion

#pragma region Callbacks
    glfwSetWindowSizeCallback(window, window_resize);
    glfwSetCursorPosCallback(window, mouse_move);
    glfwSetKeyCallback(window, keyboard_input);
#pragma endregion


    Shader frag("frag.glsl", GL_FRAGMENT_SHADER);
    Shader vert("vert.glsl", GL_VERTEX_SHADER);
    Program program({frag, vert});

    Shader frag2("light.frag", GL_FRAGMENT_SHADER);
    Shader vert2("light.vert", GL_VERTEX_SHADER);
    Program lightProgram({ frag2, vert2 });

    Texture textures[] = {
        Texture("./images/wall.jpg", GL_RGB)
    };

    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    
    Mesh light(verts, ind, tex);
    Mesh mesh(verts, ind, tex);

    float time = glfwGetTime();

    cam.position.y = 1;


    GLTFImporter::GetData("C:\\Users\\Kaide\\Documents\\skybox\\", "untitled.gltf");


    while (!glfwWindowShouldClose(window))
    {
        float delta = glfwGetTime() - time;
        time = glfwGetTime();

#pragma region Movement
        if (glfwGetKey(window, GLFW_KEY_W)) {
            cam.position += cam.lookVec * delta;
        }
        if (glfwGetKey(window, GLFW_KEY_A)) {
            cam.position -= glm::cross(cam.lookVec, glm::vec3(0,1,0)) * delta;
        }
        if (glfwGetKey(window, GLFW_KEY_S)) {
            cam.position -= cam.lookVec * delta;
        }
        if (glfwGetKey(window, GLFW_KEY_D)) {
            cam.position += glm::cross(cam.lookVec, glm::vec3(0, 1, 0)) * delta;
        }
#pragma endregion


        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Text("Look Vector: %.1f, %.1f, %.1f", cam.lookVec.x, cam.lookVec.y, cam.lookVec.z);

        static float ambColor[3] = {.1, .1, .1};
        ImGui::ColorPicker3("Abient Color", ambColor);
        program.setF3("ambientColor", ambColor[0], ambColor[1], ambColor[2]);

        static float lightColor[3] = { .1, .1, .1 };
        ImGui::ColorPicker3("Light Color", lightColor);
        program.setF3("lightColor", lightColor[0], lightColor[1], lightColor[2]);

        static float lightPosArr[3] = {1, 1, 1};
        glm::vec3 lightPos(lightPosArr[0], lightPosArr[1], lightPosArr[2]);
        ImGui::DragFloat3("Light Position: ", lightPosArr);
        program.setF3("lightPos", lightPos.x, lightPos.y, lightPos.z);

        static float specStrength = .5;
        ImGui::SliderFloat("Specular Strength", &specStrength, 0, 1);
        program.setF1("specStrength", specStrength);

        program.setF3("viewPos", cam.position.x, cam.position.y, cam.position.z);

        program.setM4("proj", glm::perspective(glm::radians(90.0f), (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f));
        program.setM4("model", glm::translate(glm::mat4(1), glm::vec3(0, 0, -1)));
        
        program.Use();

        lightProgram.Use();
        lightProgram.setM4("proj", glm::perspective(glm::radians(90.0f), (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f));
        lightProgram.setF3("lightColor", lightColor[0], lightColor[1], lightColor[2]);
        lightProgram.setM4("model", glm::translate(glm::mat4(1), lightPos));
        light.Draw(lightProgram, cam);

        mesh.Draw(program, cam);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

bool lock = false;

void window_resize(GLFWwindow*, int w, int h) {
    WIDTH = w;
    HEIGHT = h;
    glViewport(0, 0, WIDTH, HEIGHT);
}

const float sense = .1;

void keyboard_input(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (key == GLFW_KEY_L && action == GLFW_PRESS) {
        lock = !lock;
        glfwSetInputMode(window, GLFW_CURSOR, lock ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }
        
}

void mouse_move(GLFWwindow* window, double newx, double newy) {
    if (!lock)
        return;

    if (!oldX) {
        glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
        oldX = WIDTH / 2;
        oldY = HEIGHT / 2;
        return;
    }

    cam.pitch -= (newy - oldY) * sense;
    cam.yaw += (newx - oldX) * sense;

    if (cam.pitch > 89.0f)
        cam.pitch = 89.0f;
    if (cam.pitch < -89.0f)
        cam.pitch = -89.0f;

    glfwSetCursorPos(window, WIDTH / 2, HEIGHT / 2);
    oldX = WIDTH / 2;
    oldY = HEIGHT / 2;
}