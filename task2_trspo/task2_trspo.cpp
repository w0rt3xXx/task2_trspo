#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

using namespace std;

atomic<int> completedCount(0);
atomic<long long> totalSteps(0);

int collatz(int n) {
    int steps = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        }
        else {
            n = 3 * n + 1;
        }
        steps++;
    }
    return steps;
}

void worker(int start, int end) {
    for (int number = start; number <= end; ++number) {
        int steps = collatz(number);
        totalSteps += steps;
        completedCount++;


        if (completedCount % 1000 == 0) {
            cout << "Processed " << completedCount << " numbers." << endl;
        }
    }
}

int main() {
    const int numCount = 100000;
    int numThreads;
    cout << "Enter the count of threads: ";
    cin >> numThreads;

    vector<thread> threads;
    int rangePerThread = numCount / numThreads;


    for (int i = 0; i < numThreads; ++i) {
        int start = i * rangePerThread + 1;
        int end = (i == numThreads - 1) ? numCount : (i + 1) * rangePerThread;
        threads.emplace_back(worker, start, end);
    }


    for (auto& thread : threads) {
        thread.join();
    }


    double averageSteps = static_cast<double>(totalSteps) / numCount;

    cout << "avg steps count for " << numCount << " numbers: " << averageSteps << endl;

    return 0;
}

