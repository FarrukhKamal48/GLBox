#pragma once

#include <glbpch.h>
#include <stb/stb_image.h>

class Texture {
private:
    uint32_t m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
    mutable int m_Slot;
public:
    Texture(const std::string filePath);
    ~Texture();

    void Bind(uint32_t slot = 0) const;
    void UnBind() const;
    
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetSlot() const { return m_Slot; }
};
