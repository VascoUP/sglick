#version 440

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexture;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

//out vec4 vColor;
out vec2 vTexture;
out vec4 vPosition;

void main() {
	vPosition = uView * uModel * vec4(aPosition, 1.0);
	gl_Position = uProjection * vPosition;

	vPosition.xy = (vPosition.xy + 1.0) * 0.5;
	vTexture = aTexture;
}