#include "pch.h"
#include <iostream>
#include "gl_renderer.h"
#include "example_material.h"

int main()
{
	std::cout << "Hello World!\n";

	auto* window = new glick::Window();
	window->initialize(900, 900, 4, 4);
	auto* renderer = new glick::Renderer();
	renderer->initialize();

	auto* program = new glick::Program();
	program->initialize(window, renderer);

	auto* object = renderer->get_scene()->get_root();
	auto* mesh = glick::scene::ScreenQuad::get();

	auto* shader = new ExampleShader();
	shader->initialize();
	auto* material = new ExampleMaterial();
	material->initialize(shader);
	auto* mesh_renderer = new glick::scene::MeshRenderer();
	mesh_renderer->initialize(material, mesh);

	object->set_mesh(mesh_renderer);

	program->run_cycle();

	delete program;
}
