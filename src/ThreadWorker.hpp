#ifndef LC_THREADWORKER_HPP
#define LC_THREADWORKER_HPP

#include <mutex>
#include <queue>
#include <thread>
#include <tuple>

namespace lc {
	struct IWork {
		virtual ~IWork() = default;

		virtual void exec() = 0;
	};

	template<typename Fn, typename... Args>
	struct Work : public IWork {
		Work(Fn fn, Args &&...args)
			: fn{ fn }
			, args{ args... } {
		}

		void exec() override {
			std::apply(fn, args);
		}

		Fn fn;
		std::tuple<Args...> args;
	};

	struct ThreadWorker {
	public:
		ThreadWorker();
		~ThreadWorker();

	public:
		template<typename T>
		void run(T &&t) {
			std::scoped_lock _{ m_mutex };
			auto iwork = new T{ t };
			m_work_queue.push(iwork);
		}

		template<typename Fn, typename Arg1, typename... Args>
		void run(Fn fn, Arg1 &&arg1, Args &&...args) {
			run(Work<Fn, Arg1, Args...>{ fn, std::move(arg1), std::move(args)... });
		}

		[[nodiscard]] auto should_join() -> bool;
		void join();

		[[nodiscard]] auto work_available() -> bool;
		auto get_work() -> IWork *;

	private:
		std::mutex m_mutex;

		std::thread m_thread;
		std::queue<IWork *> m_work_queue;
		bool m_should_join{ false };
	};
}

#endif
