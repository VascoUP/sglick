#pragma once

#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define KEY_UNKNOWN		-1
#define KEY_DOWN		0
#define KEY_PRESSED		1
#define KEY_UP			2
#define KEY_RELEASED	3

#define SIZE_KEY_ARRAY	349

namespace glick
{
	namespace behavior
	{
		class Input
		{
		public:
			static void new_frame();
			static int check_key(int key_code);

			static void set_callback(GLFWwindow* window);

		private:
			Input();
			static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			~Input();
			
			static Input* m_instance_;
			int m_key_states_[SIZE_KEY_ARRAY]{};
			std::list<int> m_pressed_keys_;
		};

		class FPSCounter;

		class Time
		{
			friend class FPSCounter;
		public:
			Time();

			static double delta_time() { return m_instance_->m_delta_time_; };

			static void new_frame();

			~Time();
		private:
			static Time* m_instance_;

			double m_delta_time_;
			double m_time_;
		};

		class FPSCounter
		{
		public:
			FPSCounter();

			static int fps() { return m_instance_->m_fps_; };

			static void new_frame();

			~FPSCounter();
		private:
			static FPSCounter* m_instance_;

			int m_fps_;
			int m_fps_counter_;
			double m_time_to_second_;			
		};
	}
}


