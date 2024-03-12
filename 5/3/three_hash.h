#pragma once
#include <cstddef>      //for size_t
#include <optional>
#include <vector>
#include <functional>
#include <utility>

std::pair<bool, size_t> linear_probing
    (int x, std::vector<std::optional<int>>& hashTable);
std::pair<bool, size_t> quadratic_probing
    (int x, std::vector<std::optional<int>>& hashTable);
std::pair<bool, size_t> double_hashing
    (int x, std::vector<std::optional<int>>& hashTable, 
     std::function<size_t(int)> hashFunc);