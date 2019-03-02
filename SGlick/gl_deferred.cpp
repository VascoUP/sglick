#include "stdafx.h"
#include "gl_deferred.h"

glick::mat::deferred::DeferredShader::DeferredShader()
= default;

void glick::mat::deferred::DeferredShader::get_uniforms()
{}

void glick::mat::deferred::DeferredShader::initialize()
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

glick::mat::deferred::DeferredShader::~DeferredShader()
= default;


glick::mat::deferred::DeferredMaterial::DeferredMaterial()
{}

void glick::mat::deferred::DeferredMaterial::initialize(glick::mat::Shader * shader)
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

void glick::mat::deferred::DeferredMaterial::use_material()
{
	if (m_shader_)
	{
		m_shader_->use_shader();
	}
}

void glick::mat::deferred::DeferredMaterial::terminate()
{
	if (m_shader_)
		m_shader_->terminate();
}
