#pragma once

#include <string>
#include <list>
#include <iterator>

#include <assimp/Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "gl_material.h"
#include "gl_math.h"

namespace glick
{
	namespace scene
	{
		struct MeshInfo
		{
			GLfloat* vertices;
			GLuint* indices;
			unsigned int count_vertex_array;
			unsigned int count_index_array;
		};

		// Stores the mesh information
		//	vertices, indices
		//	sends the info to the GPU
		class Mesh
		{
		public:
			Mesh();

			void initialize(MeshInfo info);
			void render();
			void terminate();

			~Mesh();
		private:
			GLuint m_vao_;
			GLuint m_vbo_;
			GLuint m_ebo_;

			unsigned int count_indices_;
			unsigned int count_vertices_;
			unsigned int count_triangles_;
		};

		class MeshRenderer
		{
		public:
			MeshRenderer();

			void set_material(mat::Material* material);

			void initialize(Mesh* mesh, mat::Material* material = nullptr);
			void render();
			void terminate();

			~MeshRenderer();
		private:
			mat::Material* m_material_;
			Mesh* m_mesh_;
		};


		// Stores the transforms
		// Stores the children objects
		class Object
		{
		public:
			Object();

			void set_mesh(MeshRenderer* mesh);
			void add_child(Object* object);
			void remove_child(Object* object);
			void move(Object* new_parent);

			std::list<Object*>* get_children() { return &m_children_; }
			MeshRenderer* get_mesh_renderer() { return m_mesh_; }

			math::Transformation* get_transformation() { return m_transform_; }

			void initialize(math::Transformation* transformation = nullptr);
			void render();
			void update();

			~Object();
		private:
			std::list<Object*> m_children_;
			MeshRenderer* m_mesh_;
			math::Transformation* m_transform_;
		};

		// Loads an external model, 
		//	with multiple meshes 
		//	into separate nested objects
		class Model
		{
		public:
			static Object* load_model(Object* parent, const char* path);
		private:
			static auto load_mesh(glick::scene::Object* parent, aiMesh* mesh, const aiScene* scene) -> void;
			static Object* load_node(glick::scene::Object* parent, aiNode * node, const aiScene * scene);
		};

		class ScreenQuad
		{
		public:
			static glick::scene::Mesh* get();
		};

		// The scene keeps the information about 
		//	certain parameters that are specific
		//	to a particular scene
		class Scene
		{
		public:
			Scene();

			Object* get_root();

			void initialize();
			void render();
			void update();

			~Scene();
		private:
			Object* m_root_;
		};
	}
}
