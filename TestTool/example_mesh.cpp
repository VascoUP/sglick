#include "pch.h"
#include "example_mesh.h"

glick::scene::Mesh * example_mesh::get()
{
	auto* mesh = new glick::scene::Mesh();

	auto info = glick::scene::MeshInfo();
	GLfloat vertices[]{
		//	x,		y,		z,		u,		v,		nx,		ny,		nz
			-1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			-1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
	};
	GLuint indices[]{
		1, 2, 0,
		3, 2, 1
	};

	info.vertices = vertices;	info.count_vertex_array = sizeof(vertices) / sizeof(GLfloat);
	info.indices = indices;		info.count_index_array = sizeof(indices) / sizeof(GLuint);

	mesh->initialize(info);

	return mesh;
}
