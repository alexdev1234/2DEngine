#pragma once
#include <glad/glad.h>

#include "System.h"

class RenderSystem : public System
{
public:
    RenderSystem();
    ~RenderSystem();

    void Initialize() override;
    void Update(float dt) override;
    void Render() override;
    void Shutdown() override;

private:
    GLuint m_shaderProgram;
    GLuint VAO, VBO;

    void InitShaders();
    void InitBuffers();
};


