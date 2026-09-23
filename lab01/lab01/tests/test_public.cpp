#include "microtest.hpp"
#include "lab01.hpp"
#include <stdexcept>

TEST_CASE("линейный поиск: найден") {
    std::vector<int> v{10, 20, 30};
    CHECK(linear_search(v, 10) == 0);
    CHECK(linear_search(v, 20) == 1);
    CHECK(linear_search(v, 30) == 2);
}

TEST_CASE("линейный поиск: не найден") {
    std::vector<int> v{10, 20, 30};
    CHECK(linear_search(v, 99) == -1);
    CHECK(linear_search(v, -5) == -1);
}

TEST_CASE("линейный поиск: пустой вектор") {
    std::vector<int> v;
    CHECK(linear_search(v, 1) == -1);
}

TEST_CASE("бинарный поиск: найден") {
    std::vector<int> v{1, 3, 5, 7, 9};
    CHECK(binary_search(v, 1) == 0);
    CHECK(binary_search(v, 5) == 2);
    CHECK(binary_search(v, 9) == 4);
}

TEST_CASE("бинарный поиск: не найден") {
    std::vector<int> v{1, 3, 5, 7, 9};
    CHECK(binary_search(v, 2) == -1);
    CHECK(binary_search(v, 100) == -1);
}

TEST_CASE("бинарный поиск: пустой вектор") {
    std::vector<int> v;
    CHECK(binary_search(v, 1) == -1);
}

TEST_CASE("подсчёт пар: есть пары") {
    std::vector<int> v{1, 2, 3, 4, 5};
    CHECK(count_pairs_sum(v, 6) == 2);   // (1,5), (2,4)
    CHECK(count_pairs_sum(v, 5) == 2);   // (1,4), (2,3)
}

TEST_CASE("подсчёт пар: нет пар") {
    std::vector<int> v{1, 2, 3};
    CHECK(count_pairs_sum(v, 100) == 0);
}

TEST_CASE("подсчёт пар: пустой вектор и один элемент") {
    std::vector<int> v0;
    std::vector<int> v1{5};
    CHECK(count_pairs_sum(v0, 5) == 0);
    CHECK(count_pairs_sum(v1, 10) == 0);
}

