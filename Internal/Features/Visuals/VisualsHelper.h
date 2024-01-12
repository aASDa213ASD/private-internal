#pragma once

#include <string>

static std::string format_time(int time_in_seconds) {
	int minutes = time_in_seconds / 60;
	int seconds = time_in_seconds % 60;

	std::string formattedTime;
	if (minutes > 0)
		formattedTime += std::to_string(minutes) + ":";

	if (seconds < 10)
		formattedTime += "0";

	formattedTime += std::to_string(seconds);

	return formattedTime;
}