// includes
#include "Graphics.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>

// Helper function for reading shader file
std::string ReadFile(const std::string& filepath)
{
	std::ifstream file(filepath);
	std::stringstream fileStream;
	if (file.is_open())
	{
		fileStream << file.rdbuf();
	}
	else
	{
		std::cerr << "Error: Could not open file" << filepath << std::endl;
	}

	file.close();

	return fileStream.str();
}

Graphics::Graphics() :
	m_shaderProgram(0),
	m_VAO(0),
	m_VBO(0),
	m_EBO(0)
{
}

Graphics::~Graphics()
{
}

void Graphics::Initialize()
{
	InitShaders();
	InitBuffers();
}

void Graphics::Render()
{
	// Render square
	glClear(GL_COLOR_BUFFER_BIT);
	
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Graphics::Shutdown()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteProgram(m_shaderProgram);
}

void Graphics::InitShaders()
{
	GLint success = false;

	// Load shader files
	std::string vertexSource = ReadFile("Shaders/VertexShader.txt");
	std::string fragSource = ReadFile("Shaders/FragmentShader.txt");

	// Compiile and link shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexShaderStr = vertexSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderStr, nullptr);
	glCompileShader(vertexShader);

	// Check if we successfully compiled
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cerr << "Vertex shader failed compilation" << std::endl;
		assert(true);
	}

	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragShaderStr = fragSource.c_str();
	glShaderSource(fragShader, 1, &fragShaderStr, nullptr);
	glCompileShader(fragShader);

	// Check if we successfully compiled
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cerr << "Fragment shader failed compilation" << std::endl;
		assert(true);
	}

	// Shader program
	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragShader);
	glLinkProgram(m_shaderProgram);

	// Check if we successfully linked
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		std::cerr << "Shader program failed to link" << std::endl;
		assert(true);
	}

	// Clean up shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void Graphics::InitBuffers()
{
	// Placeholder currently for testing
	// Square vertices (centered at origin, side length 1)
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,  // Bottom-left
		 0.5f, -0.5f, 0.0f,  // Bottom-right
		 0.5f,  0.5f, 0.0f,  // Top-right
		-0.5f,  0.5f, 0.0f   // Top-left
	};

	GLuint indices[] = {
		0, 1, 2,  // First triangle
		2, 3, 0   // Second triangle
	};

	// Generate and bind VAO, VBO, and EBO
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Enable vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
