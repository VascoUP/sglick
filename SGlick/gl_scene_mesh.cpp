#include "stdafx.h"
#include "gl_scene.h"
#include <iterator>

const unsigned int COUNT_ELEMS_PER_VERTEX = 8;

// Mesh
glick::scene::Mesh::Mesh() :
	m_vao_(0),
	m_vbo_(0),
	m_ebo_(0),
	count_indices_(0),
	count_vertices_(0),
	count_triangles_(0)
{}

void glick::scene::Mesh::initialize(MeshInfo info)
{
	count_indices_ = info.count_index_array;
	count_vertices_ = info.count_vertex_array / COUNT_ELEMS_PER_VERTEX;
	count_triangles_ = info.count_index_array / 3;

	// Bind mesh values
	glGenVertexArrays(1, &m_vao_);
	glBindVertexArray(m_vao_);

	glGenBuffers(1, &m_ebo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(info.indices[0]) * info.count_index_array, info.indices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(info.vertices[0]) * info.count_vertex_array, info.vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(info.vertices[0]) * COUNT_ELEMS_PER_VERTEX, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(info.vertices[0]) * COUNT_ELEMS_PER_VERTEX, (void*)(sizeof(info.vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(info.vertices[0]) * COUNT_ELEMS_PER_VERTEX, (void*)(sizeof(info.vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	// Unbind this mesh's values
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void glick::scene::Mesh::render()
{	
	// Make sure that there is a mesh
	if (count_triangles_ == 0)
		return;

	glBindVertexArray(m_vao_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_);
	glDrawElements(GL_TRIANGLES, count_indices_, GL_UNSIGNED_INT, nullptr);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void glick::scene::Mesh::terminate()
{
	if (m_ebo_ != 0) {
		glDeleteBuffers(1, &m_ebo_);
		m_ebo_ = 0;
	}
	if (m_vbo_ != 0) {
		glDeleteBuffers(1, &m_vbo_);
		m_vbo_ = 0;
	}
	if (m_vao_ != 0) {
		glDeleteVertexArrays(1, &m_vao_);
		m_vao_ = 0;
	}

	count_indices_ = 0;
	count_vertices_ = 0;
	count_triangles_ = 0;
}

glick::scene::Mesh::~Mesh()
{
	terminate();
}

// Scene Quad
glick::scene::Mesh * glick::scene::ScreenQuad::get()
{
	auto* mesh = new scene::Mesh();

	auto info = scene::MeshInfo();
	GLfloat vertices[]{
		//	x,		y,		z,		u,		v,		nx,		ny,		nz
			-1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			1.0f,	-1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			-1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			1.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
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

// MeshRenderer
glick::scene::MeshRenderer::MeshRenderer() :
	m_material_(nullptr),
	m_mesh_(nullptr)
{}

void glick::scene::MeshRenderer::initialize(mat::Material * material, Mesh * mesh)
{
	m_material_ = material;
	m_mesh_ = mesh;
}

void glick::scene::MeshRenderer::render()
{
	if (!m_material_ || !m_mesh_)
		return;
	m_material_->use_material();
	m_mesh_->render();
}

void glick::scene::MeshRenderer::terminate()
{
	if (m_material_)
		m_material_->terminate();
	if (m_mesh_)
		m_mesh_->terminate();
}

glick::scene::MeshRenderer::~MeshRenderer()
{
	terminate();
	m_material_ = nullptr;
	m_mesh_ = nullptr;
}


// Object
glick::scene::Object::Object() :
	m_mesh_(nullptr),
	m_transform_(nullptr)
{}

void glick::scene::Object::set_mesh(MeshRenderer * mesh)
{
	m_mesh_ = mesh;
}

void glick::scene::Object::initialize(math::Transformation* transformation)
{
	if(!transformation)
	{
		m_transform_ = new math::Transformation();
	}
	else
	{
		m_transform_ = transformation;
	}
}

void glick::scene::Object::render()
{
	math::Transformation::push_matrix(m_transform_->calculate_local_matrix(true));

	if(m_mesh_)
	{
		m_mesh_->render();
	}

	auto iter = m_children_.begin();
	while(iter != m_children_.end())
	{
		Object* object = *iter;
		object->render();

		iter = iter++;
	}

	math::Transformation::pop_matrix();
}

void glick::scene::Object::update()
{

	auto iter = m_children_.begin();
	while (*iter)
	{
		Object* object = *iter;
		object->render();

		iter = iter++;
	}
}

glick::scene::Object::~Object()
{
	auto iter = m_children_.begin();
	while (iter != m_children_.end())
	{
		delete *iter;
		iter = iter++;
	}
	m_children_.clear();

	delete m_mesh_;
	m_mesh_ = nullptr;
}