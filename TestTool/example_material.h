#pragma once

#include "gl_material.h"
#include "gl_scene.h"
#include "gl_camera.h"


class ExampleShader :
	public glick::mat::Shader
{
public:
	ExampleShader();

	void get_uniforms() override;
	void initialize() override;

	~ExampleShader();

	GLuint u_projection_, u_view_, u_model_;
};

class ExampleMaterial :
	public glick::mat::Material
{
public:
	ExampleMaterial(glick::behavior::Camera* camera);

	void initialize(glick::mat::Shader* shader) override;
	void use_material() override;
	void terminate() override;

	~ExampleMaterial() = default;

	glick::scene::Object* m_object_;
	glick::behavior::Camera* m_camera_;
};

