#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "resource_manager.h"
#include "collider_manager.h"
#include "player.h"
#include "background.h"

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
//Game game;

int main(int argc, char *argv[])
{
    // glfw: initialize and configure
    // ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    Background back;
    std::vector<Texture2D> sprites;
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_10.png").c_str(), false, "layer_10"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_11.png").c_str(), false, "layer_11"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_12.png").c_str(), false, "layer_12"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_13.png").c_str(), false, "layer_13"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_14.png").c_str(), false, "layer_14"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_15.png").c_str(), false, "layer_15"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_16.png").c_str(), false, "layer_16"));
    back.PushSprite(sprites, glm::vec2(2.0f, 2.0f));
    sprites.clear();
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_20.png").c_str(), true, "layer_20"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_21.png").c_str(), true, "layer_21"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_22.png").c_str(), true, "layer_22"));
    back.PushSprite(sprites, glm::vec2(2.0f, 2.0f));
    sprites.clear();
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_40.png").c_str(), true, "layer_40"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_41.png").c_str(), true, "layer_41"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_42.png").c_str(), true, "layer_42"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_43.png").c_str(), true, "layer_43"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_44.png").c_str(), true, "layer_44"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_45.png").c_str(), true, "layer_45"));
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_46.png").c_str(), true, "layer_46"));
    back.PushSprite(sprites, glm::vec2(2.0f, 2.0f));
    sprites.clear();
    Background front;
    sprites.push_back(ResourceManager::LoadTexture(((std::string)"./Resource/Backgrounds/Dungeon2/layer_3.png").c_str(), true, "layer_3"));
    front.PushSprite(sprites, glm::vec2(2.0f, 2.0f));
    sprites.clear();

    //CollObject obj({ 1000.0f,100.0f }, { 1.0f,1.0f }, ResourceManager::LoadTexture(((std::string)"./Resource/Image/Electric_Knight.png").c_str(), true, "dog"));
    //obj.Create(ResourceManager::LoadAnims(((std::string)"./Resource/VertexData/Electric_Knight.txt").c_str(), obj.Sprite, "dog"),
    //    ColliderManager::LoadCollider(((std::string)"./Resource/ColliderData/dog.txt").c_str(), "dog"));

    Player player({ 500.0f, 0.0f }, { 2.0f,2.0f }, ResourceManager::LoadTexture("./Resource/Image/player.png", true, "player"));
    player.Create(ResourceManager::LoadAnims("./Resource/VertexData/player.txt", player.Sprite, "player"),
        ColliderManager::LoadCollider("./Resource/ColliderData/player.txt", "player"));

    CollObject obj(glm::vec2(1000.0f, 600.0f), glm::vec2(2.0f, 2.0f), ResourceManager::LoadTexture("./Resource/Image/dungeon2_tile.png", true, "dungeon2_tile"));
    obj.Create(ResourceManager::LoadAnims("./Resource/VertexData/dungeon2_tile.txt", obj.Sprite, "dungeon2_tile"),
        ColliderManager::LoadCollider("./Resource/ColliderData/dungeon2_tile1.txt","dungeon2_tile1"));
    obj.Type = ObjectType::WALL;

    CollObject obj1(glm::vec2(600.0f, 500.0f), glm::vec2(2.0f, 2.0f), ResourceManager::LoadTexture("./Resource/Image/dungeon2_tile.png", true, "dungeon2_tile"));
    obj1.Create(ResourceManager::LoadAnims("./Resource/VertexData/dungeon2_tile.txt", obj1.Sprite, "dungeon2_tile"),
        ColliderManager::LoadCollider("./Resource/ColliderData/dungeon2_tile1.txt", "dungeon2_tile1"));
    obj1.Type = ObjectType::WALL;

    player.Active = true;
    obj.Active = true;
    obj1.Active = true;

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
        back.Update(renderer, deltaTime);
        obj.Update(renderer, deltaTime);
        obj1.Update(renderer, deltaTime);
        player.Update(renderer, deltaTime);
        front.Update(renderer, deltaTime);

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