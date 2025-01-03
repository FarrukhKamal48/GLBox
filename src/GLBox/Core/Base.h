#pragma once
#include <glbpch.h>

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) [this](auto&&... args) { return this->fn(args...); }

#define BIND_FN(fn) [this](auto&&... args) { return this->fn(args...); }

#define STRINGIFY(x) #x

