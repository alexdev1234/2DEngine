#pragma once

// includes
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <string>
#include "System.h"

class WindowSystem : public System
{
public:
	
	WindowSystem(int width, int height, const std::string& windowName);
	~WindowSystem();

	void Initialize() override;
	void Update(float dt) override;
	void Render() override {}
	void Shutdown() override;

	bool ShouldClose() const;

	inline GLFWwindow* GetWindow() const { return m_pWindow; };

private:
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* m_pWindow;
	std::string m_sWindowName;
	int m_nWidth;
	int m_nHeight;
};

