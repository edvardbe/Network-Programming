#include <iostream>
#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <future>
#include <memory>

using namespace std;

class Workers {
    public:
        vector<thread> threads;
        int num_threads;
        queue<function<void()>> tasks;
        mutex mutex_t;
        condition_variable condition;
        bool started = false;
        atomic<bool> stop;

        Workers(int num_threads) {
            // Create num_threads threads
            this->num_threads = num_threads;
            this->stop = false;
        }
        void start()  {
            if (started) return;
            started = true;
            // Start the threads
            for (int i = 0; i < num_threads; i++) {
                threads.emplace_back([this] {
                    while (true) {
                        unique_lock<mutex> lock(mutex_t);
                        condition.wait(lock, [this] { return stop || !tasks.empty(); });
                        if (stop && tasks.empty()) return;
                        auto task = move(tasks.front());
                        tasks.pop();
                        lock.unlock();
                        task();
                    }
                });
            }
        }
        void post(function<void()> task) {
            // Post a task to the threads
            {
                unique_lock<mutex> lock(mutex_t);
                tasks.push(task);
            }
            condition.notify_one();
        }

        void join() {
            {
                unique_lock<mutex> lock(mutex_t);
                stop = true;
            }
            // Join the threads
            condition.notify_all();
            for (auto& thread : threads) {
                if (thread.joinable()) thread.join();
            }
        }
        ~Workers() {
            // Join the threads
            join();
        }	
};

int main(){

    Workers worker_threads(4);
    Workers event_loop(1);

    worker_threads.start(); // Create 4 internal threads
    event_loop.start(); // Create 1 internal thread

    for (int i = 0; i < 8; i++) {
        worker_threads.post([i] {
    // Task A
        int n = i >= 4 ? 2 : 1;
        printf("Task A: nr %d in group %d\n", i, n);
        this_thread::sleep_for(chrono::seconds(2));
        });
    }

    event_loop.post([] {
    // Task B
    // Might run in parallel with task A and B
        for (int i = 0; i < 10; i++) {
            cout << "Task B: " << i << endl;
        }
    });

    event_loop.post([] {
    // Task D
    // Will run after task C
    // Might run in parallel with task A and B

        for (int i = 0; i < 10; i++) {
            cout << "Task C: " << i << endl;
        }
    });

    worker_threads.join(); // Calls join () on the worker threads
    event_loop.join(); // Calls join () on the event thread

    return 0;

}