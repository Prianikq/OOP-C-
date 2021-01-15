/* Ляшун Дмитрий Сергеевич, М8О-207Б-19 */
#pragma once
#include <queue>
#include <mutex>
template<class T>
class PubSubMQ {
    private:
        std::queue<T> messages;
        std::mutex mx;
    public:
        explicit PubSubMQ() noexcept : messages(), mx() {}
        ~PubSubMQ() {}
        bool Empty() {
            mx.lock();
            bool ans = messages.empty();
            mx.unlock();
            return ans;
        }
        void Push(const T data) {
            mx.lock();
            messages.push(data);
            mx.unlock();
        }
        void Pop() {
            mx.lock();
            messages.pop();
            mx.unlock();
        }
        T Front() {
            mx.lock();
            T ans = messages.front();
            mx.unlock();
            return ans;
        }
};
