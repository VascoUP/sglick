#pragma once

#include "gl_scene.h"

namespace glick
{
	class Window
	{
	public:
		Window();

		GLFWwindow* get_window() const { return m_window_; }
		unsigned int get_width() const { return m_width_; }
		unsigned int get_height() const { return m_height_; }
		int get_buffer_width() const { return m_buffer_width_; }
		int get_buffer_height() const { return m_buffer_height_; }

		void reset_viewport() const;

		void initialize(unsigned int width, unsigned int height, int glMajor = -1, int glMinor = -1);
		void should_terminate() const;
		void terminate() const;

		~Window();
	private:
		GLFWwindow* m_window_;

		unsigned int m_width_;
		unsigned int m_height_;

		int m_buffer_width_;
		int m_buffer_height_;

		int m_gl_major_;
		int m_gl_minor_;
	};

	class Renderer
	{
	public:
		Renderer();

		scene::Scene* get_scene() { return m_scene_; };

		void initialize();
		void render();
		void terminate();

		~Renderer();
	private:
		scene::Scene* m_scene_;
	};

	class Program
	{
	public:
		Program();

		void initialize(Window* window, Renderer* renderer);
		void run_cycle();
		
		~Program();
	private:
		Window* m_window_;
		Renderer* m_renderer_;
	};
}
