#include "stdafx.h"
#include "gl_renderer.h"

glick::Renderer::Renderer() :
	m_scene_(nullptr)
{}

void glick::Renderer::initialize(Window* window)
{
	m_window_ = window;
	m_scene_ = new scene::Scene();
	m_scene_->initialize();
	m_camera_ = new behavior::Camera();
	m_camera_->initialize(m_scene_->get_root()->get_transformation(), 90.0f, m_window_->get_buffer_width(), m_window_->get_buffer_height());
}

void glick::Renderer::render()
{
	if (!m_scene_ || !m_camera_)
		return;

	glClearColor(0.5, 0.5, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_scene_->render();	
}

void glick::Renderer::terminate()
{
	delete m_scene_;
	m_scene_ = nullptr;
	delete m_camera_;
	m_camera_ = nullptr;
}

glick::Renderer::~Renderer()
= default;