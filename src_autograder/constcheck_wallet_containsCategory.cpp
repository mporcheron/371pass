#include <iostream>

#include "wallet.h"

// https://stackoverflow.com/questions/30407754/how-to-test-if-a-method-is-const

struct IsMissing { static constexpr auto value = false;  };
struct IsPresent { static constexpr auto value = true;  };
struct IsNotConst { static constexpr auto value = false; };
struct IsConst { static constexpr auto value = true; };


const std::string test = "test";


template <typename...> using void_t = void;


template <typename T, typename = void>
struct check : IsMissing {};

template <typename T>
struct check<T, void_t<decltype(std::declval<T &>().containsCategory(test))>>
    : IsPresent {};


template <typename T, typename = void>
struct checkConst : IsNotConst {};

template <typename T>
struct checkConst<T, void_t<decltype(std::declval<const T &>().containsCategory(test))>>
    : IsConst {};


int main() {
  if (check<Wallet>::value) {
    std::cout << checkConst<Wallet>::value;
    return checkConst<Wallet>::value ? 0 : 1;
  } else {
    std::cout << -1;
    return 0;
  }
}