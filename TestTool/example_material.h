#pragma once

#include "gl_material.h"
#include "gl_scene.h"
#include "gl_camera.h"


class SimpleShader :
	public glick::mat::Shader
{
public:
	SimpleShader();

	void get_uniforms() override;
	void initialize() override;

	~SimpleShader();

	GLuint u_projection_{}, u_view_{}, u_model_{};
	GLuint u_diffuse_{}, u_specular_{};
};

class SimpleMaterial :
	public glick::mat::Material
{
public:
	SimpleMaterial(glick::behavior::Camera* camera);

	void initialize(glick::mat::Shader* shader) override;
	void use_material() override;
	void terminate() override;

	~SimpleMaterial() = default;

	glick::scene::Object* m_object_;
	glick::behavior::Camera* m_camera_;

	glick::mat::Texture* m_diffuse_;
	glick::mat::Texture* m_specular_;
};

class DeferredShader :
	public glick::mat::Shader
{
public:
	DeferredShader();

	void get_uniforms() override;
	void initialize() override;

	~DeferredShader();
};

class DeferredMaterial :
	public glick::mat::Material
{
public:
	DeferredMaterial();

	void initialize(glick::mat::Shader* shader) override;
	void use_material() override;
	void terminate() override;

	~DeferredMaterial() = default;

	glm::vec3 m_albedo_;
};
