#include "WindowSystem.h"
#include <iostream>

WindowSystem::WindowSystem(int width, int height, const std::string& windowName) :
	m_fWidth(width),
	m_fHeight(height)
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		exit(EXIT_FAILURE);
	}

	// Using opengl version 3.3 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_pWindow = glfwCreateWindow(m_fWidth, m_fHeight, windowName.c_str(), nullptr, nullptr);
	if (!m_pWindow)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Set current context
	glfwMakeContextCurrent(m_pWindow);

	// Load glfw function pointers using glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		exit(EXIT_FAILURE);
	}

	// Set viewport and callback
	glViewport(0, 0, m_fWidth, m_fHeight);
	glfwSetFramebufferSizeCallback(m_pWindow, FramebufferSizeCallback);
}

WindowSystem::~WindowSystem()
{
	// Terminate glfw processes
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
}

void WindowSystem::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void WindowSystem::Update()
{
	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();
}

bool WindowSystem::ShouldClose() const
{
	return glfwWindowShouldClose(m_pWindow);
}

void WindowSystem::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
