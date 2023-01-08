#include <chrono>
#include <cstdio>
#include <filesystem>
#include <iostream>

#include <fmt/chrono.h>
#include <fmt/format.h>

#include "Log.hpp"
#include "common.hpp"
#include "version.hpp"

auto main() -> int {
	/*
	auto log_filename =
		std::filesystem::temp_directory_path() /
		fmt::format("lucifer_log_{:%Y-%m-%d_%H:%M:%S}.txt", std::chrono::system_clock::now());

	FILE *log_file = std::fopen(log_filename.c_str(), "w");
	*/

	Lc::Log log{ stdout, Lc::LogLevelInfo };
	log.info("Lucifer v{}", LC_VERSION).line("initializing...");

	std::fclose(stdout);
	return 0;
}
