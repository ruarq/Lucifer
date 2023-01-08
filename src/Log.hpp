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

		auto write(size_t level, const std::string_view &message) -> Log &;

		template<typename... Args>
		auto debug(fmt::format_string<Args...> fmt, Args &&...args) -> Log & {
			return write(LogLevelDebug, fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		auto error(fmt::format_string<Args...> fmt, Args &&...args) -> Log & {
			return write(LogLevelError, fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		auto warning(fmt::format_string<Args...> fmt, Args &&...args) -> Log & {
			return write(LogLevelWarning, fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		auto info(fmt::format_string<Args...> fmt, Args &&...args) -> Log & {
			return write(LogLevelInfo, fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		auto line(fmt::format_string<Args...> fmt, Args &&...args) -> Log & {
			if (!ignore_line) {
				fmt::print("\t{}\n", fmt::vformat(fmt, fmt::make_format_args(args...)));
			}

			return *this;
		}

		FILE *fout{};
		size_t log_level{ LogLevelWarning };
		bool ignore_line{ false };
	};
}

#endif
