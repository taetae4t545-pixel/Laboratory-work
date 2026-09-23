#pragma once
// Минимальный тестовый каркас практикума «Методы программирования».
// Имена макросов совпадают с подмножеством doctest: TEST_CASE, CHECK,
// REQUIRE, CHECK_THROWS_AS, CHECK_NOTHROW. Если в вашем классе есть
// возможность положить в third_party настоящий doctest.h, замените
// включение этого заголовка на doctest — тесты менять не придётся.

#include <cstdio>
#include <cstddef>
#include <exception>
#include <vector>

namespace microtest {

struct Case { const char* name; void (*fn)(); };

inline std::vector<Case>& registry() { static std::vector<Case> r; return r; }
inline int& failures() { static int f = 0; return f; }
inline int& checks()   { static int c = 0; return c; }

struct Registrar {
    Registrar(const char* n, void (*f)()) { registry().push_back(Case{n, f}); }
};

inline void report(bool ok, const char* expr, const char* file, int line) {
    ++checks();
    if (!ok) {
        ++failures();
        std::printf("    ПРОВАЛ  %s:%d\n            %s\n", file, line, expr);
    }
}

inline int run() {
    int failed_cases = 0;
    for (const Case& c : registry()) {
        const int before = failures();
        std::printf("[ тест ] %s\n", c.name);
        try {
            c.fn();
        } catch (const std::exception& e) {
            ++failures();
            std::printf("    ПРОВАЛ  неожиданное исключение: %s\n", e.what());
        } catch (...) {
            ++failures();
            std::printf("    ПРОВАЛ  неожиданное исключение неизвестного типа\n");
        }
        if (failures() > before) ++failed_cases;
    }
    std::printf("\nитого: тестов %zu, проверок %d, провалов %d\n",
                registry().size(), checks(), failures());
    if (failed_cases == 0) std::printf("ВСЕ ТЕСТЫ ПРОЙДЕНЫ\n");
    else                   std::printf("ПРОВАЛЕНО ТЕСТОВ: %d\n", failed_cases);
    return failed_cases == 0 ? 0 : 1;
}

} // namespace microtest

#define MT_CAT2(a, b) a##b
#define MT_CAT(a, b) MT_CAT2(a, b)

#define TEST_CASE(name)                                                       \
    static void MT_CAT(mt_fn_, __LINE__)();                                   \
    static ::microtest::Registrar MT_CAT(mt_reg_, __LINE__)(                  \
        name, &MT_CAT(mt_fn_, __LINE__));                                     \
    static void MT_CAT(mt_fn_, __LINE__)()

#define CHECK(expr) ::microtest::report(!!(expr), #expr, __FILE__, __LINE__)

#define REQUIRE(expr)                                                         \
    do {                                                                      \
        const bool mt_ok = !!(expr);                                          \
        ::microtest::report(mt_ok, #expr, __FILE__, __LINE__);                \
        if (!mt_ok) return;                                                   \
    } while (0)

#define CHECK_THROWS_AS(expr, ExcType)                                        \
    do {                                                                      \
        bool mt_caught = false;                                               \
        try { (void)(expr); }                                                 \
        catch (const ExcType&) { mt_caught = true; }                          \
        catch (...) { }                                                       \
        ::microtest::report(mt_caught,                                        \
            "ожидалось исключение " #ExcType " от: " #expr,                   \
            __FILE__, __LINE__);                                              \
    } while (0)

#define CHECK_NOTHROW(expr)                                                   \
    do {                                                                      \
        bool mt_ok = true;                                                    \
        try { (void)(expr); } catch (...) { mt_ok = false; }                  \
        ::microtest::report(mt_ok, "не должно бросать: " #expr,               \
                            __FILE__, __LINE__);                              \
    } while (0)

#ifdef MICROTEST_MAIN
int main() { return ::microtest::run(); }
#endif
