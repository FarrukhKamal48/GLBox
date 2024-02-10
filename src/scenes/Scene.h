#pragma once

namespace Scene {
    
    class Scene {
    public:
        Scene() {};
        virtual ~Scene() {};
        
        virtual void Start() {};
        virtual void Update(float dt) {};
        virtual void Render() {};
        virtual void ImGuiRender() {};
    };

};
