#include "Window.h"

#include <iostream>
#include <cassert>

#include "engine/core/Input.h"
#include "engine/core/Application.h"
#include "engine/core/event/WindowEvent.h"
#include "engine/core/event/KeyboardEvent.h"
#include "engine/core/event/MouseEvent.h"

Window::Window(
	uint32_t width, 
	uint32_t height, 
	const char* title
)
{
	_data.width = width;
	_data.height = height;
	_data.title = title;

	if (!glfwInit())
	{
		std::cerr << "Could not initialize GLFW!" << std::endl;
		assert(false);
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	_handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!_handle)
	{
		glfwTerminate();
		std::cerr << "Could not create window!" << std::endl;
		assert(false);
	}

	glfwSetWindowUserPointer(_handle, &_data);

	glfwSetFramebufferSizeCallback(_handle, [](GLFWwindow* window, int width, int height) 
	{
		// Recreate SwapChain
		wgpu::Device device = Application::GetWGPUContext()->device;
		wgpu::Surface surface = Application::GetWGPUContext()->surface;
		wgpu::TextureFormat swapChainFormat = Application::GetWGPUContext()->swapChainFormat;
		wgpu::SwapChain& swapChain = Application::GetWGPUContext()->swapChain;
		DepthTexture* depthTexture = Application::GetWGPUContext()->depthTexture;

		swapChain.release();

		wgpu::SwapChainDescriptor swapChainDesc;
		swapChainDesc.label = "SwapChain";
		swapChainDesc.width = (uint32_t)width;
		swapChainDesc.height = (uint32_t)height;
		swapChainDesc.usage = wgpu::TextureUsage::RenderAttachment;
		swapChainDesc.format = swapChainFormat;
		swapChainDesc.presentMode = wgpu::PresentMode::Fifo;
		swapChain = device.createSwapChain(surface, swapChainDesc);

		depthTexture->Resize(width, height);
	});

	glfwSetWindowCloseCallback(_handle, [](GLFWwindow* window)
	{
		WindowCloseEvent event = WindowCloseEvent();
		Application::GetState()->Event(event);
	});

	glfwSetWindowSizeCallback(_handle, [](GLFWwindow* window, int width, int height)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.width = (uint32_t)width;
		data.height = (uint32_t)height;

		WindowResizeEvent event((uint32_t)width, (uint32_t)height);
		Application::GetState()->Event(event);
	});

	glfwSetWindowPosCallback(_handle, [](GLFWwindow* window, int xPos, int yPos)
	{
		WindowMovedEvent event = WindowMovedEvent(Vec2(xPos, yPos));
		Application::GetState()->Event(event);
	});

	glfwSetWindowFocusCallback(_handle, [](GLFWwindow* window, int focused)
	{
		WindowFocusEvent event = WindowFocusEvent((bool)focused);
		Application::GetState()->Event(event);
	});

	glfwSetKeyCallback(_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (action)
		{
			case GLFW_PRESS:
			{
				{
					KeyPressedEvent event(key, false);
					Application::GetState()->Event(event);
				}

				{
					KeyJustPressedEvent event(key);
					Application::GetState()->Event(event);
				}
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, true);
				Application::GetState()->Event(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				Application::GetState()->Event(event);
				break;
			}
		}
	});

	glfwSetScrollCallback(_handle, [](GLFWwindow* window, double xScroll, double yScroll) 
	{
		Vec2 scroll = Vec2((float)xScroll, (float)yScroll);
		Input::_Scroll = scroll;

		MouseScrolledEvent event = MouseScrolledEvent(scroll);
		Application::GetState()->Event(event);
	});

	glfwSetMouseButtonCallback(_handle, [](GLFWwindow* window, int button, int action, int mods) 
	{
		switch (action) 
		{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event = MouseButtonPressedEvent(button);
				Application::GetState()->Event(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event = MouseButtonReleasedEvent(button);
				Application::GetState()->Event(event);
				break;
			}
		}
	});

	glfwSetCursorPosCallback(_handle, [](GLFWwindow* window, double xMousePos, double yMousePos) 
	{
		MouseMovedEvent event = MouseMovedEvent(Vec2(xMousePos, yMousePos));
		Application::GetState()->Event(event);
	});
}

Window::~Window()
{
	glfwDestroyWindow(_handle);
	glfwTerminate();
}
