#pragma once

#include "gl_material.h"

namespace glick
{
	namespace mat
	{
		namespace deferred {
			class DeferredShader :
				public glick::mat::Shader
			{
			public:
				DeferredShader();

				void get_uniforms() override;
				void initialize() override;

				~DeferredShader();
			};

			class DeferredMaterial :
				public glick::mat::Material
			{
			public:
				DeferredMaterial();

				void initialize(glick::mat::Shader* shader) override;
				void use_material() override;
				void terminate() override;

				~DeferredMaterial() = default;

				glm::vec3 m_albedo_;
			};
		}
	}
}

