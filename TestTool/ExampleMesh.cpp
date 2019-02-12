#include "pch.h"
#include "ExampleMesh.h"

glick::scene::Mesh * example_mesh::get()
{
	auto* mesh = new glick::scene::Mesh();

	auto info = glick::scene::MeshInfo();
	GLfloat vertices[]{
		//	x,		y,		z,		u,		v,		nx,		ny,		nz
			2.0f,	-1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			2.0f,	-1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			2.0f,	1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			2.0f,	1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
	};
	GLuint indices[]{
		0, 2, 1,
		1, 2, 3
	};

	info.vertices = vertices;	info.count_vertex_array = sizeof(vertices) / sizeof(GLfloat);
	info.indices = indices;		info.count_index_array = sizeof(indices) / sizeof(GLuint);

	mesh->initialize(info);

	return mesh;
}
