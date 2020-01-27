#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <utility>

template <typename T>
class Queue {
 public:
    T Pop() {
        std::unique_lock<std::mutex> guard(lock);
        T val = std::move(m_data.front());
        m_data.pop();
        return val;
    }

    size_t Size() {
        std::unique_lock<std::mutex> guard(lock);
        return m_data.size();
    }

    template <typename U>
    void Push(const U& val) {
        std::unique_lock<std::mutex> guard(lock);
        m_data.push(val);
    }

    template <typename U>
    void Push(U&& val) {
        std::unique_lock<std::mutex> guard(lock);
        m_data.push(std::move(val));
    }

    template <typename ... U>
    void Emplace(U&&... args) {
        std::unique_lock<std::mutex> guard(lock);
        m_data.emplace(std::forward<U>(args)...);
    }

 private:
    std::queue<T> m_data;
    std::mutex lock;
};
