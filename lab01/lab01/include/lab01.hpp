#pragma once
#include <cstddef>
#include <vector>

long long sum_range(const std::vector<int>& v, std::size_t from, std::size_t to);

int linear_search(const std::vector<int>& v, int target);
int binary_search(const std::vector<int>& v, int target);
long long count_pairs_sum(const std::vector<int>& v, int target);
