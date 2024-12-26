#pragma once

namespace Batching {

class Mesh {
public:
    virtual const float* GetVerticies() const = 0;
    virtual const int GetVertexCount() const = 0;
    virtual const int GetVertexFloatCount() const = 0;
    virtual const int GetSizeOfVerticies() const = 0;
};

}
