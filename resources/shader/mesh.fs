#version 440

in vec4 vColor;

layout(location = 0) out vec4 oColor;

void main() {
	oColor = vColor;
}