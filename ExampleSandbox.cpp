#include <Core/EntryPoint.h>
#include "ExampleSandbox.h"

class MyApp : public Application {
public:
    MyApp() {
        PushLayer(new VerletInstanced());
    }
    ~MyApp() { }
};

Application* CreateApplication() {
    return new MyApp();
}
