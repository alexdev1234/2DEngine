#include "RenderSystem.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

// Helper function for reading shader files
std::string ReadFile(const std::string& filepath)
{
    std::ifstream file(filepath);
    std::stringstream fileStream;

    if (file.is_open())
    {
        fileStream << file.rdbuf();
        file.close();
    }
    else
    {
        throw std::runtime_error("Failed to open file");
    }

    return fileStream.str();
}

RenderSystem::RenderSystem() :
    m_shaderProgram(0),
    VAO(0),
    VBO(0)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::Initialize()
{
    InitShaders();
    InitBuffers();
}

void RenderSystem::Update(float dt)
{
}

void RenderSystem::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_shaderProgram);
    glBindVertexArray(VAO);

    int colorLoc = glGetUniformLocation(m_shaderProgram, "color");
    if (colorLoc != -1)
    {
        glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f); // White color (RGBA)
    }
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void RenderSystem::Shutdown()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(m_shaderProgram);
}

void RenderSystem::InitShaders()
{
    std::string vertexSource = ReadFile("Shaders/VertexShader.txt");
    std::string fragmentSource = ReadFile("Shaders/FragmentShader.txt");

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        throw std::runtime_error("Failed to compile vertex shader.");
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fShaderCode = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        throw std::runtime_error("Failed to compile fragment shader.");
    }

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
        throw std::runtime_error("Failed to link program.");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void RenderSystem::InitBuffers()
{
    float vertices[] = {
        // Positions   // TexCoords  // Colors (RGBA)
        -0.5f, -0.5f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
         0.5f, -0.5f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f, // Bottom-right
         0.5f,  0.5f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f, 1.0f, // Top-right

        -0.5f, -0.5f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
         0.5f,  0.5f,  1.0f, 1.0f,   0.0f, 0.0f, 1.0f, 1.0f, // Top-right
        -0.5f,  0.5f,  0.0f, 1.0f,   1.0f, 1.0f, 0.0f, 1.0f  // Top-left
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position Attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // TexCoord Attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Color Attribute
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}