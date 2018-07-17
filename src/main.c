
#include "playground/playground.h"

#define WINDOW_TITLE "GLPlayground"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define UPDATE_RATE (1 / 60)

static void ErrorCallback(int error, const char* description);
static void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height);

void Render(GLFWwindow *window);

int main()
{
    GLFWwindow *window;
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        return -1;
    }

    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, Framebuffer_Size_Callback);

    float verticies[] = {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    unsigned int VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    unsigned int VAO;

    glGenVertexArrays(1, &VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int vertexShader;

    if (!CompileShader("./src/shader/simple.vert", GL_VERTEX_SHADER, &vertexShader)) {
        fprintf(stderr, "Error, Can't compile vertex shader..\n");
        return -1;
    }

    unsigned int fragementShader;

    if (!CompileShader("./src/shader/simple.frag", GL_FRAGMENT_SHADER, &fragementShader)) {
        fprintf(stderr, "Error, Can't compile fragement shader..\n");
        return -1;
    }

    unsigned int shaderProgram = glCreateProgram();

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
        return -1;
    }

    glUseProgram(shaderProgram);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        Render(window);
    }

    glfwTerminate();
    return 0;
}

static void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error : %s\n", description);
}

static void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Render(GLFWwindow *window)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
}

