#version 440

layout(location = 0) out vec4 out_diffused;
layout(location = 1) out vec4 out_position;
layout(location = 2) out vec4 out_normal;

in vec2 vertex_texture;
in vec3 vertex_position;
in vec3 vertex_normal;

layout(binding = 0) uniform sampler2D u_diffuse;
layout(binding = 1) uniform sampler2D u_specular;

void main() {
	out_diffused	= texture(u_diffuse, vertex_texture);
	float specular	= texture(u_specular, vertex_texture).r;
	out_diffused.a	= specular;
	out_position	= vec4(vertex_position, 1.0);
	out_normal		= vec4(vertex_normal, 1.0);
}