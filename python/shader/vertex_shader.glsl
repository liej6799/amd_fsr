#version 330

in vec3 position;
in vec2 vertex_uv;
uniform vec2 iResolution;
uniform vec2 WindowSize;


out vec2 uv;

void main() {
    gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
    uv = vertex_uv;
}