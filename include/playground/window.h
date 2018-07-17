
#ifndef WINDOW_H
#define WINDOW_H

#define WINDOW_TITLE "GLPlayground"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define UPDATE_RATE (1 / 60)

void ErrorCallback(int error, const char* description);
void Framebuffer_Size_Callback(GLFWwindow* window, int width, int height);
GLFWwindow* InitWindowContext(GLFWwindow *window);

#endif
