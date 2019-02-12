#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\euler_angles.hpp>

namespace glick
{
	namespace math
	{
		class Transformation
		{
		public:
			Transformation();

			static void push_matrix(glm::mat4 local_matrix);
			static glm::mat4 get_model_matrix();
			static void pop_matrix();

			glm::vec3 get_position() const { return m_position_; }
			glm::vec3 get_front() const { return m_front_; }

			void translate(glm::vec3 translation);
			void translate_local(glm::vec3 translation);
			void rotate(glm::vec3 rotation);
			void scale(float scale);

			glm::mat4 calculate_local_matrix(bool scale) const;

			~Transformation();
		private:
			void update_rotation();

			static float hello;
			static std::vector<glm::mat4> model_matrix_;

			glm::vec3 m_front_;
			glm::vec3 m_up_;
			glm::vec3 m_right_;

			glm::vec3 m_position_;
			glm::vec3 m_rotation_;
			float m_scale_;
		};
	}
}


