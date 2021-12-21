#pragma once


#include <chrono>
// -- LOCAL

// .. REFERENCES

// -- GLOBAL

// .. TYPES

class FUNDAMENTAL_DELTA_TIME
{
	// -- PUBLIC

public:

	// .. CONSTRUCTORS

	FUNDAMENTAL_DELTA_TIME(void)
	{
	}

	// ~~

	virtual ~FUNDAMENTAL_DELTA_TIME(void)
	{
	}

	// .. FUNCTIONS

	static const float GetDeltaTime(void)
	{
		static std::chrono::steady_clock::time_point t_start = std::chrono::high_resolution_clock::now();
		static std::chrono::steady_clock::time_point t_end = std::chrono::high_resolution_clock::now();

		t_end = std::chrono::high_resolution_clock::now();
		float elapsed_time_ms = float(std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count());
		t_start = std::chrono::high_resolution_clock::now();

		return elapsed_time_ms * 0.001f;
	}

	// -- PRIVATE

private:

	// .. VARIABLES

};

// .. VARIABLES

