#include "ThreadWorker.hpp"

#include <mutex>

namespace lc {
	void thread_func(ThreadWorker *tw) {
		while (!tw->should_join()) {
			if (tw->work_available()) {
				auto work = tw->get_work();
				if (work) {
					work->exec();
					delete work;
				}
			}
		}
	}

	ThreadWorker::ThreadWorker()
		: m_thread{ thread_func, this } {
	}

	ThreadWorker::~ThreadWorker() {
		join();
	}

	auto ThreadWorker::should_join() -> bool {
		std::scoped_lock _{ m_mutex };
		return m_should_join;
	}

	void ThreadWorker::join() {
		std::unique_lock lock{ m_mutex };
		m_should_join = true;
		lock.unlock();
		m_thread.join();
	}

	auto ThreadWorker::work_available() -> bool {
		std::scoped_lock _{ m_mutex };
		return !m_work_queue.empty();
	}

	auto ThreadWorker::get_work() -> IWork * {
		std::scoped_lock _{ m_mutex };
		if (m_work_queue.empty()) {
			return nullptr;
		}

		auto work = m_work_queue.front();
		m_work_queue.pop();
		return work;
	}
}
