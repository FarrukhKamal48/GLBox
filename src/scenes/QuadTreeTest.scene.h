#include "Scene.h"
#include "../layer/Instancing/RendererInstanced.h"
#include "../layer/Input.h"
#include <cstdlib>
#include <vector>

struct Boundry
{
    glm::vec2 centre;
    glm::vec2 scale;

    bool contains(glm::vec2 point) {
        return (
            point.x <= centre.x + scale.x/2 && 
            point.x >= centre.x - scale.x/2 && 
            point.y <= centre.y + scale.y/2 && 
            point.y >= centre.y - scale.y/2
        );
    }

    bool intersects(const Boundry& box) {
        return (box.centre.x - centre.x) <= box.scale.x+scale.x || (box.centre.x - centre.x) >= -box.scale.x-scale.x && 
                (box.centre.y - centre.y) <= box.scale.y+scale.y || (box.centre.y - centre.y) >= -box.scale.y-scale.y;
    }
};

template<int Capacity>
class QuadTree {
public:
    bool isDivided;
public:
    QuadTree(glm::vec2 centre, glm::vec2 scale) : 
        isDivided(false), m_Boundry({centre, scale}), m_ObjectCount(0) {
        for (int i=0; i < 4; i++)
            m_Cells[i] = nullptr;
    }
    ~QuadTree() {
        // Delete(this);
    }

    bool Insert(glm::vec2* pos, int objID) {
        if (!m_Boundry.contains(*pos))
            return false;
        if (m_ObjectCount < Capacity) {
            m_ObjectCount++;
            m_Objects[m_ObjectCount-1].ID = objID;
            m_Objects[m_ObjectCount-1].pos = pos;
            return true;
        }
        if (!isDivided) {
            SubDivide();
        }
        if (m_Cells[0]->Insert(pos, objID))
            return true;
        if (m_Cells[1]->Insert(pos, objID))
            return true;
        if (m_Cells[2]->Insert(pos, objID))
            return true;
        if (m_Cells[3]->Insert(pos, objID))
            return true;
        return false;
    }

    void Query(Boundry& range, std::vector<int>& result) {
        if (!m_Boundry.intersects(range))
            return;

        for (int i = 0; i < m_ObjectCount; i++) {
            if (range.contains(*m_Objects[i].pos)) {
                result.push_back(m_Objects[i].ID);
            }
        }

        if (isDivided) {
            m_Cells[0]->Query(range, result);
            m_Cells[1]->Query(range, result);
            m_Cells[2]->Query(range, result);
            m_Cells[3]->Query(range, result);
        }
    }

private:
    Boundry m_Boundry;
    unsigned int m_ObjectCount;
    struct point {
        int ID;
        glm::vec2* pos;
    };
    union {
        point m_Objects[Capacity];
        QuadTree<Capacity>* m_Cells[4];
    };

    void SubDivide() {
        glm::vec2& C = m_Boundry.centre;
        glm::vec2& S = m_Boundry.scale;
        m_Cells[0] = new QuadTree<Capacity>(glm::vec2(C + S/4.0f), S/2.0f);
        m_Cells[1] = new QuadTree<Capacity>(glm::vec2(C.x - S.x/4.0f, C.y + S.y/4.0f), S/2.0f);
        m_Cells[2] = new QuadTree<Capacity>(glm::vec2(C.x + S.x/4.0f, C.y - S.y/4.0f), S/2.0f);
        m_Cells[3] = new QuadTree<Capacity>(glm::vec2(C - S/4.0f), S/2.0f);
        isDivided = true;
    }

    void Delete(QuadTree<Capacity>* tree) {
        if (!tree->isDivided) // if one child cell is null, all child cells are null 
            return;
        for (int i=0; i < 4; i++) {
            Delete(m_Cells[i]); // delete all children's child cells
            delete m_Cells[i];  // delete chilren
        }
    }
};

namespace Scene {
class QuadTreeTest : public Scene {
private:
    constexpr static int m_ObjCount = 1000;
    Pos_Scale_Col* m_ObjData = new Pos_Scale_Col[m_ObjCount];
    RendererInstanced<QuadData, Pos_Scale_Col, m_ObjCount> m_Renderer;
    QuadTree<4> m_QTree;
    Boundry m_CheckRange;
public:
    QuadTreeTest() 
        : m_Renderer(m_ObjData), m_QTree({WIDTH/2, HEIGHT/2}, {WIDTH, HEIGHT}), m_CheckRange({glm::vec2(WIDTH/2, HEIGHT/2), glm::vec2(50)})
    {
        m_Renderer.ShaderInit("assets/shaders/instancing/BasicColorScale.vert", 
                              "assets/shaders/instancing/CircleInRectColor.frag");
        m_Renderer.InstanceShader->SetUniform<float>("u_CullRadius", 0.5f);
        m_Renderer.InstanceShader->SetUniform<float>("u_EdgeSmooth", 1.2f);
    }
    ~QuadTreeTest() {
        delete [] m_ObjData;
    }

    void Start() override {
        float ip = 0;
        for (int i = 0; i < m_ObjCount; i++) {
            // p = (i+1.0f)/(m_ObjCount);
            ip = i + 1.0f;
            m_ObjData[i].position = glm::vec2((float)rand()/RAND_MAX * (WIDTH-20) + 10, (float)rand()/RAND_MAX * (HEIGHT-20) + 10);
            // m_ObjData[i+2].scale = 2.0f * glm::vec2(4 + glm::sin(ip * m_SimData.SpawnRadiusFreq));
            m_ObjData[i].scale = glm::vec2(8.0f);
            // m_ObjData[i+2].color = glm::vec4(glm::sin(ip * m_SimData.SpawnColorFreq), 0.3, 1-glm::sin(ip * m_SimData.SpawnColorFreq), 1);
            // m_ObjData[i+2].color = glm::vec4(p, 0.3, 1-p, 1);
            // float theta = m_SimData.SpawnAngleDisplacement + m_SimData.SpawnAngle/2 * (sin(ip * m_SimData.SpawnAngleFreq) - 1);
            m_QTree.Insert(&m_ObjData[i].position, i);
        }
    }


    void Update(float dt) override {
        m_CheckRange.centre = glm::vec2(Input::GetMousePos().x, HEIGHT - Input::GetMousePos().y);
        m_CheckRange.scale = glm::vec2(500);
        
        std::vector<int> points;
        m_QTree.Query(m_CheckRange, points);

        for (int i = 0; i < m_ObjCount; i++) {
            m_ObjData[i].color = {0, 0, 0, 0};
        }
        for (int p = 0; p < points.size(); p++) {
            m_ObjData[points[p]].color = {0, 1, 0, 0};
        }


    }

    void Render() override {
        Render::Clear(0.9, 0.9, 0.9, 1);
        m_Renderer.Draw();
    }

};
}
