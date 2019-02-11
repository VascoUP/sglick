#pragma once

#include "gl_material.h"

class ExampleShader :
	public glick::mat::Shader
{
public:
	ExampleShader();

	void get_uniforms() override;
	void initialize() override;

	~ExampleShader();
};

class ExampleMaterial :
	public glick::mat::Material
{
public:
	ExampleMaterial();

	void initialize(glick::mat::Shader* shader) override;
	void use_material() override;
	void terminate() override;

	~ExampleMaterial();
};

