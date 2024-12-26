#include <Core/EntryPoint.h>
#include <Core/Application.h>
#include <ExampleLayers/VerletInstancingLayer.h>

class MyApp : public Application {
public:
    MyApp() : Application({ "GLBox", 1920, 1080 })
    {
        PushLayer(new VerletInstanced());
    }
    ~MyApp() { }
};

Application* CreateApplication() {
    return new MyApp();
}
