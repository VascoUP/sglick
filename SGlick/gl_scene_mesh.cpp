#include "stdafx.h"
#include "gl_scene.h"

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
			1.0f,	-1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,	0.0f,
			-1.0f,	1.0f,	0.0f,	0.0f,	1.0f,	0.0f,	0.0f,	0.0f,
			1.0f,	1.0f,	0.0f,	1.0f,	1.0f,	0.0f,	0.0f,	0.0f,
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

void glick::scene::MeshRenderer::set_material(mat::Material* material)
{
	m_material_ = material;
}

void glick::scene::MeshRenderer::initialize(Mesh* mesh, mat::Material* material)
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

void glick::scene::Object::add_child(Object* object)
{
	m_children_.push_back(object);
}

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
	glm::mat4 local_mat = m_transform_->calculate_local_matrix(false);
	float local_scale = m_transform_->get_scale();
	math::Transformation::push_matrix(local_mat, local_scale);

	if(m_mesh_)
	{
		m_mesh_->render();
	}

	for(auto iter = m_children_.begin(); iter != m_children_.end(); ++iter)
	{
		Object* object = *iter;
		object->render();
	}

	math::Transformation::pop_matrix();
}

void glick::scene::Object::update()
{
	for (auto iter = m_children_.begin(); iter != m_children_.end(); ++iter)
	{
		Object* object = *iter;
		object->update();
	}
}

glick::scene::Object::~Object()
{
	for (auto iter = m_children_.begin(); iter != m_children_.end(); ++iter)
	{
		delete *iter;
	}
	m_children_.clear();

	delete m_mesh_;
	m_mesh_ = nullptr;
}

// Model
void glick::scene::Model::load_mesh(glick::scene::Object* parent, aiMesh * mesh, const aiScene * scene)
{
	auto* transform = new glick::math::Transformation();

	auto* object = new glick::scene::Object();
	object->initialize(transform);

	parent->add_child(object);

	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
		if (mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else {
			vertices.insert(vertices.end(), { 0.0f, 0.0f });
		}
		vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
	}

	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	auto info = glick::scene::MeshInfo();
	info.vertices = &vertices[0]; info.indices = &indices[0];
	info.count_vertex_array = vertices.size(); info.count_index_array = indices.size();

	glick::scene::Mesh* mesh_object = new glick::scene::Mesh();
	mesh_object->initialize(info);

	auto* mesh_renderer = new glick::scene::MeshRenderer();
	mesh_renderer->initialize(mesh_object);

	object->set_mesh(mesh_renderer);

	//meshList.push_back(newMesh);
	//meshToTex.push_back(mesh->mMaterialIndex);
}

glick::scene::Object* glick::scene::Model::load_node(glick::scene::Object* parent, aiNode * node, const aiScene * scene)
{
	auto* transform = new glick::math::Transformation();

	auto* object = new glick::scene::Object();
	object->initialize(transform);

	parent->add_child(object);

	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		load_mesh(object, scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		load_node(object, node->mChildren[i], scene);
	}

	return object;
}

glick::scene::Object* glick::scene::Model::load_model(glick::scene::Object* parent, const char* path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices | aiProcess_FlipWindingOrder);

	if (!scene)
	{
		printf("Model (%s) failed to load: %s", path, importer.GetErrorString());
		return nullptr;
	}

	auto* object = load_node(parent, scene->mRootNode, scene);
	//LoadMaterials(scene);

	return object;
}
