#pragma once

namespace glick
{
	namespace perf
	{
		class Performance
		{
		public:
			static void new_frame();
			static void log_performance_metrics();
			static void set_input_poll(double lag);
			static void set_input_new(double lag);
			static void set_update(double lag);
			static void set_render(double lag);
			static void set_swap_buffers(double lag);

		private:
			Performance();

			~Performance();

			static Performance* m_instance_;

			double m_time_to_second_;

			double input_poll_lag_;
			double input_new_lag_;
			double swap_buffers_lag_;
			double update_lag_;
			double render_lag_;
		};
		
	}
}


