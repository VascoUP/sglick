#include "pch.h"
#include <iostream>
#include "gl_renderer.h"
#include "example_material.h"
#include "ExampleMesh.h"

int main()
{
	std::cout << "Hello World!\n";

	auto* window = new glick::Window();
	window->initialize(900, 900, 4, 4);
	auto* renderer = new glick::Renderer();
	renderer->initialize(window);

	auto* program = new glick::Program();
	program->initialize(window, renderer);

	auto* object = renderer->get_scene()->get_root();
	auto* mesh = example_mesh::get();

	auto* transformation = new glick::math::Transformation();
	transformation->translate_local(glm::vec3(-2.0f, 0.0f, 0.0f));
	renderer->get_camera()->set_transformation(transformation);

	auto* shader = new ExampleShader();
	shader->initialize();
	auto* material = new ExampleMaterial(renderer->get_camera());
	material->initialize(shader);
	auto* mesh_renderer = new glick::scene::MeshRenderer();
	mesh_renderer->initialize(material, mesh);

	object->set_mesh(mesh_renderer);

	program->run_cycle();

	delete program;
}
