#include "engine.h"
#include "../renderer/Shader.h"
#include "../primitives/Cube.h"
void glfw_error_callback(int error, const char *description) 
{
    fprintf(stderr, "Error: %s\n", description);
}

void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height)  
{
    glViewport(0, 0, width, height);
}

Engine::Engine() 
{
    deltaTime =0;
    lastFrameTime =0;
}

Engine::~Engine() 
{
    
}

void Engine::run() 
{
    if(!init()){
        std::cout<<"Error while initializing!"<<std::endl;
        exit(-1);
    }
    mainLoop();
    cleanUp();
}

bool Engine::initGLFW()  
{
    glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit()){
        return false;
    }
    window = glfwCreateWindow(1600,900, "DEngine", NULL, NULL);
    if(!window){
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
    return true;
}

bool Engine::initGLAD() 
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return false;
    }
    return true;
}

bool Engine::init() 
{
    if(!initGLFW()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    if (!initGLAD())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}

void Engine::mainLoop() 
{

    Shader testShader{"D:\\pkgl\\lab1\\Engine3D\\src\\shaders\\VertexTest.glsl", "D:\\pkgl\\lab1\\Engine3D\\src\\shaders\\FragmentTest.glsl"};


    Cube testCube;

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, testCube.getVerticesSize(), testCube.getVerticesPtr(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    projection = glm::perspective(45.0f, 1600.0f/900.0f, 0.1f, 100.0f);
    //std::cout<<<<'\n';

    //testShader.Use();
    //testShader.Use();

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        input();
        processEvents();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        testShader.Use();
        view  = camera.GetViewMatrix();
        testShader.SetUniformMat4f("projection", projection);
        testShader.SetUniformMat4f("view", view);
        testShader.SetUniformMat4f("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



}
void Engine::cleanUp() 
{
    glfwDestroyWindow(window);
    glfwTerminate();
}



void Engine::input()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    camera.Inputs(window,deltaTime);
}

void Engine::processEvents()
{

}
