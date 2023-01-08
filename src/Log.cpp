#include "Log.hpp"

#include <chrono>

#include <fmt/chrono.h>

namespace Lc {
	auto Log::self() -> Log & {
		static Log log;
		return log;
	}

	void Log::init(FILE *fout, const size_t log_level) {
		self().fout = fout;
		self().log_level = log_level;
	}

	auto Log::write(const size_t level,
		const std::string_view &kind,
		const std::string_view &message) -> Log & {
		if (level > self().log_level) {
			self().ignore_line = true;
			return self();
		}
		self().ignore_line = false;
		fmt::print(self().fout, "[{}] {}: {}\n", std::chrono::system_clock::now(), kind, message);
		return self();
	}
}
