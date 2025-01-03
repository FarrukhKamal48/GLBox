// #include <glbpch.h>
//
// #include "GLBox/Core/Layer.h"
//
// #include "GLBox/Events/MouseEvent.h"
// #include "GLBox/Renderer/RenderCommands.h"
// #include "GLBox/Renderer/RendererInstanced.h"
//
//
// struct Boundry
// {
//     glm::vec2 centre;
//     glm::vec2 scale;
//
//     bool contains(glm::vec2 point) {
//         return (
//             point.x <= centre.x + scale.x/2 && 
//             point.x >= centre.x - scale.x/2 && 
//             point.y <= centre.y + scale.y/2 && 
//             point.y >= centre.y - scale.y/2
//         );
//     }
//
//     bool intersects(const Boundry& box) {
//         return (box.centre.x - centre.x <= box.scale.x+scale.x || box.centre.x - centre.x >= -box.scale.x-scale.x) && 
//                 (box.centre.y - centre.y <= box.scale.y+scale.y || (box.centre.y - centre.y) >= -box.scale.y-scale.y);
//     }
// };
// struct Point {
//     int ID;
//     glm::vec2 pos;
// };
// template<int Capacity>
// struct Cell {
//     Point points[Capacity];
//     int count = 0;
// };
//
// template <int Cols, int Rows, int CellCapacity>
// class Grid {
// public:
//     Grid() 
//         : m_CellBoundry({glm::vec2(0)
//         , glm::vec2(Renderer::GetData().WindowWidth/Cols, Renderer::GetData().WindowHeight/Rows)})
//     { }
//     ~Grid() {}
//     
//     bool Insert(int pointIndex, glm::vec2 pointPos) {
//         int col = pointPos.x / m_CellBoundry.scale.x;
//         int row = pointPos.y / m_CellBoundry.scale.y;
//         if (col < 0 || col >= Cols || row < 0 || row >= Rows)
//             return false;
//         auto& cell = m_Cells[col][row];
//         
//         assert(cell.count < CellCapacity && "Cell Capacity reached");
//         
//         cell.points[cell.count] = { pointIndex, pointPos };
//         cell.count++;
//         return true;
//     }
//     
//     void QueryRange(Boundry& range, std::vector<int>& result) {
//         for (int i = 0; i < Cols; i++) {
//             for (int j = 0; j < Rows; j++) {
//                 m_CellBoundry.centre = {
//                     i*Renderer::GetData().WindowWidth/Cols, 
//                     j*Renderer::GetData().WindowHeight/Rows
//                 };
//                 auto& cell = m_Cells[i][j];
//                 for (int p = 0; p < cell.count; p++) {
//                     if (range.contains(cell.points[p].pos)) {
//                         result.push_back(cell.points[p].ID);
//                     }
//                 }
//             }
//         }
//     }
//     Cell<CellCapacity>& PosToCell(glm::vec2 pointPos) {
//         int col = pointPos.x / m_CellBoundry.scale.x;
//         int row = pointPos.y / m_CellBoundry.scale.y;
//         return m_Cells[col][row];
//     }
//
//     void Clear() {
//         for (int i = 0; i < Cols; i++) {
//             for (int j = 0; j < Rows; j++) {
//                 m_Cells[i][j].count = 0;
//             }
//         }
//     }
//
//     Cell<CellCapacity>* operator[](int i) {
//         assert(i > 0 && i < Cols && "Index out of bounds of array.");
//         return m_Cells[i];
//     }
//
// private:    
//     Boundry m_CellBoundry;
//     Cell<CellCapacity> m_Cells[Cols][Rows];
// };
//
// class FixedGridSpacePartitionTest : public Layer {
// private:
//     constexpr static int m_ObjCount = 5000;
//     constexpr static int m_Cols = 20;
//     constexpr static int m_Rows = 10;
//     Pos_Scale_Col_Quad_Manager m_Manager = Pos_Scale_Col_Quad_Manager();
//     unsigned int m_ObjData;
//     Grid<m_Cols, m_Rows, 100> m_Grid;
//     Boundry m_CheckRange;
//     glm::vec2 m_WidowSize;
//     glm::vec2 m_MousePos;
// public:
//     FixedGridSpacePartitionTest() 
//         : Layer("FixedGridSpacePartitionTest")
//         , m_ObjData(m_Manager.AllocateObject(m_ObjCount, &ConfigureShader))
//         , m_CheckRange({glm::vec2(Renderer::GetData().WindowWidth/2.0f, 
//                                   Renderer::GetData().WindowHeight/2.0f), glm::vec2(50)})
//     { }
//     ~FixedGridSpacePartitionTest() { }
//
//     void OnEvent(Event& event) override {
//         EventDispacher dispacher(event);       
//         dispacher.Dispatch<MouseMovedEvent>([this](MouseMovedEvent& event){
//             m_MousePos = { event.GetX(), event.GetY() };
//             return false;
//         });
//     }
//
//     void OnAttach() override {
//         m_WidowSize = { Renderer::GetData().WindowWidth, Renderer::GetData().WindowHeight };
//         float ip = 0;
//         for (int i = 0; i < m_ObjCount; i++) {
//             // p = (i+1.0f)/(m_ObjCount);
//             ip = i + 1.0f;
//             m_Manager[m_ObjData+i].position = glm::vec2((float)rand()/RAND_MAX * (m_WidowSize.x) + 10, 
//                                               (float)rand()/RAND_MAX * (m_WidowSize.y) + 10);
//             // m_Manager[m_ObjData+i+2].scale = 2.0f * glm::vec2(4 + glm::sin(ip * m_SimData.SpawnRadiusFreq));
//             m_Manager[m_ObjData+i].scale = glm::vec2(8.0f);
//             m_Manager[m_ObjData+i].color = glm::vec4(glm::sin(ip * 0.01f), 0.3, 1-glm::sin(ip * 0.01f), 1);
//             // m_Manager[m_ObjData+i+2].color = glm::vec4(p, 0.3, 1-p, 1);
//             // float theta = m_SimData.SpawnAngleDisplacement + m_SimData.SpawnAngle/2 * (sin(ip * m_SimData.SpawnAngleFreq) - 1);
//             m_Grid.Insert(i, m_Manager[m_ObjData+i].position);
//         }
//     }
//
//
//     void Update(float dt) override {
//         m_CheckRange.centre = glm::vec2(m_MousePos.x, m_WidowSize.y - m_MousePos.y);
//         m_CheckRange.scale = glm::vec2(192, 216);
//         m_Grid.Clear();
//         
//         // add all the points to grid
//         for (int i = 0; i < m_ObjCount; i++) {
//             m_Manager[m_ObjData+i].position += glm::vec2((float)rand()/RAND_MAX * 8 - 4, 
//                                                (float)rand()/RAND_MAX * 8 - 4);
//             if (m_Manager[m_ObjData+i].position.x > m_WidowSize.x-8)
//                 m_Manager[m_ObjData+i].position.x = m_WidowSize.x-8;
//             else if (m_Manager[m_ObjData+i].position.x < 8)
//                 m_Manager[m_ObjData+i].position.x = 8;
//             if (m_Manager[m_ObjData+i].position.y > m_WidowSize.y-8)
//                 m_Manager[m_ObjData+i].position.y = m_WidowSize.y-8;
//             else if (m_Manager[m_ObjData+i].position.y < 8)
//                 m_Manager[m_ObjData+i].position.y = 8;
//                 
//             m_Grid.Insert(i, m_Manager[m_ObjData+i].position);
//         }
//
//         // reset color of all points to black
//         for (int i = 0; i < m_ObjCount; i++) {
//             m_Manager[m_ObjData+i].color = {0, 0, 0, 0};
//         }
//         
//         // loop over each cell
//         for (int cellx = 0; cellx < m_Cols; cellx++) {
//             for (int celly = 0; celly < m_Rows; celly++) {
//                 
//                 // accumulate points from this and neighbouring cells
//                 std::vector<int> points;
//                 for (int dx = -1; dx < 2; dx++) {
//                     for (int dy = -1; dy < 2; dy++) {
//                         if (cellx+dx < 0 || cellx+dx >= m_Cols || celly+dy < 0 || celly+dy >= m_Rows)
//                             continue;
//                         auto& cell = m_Grid[cellx+dx][celly+dy];
//                         for (int p = 0; p < cell.count; p++) {
//                             points.push_back(cell.points[p].ID);
//                         }
//                     }
//                 }
//
//                 // loop over all posible collisions from points in this and neighbouring cells
//                 for (int i : points) {
//                     for (int j : points) { 
//                         if (i == j) continue;
//
//                         // skip over collision pairs that don't have overlap in both axes
//                         if (std::abs(-m_Manager[m_ObjData+i].position.x + m_Manager[m_ObjData+j].position.x) > m_Manager[m_ObjData+i].scale.x + m_Manager[m_ObjData+j].scale.x || 
//                             std::abs(-m_Manager[m_ObjData+i].position.y + m_Manager[m_ObjData+j].position.y) > m_Manager[m_ObjData+i].scale.y + m_Manager[m_ObjData+j].scale.y) continue;
//
//                         // color collided points
//                         if (Collide(m_Manager[m_ObjData+i].position, m_Manager[m_ObjData+i].scale.x, m_Manager[m_ObjData+j].position, m_Manager[m_ObjData+j].scale.x)) {
//                             m_Manager[m_ObjData+i].color = {0, 1, 0, 0};
//                             m_Manager[m_ObjData+j].color = {0, 1, 0, 0};
//                         }
//                     }
//                 }
//             }
//
//         }
//     }
//     
//     bool Collide(glm::vec2& posA, float radiusA, glm::vec2& posB, float radiusB) {
//         glm::vec2 axis = -posA + posB;
//         float sqrDist = axis.x*axis.x + axis.y*axis.y;
//
//         if (sqrDist <= (radiusA + radiusB)*(radiusA + radiusB)) {
//             float dist = glm::length(axis);
//             float overlap = radiusA + radiusB - dist;
//             axis /= dist;
//             
//             posA -= axis * overlap/2.0f;
//             posB += axis * overlap/2.0f;
//             return true;
//         }
//         return false;
//     }
//
//     void Render() override {
//     }
// private:
//     static void ConfigureShader(InstanceRenderer& m_Renderer) {
//         m_Renderer.CreateShader("assets/shaders/instancing/BasicColorScale.vert", 
//                               "assets/shaders/instancing/CircleInRectColor.frag");
//         m_Renderer.InstanceShader->SetUniform<float>("u_CullRadius", 0.5f);
//         m_Renderer.InstanceShader->SetUniform<float>("u_EdgeSmooth", 1.2f);
//     }
//
// };
