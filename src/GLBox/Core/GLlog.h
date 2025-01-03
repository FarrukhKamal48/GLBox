#pragma once
#include <glbpch.h>

#define GLCall(X) GLClearError(); X; GLLogCall(#X, __FILE__, __LINE__)

void GLClearError();
bool GLLogCall(const char* funcion, const char* file, int line);

#define BASIC_LOG(...) LogList({__VA_ARGS__})

template<typename T>
void LogList(std::initializer_list<T> list) {
    for (T x : list) {
        std::cout << x << ", ";
    }
    std::cout << '\n';
}
