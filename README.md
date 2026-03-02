# LiotruEngine

Minimal C++20 OpenGL bootstrap using GLFW + GLAD + GLM with CMake.

## Prerequisites (Windows)

- Visual Studio C++ toolchain (MSVC)
- Git
- CMake (optional in PATH; local CMake from `vcpkg` is also supported)

## First-time Setup (project-local vcpkg)

From repository root:

```powershell
git clone https://github.com/microsoft/vcpkg external/vcpkg
.\external\vcpkg\bootstrap-vcpkg.bat
.\external\vcpkg\vcpkg.exe install glfw3:x64-windows glad:x64-windows glm:x64-windows
```

## Configure and Build

If `cmake` is in PATH:

```powershell
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=external/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build
```

If `cmake` is NOT in PATH, use the one downloaded by `vcpkg`:

```powershell
.\external\vcpkg\downloads\tools\cmake-3.31.10-windows\cmake-3.31.10-windows-x86_64\bin\cmake.exe -S . -B build -DCMAKE_TOOLCHAIN_FILE=external/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows
.\external\vcpkg\downloads\tools\cmake-3.31.10-windows\cmake-3.31.10-windows-x86_64\bin\cmake.exe --build build
```

## Run

```powershell
.\build\LiotruEngine.exe
```

## Notes

- Shaders are copied post-build to `build/shaders` from `src/shaders`.
- Runtime shader loading is resilient to working-directory differences.
- VS Code IntelliSense is configured to use `build/compile_commands.json`.
- If you used a previous global `vcpkg` installation, this project now uses `external/vcpkg` to avoid mismatched dependency roots.

## Troubleshooting

- Error `LNK1104: cannot open file 'kernel32.lib'`:
  run configure/build from a "Developer Command Prompt for VS" (or execute `vcvars64.bat` before CMake).
- Package not found even if installed:
  ensure configure uses `-DCMAKE_TOOLCHAIN_FILE=external/vcpkg/scripts/buildsystems/vcpkg.cmake`.
