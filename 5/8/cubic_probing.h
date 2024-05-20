#pragma once
#include <cstddef>
#include <utility>
#include <vector>
#include <optional>

std::pair<bool, size_t> quadratic_probing
    (int x, std::vector<std::optional<int>>& hashTable);

std::pair<bool, size_t> cubic_probing
    (int x, std::vector<std::optional<int>>& hashTable);
