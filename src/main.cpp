#include <iostream>

#include "Log.hpp"
#include "ThreadWorker.hpp"
#include "common.hpp"
#include "version.hpp"

auto main() -> int {
#if defined(DEBUG)
	lc::Log::init(stdout, lc::LogLevelDebug);
	lc::Log::info("Lucifer v{} (debug)", LC_VERSION);
#else
	lc::Log::init(stdout, Lc::LogLevelError);
	lc::Log::info("Lucifer v{}", LC_VERSION);
#endif

	lc::ThreadWorker engine_thread;

	std::string input;
	while (std::getline(std::cin, input)) {
		// parse input
		engine_thread.run(
			[](auto str) {
				lc::Log::debug("engine_thread: {}", str);
			},
			std::move(input));
	}

	engine_thread.join();

	return 0;
}
