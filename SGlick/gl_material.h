#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

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

			virtual ~Shader() = default;

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

			virtual ~Material();

		protected:
			Shader* m_shader_;
		};

		struct TextureInfo
		{
			bool use_default_settings;
			GLenum texture_type;

			struct ImageData
			{
				void* data;
				int bit_depth;
				int width;
				int height;
			}* texture_data;
			size_t texture_count;
		};

		struct ImageInfo
		{
			bool use_default_settings;
			GLenum texture_type;
			const char** image_location;
			size_t image_count;
		};

		class Texture
		{
		public:
			Texture();

			virtual void initialize(TextureInfo texture_info);
			void use_texture(GLuint texture_index);
			void terminate();

			static Texture* initialize_images(const ImageInfo image_info);

			virtual ~Texture();

		private:
			GLuint m_id_;
			GLenum m_type_;
		};
	}
}
