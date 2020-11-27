/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <stb_image.h>

// Instantiate static variables
std::map<std::string, Texture2D>                ResourceManager::Textures;
std::map<std::string, Shader>                   ResourceManager::Shaders;
std::map<std::string, SpriteAnimation>          ResourceManager::Anims;


Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    if(Shaders.find(name) == Shaders.end())
        Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);

    return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
    if(Textures.find(name) == Textures.end())
        Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

SpriteAnimation ResourceManager::LoadAnims(const char *file, Texture2D texture, std::string name)
{
    if (Anims.find(name) == Anims.end())
    {
        loadAnimFromFile(file, texture, name);
    }

    return Anims[name];
}

SpriteAnimation ResourceManager::GetAnims(std::string name)
{
    return Anims[name];
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
	Shaders.clear();
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
	Textures.clear();
    for (auto iter : Anims)
    {
        int count_s = iter.second.GetAnimStatusMax();
        for (int i = 0; i < count_s; ++i)
        {
            int count_i = iter.second.GetAnimIndexMax(i);
            for (int j = 0; j < count_i; ++j)
                glDeleteVertexArrays(1, iter.second.GetVao(i, j));
        }
        iter.second.DeleteAnim();
    }
	Anims.clear();
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    // create texture object
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}

void ResourceManager::loadAnimFromFile(const char* file, Texture2D texture, std::string name)
{
    SpriteAnimation anims;
    std::ifstream fileopen(file);
    char ch[256];
    std::vector<std::vector<int>> vao;
    std::vector<float> interval_max;
    std::vector<std::vector<int>> xCenter;
    std::vector<std::vector<int>> yCenter;
    std::vector<std::vector<int>> width;
    std::vector<std::vector<int>> height;

    std::vector<int> t_vao;
    std::vector<int> t_xCenter;
    std::vector<int> t_yCenter;
    std::vector<int> t_width;
    std::vector<int> t_height;

    while (!fileopen.eof())
    {
        char t = '0';
        int index = 0;
        std::string str;
        std::vector<int> nums;

        fileopen.getline(ch, 256);
        while (index < 256)
        {
            while (index < 256)
            {
                t = ch[index++];
                if (t == ' ' || t == '\0')
                    break;
                str += t;
            }
            nums.push_back(std::stoi(str));
            str.clear();
            if (t == '\0')
                break;
        }
        t_vao.push_back(ImportVAO(nums, texture));
        t_xCenter.push_back(nums[4]);
        t_yCenter.push_back(nums[5]);
        t_width.push_back(nums[2] - nums[0]);
        t_height.push_back(nums[3] - nums[1]);

        if (nums.size() == 7)
        {
            interval_max.push_back((float)nums[6]);
            vao.push_back(t_vao);
            xCenter.push_back(t_xCenter);
            yCenter.push_back(t_yCenter);
            width.push_back(t_width);
            height.push_back(t_height);
            t_vao.clear();
            t_xCenter.clear();
            t_yCenter.clear();
            t_width.clear();
            t_height.clear();
        }
    }

    anims.SetAnimInfo(vao, interval_max, xCenter, yCenter, width, height);

    fileopen.close();

    Anims[name] = anims;

    anims.DeleteAnim();
}

unsigned int ResourceManager::ImportVAO(std::vector<int> rect, Texture2D texture)
{
    float t_width = (float)texture.Width;
    float t_height = (float)texture.Height;
    float left = (float)rect[0] / t_width;
    float bottom = (float)rect[1] / t_height;
    float right = (float)rect[2] / t_width;
    float top = (float)rect[3] / t_height;
    unsigned int VAO, VBO;

    float vertices[24] = {
        // pos      // tex
        left, bottom, left, bottom,
        right, top, right, top,
        left, top, left, top,

        left, bottom, left, bottom,
        right, bottom, right, bottom,
        right, top, right, top
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return VAO;
}
