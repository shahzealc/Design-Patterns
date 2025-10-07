#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>
#include <atomic>

class ThreadPool
{
public:
    static ThreadPool &Get()
    {
        static ThreadPool threadPool;
        return threadPool;
    }

    void start(int threads)
    {
        std::lock_guard lock(mtx);
        if (_isRunning)
            return;

        _isRunning = true;
        for (int i = 0; i < threads; ++i)
        {
            _threads.emplace_back([this, i]
                                  {
                std::function<void()> task;
                while (true) {
                    {
                        std::unique_lock lock(mtx);
                        cv.wait(lock, [this] { return !_tasks.empty() || !_isRunning; });

                        if (!_isRunning && _tasks.empty())
                            return;

                        task = std::move(_tasks.front());
                        _tasks.pop();
                    }
                        task();
                    
                } });
        }
    }

    void stop()
    {
        {
            std::lock_guard lock(mtx);
            _isRunning = false;
        }

        cv.notify_all();

        for (auto &thread : _threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
        _threads.clear();
    }

    void addTask(std::function<void()> task)
    {
        {
            std::lock_guard lock(mtx);
            _tasks.push(std::move(task));
        }
        cv.notify_one();
    }

private:
    ThreadPool() = default;
    ~ThreadPool() { stop(); };
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;

    std::mutex mtx{};
    std::condition_variable cv{};
    std::vector<std::thread> _threads{};
    std::queue<std::function<void()>> _tasks{};
    std::atomic<bool> _isRunning{false};
};

void add()
{
    for (int i = 0; i <= 10; ++i)
        std::cout << "+ \n";
}
void substract()
{
    for (int i = 0; i <= 10; ++i)
        std::cout << "- \n";
}
void multiply()
{
    for (int i = 0; i <= 10; ++i)
        std::cout << "* \n";
}
void division()
{
    for (int i = 0; i <= 10; ++i)
        std::cout << "/ \n";
}

int main()
{
    ThreadPool::Get().start(4);

    ThreadPool::Get().addTask(add);
    ThreadPool::Get().addTask(substract);
    ThreadPool::Get().addTask(multiply);
    ThreadPool::Get().addTask(division);

    ThreadPool::Get().stop();

    return 0;
}