#pragma once
#include <cstddef>      //for size_t
#include <optional>
#include <vector>
#include <functional>
#include <utility>
#include <string>

std::pair<bool, size_t> linear_probing
    (int x, std::vector<std::optional<int>>& hashTable);
std::pair<bool, size_t> quadratic_probing
    (int x, std::vector<std::optional<int>>& hashTable);
std::pair<bool, size_t> double_hashing
    (int x, std::vector<std::optional<int>>& hashTable, 
     std::function<size_t(int)> hashFunc);

std::pair<bool, size_t> quadratic_probing
    (std::string_view x, std::vector<std::optional<std::string>>& hashTable,
     std::function<size_t(const std::string&, size_t)> hashFunc);
