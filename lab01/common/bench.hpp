#pragma once
// Измерение времени для практикума. Читайте ПР-2: минимум по повторам,
// обязательный разогрев, обязательное использование результата.

#include <chrono>
#include <cstdint>

namespace bench {

// Приёмник результата. Записывайте сюда то, что вернула измеряемая
// функция, иначе оптимизатор удалит её вызов целиком.
inline volatile std::int64_t sink = 0;

template <class F>
double measure_ms(F f, int reps = 5) {
    f();                     // разогрев: кэш и предсказатель переходов
    double best = 1e18;
    for (int i = 0; i < reps; ++i) {
        const auto t0 = std::chrono::steady_clock::now();
        f();
        const auto t1 = std::chrono::steady_clock::now();
        const double d =
            std::chrono::duration<double, std::milli>(t1 - t0).count();
        if (d < best) best = d;
    }
    return best;
}

} // namespace bench
