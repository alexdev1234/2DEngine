#include "WindowSystem.h"
#include <iostream>

WindowSystem::WindowSystem(int width, int height, const std::string& windowName) :
	m_fWidth(width),
	m_fHeight(height),
	m_sWindowName(windowName),
	m_pWindow(nullptr)
{
}

WindowSystem::~WindowSystem()
{
	Shutdown();
}

void WindowSystem::Initialize()
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

	m_pWindow = glfwCreateWindow(m_fWidth, m_fHeight, m_sWindowName.c_str(), nullptr, nullptr);
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

void WindowSystem::Update(float dt)
{
	// Process any window events
	glfwPollEvents();
}

void WindowSystem::Shutdown()
{
	if (m_pWindow)
	{
		glfwDestroyWindow(m_pWindow);
		std::cout << "Window destroyed" << std::endl;
	}

	glfwTerminate();
}

bool WindowSystem::ShouldClose()
{
	return glfwWindowShouldClose(m_pWindow);
}

void WindowSystem::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


