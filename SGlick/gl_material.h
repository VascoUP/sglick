#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include <string>

namespace glick {
	class Window;
}

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

			struct Data
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

		struct FramebufferInfo
		{
			bool use_default_settings;
			GLenum texture_type;

			struct Data
			{
				int bit_depth;
				unsigned int format_range;
				int width;
				int height;
			};
	
			size_t texture_count;
			Data* texture_data;

			bool depth_attachment;
			Data depth_data;
		};

		class Framebuffer
		{
		public:
			Framebuffer();

			GLuint get_fbo() const { return m_fbo_; }
			GLuint* color_attachments() const { return m_color_attachments_; };
			GLuint depth_attachment() const { return m_depth_attachment_; };
			size_t size_color_attachment() const { return m_size_color_attachments_; };

			bool initialize(FramebufferInfo info);
			void use_framebuffer() const;
			void terminate();

			~Framebuffer();

		protected:
			GLuint	m_fbo_;
			GLuint*	m_color_attachments_;
			GLuint	m_depth_attachment_;
			size_t	m_size_color_attachments_;
			GLuint*	m_draw_buffers_;
		};
	}
}
