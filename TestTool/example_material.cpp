#include "pch.h"
#include "example_material.h"

SimpleShader::SimpleShader()
= default;

void SimpleShader::get_uniforms()
{
	u_projection_ = get_uniform("u_projection");
	u_view_ = get_uniform("u_view");
	u_model_ = get_uniform("u_model");
	u_diffuse_ = get_uniform("u_diffuse");
	u_specular_ = get_uniform("u_specular");
}

void SimpleShader::initialize()
{
	glick::mat::ShaderInfo info_vs;
	info_vs.shader_location = "C:/Users/vasco/Documentos/GitHub/GLRenderer/resources/shader/mesh.vs";
	info_vs.shader_type = GL_VERTEX_SHADER;
	glick::mat::ShaderInfo info_fs;
	info_fs.shader_location = "C:/Users/vasco/Documentos/GitHub/GLRenderer/resources/shader/mesh.fs";
	info_fs.shader_type = GL_FRAGMENT_SHADER;

	glick::mat::ShaderInfo infos[]{
		info_vs, info_fs
	};

	m_shader_id_ = initialize_shader(infos, 2);

	get_uniforms();
}

SimpleShader::~SimpleShader()
= default;


SimpleMaterial::SimpleMaterial(glick::behavior::Camera* camera) :
	m_camera_(camera)
{}

void SimpleMaterial::initialize(glick::mat::Shader * shader)
{
	if(auto* e_shader = dynamic_cast<SimpleShader*>(shader))
	{
		m_shader_ = e_shader;
	} else
	{
		m_shader_ = nullptr;
	}
}

void SimpleMaterial::use_material()
{
	if(!m_shader_)
		return;

	auto* e_shader = static_cast<SimpleShader*>(m_shader_);
	auto view_projection = m_camera_->get_camera_view_projection();
	auto model = glick::math::Transformation::get_model_matrix();

	m_shader_->use_shader();
	glUniformMatrix4fv(e_shader->u_projection_, 1, GL_FALSE, glm::value_ptr(view_projection.m_projection_));
	glUniformMatrix4fv(e_shader->u_view_, 1, GL_FALSE, glm::value_ptr(view_projection.m_view_));
	glUniformMatrix4fv(e_shader->u_model_, 1, GL_FALSE, glm::value_ptr(model));

	m_diffuse_->use_texture(0);
	m_specular_->use_texture(1);
}

void SimpleMaterial::terminate()
{
	if (m_shader_)
		m_shader_->terminate();
}


DeferredShader::DeferredShader()
= default;

void DeferredShader::get_uniforms()
{}

void DeferredShader::initialize()
{
	glick::mat::ShaderInfo info_vs;
	info_vs.shader_location = "C:/Users/vasco/Documentos/GitHub/GLRenderer/resources/shader/deferred.vs";
	info_vs.shader_type = GL_VERTEX_SHADER;
	glick::mat::ShaderInfo info_fs;
	info_fs.shader_location = "C:/Users/vasco/Documentos/GitHub/GLRenderer/resources/shader/deferred.fs";
	info_fs.shader_type = GL_FRAGMENT_SHADER;

	glick::mat::ShaderInfo infos[]{
		info_vs, info_fs
	};

	m_shader_id_ = initialize_shader(infos, 2);

	get_uniforms();
}

DeferredShader::~DeferredShader()
= default;


DeferredMaterial::DeferredMaterial()
{}

void DeferredMaterial::initialize(glick::mat::Shader * shader)
{
	if (auto* e_shader = dynamic_cast<DeferredShader*>(shader))
	{
		m_shader_ = e_shader;
	}
	else
	{
		m_shader_ = nullptr;
	}
}

void DeferredMaterial::use_material()
{
	if (m_shader_)
	{
		m_shader_->use_shader();
	}
}

void DeferredMaterial::terminate()
{
	if (m_shader_)
		m_shader_->terminate();
}