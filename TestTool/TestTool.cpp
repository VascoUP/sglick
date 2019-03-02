#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "gl_window.h"

#include "example_material.h"
#include "example_mesh.h"
#include "MyProgram.h"

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
	auto * scene = new glick::scene::Scene();
	scene->initialize();
	
	auto* camera = new glick::behavior::Camera();
	camera->initialize(scene->get_root()->get_transformation(), 90.0f, window->get_buffer_width(), window->get_buffer_height());

	auto* program = new MyProgram(window, scene, camera);

	auto* parent = scene->get_root();
	auto* object_1 = glick::scene::Model::load_model(parent, "C:/Users/vasco/Documentos/GitHub/GLRenderer/resources/model/SHIP_1/SHIP_1.obj");
	object_1->get_children()->front()->get_transformation()->translate(glm::vec3(1.5f, 0.0f, -1.7f));
	object_1->get_children()->front()->get_transformation()->scale(5.0f);

	auto* transformation = new glick::math::Transformation();
	transformation->translate_local(glm::vec3(0.0f, 0.0f, -2.0f));
	camera->set_transformation(transformation);

	auto* shader = new SimpleShader();
	shader->initialize();
	auto* material = new SimpleMaterial(camera);
	material->initialize(shader);

	const char* diffuse_texture_location[]
	{
		"C:/Users/vasco/Documentos/GitHub/GLRenderer/resources/model/SHIP_1/SHIP_1_DIFFUSE.jpg"
	};
	const char* specular_texture_location[]
	{
		"C:/Users/vasco/Documentos/GitHub/GLRenderer/resources/model/SHIP_1/SHIP_1_SPECULAR.jpg"
	};
	{
		const glick::mat::ImageInfo info_diffuse {
			true,
			GL_TEXTURE_2D,
			diffuse_texture_location,
			1
		};
		material->m_diffuse_ = glick::mat::Texture::initialize_images(info_diffuse);
		const glick::mat::ImageInfo info_specular {
			true,
			GL_TEXTURE_2D,
			specular_texture_location,
			1
		};
		material->m_specular_ = glick::mat::Texture::initialize_images(info_specular);
	}

	set_material(object_1, material);

	program->run();

	delete program;
}
