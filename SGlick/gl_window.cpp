#include "stdafx.h"
#include "gl_window.h"

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

glick::Window::Window() :
	m_width_(0),
	m_height_(0),
	m_gl_major_(4),
	m_gl_minor_(5)
{}

void glick::Window::reset_viewport() const
{
	glViewport(0, 0, m_width_, m_height_);
}

void glick::Window::initialize(unsigned int width, unsigned int height, int glMajor, int glMinor)
{
	m_width_ = width; m_height_ = height;
	m_gl_major_ = glMajor >= 0 ? glMajor : m_gl_major_;
	m_gl_minor_ = glMinor >= 0 ? glMinor : m_gl_minor_;

	if (!glfwInit())
	{
		// Initialization failed	
		error_callback(0, "GLFW initialization failed.");
		glfwTerminate();
		exit(-1);
	}

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_gl_major_);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_gl_minor_);
	// Core profile = No Backwared Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLU_TRUE);

	m_window_ = glfwCreateWindow(m_width_, m_height_, "SGLICK", nullptr, nullptr);
	if (!m_window_)
	{
		// Window or OpenGL context creation failed
		error_callback(0, "Window creation failed.");
		glfwTerminate();
		exit(-1);
	}

	// Get Buffer size information
	glfwGetFramebufferSize(m_window_, &m_buffer_width_, &m_buffer_height_);

	// Set context for glfw to use
	glfwMakeContextCurrent(m_window_);

	// Set input interruption callbacks
	behavior::Input::set_callback(m_window_);
	glfwSetInputMode(m_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("GLEW initialization failed");
		glfwDestroyWindow(m_window_);
		glfwTerminate();
		exit(-1);
	}

	glCullFace(GL_FRONT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_FRAMEBUFFER_SRGB);

	// Setup viewport
	reset_viewport();

	// Define the user of main window
	glfwSetWindowUserPointer(m_window_, this);
}

void glick::Window::should_terminate() const
{
	glfwSetWindowShouldClose(m_window_, GLFW_TRUE);
}

void glick::Window::terminate() const
{
	glfwDestroyWindow(m_window_);
	glfwTerminate();
}

glick::Window::~Window()
= default;
