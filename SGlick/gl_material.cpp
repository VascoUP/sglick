#include "stdafx.h"
#include "gl_scene.h"
#include <fstream>
#include <iostream>
#include <vector>

std::string read_file(const char* file) {
	std::string code;
	std::ifstream fileStream(file, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File does not exist\n", file);
		return "";
	}

	std::string line;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		code.append(line + "\n");
	}
	fileStream.close();

	return code;
}

bool add_shader(GLuint m_program, const char* shader_code, GLenum shader_type) {
	const auto m_shader = glCreateShader(shader_type);

	const GLchar* my_code[1];
	my_code[0] = shader_code;

	GLint code_length[1];
	code_length[0] = static_cast<GLint>(strlen(shader_code));

	glShaderSource(m_shader, 1, my_code, code_length);
	glCompileShader(m_shader);

	auto result = 0;
	GLchar info_log[1024] = { 0 };

	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(m_shader, 1024, NULL, info_log);
		printf("Error compiling the %d shader: '%s'\n", shader_type, info_log);
		return false;
	}

	glAttachShader(m_program, m_shader);

	return true;
}


glick::mat::Shader::Shader() :
	m_shader_id_(0)
{
}

GLuint glick::mat::Shader::get_uniform(const char* name) const
{
	return glGetUniformLocation(m_shader_id_, name);
}

void glick::mat::Shader::use_shader() const
{
	if(!m_shader_id_)
	{
		std::cerr << "Shader was not properly compiled" << std::endl;
		exit(-1);
	}

	glValidateProgram(m_shader_id_);
	GLint result;
	glGetProgramiv(m_shader_id_, GL_VALIDATE_STATUS, &result);
	if (result != GL_TRUE)
	{
		GLint length;
		glGetProgramiv(m_shader_id_, GL_INFO_LOG_LENGTH, &length);
		char* error = static_cast<char*>(malloc(length * sizeof(char)));
		glGetProgramInfoLog(m_shader_id_, length, &length, &error[0]);
		std::cerr << "Failed to validate the shader program!" << std::endl;
		std::cerr << &error[0] << std::endl;
		glDeleteProgram(m_shader_id_);
		exit(-1);
	}
	glUseProgram(m_shader_id_);
}

GLuint glick::mat::Shader::initialize_shader(ShaderInfo infos[], size_t count_infos)
{
	const auto shader_id = glCreateProgram();
	if (!shader_id) {
		printf("Error creating shader program\n");
		return shader_id;
	}

	for(size_t i = 0; i < count_infos; i++)
	{
		auto str_code = read_file(infos[i].shader_location.c_str());
		if(str_code.empty())
		{
			printf("Error reading shader file <%s> of type <%u>\n", infos[i].shader_location.c_str(), infos[i].shader_type);
			return 0;			
		}

		const auto code = str_code.c_str();
		if(!add_shader(shader_id, code, infos[i].shader_type))
		{
			printf("Error adding shader file <%s> of type <%u>\n", infos[i].shader_location.c_str(), infos[i].shader_type);
			return 0;
		}
	}

	auto result = 0;
	GLchar info_log[1024] = { 0 };

	glLinkProgram(shader_id);
	glGetProgramiv(shader_id, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader_id, sizeof(info_log), nullptr, info_log);
		printf("Error linking program <%s>\n", info_log);
		return 0;
	}

	return shader_id;
}

void glick::mat::Shader::terminate()
{
	glDeleteProgram(m_shader_id_);
}


glick::mat::Material::Material() :
	m_shader_(nullptr)
{
}

glick::mat::Material::~Material()
{
	delete m_shader_;
	m_shader_ = nullptr;
}


//glick::mat::MeshShader::MeshShader() :
//	u_projection_(0),
//	u_view_(0),
//	u_model_(0)
//{}
//
//void glick::mat::MeshShader::get_uniforms()
//{
//	u_projection_ = get_uniform("uProjection");
//	u_view_ = get_uniform("uView");
//	u_model_ = get_uniform("uModel");
//
//	get_uniforms_();
//}
//
//glick::mat::MeshMaterial::MeshMaterial()
//= default;