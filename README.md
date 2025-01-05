# GLBox
GLBox is primarily a 2D OpenGL Rendering Engine for linux. It provides wrapper classes for basic OpenGL objects (Vertex Arrays, Vertex Buffers, Index Buffers etc) while also implementing an Instance Renderer that clasifies all rendering objects and renders them automatically.

***

## Dependencies

GLBox requires CMake 3.16 of later. The folowing are also required:

1. [glew](https://github.com/nigels-com/glew).
2. [glfw](https://github.com/glfw/glfw).

## Getting Started

<ins>**1. Cloning the repository:**</ins>

Start by cloning the repository with: 
```
git clone --recursive https://github.com/FarrukhKamal48/GLBox.git
```

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

<ins>**2. Build:**</ins>

GLBox compiles into a static library file.

1. Run the [build.sh](https://github.com/FarrukhKamal48/GLBox/blob/main/scripts/build.sh) file found in `scripts`.
2. The static library file can then be found at `build/libGLBox.a`.

***

## Planed Features
- Windows Support
- Text Rendering using SDFs (Sighned Distance Fields)

