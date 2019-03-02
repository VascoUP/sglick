#version 440

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texture;
layout(location = 2) in vec3 a_normal;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

out vec2 vertex_texture;
out vec3 vertex_position;
out vec3 vertex_normal;

void main() {
	vec4 world_position = u_model * vec4(a_position, 1.0);
	vertex_position = world_position.xyz;
	gl_Position = u_projection * u_view * world_position;

	vertex_texture = a_texture;

	mat4 nWorld = u_model;
	nWorld[3][0] = 0;
	nWorld[3][1] = 0;
	nWorld[3][2] = 0;

	vertex_normal = (nWorld * vec4(a_normal, 1.0)).xyz;
}