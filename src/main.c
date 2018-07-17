
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "playground/playground.h"

bool SetupGL();
void RenderCommand();
void UICommand(GLFWwindow *window);

float verticies[] = {
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

unsigned int VBO;
unsigned int VAO;
unsigned int vertexShader;
unsigned int fragementShader;
unsigned int shaderProgram;

bool isShowDemoMenu = true;

int main()
{
    GLFWwindow *window = NULL;
    window = InitWindowContext(window);

    if (!window) {
        fprintf(stderr, "Error : can't init window..");
        return -1;
    }

    if (!SetupGL()) {
        return -1;
    }

    SetupUI(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        UICommand(window);

        ImGui::Render();
        RenderCommand();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

bool SetupGL()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (!CompileShader((char*)"./src/shader/simple.vert", GL_VERTEX_SHADER, &vertexShader)) {
        fprintf(stderr, "Error, Can't compile vertex shader..\n");
        return false;
    }

    if (!CompileShader((char*)"./src/shader/simple.frag", GL_FRAGMENT_SHADER, &fragementShader)) {
        fprintf(stderr, "Error, Can't compile fragement shader..\n");
        return false;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragementShader);

    glLinkProgram(shaderProgram);

    int linkSuccess = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);

    if (linkSuccess) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragementShader);
    }
    else {
        fprintf(stderr, "Can't link shader..\n");
        return false;
    }

    glUseProgram(shaderProgram);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    return true;
}

void RenderCommand()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void UICommand(GLFWwindow *window)
{
    {
        ImGui::Text("Hi");
        if (ImGui::Button("Close app")) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }

    if (isShowDemoMenu) {
        ImGui::ShowDemoWindow(&isShowDemoMenu);
    }
}

