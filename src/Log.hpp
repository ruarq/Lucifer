#ifndef LC_LOG_HPP
#define LC_LOG_HPP

#include <cstdio>

#include <fmt/format.h>

#include "common.hpp"
#include "fmt/core.h"

namespace lc {
	enum LogLevel : size_t {
		LogLevelNoLogs,
		LogLevelError,
		LogLevelWarning,
		LogLevelInfo,
		LogLevelDebug
	};

	/**
	 * @brief thread safe logging
	 */
	struct Log {
		static auto self() -> Log &;

		static void init(FILE *fout, size_t log_level);

		static auto
		write(size_t level, const std::string_view &kind, const std::string_view &message) -> Log &;

		template<typename... Args>
		static auto debug(fmt::format_string<Args...> fmt, Args &&...args) -> Log & {
			return write(LogLevelDebug, "Debug", fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		static auto error(fmt::format_string<Args...> fmt, Args &&...args) -> Log & {
			return write(LogLevelError, "Error", fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		static auto warning(fmt::format_string<Args...> fmt, Args &&...args) -> Log & {
			return write(LogLevelWarning,
				"Warning",
				fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		static auto info(fmt::format_string<Args...> fmt, Args &&...args) -> Log & {
			return write(LogLevelInfo, "Info", fmt::vformat(fmt, fmt::make_format_args(args...)));
		}

		template<typename... Args>
		static auto line(fmt::format_string<Args...> fmt, Args &&...args) -> Log & {
			if (!self().ignore_line) {
				fmt::print("\t{}\n", fmt::vformat(fmt, fmt::make_format_args(args...)));
			}

			return self();
		}

		FILE *fout{};
		size_t log_level{ LogLevelWarning };
		bool ignore_line{ false };
	};
}

#endif
