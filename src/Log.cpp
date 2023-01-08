#include "Log.hpp"

#include <chrono>

#include <fmt/chrono.h>

namespace Lc {
	Log::Log(FILE *fout, const size_t log_level)
		: fout{ fout }
		, log_level{ log_level } {
	}

	void Log::write(const size_t level, const std::string_view &message) {
		if (level > log_level) {
			return;
		}

		fmt::print(fout, "[{}] {}\n", std::chrono::system_clock::now(), message);
	}
}
