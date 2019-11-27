//
// Created by artyom on 18.10.2019.
//
#include <iostream>
#include "big_integer.h"

namespace big_num_arithmetic {

int32_t BigInteger::internal_base = 10000;

BigInteger::BigInteger() {
  big_number_.push_back(0);
}
BigInteger::BigInteger(int64_t new_number) {
  bool flag = (new_number == 0x8000000000000000);
  if (flag) {
    ++new_number;
  }
  if (new_number < 0) {
    this->sign_ = true;
    new_number = -new_number;
  }
  if (new_number == 0) {
    this->big_number_.push_back(0);
  }
  while (new_number > 0) {
    this->big_number_.push_back(new_number % internal_base);
    new_number /= internal_base;
  }
  if (flag) {
    --*this;
  }
}

int BigInteger::Sign() const {
  if (sign_) {
    return -1;
  } else if (*this == 0) {
    return 0;
  }
  return 1;
  return 0;
}
void BigInteger::Negate() {
  if (*this != 0) {
    sign_ = !sign_;
  }
}
void BigInteger::Abs() {
  sign_ = false;
}

BigInteger BigInteger::FromString(const std::string& str, const int& base) {
  int digit = 0;
  BigInteger number;
  //
  // if (base < 2 || base > 36) {
  //   throw std::logic_error("Invalid base");
  // }
  // for (int i = 0; i < str.length(); ++i) {
  //   if (str[i] >= '0' && str[i] <= '9') {
  //     digit = str[i] - '0';
  //   } else if (str[i] >= 'a' && str[i] <= 'z') {
  //     digit = str[i] - 'a' + 10;
  //   } else if (!(i == 0 && str[i] == '-')) {
  //     number = BigInteger();
  //     throw std::runtime_error("Invalid symbol at index "
  //                                  + std::to_string(i) + '\n');
  //   }
  //   if (digit < base) {
  //     number = number * base + digit;
  //   } else {
  //     throw std::runtime_error("Invalid symbol at index "
  //                                  + std::to_string(i) + '\n');
  //   }
  // }
  // if (str[0] == '-' && number != 0) {
  //   number.Negate();
  // }
  return number;
}
std::string BigInteger::ToString(const int& base) const {
  std::string number;
  // if (base < 2 || base > 36) {
  //   throw std::logic_error("Invalid base");
  // }
  // BigInteger this_number = *this;
  // if (sign_) {
  //   this_number.Negate();
  // }
  // if (this_number == 0) {
  //   return "0";
  // }
  // char digit;
  // while (this_number > 0) {
  //   digit = this_number % base;
  //   this_number /= base;
  //   if (digit >= 0 && digit <= 9) {
  //     digit += '0';
  //   }
  //   if (digit >= 10 && digit <= 36) {
  //     digit += 'a' - 10;
  //   }
  //   number = digit + number;
  // }
  // if (sign_) {
  //   number = '-' + number;
  // }
  return number;
}

bool BigInteger::operator==(const BigInteger& eq_number) const {
  if (this->sign_ != eq_number.sign_) {
    return false;
  }
  int size1 = this->big_number_.size();
  int size2 = eq_number.big_number_.size();
  if (size1 == size2) {
    for (int i = size1 - 1; i >= 0; --i) {
      if (this->big_number_[i] != eq_number.big_number_[i]) {
        return false;
      }
    }
    return true;
  } else {
    return false;
  }
}
bool BigInteger::operator==(const int64_t& eq_number) const {
  BigInteger eq_big_number(eq_number);
  return *this == eq_big_number;
}
bool operator==(const int64_t& eq_number, const BigInteger& eq_big_number) {
  BigInteger eq_big_number2(eq_number);
  return eq_big_number == eq_big_number2;
}

bool BigInteger::operator!=(const BigInteger& not_eq_number) const {
  return !(*this == not_eq_number);
}
bool BigInteger::operator!=(const int64_t& not_eq_number) const {
  return !(*this == not_eq_number);
}
bool operator!=(const int64_t& not_eq_number,
                const BigInteger& not_eq_big_number) {
  return !(not_eq_number == not_eq_big_number);
}

bool BigInteger::operator<(const BigInteger& less_number) const {
  if (sign_ && !less_number.sign_) {
    return true;
  }
  if (!sign_ && less_number.sign_) {
    return false;
  }
  if (big_number_.size() == less_number.big_number_.size()) {
    for (int i = 0; i < big_number_.size(); ++i) {
      if (big_number_[i] < less_number.big_number_[i]) {
        return !sign_;
      }
      if (big_number_[i] > less_number.big_number_[i]) {
        return sign_;
      }
    }
  } else {
    if (sign_) {
      return big_number_.size() > less_number.big_number_.size();
    } else {
      return big_number_.size() < less_number.big_number_.size();
    }
  }
  return false;
}
bool BigInteger::operator<(const int64_t& less_number) const {
  BigInteger number(less_number);
  return *this < number;
}
bool operator<(const int64_t& less_number, const BigInteger& less_big_number) {
  BigInteger number(less_number);
  return less_number < less_big_number;
}

bool BigInteger::operator>(const BigInteger& bigger_number) const {
  if (sign_ && !bigger_number.sign_) {
    return false;
  }
  if (!sign_ && bigger_number.sign_) {
    return true;
  }
  if (big_number_.size() == bigger_number.big_number_.size()) {
    for (int i = 0; i < big_number_.size(); ++i) {
      if (big_number_[i] > bigger_number.big_number_[i]) {
        return !sign_;
      }
      if (big_number_[i] < bigger_number.big_number_[i]) {
        return sign_;
      }
    }
  } else {
    if (sign_) {
      return big_number_.size() < bigger_number.big_number_.size();
    } else {
      return big_number_.size() > bigger_number.big_number_.size();
    }
  }
  return false;

  // bool result = false;
  // if (!this->sign_ && bigger_number.sign_) {
  //   return true;
  // }
  // if (this->sign_ && !bigger_number.sign_) {
  //   return false;
  // }
  // if (*this == bigger_number) {
  //   return false;
  // }
  // int size1 = this->big_number_.size();
  // int size2 = bigger_number.big_number_.size();
  // if (size1 == size2) {
  //   for (int i = size1 - 1; i >= 0; --i) {
  //     if (this->big_number_[i] > bigger_number.big_number_[i]) {
  //       result = true;
  //       break;
  //     } else if (this->big_number_[i] < bigger_number.big_number_[i]) {
  //       result = false;
  //       break;
  //     }
  //   }
  // } else {
  //   result = size1 > size2;
  // }
  // return !this->sign_ == result;
}
bool BigInteger::operator>(const int64_t& bigger_number) const {
  BigInteger number(bigger_number);
  return *this > number;
}
bool operator>(const int64_t& bigger_number,
               const BigInteger& bigger_big_number) {
  BigInteger number(bigger_number);
  return bigger_number > bigger_big_number;
}

bool BigInteger::operator<=(const BigInteger& less_number) const {
  return !(*this > less_number);
}
bool BigInteger::operator<=(const int64_t& less_number) const {
  return !(*this > less_number);
}
bool operator<=(const int64_t& less_number, const BigInteger& less_big_number) {
  return !(less_number > less_big_number);
}

bool BigInteger::operator>=(const BigInteger& bigger_number) const {
  return !(*this < bigger_number);
}
bool BigInteger::operator>=(const int64_t& bigger_number) const {
  return !(*this < bigger_number);
}
bool operator>=(const int64_t& bigger_number,
                const BigInteger& bigger_big_number) {
  return !(bigger_number < bigger_big_number);
}

BigInteger& BigInteger::operator+=(const BigInteger& add) {
  // uint64_t container = 0;
  // if (!(this->sign_ ^ add.sign_)) {
  //   int size1 = this->big_number_.size();
  //   int size2 = add.big_number_.size();
  //   if (size2 > size1) {
  //     this->big_number_.resize(size2, 0);
  //   }
  //   for (int i = 0; i < size2; ++i) {
  //     this->big_number_[i] += add.big_number_[i] + container;
  //     container = 0;
  //     if (this->big_number_[i] >= internal_base) {
  //       container = 1;
  //       this->big_number_[i] -= internal_base;
  //     }
  //   }
  //   if (container == 1) {
  //     this->big_number_.push_back(container);
  //   }
  // } else {
  //   this->Negate();
  //   *this -= add;
  //   this->Negate();
  // }
  return *this;
}
BigInteger& BigInteger::operator+=(const int64_t& add) {
  BigInteger number(add);
  *this += number;
  return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& subtract) {
  // if (*this == 0) {
  //   *this = subtract;
  //   this->Negate();
  //   return *this;
  // }
  // if (!(this->sign_ ^ subtract.sign_)) {
  //   int size1 = this->big_number_.size();
  //   int size2 = subtract.big_number_.size();
  //   if (size2 > size1) {
  //     this->big_number_.resize(size2, 0);
  //   }
  //   for (int i = 0; i < size2; ++i) {
  //     this->big_number_[i] -= subtract.big_number_[i];
  //   }
  //   DeleteExtraZeros(*this);
  //   int new_size = this->big_number_.size();
  //   if (this->big_number_[new_size - 1] < 0) {
  //     this->Negate();
  //     for (int i = 0; i < new_size; ++i) {
  //       this->big_number_[i] = -this->big_number_[i];
  //     }
  //   }
  //   for (int i = 0; i < new_size - 1; ++i) {
  //     if ((i != new_size - 1) && this->big_number_[i] < 0) {
  //       this->big_number_[i] += internal_base;
  //       this->big_number_[i + 1]--;
  //     }
  //   }
  // } else {
  //   this->Negate();
  //   *this += subtract;
  //   this->Negate();
  // }
  return *this;
}
BigInteger& BigInteger::operator-=(const int64_t& subtract) {
  BigInteger number(subtract);
  *this -= number;
  return *this;
}

BigInteger BigInteger::operator+(const BigInteger& add) const {
  BigInteger result(*this);
  result += add;
  return result;
}
BigInteger BigInteger::operator+(const int64_t& add) const {
  BigInteger big_add(add);
  return *this + big_add;
}
BigInteger operator+(const int64_t& add, const BigInteger& big_add) {
  BigInteger big_add2(add);
  return big_add2 + big_add;
}

BigInteger BigInteger::operator-(const BigInteger& add) const {
  BigInteger result(*this);
  result -= add;
  return result;
}
BigInteger BigInteger::operator-(const int64_t& add) const {
  BigInteger big_add(add);
  return *this - big_add;
}
BigInteger operator-(const int64_t& add, const BigInteger& big_add) {
  BigInteger big_add2(add);
  return big_add2 - big_add;
}

BigInteger BigInteger::operator*(const BigInteger& multiply) const {
  BigInteger result;
  // result.sign_ = this->sign_ ^ multiply.sign_;
  // int size1 = this->big_number_.size();
  // int size2 = multiply.big_number_.size();
  // result.big_number_.resize(size1 + size2 - 1, 0);
  // int container = 0;
  // for (int i = 0; i < size2; ++i) {
  //   for (int j = 0; j < size1; ++j) {
  //     result.big_number_[i + j] +=
  //         this->big_number_[j] * multiply.big_number_[i]
  //             + container;
  //     container = 0;
  //     if (result.big_number_[i + j] >= internal_base) {
  //       container = result.big_number_[i + j] / internal_base;
  //       result.big_number_[i + j] %= internal_base;
  //     }
  //   }
  //   if (container != 0 && i != size2 - 1) {
  //     result.big_number_[i + size1] += container;
  //     container = 0;
  //   }
  // }
  // if (container != 0) {
  //   result.big_number_.push_back(container);
  // }
  return result;
}
BigInteger BigInteger::operator*(const int64_t& multiply) const {
  BigInteger big_multiply(multiply);
  return *this * big_multiply;
}
BigInteger operator*(const int64_t& multiply, const BigInteger& big_multiply) {
  BigInteger big_multiply2(multiply);
  return big_multiply2 * big_multiply;
}

void BigInteger::operator*=(const BigInteger& multiply) {
  *this = *this * multiply;
}
void BigInteger::operator*=(const int64_t& multiply) {
  *this = *this * multiply;
}

BigInteger BigInteger::operator/(const int64_t& divide) const {
  BigInteger result;
  // if (divide == 0) {
  //   throw DivisionByZeroError();
  // }
  // if (divide == 2) {
  //   result = *this;
  //   DivideByTwo(result);
  //   return result;
  // }
  // result.sign_ = this->sign_ ^ (divide < 0);
  // int current_divident = 0;
  // for (int i = this->big_number_.size() - 1; i >= 0; --i) {
  //   current_divident =
  //       current_divident * internal_base + this->big_number_[i];
  //   result = result * internal_base + current_divident / divide;
  //   current_divident -= result.big_number_[0] * divide;
  // }
  // DeleteExtraZeros(result);
  return result;
}
BigInteger BigInteger::operator/(const BigInteger& divide) const {
  BigInteger left;
  // if (*this == 0) {
  //   return BigInteger();
  // }
  // if (divide == 2) {
  //   left = *this;
  //   DivideByTwo(left);
  //   return left;
  // }
  // if (divide == 0) {
  //   throw DivisionByZeroError();
  // }
  // BigInteger numerator = *this;
  // BigInteger divisor = divide;
  // numerator.Abs();
  // divisor.Abs();
  // BigInteger right = numerator;
  // while (left < (right - 1)) {
  //   if (divisor == 1) {
  //     left = numerator;
  //     break;
  //   }
  //   BigInteger middle = (right - left) / 2 + left;
  //   if (numerator < (middle * divisor)) {
  //     right = middle;
  //   } else {
  //     left = middle;
  //     if (numerator == (middle * divisor)) {
  //       break;
  //     }
  //   }
  // }
  // left.sign_ = this->sign_ ^ divide.sign_;
  return left;
}
BigInteger operator/(const int64_t& divide, const BigInteger& big_divide) {
  BigInteger big_multiply2(divide);
  return big_multiply2 / big_divide;
}

BigInteger& BigInteger::DivideByTwo(BigInteger& number) {
  bool container = false;
  for (int i = number.big_number_.size() - 1; i >= 0; --i) {
    if (container) {
      number.big_number_[i] += internal_base;
    }
    container = (number.big_number_[i] & 1) == 1;
    number.big_number_[i] >>= 1;
  }
  DeleteExtraZeros(number);
  return number;
}

void BigInteger::operator/=(const int64_t& divide) {
  *this = *this / divide;
}
void BigInteger::operator/=(const BigInteger& divide) {
  *this = *this / divide;
}

uint32_t BigInteger::operator%(const uint32_t& modulo) const {
  int32_t result = 0;
  // if (modulo == 0) {
  //   throw DivisionByZeroError();
  // }
  // for (int i = this->big_number_.size() - 1; i >= 0; --i) {
  //   result = result * internal_base + this->big_number_[i];
  //   result = result % modulo;
  // }
  // if (result < 0) {
  //   result = modulo - result;
  // }
  return result;
}

BigInteger BigInteger::operator++() {
  *this += 1;
  return *this;
}
BigInteger BigInteger::operator++(int) {
  BigInteger temp = *this;
  ++*this;
  return temp;
}

BigInteger BigInteger::operator--() {
  *this -= 1;
  return *this;
}
BigInteger BigInteger::operator--(int) {
  BigInteger temp = *this;
  --*this;
  return temp;
}

BigInteger::operator int64_t() const {
  int64_t result = 0;
  // if ((*this > 0x7fffffffffffffff) || (*this < 0x8000000000000000)) {
  //   throw std::runtime_error("int64_t overflow");
  // }
  // for (int i = this->big_number_.size() - 1; i >= 0; --i) {
  //   result = result * internal_base + this->big_number_[i];
  // }
  return result;
}

BigInteger& BigInteger::DeleteExtraZeros(BigInteger& number) {
  // int new_size = 1;
  // for (int i = number.big_number_.size() - 1; i > 0; --i) {
  //   if (number.big_number_[i] != 0) {
  //     new_size = i + 1;
  //     break;
  //   }
  // }
  // if (new_size < number.big_number_.size()) {
  //   number.big_number_.resize(new_size);
  // }
  return number;
}

}  // namespace big_num_arithmetic
