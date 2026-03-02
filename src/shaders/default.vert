#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 color;

// Uniform: una variabile che rimane costante per tutti i vertici di un oggetto
uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(aPos, 1.0);
    color = aCol;
}