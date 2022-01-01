#include <iostream>

#include "category.h"

// https://stackoverflow.com/questions/30407754/how-to-test-if-a-method-is-const

struct IsMissing { static constexpr auto value = false;  };
struct IsPresent { static constexpr auto value = true;  };
struct IsNotConst { static constexpr auto value = false; };
struct IsConst { static constexpr auto value = true; };


template <typename...> using void_t = void;


template <typename T, typename = void>
struct check : IsMissing {};

template <typename T>
struct check<T, void_t<decltype(std::declval<T &>().size())>>
    : IsPresent {};


template <typename T, typename = void>
struct checkConst : IsNotConst {};

template <typename T>
struct checkConst<T, void_t<decltype(std::declval<const T &>().size())>>
    : IsConst {};


int main() {
  if (check<Category>::value) {
    std::cout << checkConst<Category>::value;
    return checkConst<Category>::value ? 0 : 1;
  } else {
    std::cout << -1;
    return 0;
  }
}