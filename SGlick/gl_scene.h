#pragma once

#include <string>
#include <list>

#include "gl_material.h"

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

		class ScreenQuad
		{
		public:
			static Mesh* get();
		};

		class MeshRenderer
		{
		public:
			MeshRenderer();

			void initialize(mat::Material* material, Mesh* mesh);
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

			void initialize();
			void render();
			void update();

			~Object();
		private:
			std::list<Object*> m_children_;
			MeshRenderer* m_mesh_;
		};

		// Loads an external model, 
		//	with multiple meshes 
		//	into separate nested objects
		class Model
		{
		public:
			static Object* load_model(std::string* path);
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
