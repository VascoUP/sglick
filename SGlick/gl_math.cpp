#include "stdafx.h"
#include "gl_math.h"

std::vector<glick::math::Transformation::local*> glick::math::Transformation::model_matrix_ = 
	std::vector<local*>({ new local() });


void glick::math::Transformation::push_matrix(const glm::mat4 local_matrix, const float scale)
{
	auto *local_info = new local();
	local_info->model_matrix = (*(--model_matrix_.end()))->model_matrix * local_matrix;
	local_info->scale = (*(--model_matrix_.end()))->scale * scale;
	model_matrix_.push_back(local_info);
}

glm::mat4 glick::math::Transformation::get_model_matrix()
{
	auto* local_info = *(--model_matrix_.end());
	return glm::scale(glm::mat4(), glm::vec3(local_info->scale, local_info->scale, local_info->scale)) * local_info->model_matrix;
}

void glick::math::Transformation::pop_matrix()
{
	// Don't pop the last matrix
	if (model_matrix_.size() <= 1)
		return;

	auto* local_info = *(--model_matrix_.end());
	delete local_info;

	model_matrix_.pop_back();
}


glick::math::Transformation::Transformation() :
	m_position_(glm::vec3()),
	m_rotation_(glm::vec3()),
	m_scale_(1.0f)
{
	update_rotation();
}

void glick::math::Transformation::translate(const glm::vec3 translation)
{
	m_position_ += m_right_ * translation.x + m_up_ * translation.y + m_front_ * translation.z;
}

void glick::math::Transformation::translate_local(const glm::vec3 translation)
{
	m_position_ += translation;
}

void glick::math::Transformation::rotate(glm::vec3 rotation)
{
	m_rotation_+= rotation;
	update_rotation();
}

void glick::math::Transformation::scale(float scale)
{
	m_scale_ *= scale;
}

void glick::math::Transformation::update_rotation()
{
	glm::mat4 axis = glm::mat4(1.0f) * glm::yawPitchRoll(m_rotation_.y, m_rotation_.x, m_rotation_.z);
	m_front_ = axis[2]; m_right_ = axis[0]; m_up_ = axis[1];
}

glm::mat4 glick::math::Transformation::calculate_local_matrix(bool scale) const
{
	auto local_mat = glm::mat4();
	local_mat = glm::translate(local_mat, m_position_);
	local_mat = local_mat * glm::yawPitchRoll(m_rotation_.y, m_rotation_.x, m_rotation_.z);
	if(scale)
		local_mat = local_mat * glm::scale(glm::mat4(), glm::vec3(m_scale_, m_scale_, m_scale_));
	return local_mat;
}

glick::math::Transformation::~Transformation()
= default;
