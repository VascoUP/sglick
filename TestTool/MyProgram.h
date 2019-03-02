#pragma once

#include "gl_behavior.h"
#include "gl_performance.h"
#include "gl_camera.h"
#include "gl_material.h"
#include "gl_scene.h"
#include "gl_deferred.h"
#include "gl_window.h"

class MyProgram
{
public:
	MyProgram(glick::Window* window, glick::scene::Scene* scene, glick::behavior::Camera* camera);

	void run();
	
	~MyProgram();

private:
	void update();
	void render();

	glick::Window* m_window_;
	
	glick::scene::Scene* m_scene_;
	glick::behavior::Camera* m_camera_;

	glick::mat::Framebuffer* m_framebuffer_;
	glick::scene::Mesh* m_screen_quad_;
	glick::mat::deferred::DeferredMaterial* m_deferred_mat_;
};

