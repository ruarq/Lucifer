#include <chrono>
#include <cstdio>
#include <filesystem>
#include <iostream>

#include <fmt/chrono.h>
#include <fmt/format.h>

#include "Log.hpp"
#include "Uci.hpp"
#include "common.hpp"
#include "version.hpp"

struct DummyEngine : public Lc::UciEngine {
	void on_uci() override {
		Lc::Log::info("DummyEngine::on_uci()");
	}

	void on_debug(const bool on) override {
		Lc::Log::info("DummyEngine::on_debug() : on = {}", on);
	}

	void on_isready() override {
		Lc::Log::info("DummyEngine::on_isready()");
	}

	void on_setoption() override {
		Lc::Log::info("DummyEngine::on_setoption()");
	}

	void on_register() override {
		Lc::Log::info("DummyEngine::on_register()");
	}

	void on_ucinewgame() override {
		Lc::Log::info("DummyEngine::on_ucinewgame()");
	}

	void on_position() override {
		Lc::Log::info("DummyEngine::on_position()");
	}

	void on_go() override {
		Lc::Log::info("DummyEngine::on_go()");
	}

	void on_stop() override {
		Lc::Log::info("DummyEngine::on_stop()");
	}

	void on_ponderhit() override {
		Lc::Log::info("DummyEngine::on_ponderhit()");
	}

	void on_quit() override {
		Lc::Log::info("DummyEngine::on_quit()");
		running = false;
	}

	[[nodiscard]] auto is_running() const -> bool override {
		return running;
	}

	bool running = true;
};

auto main() -> int {
	/*
	auto log_filename =
		std::filesystem::temp_directory_path() /
		fmt::format("lucifer_log_{:%Y-%m-%d_%H:%M:%S}.txt", std::chrono::system_clock::now());

	FILE *log_file = std::fopen(log_filename.c_str(), "w");
	*/

	Lc::Log::init(stdout, Lc::LogLevelInfo /* Lc::LogLevelNoLogs */);
	Lc::Log::info("Lucifer v{}", LC_VERSION).line("initializing...");

	Lc::UciEngine *engine = new DummyEngine{};

	Lc::Uci uci{ engine };

	std::string command;
	while (engine->is_running() && std::getline(std::cin, command)) {
		uci.exec(command);
	}

	delete engine;

	return 0;
}
