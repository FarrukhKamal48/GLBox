#include "Scene.h"
#include "../layer/Instancing/RendererInstanced.h"
#include "../layer/Input.h"
#include <cstdlib>
#include <vector>

namespace Scene {
    class FixedGridSpacePartitionTest : public Scene {
    private:
        constexpr static int m_ObjCount = 1000;
        Pos_Scale_Col_Quad* m_ObjData;
    public:
        FixedGridSpacePartitionTest() 
            : m_ObjData(Pos_Scale_Col_Quad_Manager().Instantiate(m_ObjCount, &ConfigureShader))
        { }
        ~FixedGridSpacePartitionTest() { }
        static void ConfigureShader(InstanceRenderer& m_Renderer) {
            m_Renderer.CreateShader("assets/shaders/instancing/BasicColorScale.vert", 
                                  "assets/shaders/instancing/CircleInRectColor.frag");
            m_Renderer.InstanceShader->SetUniform<float>("u_CullRadius", 0.5f);
            m_Renderer.InstanceShader->SetUniform<float>("u_EdgeSmooth", 1.2f);
        }

        void Start() override {
            // float ip = 0;
            for (int i = 0; i < m_ObjCount; i++) {
                // p = (i+1.0f)/(m_ObjCount);
                // ip = i + 1.0f;
                m_ObjData[i].position = glm::vec2((float)rand()/RAND_MAX * (WIDTH-20) + 10, (float)rand()/RAND_MAX * (HEIGHT-20) + 10);
                // m_ObjData[i+2].scale = 2.0f * glm::vec2(4 + glm::sin(ip * m_SimData.SpawnRadiusFreq));
                m_ObjData[i].scale = glm::vec2(8.0f);
                // m_ObjData[i+2].color = glm::vec4(glm::sin(ip * m_SimData.SpawnColorFreq), 0.3, 1-glm::sin(ip * m_SimData.SpawnColorFreq), 1);
                // m_ObjData[i+2].color = glm::vec4(p, 0.3, 1-p, 1);
                // float theta = m_SimData.SpawnAngleDisplacement + m_SimData.SpawnAngle/2 * (sin(ip * m_SimData.SpawnAngleFreq) - 1);
            }
        }


        void Update(float dt) override {
        
        }

        void Render() override {
            Render::Clear(0.9, 0.9, 0.9, 1);
            Render::DrawAllInstanced();
        }

    };
}
