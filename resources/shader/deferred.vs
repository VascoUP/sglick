#version 440

layout(location = 0) in vec3 a_position;

out vec2 vertex_texture;

void main() {
	gl_Position = vec4(a_position, 1.0);
	vertex_texture = (a_position.xy + 1.0) / 2.0;
}