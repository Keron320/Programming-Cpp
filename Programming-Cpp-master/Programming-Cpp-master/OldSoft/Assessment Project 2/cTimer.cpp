#include <chrono>
#include "cTimer.h"


// ----------------------------------------------------------------------------
cTimer::cTimer()
{
	reset_ = std::chrono::steady_clock::now();
	elapsed_.zero();
}

// ----------------------------------------------------------------------------
double	cTimer::start()
{
	// set the start time to now
	timerIsTiming_ = true;
	start_ = std::chrono::steady_clock::now();
	// create a temp duration, from when the clock was created/reset until now - in B
	std::chrono::duration<double, std::chrono::milliseconds::period> msSinceReset{ start_ - reset_ };
	// convert the duration to a double in ms and return
	return std::chrono::duration_cast<std::chrono::duration<double, std::chrono::milliseconds::period>>(msSinceReset).count();
}

// ----------------------------------------------------------------------------
double	cTimer::stop()
{
	// set the stop time to now
	stop_ = std::chrono::steady_clock::now();
	// increment the elapsed time with the just-ended interval
	elapsed_ += stop_ - start_;
	// stop timing
	timerIsTiming_ = false;
	// convert the duration to a double in ms and return
	return std::chrono::duration_cast<std::chrono::duration<double, std::chrono::milliseconds::period>>(elapsed_).count();
}

// ----------------------------------------------------------------------------
double	cTimer::reset()
{
	// set time of last reset
	reset_ = std::chrono::steady_clock::now();
	// clear the elapsed time
	elapsed_ = std::chrono::duration<double, std::chrono::milliseconds::period>::zero();
	// if within a timing interval, set the start time to now but
	if (timerIsTiming_)
		start_ = reset_;
	
	//double now = std::chrono::duration_cast<std::chrono::duration<double, std::chrono::milliseconds::period>>(elapsed_).count();
	return 0;
}

// ----------------------------------------------------------------------------
double cTimer::getElapsed_ns()
{
	// temporary duration var to hold calculation
	std::chrono::duration<double, std::chrono::nanoseconds::period> elapsed{ elapsed_ };

	// if within an interval (started but not stopped) add elapsed_ and time from start_ of interval to now
	if (timerIsTiming_)
	{
		std::chrono::time_point<std::chrono::steady_clock>	mark = std::chrono::steady_clock::now();
		elapsed += mark - start_;
	}
	// convert the elapsed time to nanoseconds
	double duration_ms = std::chrono::duration_cast<std::chrono::duration<double, std::chrono::nanoseconds::period>>(elapsed).count();
	return duration_ms;
}

// ----------------------------------------------------------------------------
double cTimer::getElapsed_ms()
{
	// temporary duration var to hold calculation
	std::chrono::duration<double, std::chrono::milliseconds::period> elapsed{ elapsed_ };
	
	// if within an interval (started but not stopped) add elapsed_ and time from start_ of interval to now
	if (timerIsTiming_)
	{
		std::chrono::time_point<std::chrono::steady_clock>	mark = std::chrono::steady_clock::now();
		elapsed += mark - start_;
	}
	// convert the elapsed time to milliseconds
	double duration_ms = std::chrono::duration_cast<std::chrono::duration<double, std::chrono::milliseconds::period>>(elapsed).count();
	return duration_ms;
}

// ----------------------------------------------------------------------------
double cTimer::getElapsed_sec()
{
	// temporary duration var to hold calculation
	std::chrono::duration<double, std::chrono::seconds::period> elapsed{ elapsed_ };

	// if within an interval (started but not stopped) add elapsed_ and time from start_ of interval to now
	if (timerIsTiming_)
	{
		std::chrono::time_point<std::chrono::steady_clock>	mark = std::chrono::steady_clock::now();
		elapsed += mark - start_;
	}
	// convert the elapsed time to seconds
	double duration_ms = std::chrono::duration_cast<std::chrono::duration<double, std::chrono::seconds::period>>(elapsed).count();
	return duration_ms;
}
