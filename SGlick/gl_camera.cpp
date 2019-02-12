#include "stdafx.h"
#include "gl_camera.h"

glick::behavior::Camera::Camera() :
	m_view_projection_(CameraViewProjection())
{}

void glick::behavior::Camera::set_projection()
{
	m_view_projection_.m_projection_ = 
		glm::perspective(m_view_angle_, 
						GLfloat(m_width_) / GLfloat(m_height_), 
						0.1f, 
						100.0f);
}

void glick::behavior::Camera::set_view()
{
	m_view_projection_.m_view_ = 
		glm::lookAt(m_transform_->get_position(), 
					m_transform_->get_position() + m_transform_->get_front(), 
					glm::vec3(0.0f, 1.0f, 0.0f));
}


void glick::behavior::Camera::set_view_angle(const float angle)
{
	m_view_angle_ = glm::radians(angle);
	set_projection();
}

void glick::behavior::Camera::set_size(unsigned int width, unsigned int height)
{
	m_width_ = width; m_height_ = height;
	set_projection();
}

void glick::behavior::Camera::set_transformation(math::Transformation * transformation)
{
	m_transform_ = transformation;
	set_view();
}

void glick::behavior::Camera::initialize(math::Transformation* transformation, float angle, unsigned int width, unsigned int height)
{
	m_view_angle_ = glm::radians(angle);
	m_width_ = width; m_height_ = height;
	m_transform_ = transformation;

	set_projection();
	set_view();
}
