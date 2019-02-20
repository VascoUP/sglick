#version 440

//in vec4 vColor;
in vec2 vTexture;
in vec4 vPosition;

layout(location = 0) out vec4 oColor;

uniform sampler2D uAlbedo;
uniform vec3 uAlbedoColor;

void main() {
	//vec4 position = vPosition;
	//position.z = position.z / vPosition.w;
	//position.w = 1.0;
	//oColor = position;

	//oColor = vec4(uAlbedoColor, 1.0);
	oColor = texture(uAlbedo, vTexture) * vec4(uAlbedoColor,1.0);
	//oColor = vColor;
}