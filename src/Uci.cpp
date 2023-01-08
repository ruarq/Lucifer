#include "Uci.hpp"

namespace Lc {
	constexpr auto is_ident(const char c) -> bool {
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}

	constexpr auto is_whitespace(const char c) -> bool {
		return c == ' ';
	}

	struct UciExecutor {
		UciExecutor(const std::string_view &command, UciEngine *engine)
			: command{ command }
			, engine{ engine } {
		}

		void run() {
			const auto command = next_token();
			if (command == "uci") {
				engine->on_uci();
			} else if (command == "debug") {
				parse_debug();
			} else if (command == "isready") {
				engine->on_isready();
			} else if (command == "setoption") {
				engine->on_setoption();
			} else if (command == "register") {
				engine->on_register();
			} else if (command == "ucinewgame") {
				engine->on_ucinewgame();
			} else if (command == "position") {
				engine->on_position();
			} else if (command == "go") {
				engine->on_go();
			} else if (command == "stop") {
				engine->on_stop();
			} else if (command == "ponderhit") {
				engine->on_ponderhit();
			} else if (command == "quit") {
				engine->on_quit();
			} else {
				Log::error("Lc::UciExecutor::parse_command()")
					.line("unexpected command '{}'", command)
					.line("please read the uci protocol for further information");
			}
		}

		void parse_debug() {
			const auto onoff = next_token();
			if (onoff == "on") {
				engine->on_debug(true);
			} else if (onoff == "off") {
				engine->on_debug(false);
			} else {
				Log::error("Lc::UciExecutor::parse_debug()")
					.line("expected 'on' or 'off' but found '{}'", onoff)
					.line("defaulting to 'off'");
				engine->on_debug(false);
			}
		}

		auto next_token() -> std::string {
			while (is_whitespace(current())) {
				next();
			}

			switch (current()) {
				case 'a' ... 'z':
				case 'A' ... 'Z': {
					std::string word;
					while (is_ident(current())) {
						word += next();
					}
					return word;
				}

				default: Log::error("Lc::UciExecutor::next_token() : unknown token"); break;
			}

			return "ERROR";
		}

		[[nodiscard]] auto current() const -> char {
			return command[command_itr];
		}

		auto next() -> char {
			return command[command_itr++];
		}

		std::string_view command;
		size_t command_itr = 0;

		UciEngine *engine{};
	};

	Uci::Uci(UciEngine *engine)
		: engine{ engine } {
	}

	void Uci::exec(const std::string &command) {
		UciExecutor executor{ command, engine };
		executor.run();
	}
}
