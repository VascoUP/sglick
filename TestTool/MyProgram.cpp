#include "pch.h"
#include "MyProgram.h"


MyProgram::MyProgram(glick::Window * window, glick::scene::Scene* scene, glick::behavior::Camera * camera) :
	m_window_(window),
	m_scene_ (scene),
	m_camera_(camera)
{
	m_framebuffer_ = new glick::mat::Framebuffer();
	{
		auto info = glick::mat::FramebufferInfo();
		info.use_default_settings = true;
		info.texture_type = GL_TEXTURE_2D;
		info.depth_attachment = true;
		info.depth_data = glick::mat::FramebufferInfo::Data();
		info.depth_data.width = m_window_->get_buffer_width();
		info.depth_data.height = m_window_->get_buffer_height();
		info.texture_count = 3;

		auto color0 = glick::mat::FramebufferInfo::Data();
		color0.bit_depth = 4;
		color0.format_range = 1;
		color0.width = m_window_->get_buffer_width();
		color0.height = m_window_->get_buffer_height();
		auto color1 = glick::mat::FramebufferInfo::Data();
		color1.bit_depth = 3;
		color1.format_range = 1;
		color1.width = m_window_->get_buffer_width();
		color1.height = m_window_->get_buffer_height();
		auto color2 = glick::mat::FramebufferInfo::Data();
		color2.bit_depth = 3;
		color2.format_range = 1;
		color2.width = m_window_->get_buffer_width();
		color2.height = m_window_->get_buffer_height();

		glick::mat::FramebufferInfo::Data texData[]{ color0, color1, color2 };
		info.texture_data = texData;

		m_framebuffer_->initialize(info);
	}

	m_screen_quad_ = glick::scene::ScreenQuad::get();
	auto* defShader = new glick::mat::deferred::DeferredShader();
	defShader->initialize();
	m_deferred_mat_ = new glick::mat::deferred::DeferredMaterial();
	m_deferred_mat_->initialize(defShader);
}

void MyProgram::run()
{
	if (!m_window_)
		return;

	while (!glfwWindowShouldClose(m_window_->get_window()))
	{
		glick::behavior::Input::new_frame();
		glick::behavior::Time::new_frame();
		glick::behavior::FPSCounter::new_frame();
		glick::perf::Performance::new_frame();

		glfwPollEvents();

		// Update all scene objects
		{
			const double start = glfwGetTime();
			update();
			const double end = glfwGetTime();
			const double delta_interruption = end - start;
			glick::perf::Performance::set_render(delta_interruption);
		}

		// Render all renderable objects in the scene
		{
			const double start = glfwGetTime();
			render();
			const double end = glfwGetTime();
			const double delta_interruption = end - start;
			glick::perf::Performance::set_render(delta_interruption);
		}

		glUseProgram(0);

		// Display to screen
		{
			const double start = glfwGetTime();
			glfwSwapBuffers(m_window_->get_window());
			const double end = glfwGetTime();
			const double delta_interruption = end - start;
			glick::perf::Performance::set_swap_buffers(delta_interruption);
		}
	}
}

void MyProgram::update()
{}

void MyProgram::render()
{
	if (!m_scene_ || !m_camera_)
		return;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Here I can draw the skybox onto the screen

	// Set up framebuffer for deferred rendering paramenters
	// that is: diffuse color, specular color, among other
	// position and normals in screen space (or clip space/view space)
	m_framebuffer_->use_framebuffer();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_scene_->render();

	// Other effects can then be added by increasing the number
	// of color attachments to the base framebuffer

	// Unbind the bound framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// The final rendering step is based on the use of
	// the framebuffer color and depth attachments to draw
	// the scene onto the screen + the lighting step 
	m_deferred_mat_->use_material();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_framebuffer_->color_attachments()[0]);

	m_screen_quad_->render();
}

MyProgram::~MyProgram()
{
	if (m_window_)
		m_window_->terminate();
	delete m_window_;
	m_window_ = nullptr;

	if (m_framebuffer_)
		m_framebuffer_->terminate();
	delete m_framebuffer_;
	m_framebuffer_ = nullptr;

	if(m_deferred_mat_)
		m_deferred_mat_->terminate();
	delete m_deferred_mat_;
	m_deferred_mat_ = nullptr;

	delete m_scene_;
	m_scene_ = nullptr;
	delete m_camera_;
	m_camera_ = nullptr;
}

