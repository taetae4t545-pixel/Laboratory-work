#include "lab01.hpp"
#include <stdexcept>

long long sum_range(const std::vector<int>& v, std::size_t from, std::size_t to) {
    if (from > to || to > v.size())
        throw std::out_of_range("sum_range: bad range");
    long long sum = 0;
    for (std::size_t i = from; i < to; ++i) sum += v[i];
    return sum;
}

int linear_search(const std::vector<int>& v, int target) {
    for (std::size_t i = 0; i < v.size(); ++i)
        if (v[i] == target) return static_cast<int>(i);
    return -1;
}

int binary_search(const std::vector<int>& v, int target) {
    std::size_t lo = 0, hi = v.size();
    while (lo < hi) {
        std::size_t mid = lo + (hi - lo) / 2;
        if (v[mid] == target) return static_cast<int>(mid);
        if (v[mid] < target)  lo = mid + 1;
        else                  hi = mid;
    }
    return -1;
}

long long count_pairs_sum(const std::vector<int>& v, int target) {
    long long count = 0;
    for (std::size_t i = 0; i + 1 < v.size(); ++i)
        for (std::size_t j = i + 1; j < v.size(); ++j)
            if (v[i] + v[j] == target) ++count;
    return count;
}
