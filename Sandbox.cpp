#include "Sandbox.h"

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
#include <Core/EntryPoint.h>

