#include "stdafx.h"
#include "gl_performance.h"
#include <iostream>

glick::perf::Performance* glick::perf::Performance::m_instance_ = new glick::perf::Performance();

void glick::perf::Performance::log_performance_metrics()
{
	char log[1000]{};
	sprintf_s(log, 
		"\
		==========================================\n\
		Input poll lag %lf\n\
		Input new lag: %lf\n\
		Update lag: %lf\n\
		Render lag: %lf\n\
		Swap buffers lag: %lf\n\
		FPS: %d\n\
		==========================================\n", 
		m_instance_->input_poll_lag_,
		m_instance_->input_new_lag_,
		m_instance_->update_lag_,
		m_instance_->render_lag_,
		m_instance_->swap_buffers_lag_,
		behavior::FPSCounter::fps());
	std::cout << log;
}

void glick::perf::Performance::set_input_poll(const double lag)
{
	m_instance_->input_poll_lag_ = lag;
}

void glick::perf::Performance::set_input_new(const double lag)
{
	m_instance_->input_new_lag_ = lag;
}

void glick::perf::Performance::set_update(const double lag)
{
	m_instance_->update_lag_ = lag;
}

void glick::perf::Performance::set_render(const double lag)
{
	m_instance_->render_lag_ = lag;
}

void glick::perf::Performance::set_swap_buffers(const double lag)
{
	m_instance_->swap_buffers_lag_ = lag;
}

void glick::perf::Performance::new_frame()
{
	m_instance_->m_time_to_second_ += behavior::Time::delta_time();
	if(m_instance_->m_time_to_second_ >= 1.0)
	{
		log_performance_metrics();

		m_instance_->m_time_to_second_ -= floor(m_instance_->m_time_to_second_);
	}
}

glick::perf::Performance::Performance() :
	input_poll_lag_(0.0f),
	input_new_lag_(0.0f),
	update_lag_(0.0f),
	render_lag_(0.0f),
	swap_buffers_lag_(0.0f),
	m_time_to_second_(0.0f)
{
}

glick::perf::Performance::~Performance()
= default;