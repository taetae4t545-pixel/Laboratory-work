#include "lab01.hpp"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

volatile long long sink = 0;  // не даёт оптимизатору выбросить вызов

template <class F>
double measure_ms(F f, int reps = 5) {
    f();                              // разогрев
    double best = 1e18;
    for (int i = 0; i < reps; ++i) {
        auto t0 = std::chrono::steady_clock::now();
        f();
        auto t1 = std::chrono::steady_clock::now();
        double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
        if (ms < best) best = ms;
    }
    return best;
}

std::vector<int> make_sorted(std::size_t n) {
    std::vector<int> v(n);
    for (std::size_t i = 0; i < n; ++i) v[i] = static_cast<int>(i);
    return v;
}

int main() {
    std::cout << "n,lin_best_ms,lin_mid_ms,lin_worst_ms,binary_ms,pairs_ms\n";

    // 2^10 .. 2^18
    for (int k = 10; k <= 18; ++k) {
        std::size_t n = std::size_t(1) << k;
        auto v = make_sorted(n);

        // лучший случай: ищем первый элемент (0)
        double t_best = measure_ms([&]{
            sink += linear_search(v, 0);
        });

        // средний случай: ищем элемент в середине (n/2)
        double t_mid = measure_ms([&]{
            sink += linear_search(v, static_cast<int>(n / 2));
        });

        // худший случай: искомого нет — проходим весь массив
        double t_worst = measure_ms([&]{
            sink += linear_search(v, -1);
        });

        // бинарный поиск: ищем значение, которого нет
        double t_bin = measure_ms([&]{
            sink += binary_search(v, -1);
        });

        // пары — только до 2^14, дальше слишком долго
        double t_pairs = -1.0;
        if (k <= 14) {
            t_pairs = measure_ms([&]{
                sink += count_pairs_sum(v, -1);
            });
        }

        std::cout << n << ","
                  << t_best  << ","
                  << t_mid   << ","
                  << t_worst << ","
                  << t_bin   << ","
                  << t_pairs << "\n";
    }
    std::cout << "sink=" << sink << "\n";
}