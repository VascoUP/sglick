#version 440

layout(location = 0) out vec4 out_color;

layout(binding = 0) uniform sampler2D u_color;

in vec2 vertex_texture;

void main() {
	vec2 text_position	= vec2(vertex_texture);
	out_color			= vec4(texture(u_color, text_position).rgb, 1.0);
	//float specular	= texture(u_color, text_position).a;
	//out_color			= vec4(specular, specular, specular, 1.0);
}