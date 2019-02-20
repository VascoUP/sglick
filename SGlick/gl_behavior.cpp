#include "stdafx.h"
#include "gl_behavior.h"
#include "gl_performance.h"

glick::behavior::Input* glick::behavior::Input::m_instance_ = new glick::behavior::Input();

void glick::behavior::Input::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	const double start = glfwGetTime();
	switch(action)
	{
	case GLFW_PRESS:
		m_instance_->m_pressed_keys_.push_back(key);
		m_instance_->m_key_states_[key] = KEY_DOWN;

		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);

		break;
	case GLFW_RELEASE:
		m_instance_->m_key_states_[key] = KEY_UP;
		break;
	default: ;
	}
	const double end = glfwGetTime();
	const double delta_interruption = end - start;
	perf::Performance::set_input_poll(delta_interruption);
}

void glick::behavior::Input::set_callback(GLFWwindow* window)
{
	glfwSetKeyCallback(window, glick::behavior::Input::key_callback);
}

void glick::behavior::Input::new_frame()
{
	const double start = glfwGetTime();
	auto i = 0;
	for(auto iter = m_instance_->m_pressed_keys_.begin(); iter != m_instance_->m_pressed_keys_.end(); ++iter)
	{
		const auto key_code = *iter;
		switch(m_instance_->m_key_states_[key_code])
		{
		case KEY_DOWN:
			m_instance_->m_key_states_[key_code] = KEY_PRESSED;
			break;
		case KEY_UP:
			m_instance_->m_key_states_[key_code] = KEY_RELEASED;
			m_instance_->m_pressed_keys_.remove(i);
			break;
		default: ;
		}

		i++;
	}

	const double end = glfwGetTime();
	const double delta_interruption = end - start;
	perf::Performance::set_input_new(delta_interruption);
}

int glick::behavior::Input::check_key(int key_code)
{
	if(key_code >= 0 && key_code < SIZE_KEY_ARRAY)
	{
		return m_instance_->m_key_states_[key_code];
	}

	return KEY_UNKNOWN;
}

glick::behavior::Input::Input()
= default;

glick::behavior::Input::~Input()	
{
	m_instance_ = nullptr;
}