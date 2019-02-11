#include "stdafx.h"
#include "gl_scene.h"

glick::scene::Scene::Scene() :
	m_root_(nullptr)
{}

glick::scene::Object * glick::scene::Scene::get_root()
{
	return m_root_;
}

void glick::scene::Scene::initialize()
{
	m_root_ = new Object();
	m_root_->initialize();
}

void glick::scene::Scene::render()
{
	if(m_root_)
	{
		m_root_->render();
	}
}

void glick::scene::Scene::update()
{
	if(m_root_)
	{
		m_root_->update();
	}
}

glick::scene::Scene::~Scene()
{
	delete m_root_;
}