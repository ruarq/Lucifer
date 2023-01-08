#ifndef LC_LOG_HPP
#define LC_LOG_HPP

#include <cstdio>

#include <fmt/format.h>

#include "common.hpp"
#include "fmt/core.h"

namespace Lc {
	enum LogLevel : size_t {
		LogLevelDebug,
		LogLevelError,
		LogLevelWarning,
		LogLevelInfo
	};

	struct Log {
		Log(FILE *fout, size_t log_level);

		void write(size_t level, const std::string_view &message);

		template<typename... Args>
		void debug(fmt::format_string<Args...> fmt, Args &&...args) {
			write(LogLevelDebug, fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		void error(fmt::format_string<Args...> fmt, Args &&...args) {
			write(LogLevelError, fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		void warning(fmt::format_string<Args...> fmt, Args &&...args) {
			write(LogLevelWarning, fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		void info(fmt::format_string<Args...> fmt, Args &&...args) {
			write(LogLevelInfo, fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		FILE *fout{};
		size_t log_level{ LogLevelWarning };
	};
}

#endif
