#pragma once

#include "vector"
#include "map"
#include "unordered_map"
#include "tuple"

template<typename T>
using ArrayList = std::vector<T>;

template<typename K, typename V>
using Map = std::map<K, V>;

template<typename K, typename V>
using UnorderedMap = std::unordered_map<K, V>;