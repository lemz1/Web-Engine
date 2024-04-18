#include "engine/Engine.h"

class ExampleState : public State 
{
public:
    void Create() override
    {
        camera = MakeRef<Camera>(Application::GetWindow()->GetWidth(), Application::GetWindow()->GetHeight());
        camera->SetPosition(Vec3(0.0f, 0.0f, -10.0f));

        image = AssetManager::LoadImage("assets/images/test.png");

        sprite = MakeScoped<Sprite>(image);
        sprite->transform.position.x = -0.5f;
        sprite->camera = camera;

        sprite2 = MakeScoped<Sprite>(0xFF0000FF);
        sprite2->transform.position.x = 0.5f;
        sprite2->camera = camera;
    }

    void Draw(wgpu::RenderPassEncoder renderPass) override
    {
        sprite->Draw(renderPass);
        sprite2->Draw(renderPass);
    }

    void DrawImGui() override
    {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::ShowDemoWindow();
    }
public:
    Scoped<Sprite> sprite = nullptr;
    Scoped<Sprite> sprite2 = nullptr;
    Ref<Camera> camera = nullptr;
    Ref<Image> image = nullptr;
};

int main() 
{
    Instrumentor::Get().BeginSession("Game", "Chrome-Tracing-Example.json");
    Application* app = new Application(1280, 720, "Example", new ExampleState());
    app->Run();
    delete app;
    Instrumentor::Get().EndSession();

    return 0;
}
