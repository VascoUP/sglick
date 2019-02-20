#include "pch.h"
#include "example_material.h"

ExampleShader::ExampleShader()
= default;

void ExampleShader::get_uniforms()
{
	u_projection_ = get_uniform("uProjection");
	u_view_ = get_uniform("uView");
	u_model_ = get_uniform("uModel");
	u_albedo_color_ = get_uniform("uAlbedoColor");
	u_albedo_ = get_uniform("uAlbedo");
}

void ExampleShader::initialize()
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

ExampleShader::~ExampleShader()
= default;


ExampleMaterial::ExampleMaterial(glick::behavior::Camera* camera) :
	m_camera_(camera)
{}

void ExampleMaterial::initialize(glick::mat::Shader * shader)
{
	if(auto* e_shader = dynamic_cast<ExampleShader*>(shader))
	{
		m_shader_ = e_shader;
	} else
	{
		m_shader_ = nullptr;
	}
}

void ExampleMaterial::use_material()
{
	if(m_shader_)
	{
		auto* e_shader = static_cast<ExampleShader*>(m_shader_);
		auto view_projection = m_camera_->get_camera_view_projection();
		auto model = glick::math::Transformation::get_model_matrix();

		m_shader_->use_shader();
		glUniformMatrix4fv(e_shader->u_projection_, 1, GL_FALSE, glm::value_ptr(view_projection.m_projection_));
		glUniformMatrix4fv(e_shader->u_view_, 1, GL_FALSE, glm::value_ptr(view_projection.m_view_));
		glUniformMatrix4fv(e_shader->u_model_, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3f(e_shader->u_albedo_color_, 1.0f, 1.0f, 1.0f);

		m_albedo_->use_texture(0);
	}
}

void ExampleMaterial::terminate()
{
	if (m_shader_)
		m_shader_->terminate();
}