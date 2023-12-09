#pragma once

#include <iostream>
#include <type_traits>

template <typename T>
concept HasOutputOperator = requires(std::ostream &os, const T &obj) {
    os << obj;
};

template <typename T>
concept HasInputOperator = requires(std::istream &is, T &obj) {
    is >> obj;
};

template <typename T>
concept HasInputOutputOperators = HasOutputOperator<T> && HasInputOperator<T>;
