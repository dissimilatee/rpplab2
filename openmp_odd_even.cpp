#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include <omp.h>

using namespace std;

vector<int> generateArray(int n, int seed = 42) {
    mt19937 gen(seed);
    uniform_int_distribution<int> dist(0, 1000000);
    vector<int> a(n);
    for (int &x : a) x = dist(gen);
    return a;
}

bool isSorted(const vector<int>& a) {
    for (size_t i = 1; i < a.size(); ++i) if (a[i - 1] > a[i]) return false;
    return true;
}

void oddEvenSortSequential(vector<int>& a) {
    int n = static_cast<int>(a.size());
    for (int phase = 0; phase < n; ++phase) {
        int start = phase % 2;
        for (int i = start; i < n - 1; i += 2) {
            if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
        }
    }
}

void oddEvenSortOpenMP(vector<int>& a, int threads) {
    int n = static_cast<int>(a.size());
    omp_set_num_threads(threads);

    #pragma omp parallel
    {
        for (int phase = 0; phase < n; ++phase) {
            int start = phase % 2;
            #pragma omp for schedule(static)
            for (int i = start; i < n - 1; i += 2) {
                if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int n = 10000;
    int threads = 4;
    int seed = 42;

    if (argc >= 2) n = stoi(argv[1]);
    if (argc >= 3) threads = stoi(argv[2]);
    if (argc >= 4) seed = stoi(argv[3]);

    vector<int> arr = generateArray(n, seed);

    auto start = chrono::high_resolution_clock::now();
    if (threads <= 1) oddEvenSortSequential(arr);
    else oddEvenSortOpenMP(arr, threads);
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = end - start;

    cout << fixed << setprecision(6);
    cout << "OpenMP Odd-Even Sort\n";
    cout << "Array size: " << n << "\n";
    cout << "Threads: " << threads << "\n";
    cout << "Time: " << elapsed.count() << " seconds\n";
    cout << "Sorted: " << (isSorted(arr) ? "yes" : "no") << "\n";

    return 0;
}
