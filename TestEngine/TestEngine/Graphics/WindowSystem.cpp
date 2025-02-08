#include "WindowSystem.h"

#include <cassert>
#include <iostream>

WindowSystem::WindowSystem(int width, int height, const std::string& windowName) :
	m_nWidth(width),
	m_nHeight(height),
	m_sWindowName(windowName),
	m_pWindow(nullptr)
{
}

WindowSystem::~WindowSystem()
{
}

void WindowSystem::Initialize()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		assert(true);
	}

	// Using opengl version 3.3 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Get primary monitor
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	if (!monitor)
	{
		std::cerr << "Failed to get primary monitor\n";
		assert(true);
	}

	// Get current resolution of primary monitor
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	if (!mode)
	{
		std::cerr << "Failed to get video mode\n";
		assert(true);
	}

	m_nWidth = mode->width;
	m_nHeight = mode->height;

	m_pWindow = glfwCreateWindow(m_nWidth, m_nHeight, m_sWindowName.c_str(), nullptr, nullptr);
	if (!m_pWindow)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		assert(true);
	}

	// Set current context
	glfwMakeContextCurrent(m_pWindow);
	//glfwSwapInterval(1); // enable v-sync --> not necessary right now

	// Load glfw function pointers using glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		assert(true);
	}

	// Set viewport and callback
	glViewport(0, 0, m_nWidth, m_nHeight);
	glfwSetFramebufferSizeCallback(m_pWindow, FramebufferSizeCallback);
}

void WindowSystem::Update(float dt)
{
	// TODO: utilize message system to tell engine to close window if need be
	//if (glfwWindowShouldClose)
	//{
	//	// Send close message to engine
	//}

	// Process any window events
	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();
}

void WindowSystem::Shutdown()
{
	if (m_pWindow)
	{
		glfwDestroyWindow(m_pWindow);
		std::cout << "Window destroyed\n";
	}

	glfwTerminate();
}

bool WindowSystem::ShouldClose() const
{
	return glfwWindowShouldClose(m_pWindow);
}

void WindowSystem::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


