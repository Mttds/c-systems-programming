/* g++ -o cas-lock -std=c++11 compare-and-swap-lock.cpp -pthread */

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class CASLock {
private:
    std::atomic<int> flag;

public:
    CASLock() : flag(0) {}

    void lock() {
        int expected = 0;
        while (!flag.compare_exchange_strong(expected, 1)) {
            expected = 0; // Reset expected as it gets modified by compare_exchange_strong
        }
    }

    void unlock() {
        flag.store(0);
    }
};

void criticalSection(int threadID, CASLock &casLock) {
    std::cout << "Thread " << threadID << " attempting to acquire lock..." << std::endl;
    casLock.lock();
    std::cout << "Thread " << threadID << " has acquired lock." << std::endl;
    std::cout << "Thread " << threadID << " is in critical section." << std::endl;
    casLock.unlock();
    std::cout << "Thread " << threadID << " has released lock." << std::endl;
}

int main() {
    const int numThreads = 5;
    CASLock casLock;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(criticalSection, i, std::ref(casLock));
    }

    for (auto &thread : threads) {
        thread.join();
    }

    return 0;
}
