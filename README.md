# LiotruEngine

LiotruEngine is a minimal C++20 OpenGL engine bootstrap using GLFW + GLAD and CMake.

## Requirements

- CMake 3.20+
- C++20 compiler (MSVC, clang, or gcc)
- Dependencies available to CMake (`glfw3`, `glad`)

## Build (Windows example)

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

## Run

```powershell
.\build\LiotruEngine.exe
```

On multi-config generators, the executable may be under `build/Debug/`.

## Project Layout

- `src/main.cpp`: application entry point
- `src/Core/Application.*`: app lifecycle and main loop
- `src/Core/Window.*`: window/context management
- `CMakeLists.txt`: build configuration

## Notes

- `build/` and generated artifacts are intentionally ignored in Git via `.gitignore`.
- The app currently clears the window each frame and is ready for rendering logic expansion.