#ifndef SEVEN_H
#define SEVEN_H

#include <cstddef>
#include <initializer_list>
#include <iosfwd>
#include <stdexcept>
#include <string>

class Seven final {
public:
  Seven();
  Seven(const size_t &n, unsigned char defaultVal = 0);
  Seven(const std::initializer_list<unsigned char> &initVals);
  Seven(const std::string &srcStr);
  Seven(const Seven &other);
  Seven(Seven &&other) noexcept;
  Seven &operator=(const Seven &other);
  Seven &operator=(Seven &&other) noexcept;
  ~Seven() noexcept;

  Seven operator+(const Seven &other) const;
  Seven operator-(const Seven &other) const;
  bool operator==(const Seven &other) const;
  bool operator>=(const Seven &other) const;

  friend std::ostream &operator<<(std::ostream &os, const Seven &f);

private:
  unsigned char *data;
  size_t size;
};

#endif // SEVEN_H