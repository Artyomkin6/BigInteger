//
// Created by artyom on 18.10.2019.
//

#ifndef BIG_INTEGER_H_
#define BIG_INTEGER_H_

#include <cstdint>
#include <vector>
#include <string>
#include <stdexcept>

namespace big_num_arithmetic {

struct DivisionByZeroError : std::exception{};

class BigInteger {
 public:
  static int32_t internal_base;

  BigInteger();
  explicit BigInteger(int64_t new_number);
  BigInteger(const BigInteger&) = default;

  int Sign() const;
  void Negate();
  void Abs();

  static BigInteger FromString(const std::string&, const int& base);
  std::string ToString(const int& base) const;

  bool operator==(const BigInteger&) const;
  bool operator==(const int64_t&) const;
  friend bool operator==(const int64_t&, const BigInteger&);

  bool operator!=(const BigInteger&) const;
  bool operator!=(const int64_t&) const;
  friend bool operator!=(const int64_t&, const BigInteger&);

  bool operator<(const BigInteger&) const;
  bool operator<(const int64_t&) const;
  friend bool operator<(const int64_t&, const BigInteger&);

  bool operator>(const BigInteger&) const;
  bool operator>(const int64_t&) const;
  friend bool operator>(const int64_t&, const BigInteger&);

  bool operator<=(const BigInteger&) const;
  bool operator<=(const int64_t&) const;
  friend bool operator<=(const int64_t&, const BigInteger&);

  bool operator>=(const BigInteger&) const;
  bool operator>=(const int64_t&) const;
  friend bool operator>=(const int64_t&, const BigInteger&);

  BigInteger& operator+=(const BigInteger&);
  BigInteger& operator+=(const int64_t&);

  BigInteger& operator-=(const BigInteger&);
  BigInteger& operator-=(const int64_t&);

  void operator*=(const BigInteger&);
  void operator*=(const int64_t&);

  void operator/=(const BigInteger&);
  void operator/=(const int64_t&);

  BigInteger operator+(const BigInteger&) const;
  BigInteger operator+(const int64_t&) const;
  friend BigInteger operator+(const int64_t&, const BigInteger&);

  BigInteger operator-(const BigInteger&) const;
  BigInteger operator-(const int64_t&) const;
  friend BigInteger operator-(const int64_t&, const BigInteger&);

  BigInteger operator*(const BigInteger&) const;
  BigInteger operator*(const int64_t&) const;
  friend BigInteger operator*(const int64_t&, const BigInteger&);

  BigInteger operator/(const BigInteger&) const;
  BigInteger operator/(const int64_t&) const;
  friend BigInteger operator/(const int64_t&, const BigInteger&);

  uint32_t operator%(const uint32_t&) const;

  BigInteger operator++();
  BigInteger operator++(int);

  BigInteger operator--();
  BigInteger operator--(int);

  explicit operator int64_t() const;

 private:
  static BigInteger& DivideByTwo(BigInteger&);
  static BigInteger& DeleteExtraZeros(BigInteger&);

  std::vector<int> big_number_;
  bool sign_ = false;
};

}  // namespace big_num_arithmetic

#endif  // BIG_INTEGER_H_
