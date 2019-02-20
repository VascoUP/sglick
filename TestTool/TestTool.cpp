#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "gl_renderer.h"
#include "example_material.h"
#include "example_mesh.h"

void set_material(glick::scene::Object* object, glick::mat::Material* material)
{
	auto* children = object->get_children();
	for(auto iter = children->begin(); iter != children->end(); ++iter)
	{
		glick::scene::Object* child = *iter;
		set_material(child, material);
	}

	if (auto* mesh_renderer = object->get_mesh_renderer())
	{
		mesh_renderer->set_material(material);
	}
}

int main()
{
	std::cout << "Hello World!\n";

	auto* window = new glick::Window();
	window->initialize(900, 900, 4, 4);
	auto* renderer = new glick::Renderer();
	renderer->initialize(window);

	auto* program = new glick::Program();
	program->initialize(window, renderer);

	auto* parent = renderer->get_scene()->get_root();
	auto* object_1 = glick::scene::Model::load_model(parent, "C:/Users/vasco/Documentos/GitHub/GLRenderer/resources/model/SHIP_1/SHIP_1.obj");
	object_1->get_children()->front()->get_transformation()->translate(glm::vec3(1.5f, 0.0f, -1.7f));
	object_1->get_children()->front()->get_transformation()->scale(5.0f);
	auto* object_2 = glick::scene::Model::load_model(object_1, "C:/Users/vasco/Documentos/GitHub/GLRenderer/resources/model/SPHERE_1/SPHERE_1.obj");
	object_2->get_transformation()->scale(0.1f);

	auto* transformation = new glick::math::Transformation();
	transformation->translate_local(glm::vec3(0.0f, 0.0f, -2.0f));
	renderer->get_camera()->set_transformation(transformation);

	auto* shader = new ExampleShader();
	shader->initialize();
	auto* material = new ExampleMaterial(renderer->get_camera());
	material->initialize(shader);

	const char* locations[]{ "C:/Users/vasco/Documentos/GitHub/GLRenderer/resources/model/SHIP_1/SHIP_1_DIFFUSE.jpg" };
	glick::mat::ImageInfo info;
	info.image_location = locations;
	info.texture_type = GL_TEXTURE_2D;
	info.use_default_settings = true;
	info.image_count = 1;
	material->m_albedo_ = glick::mat::Texture::initialize_images(info);

	set_material(object_1, material);
	set_material(object_2, material);

	program->run_cycle();

	delete program;
}
