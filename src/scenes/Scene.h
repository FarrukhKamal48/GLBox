#pragma once

namespace Scene {
    
    class Scene {
    public:
        Scene() {};
        virtual ~Scene() {};
        
        virtual void Update(float deltaTime) {};
        virtual void Render() {};
        virtual void ImGuiRender() {};
    };

};
