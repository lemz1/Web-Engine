#include "engine/core/Application.h"
#include "engine/object/Sprite.h"

class ExampleState : public State 
{
public:
    void Create() override
    {
        sprite = MakeScoped<Sprite>();
    }

    void Draw(wgpu::RenderPassEncoder renderPass) override
    {
        sprite->Draw(renderPass);
    }
public:
    Scoped<Sprite> sprite = nullptr;
};

int main() 
{
    Application* app = new Application(1280, 720, "Example", new ExampleState());
    app->Run();
    delete app;

    return 0;
}
