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
	m_shader_id_ = 0;
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


glick::mat::Texture::Texture() :
	m_id_(0),
	m_type_(0)
{}

void glick::mat::Texture::initialize(TextureInfo texture_info)
{
	m_type_ = texture_info.texture_type;

	glGenTextures(1, &m_id_);
	glBindTexture(m_type_, m_id_);

	for(size_t i = 0; i < texture_info.texture_count; i++)
	{
		GLuint target = m_type_;
		if (m_type_ == GL_TEXTURE_CUBE_MAP) {
			target = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		}

		GLenum format = 
			texture_info.texture_data[i].bit_depth == 3 ? 
				GL_RGB : GL_RGBA;

		glTexImage2D(target, 0, format,
			texture_info.texture_data[i].width, 
			texture_info.texture_data[i].height,
			0, format,
			GL_UNSIGNED_BYTE, 
			texture_info.texture_data[i].data);
	}

	if (texture_info.use_default_settings) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_type_, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_type_, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void glick::mat::Texture::use_texture(GLuint texture_index)
{
	glActiveTexture(GL_TEXTURE0 + texture_index);
	glBindTexture(m_type_, m_id_);
}

void glick::mat::Texture::terminate()
{
	glDeleteTextures(1, &m_id_);
	m_id_ = 0;
	m_type_ = 0;
}

glick::mat::Texture* glick::mat::Texture::initialize_images(const ImageInfo image_info)
{
	auto* texture = new Texture();

	auto info = TextureInfo();
	info.use_default_settings = image_info.use_default_settings;
	info.texture_type = image_info.texture_type;
	info.texture_count = image_info.image_count;
	info.texture_data = new TextureInfo::ImageData[image_info.image_count];
	
	for(size_t i = 0; i < info.texture_count; i++)
	{
		info.texture_data[i].data =
			stbi_load(image_info.image_location[i], 
				&info.texture_data[i].width,
				&info.texture_data[i].height,
				&info.texture_data[i].bit_depth,
				0);
		if (!info.texture_data[i].data) {
			printf("Failed to find: %s\n", image_info.image_location[i]);
			return nullptr;
		}
	}

	texture->initialize(info);

	for (size_t i = 0; i < info.texture_count; i++)
	{
		stbi_image_free(info.texture_data[i].data);
	}
	delete info.texture_data;

	return texture;
}

glick::mat::Texture::~Texture()
= default;