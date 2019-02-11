#include "stdafx.h"
#include "gl_renderer.h"

glick::Renderer::Renderer() :
	m_scene_(nullptr)
{}

void glick::Renderer::initialize()
{
	m_scene_ = new scene::Scene();
	m_scene_->initialize();
}

void glick::Renderer::render()
{
	if (!m_scene_)
		return;

	glClearColor(0.5, 0.5, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_scene_->render();	
}

void glick::Renderer::terminate()
{
	delete m_scene_;
	m_scene_ = nullptr;
}

glick::Renderer::~Renderer()
= default;