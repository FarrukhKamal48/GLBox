#include "GLBox/Core/LayerStack.h"
#include <algorithm>

LayerStack::LayerStack() { }

LayerStack::~LayerStack() {
    for (Layer* layer : m_Layers) {
        layer->OnDetach();
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* layer) {
    m_Layers.emplace(m_Layers.begin() + m_PushIndex, layer);
    m_PushIndex++;
}
void LayerStack::PopLayer(Layer* layer) {
    auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_PushIndex, layer);
    if (it != m_Layers.begin() + m_PushIndex) {
        m_Layers.erase(it);
        layer->OnDetach();
        m_PushIndex--;
    }
}

void LayerStack::PushOverlay(Layer* layer) {
    m_Layers.emplace_back(layer);
}
void LayerStack::PopOverlay(Layer* layer) {
    auto it = std::find(m_Layers.begin() + m_PushIndex, m_Layers.end(), layer);
    if (it != m_Layers.end()) {
        m_Layers.erase(it);
        layer->OnDetach();
    }
}
