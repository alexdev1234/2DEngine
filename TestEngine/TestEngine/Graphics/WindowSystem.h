#pragma once

// includes
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <string>

class WindowSystem
{
public:
	
	WindowSystem(int width, int height, const std::string& windowName);
	~WindowSystem();

	void Update();
	bool ShouldClose() const;
	void SetClearColor(float r, float g, float b, float a);

private:
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* m_pWindow;
	int m_fWidth;
	int m_fHeight;
};

