#include "stdafx.h"
#include "gl_renderer.h"

glick::Program::Program() :
	m_window_(nullptr),
	m_renderer_(nullptr)
{}

void glick::Program::initialize(Window * window, Renderer * renderer)
{
	m_window_ = window;
	m_renderer_ = renderer;
}

void glick::Program::run_cycle()
{
	if (!m_window_ || !m_renderer_)
		return;

	while (!glfwWindowShouldClose(m_window_->get_window()))
	{
		behavior::Input::new_frame();

		glfwPollEvents();

		{
			const double start = glfwGetTime();
			m_renderer_->render();
			const double end = glfwGetTime();
			const double delta_interruption = end - start;
			perf::Performance::set_render(delta_interruption);
		}

		glUseProgram(0);

		{
			const double start = glfwGetTime();
			glfwSwapBuffers(m_window_->get_window());
			const double end = glfwGetTime();
			const double delta_interruption = end - start;
			perf::Performance::set_swap_buffers(delta_interruption);
		}

		perf::Performance::log_performance_metrics();
	}
}

glick::Program::~Program()
{
	if (m_window_)
		m_window_->terminate();
	delete m_window_;

	if (m_renderer_)
		m_renderer_->terminate();
	delete m_renderer_;
}