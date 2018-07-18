
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <cstdio>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "playground/playground.h"

#define VERTEX_SHADER_SOURCE_PATH "./src/shader/simple.vert"
#define FRAGEMENT_SHADER_SOURCE_PATH "./src/shader/simple.frag"

bool SetupGL();
void RenderCommand();
void UICommand(GLFWwindow *window);

void DrawDebugUI(GLFWwindow *window);
void DrawTextWindow();

char *openglVersion;
char *glslVersion;

char *vertexSourceFile;
char *fragementSourceFile;

int vertextOffsetLocation;
int vertextColorLocation;

unsigned int VBO;
unsigned int VAO;
unsigned int vertexShader;
unsigned int fragementShader;
unsigned int shaderProgram;

float verticies[] = {
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

glm::vec2 vertexOffset = { 0.0f, 0.0f };
glm::vec2 defaultVertexOffset = { 0.0f, 0.0f };

glm::vec4 clearColor = { 0.2f, 0.3f, 0.3f, 1.0f };
glm::vec4 defaultClearColor = { 0.2f, 0.3f, 0.3f, 1.0f };

glm::vec4 vertextColor = { 1.0f, 1.0f, 1.0f, 1.0f };
glm::vec4 defaultVertexColor = { 1.0f, 1.0f, 1.0f, 1.0f };

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

    vertexSourceFile = LoadFile((char*)VERTEX_SHADER_SOURCE_PATH);
    fragementSourceFile = LoadFile((char*)FRAGEMENT_SHADER_SOURCE_PATH);

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

    glDeleteProgram(shaderProgram);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    free(vertexSourceFile);
    free(fragementSourceFile);

    return 0;
}

bool SetupGL()
{
    openglVersion = (char*)glGetString(GL_VERSION);
    glslVersion = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (!CompileShader((char*)VERTEX_SHADER_SOURCE_PATH, GL_VERTEX_SHADER, &vertexShader)) {
        fprintf(stderr, "Error, Can't compile vertex shader..\n");
        return false;
    }

    if (!CompileShader((char*)FRAGEMENT_SHADER_SOURCE_PATH, GL_FRAGMENT_SHADER, &fragementShader)) {
        fprintf(stderr, "Error, Can't compile fragement shader..\n");
        return false;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragementShader);

    glLinkProgram(shaderProgram);

    int linkSuccess = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);

    if (!linkSuccess) {
        fprintf(stderr, "Can't link shader..\n");

        glDeleteShader(vertexShader);
        glDeleteShader(fragementShader);

        return false;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragementShader);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    return true;
}

void RenderCommand()
{
    glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    vertextOffsetLocation = glGetUniformLocation(shaderProgram, "offset");
    vertextColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    glUniform2f(vertextOffsetLocation, vertexOffset.x, vertexOffset.y);
    glUniform4f(vertextColorLocation, vertextColor.x, vertextColor.y, vertextColor.z, vertextColor.w);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void UICommand(GLFWwindow *window)
{
    DrawDebugUI(window);
    DrawTextWindow();
}

void DrawDebugUI(GLFWwindow *window)
{
    {
        ImGui::Text("OpenGL : ");
        ImGui::BulletText("Version : %s", openglVersion);

        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("GLSL : ");
        ImGui::BulletText("Version : %s", glslVersion);

        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Color : ");
        ImGui::ColorEdit4("Background", (float*)&clearColor);
        ImGui::ColorEdit4("Vertex", (float*)&vertextColor);

        if (ImGui::Button("Reset##1")) {
            clearColor = defaultClearColor;
            vertextColor = defaultVertexColor;
        }

        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Offset : (%.2f, %.2f)", vertexOffset.x, vertexOffset.y);
        ImGui::SliderFloat("X", &vertexOffset.x, -1.0f, 1.0f, "");
        ImGui::SliderFloat("Y", &vertexOffset.y, -1.0f, 1.0f, "");

        if (ImGui::Button("Reset##2")) {
            vertexOffset = defaultVertexOffset;
        }

        ImGui::Separator();

        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        if (ImGui::Button("Quit")) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

void DrawTextWindow()
{
    ImGui::Begin("Vertex Shader", NULL);
    ImGui::Text(vertexSourceFile);
    ImGui::End();

    ImGui::Begin("Fragement Shader", NULL);
    ImGui::Text(fragementSourceFile);
    ImGui::End();
}

