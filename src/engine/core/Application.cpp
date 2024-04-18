#include "Application.h"

#include "engine/core/Input.h"
#include "engine/render/Renderer.h"

Application* Application::_Instance = nullptr;

Application::Application(
	uint32_t width, 
	uint32_t height, 
	const char* title,
	State* initialState
)
{
	if (_Instance)
	{
		return;
	}

	_Instance = this;

	_window = new Window(width, height, title);

	_wgpuContext = new WGPUContext(_window->GetHandle(), _window->GetWidth(), _window->GetHeight());

	Renderer::Init();

	_myguiContext = new MyGuiContext();

	_state = initialState;
	_state->Create();
}

Application::~Application()
{
	_state->Destroy();
	delete _state;

	delete _myguiContext;

	Renderer::Shutdown();

	delete _wgpuContext;
	delete _window;
}

void Application::Run()
{
	_time = 0;

	while (!glfwWindowShouldClose(_window->GetHandle()))
	{
		float newTime = (float)glfwGetTime();
		float deltaTime = newTime - _time;
		_time = newTime;

		Input::_Scroll = Vec2(0.0f, 0.0f);

		glfwPollEvents();

		_state->Update(deltaTime);

		_wgpuContext->StartFrame();

		_state->Draw(_wgpuContext->renderPass);

		_myguiContext->StartFrame();
		_state->DrawImGui();
		_myguiContext->EndFrame();

		_wgpuContext->EndFrame();
	}
}

void Application::SwitchState(State* nextState)
{
	_Instance->_state->Destroy();
	delete _Instance->_state;
	_Instance->_state = nextState;
	_Instance->_state->Create();
}
