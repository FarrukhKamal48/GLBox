#include <Core/EntryPoint.h>
#include "Sandbox.h"


Scene::Scene* CreateScene() {
    return new Scene::VerletInstanced();
}
