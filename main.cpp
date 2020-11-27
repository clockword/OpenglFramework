#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "resource_manager.h"
#include "collider_manager.h"
#include "player.h"

#include "game.h"

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// GLFW function declerations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//Game Breakout(SCR_WIDTH, SCR_HEIGHT);
Game game;

int main(int argc, char *argv[])
{
    // glfw: initialize and configure
    // ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // configure global opengl state
    // -----------------------------
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    // ---------------
    //Breakout.Init();

    ResourceManager::LoadShader("vs_sprite.glsl", "fs_sprite.glsl", nullptr, "sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

    Shader temp = ResourceManager::GetShader("sprite");
    SpriteRenderer renderer(temp);

    CollObject obj({ 1000.0f,100.0f }, { 1.0f,1.0f }, ResourceManager::LoadTexture(((std::string)"./Resource/Image/dog.png").c_str(), true, "dog"));
    obj.Create(ResourceManager::LoadAnims(((std::string)"./Resource/VertexData/dog.txt").c_str(), obj.Sprite, "dog"),
        ColliderManager::LoadCollider(((std::string)"./Resource/ColliderData/dog.txt").c_str(), "dog"));

    Player player({ 500.0f,100.0f }, { 1.0f,1.0f }, ResourceManager::LoadTexture(((std::string)"./Resource/Image/dog.png").c_str(), true, "dog"));
    player.Create(ResourceManager::LoadAnims(((std::string)"./Resource/VertexData/dog.txt").c_str(), player.Sprite, "dog"),
        ColliderManager::LoadCollider(((std::string)"./Resource/ColliderData/dog.txt").c_str(), "dog"));

    obj.xFlip = true;
    obj.yFlip = true;

    /*game.Init(SCR_WIDTH, SCR_HEIGHT);*/

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    float fixedDuration = 0.0f;
    float fixedDeltaTime = 0.0f;
    float fixedLastFrame = 0.0f;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        fixedDuration += deltaTime;
        glfwPollEvents();

        // message input
        // -----

        // manage user input
        // -----------------
        //Breakout.ProcessInput(deltaTime);

        // update game state
        // -----------------
        //Breakout.Update(deltaTime);

        // render
        // ------
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Breakout.Render();
        //Texture2D temp = ResourceManager::GetTexture("crying_cat");
        //renderer.DrawSprite(temp, glm::vec2(100.0f, 100.0f));
        player.Update(renderer, deltaTime);
        obj.Update(renderer, deltaTime);

        /*game.Update(renderer, deltaTime);*/

        if (fixedDuration > 0.02f)
        {
            float fixedFrame = (float)glfwGetTime();
            fixedDeltaTime = fixedFrame - fixedLastFrame;
            fixedLastFrame = fixedFrame;
            fixedDuration = 0.0f;
            /*fixedUpdate*/
            ColliderManager::FixedUpdate(fixedDeltaTime);
            /*game.FixedUpdate(fixedDeltaTime);*/
        }

        glfwSwapBuffers(window);
    }
    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    ResourceManager::Clear();
    ColliderManager::Delete();
    /*game.Clear();*/

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //if (key >= 0 && key < 1024)
    //{
    //    if (action == GLFW_PRESS)
    //        Breakout.Keys[key] = true;
    //    else if (action == GLFW_RELEASE)
    //    {
    //        Breakout.Keys[key] = false;
    //        Breakout.KeysProcessed[key] = false;
    //    }
    //}
}