#pragma once

#include <glm/glm.hpp>
#include "gl_math.h"

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

		public:
			Camera();

			CameraViewProjection get_camera_view_projection()
			{
				m_transform_->rotate(glm::vec3(0.0f, 0.01f, 0.0f));
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
