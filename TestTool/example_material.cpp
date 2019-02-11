#include "pch.h"
#include "example_material.h"

ExampleShader::ExampleShader()
= default;

void ExampleShader::get_uniforms()
{}

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
}

ExampleShader::~ExampleShader()
= default;


ExampleMaterial::ExampleMaterial()
= default;

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
		m_shader_->use_shader();
	}
}

void ExampleMaterial::terminate()
{
	if (m_shader_)
		m_shader_->terminate();
}