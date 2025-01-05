# GLBox
GLBox is primarily an OpenGL wrapper for linux.

***

## Getting Started
Visual Studio 2017 or 2019 is recommended, Hazel is officially untested on other development environments whilst we focus on a Windows build.

<ins>**1. Cloning the repository:**</ins>

Start by cloning the repository with `git clone --recursive https://github.com/FarrukhKamal48/GLBox.git`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

<ins>**2. Dependencies:**</ins>
GLBox requirs CMake 3.16 of later. The folowing are also required:
1. [glew](https://github.com/nigels-com/glew).
2. [glfw](https://github.com/glfw/glfw).

<ins>**3. Build:**</ins>
1. Run the [build.sh](https://github.com/FarrukhKamal48/GLBox/blob/main/scripts/build.sh) file found in `scripts`.
2. The static library file can then be found at `build/libGLBox.a`.

***

