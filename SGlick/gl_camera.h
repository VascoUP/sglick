#pragma once

#include <glm/glm.hpp>

#include "gl_math.h"
#include "gl_behavior.h"

namespace glick
{
	namespace behavior
	{
		struct CameraViewProjection
		{
			glm::mat4 m_projection_;
			glm::mat4 m_view_;
		};

		class Camera
		{
		private:
			void set_projection();
			void set_view();

			static float rotation_;
			static float translation_;

		public:
			Camera();

			CameraViewProjection get_camera_view_projection()
			{
				if(Input::check_key(GLFW_KEY_SPACE) == KEY_PRESSED)
				{
					m_transform_->rotate(glm::vec3(0.0f, rotation_, 0.0f));
					m_transform_->translate(glm::vec3(translation_, 0.0f, 0.0f));
				}
				set_view();
				return m_view_projection_;
			}

			void set_view_angle(const float angle);
			void set_size(unsigned int width, unsigned int height);
			void set_transformation(math::Transformation* transformation);

			void initialize(math::Transformation* transformation, float angle, unsigned int width, unsigned int height);

		private:

			CameraViewProjection m_view_projection_;
			math::Transformation* m_transform_;
			float m_view_angle_;
			unsigned int m_width_;
			unsigned int m_height_;
		};
	}
}
