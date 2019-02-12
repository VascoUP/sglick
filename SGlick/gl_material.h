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

		//class MeshShader :
		//	public Shader
		//{
		//public:
		//	MeshShader();

		//	void get_uniforms() override;
		//	void initialize() override;

		//	void use_shader() const;
		//	void terminate();

		//	virtual ~MeshShader() = default;

		//protected:
		//	virtual void get_uniforms_() = 0;
		//	virtual void initialize_() = 0;

		//private:
		//	GLuint u_projection_;
		//	GLuint u_view_;
		//	GLuint u_model_;
		//};

		//class MeshMaterial :
		//	public Material
		//{
		//public:
		//	MeshMaterial();

		//	void initialize(Shader* shader) override;
		//	void use_material() override;
		//	void terminate() override;

		//	virtual ~MeshMaterial();

		//protected:
		//	virtual void initialize_() = 0;
		//	virtual void use_material_() = 0;
		//	virtual void terminate_() = 0;
		//};
	}
}
