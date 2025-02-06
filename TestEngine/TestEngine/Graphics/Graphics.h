#pragma once

// includes
#include "System.h"
#include <glad/glad.h>

class Graphics : public System
{
public:
	Graphics();
	~Graphics();

	void Initialize() override;
	void Update(float dt) override {};
	void Render() override;
	void Shutdown() override;

private:
	void InitShaders();
	void InitBuffers();

	GLuint m_shaderProgram;
	GLuint m_VAO, m_VBO, m_EBO;
};