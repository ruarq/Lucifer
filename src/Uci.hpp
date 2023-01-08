#ifndef LC_UCI_HPP
#define LC_UCI_HPP

#include "Log.hpp"
#include "common.hpp"

namespace Lc {
	struct UciEngine {
		UciEngine() = default;
		virtual ~UciEngine() = default;

		virtual void on_uci() = 0;
		virtual void on_debug(bool on) = 0;
		virtual void on_isready() = 0;
		virtual void on_setoption() = 0;
		virtual void on_register() = 0;
		virtual void on_ucinewgame() = 0;
		virtual void on_position() = 0;
		virtual void on_go() = 0;
		virtual void on_stop() = 0;
		virtual void on_ponderhit() = 0;
		virtual void on_quit() = 0;

		[[nodiscard]] virtual auto is_running() const -> bool = 0;
	};

	struct Uci {
		Uci(UciEngine *engine);

		void exec(const std::string &str);

		UciEngine *engine{};
	};
}

#endif
