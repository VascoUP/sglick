#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace glick
{
	namespace mat
	{
		struct ShaderInfo
		{
			std::string shader_location;
			GLenum shader_type;
		};

		class Shader
		{
		public:
			Shader();

			GLuint get_uniform(const char* name) const;

			virtual void get_uniforms() = 0;
			virtual void initialize() = 0;

			void use_shader() const;
			void terminate();

			~Shader() = default;

		protected:
			static GLuint initialize_shader(ShaderInfo infos[], size_t count_infos);

			GLuint m_shader_id_;
		};

		class Material
		{
		public:
			Material();

			virtual void initialize(Shader* shader) = 0;
			virtual void use_material() = 0;
			virtual void terminate() = 0;

			~Material();

		protected:
			Shader* m_shader_;
		};
	}
}
