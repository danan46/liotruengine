#include "Shader.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

namespace {
std::filesystem::path getExecutableDirectory() {
#if defined(_WIN32)
    char buffer[MAX_PATH];
    const DWORD length = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    if (length == 0 || length == MAX_PATH) {
        return {};
    }
    return std::filesystem::path(buffer).parent_path();
#elif defined(__APPLE__)
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);
    std::string path(size, '\0');
    if (_NSGetExecutablePath(path.data(), &size) != 0) {
        return {};
    }
    return std::filesystem::path(path).parent_path();
#elif defined(__linux__)
    char buffer[4096];
    const ssize_t length = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (length <= 0) {
        return {};
    }
    buffer[length] = '\0';
    return std::filesystem::path(buffer).parent_path();
#else
    return {};
#endif
}

bool readTextFile(const std::filesystem::path& path, std::string& out) {
    std::ifstream file(path, std::ios::in);
    if (!file.is_open()) {
        return false;
    }

    std::stringstream stream;
    stream << file.rdbuf();
    out = stream.str();
    return true;
}
} // namespace

Shader::Shader(const char* vertexPath, const char* fragmentPath) : ID(0) {
    const std::filesystem::path vertexInputPath(vertexPath);
    const std::filesystem::path fragmentInputPath(fragmentPath);
    std::filesystem::path resolvedVertexPath = vertexInputPath;
    std::filesystem::path resolvedFragmentPath = fragmentInputPath;

    std::string vertexCode;
    std::string fragmentCode;
    bool vertexLoaded = readTextFile(resolvedVertexPath, vertexCode);
    bool fragmentLoaded = readTextFile(resolvedFragmentPath, fragmentCode);

    if (!vertexLoaded || !fragmentLoaded) {
        const std::filesystem::path exeDir = getExecutableDirectory();
        if (!exeDir.empty()) {
            if (!vertexLoaded && vertexInputPath.is_relative()) {
                resolvedVertexPath = exeDir / vertexInputPath;
                vertexLoaded = readTextFile(resolvedVertexPath, vertexCode);
            }
            if (!fragmentLoaded && fragmentInputPath.is_relative()) {
                resolvedFragmentPath = exeDir / fragmentInputPath;
                fragmentLoaded = readTextFile(resolvedFragmentPath, fragmentCode);
            }
        }
    }

    if (!vertexLoaded || !fragmentLoaded) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n"
                  << "Vertex path: " << resolvedVertexPath.string() << "\n"
                  << "Fragment path: " << resolvedFragmentPath.string() << std::endl;
        return;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader() {
    deleteShader();
}

void Shader::use() const {
    if (ID != 0) {
        glUseProgram(ID);
    }
}

void Shader::deleteShader() {
    if (ID != 0) {
        glDeleteProgram(ID);
        ID = 0;
    }
}

void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type) const {
    int success = 0;
    char infoLog[1024] = {};

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << std::endl;
        }
    }
}
