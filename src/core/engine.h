#ifndef ENGINE_H_
#define ENGINE_H_
#include <vector>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <ctime>
#include <cmath>
#include <iostream>

#include "../renderer/Shader.h"
#include "../camera/Camera.h"

struct WindowData
{
    WindowData():
    windowWidth(1600), 
    windowHeight(900){
    }
    int windowWidth;
    int windowHeight;
};


class Engine
{
private:
    bool initGLFW(); 
    bool initGLAD(); 
    bool init();
    void mainLoop();
    void input();
    void processEvents();
    void cleanUp();
    void setFullScreen(bool isFullscreen);
    void setWindowSize(int width, int height);

public:
    GLFWwindow* window;
    float deltaTime;
    float lastFrame;
    double lastFrameTime;
    Camera camera{1600, 900, glm::vec3(0.0f, 0.0f, 3.0f)};
    Engine();
    ~Engine();
    void run();
};
#endif
