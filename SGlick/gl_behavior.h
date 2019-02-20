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
	}
}


