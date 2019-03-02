#version 440

layout(location = 0) out vec4 out_color;

layout(binding = 0) uniform sampler2D u_diffuse;

in vec2 vertex_texture;

void main() {
	vec2 text_position	= vec2(vertex_texture);
	out_color			= vec4(texture(u_diffuse, text_position).xyz, 1.0);
	//out_color = max(vec4(1),texture(u_diffuse, vertex_texture)) * vec4(text_position, 0.0, 1.0);
}