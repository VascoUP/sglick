#version 440

layout(location = 0) in vec3 aPosition;

out vec4 vColor;

void main() {
	gl_Position = vec4(aPosition, 1.0);
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