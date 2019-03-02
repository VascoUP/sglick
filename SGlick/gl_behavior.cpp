#include "stdafx.h"
#include "gl_behavior.h"
#include "gl_performance.h"

glick::behavior::Input* glick::behavior::Input::m_instance_ = new Input();
glick::behavior::Time* glick::behavior::Time::m_instance_ = new Time();
glick::behavior::FPSCounter* glick::behavior::FPSCounter::m_instance_ = new FPSCounter();

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

glick::behavior::Time::Time() :
	m_delta_time_(0),
	m_time_(0.0)
{}

void glick::behavior::Time::new_frame()
{
	double time = glfwGetTime();
	m_instance_->m_delta_time_ = time - m_instance_->m_time_;
	m_instance_->m_time_ = time;
}

glick::behavior::Time::~Time()
= default;

glick::behavior::FPSCounter::FPSCounter() :
	m_fps_(0),
	m_fps_counter_(0),
	m_time_to_second_(0.0)
{}

void glick::behavior::FPSCounter::new_frame()
{
	m_instance_->m_time_to_second_ += Time::delta_time();
	++m_instance_->m_fps_counter_;
	while(m_instance_->m_time_to_second_ >= 1.0)
	{
		m_instance_->m_time_to_second_ -= 1.0;
		m_instance_->m_fps_ = m_instance_->m_fps_counter_;
		m_instance_->m_fps_counter_ = 0;
	}
}

glick::behavior::FPSCounter::~FPSCounter()
= default;
