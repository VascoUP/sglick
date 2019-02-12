#version 440

layout(location = 0) in vec3 aPosition;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

out vec4 vColor;

void main() {
	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
	if(gl_VertexID == 0){
		vColor = vec4(0, 0, 1, 1);
	}else if(gl_VertexID == 1){
		vColor = vec4(0, 1, 0, 1);
	}else if(gl_VertexID == 2){
		vColor = vec4(1, 0, 0, 1);
	}else {
		vColor = vec4(0, 0, 1, 1);
	}
}