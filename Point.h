#pragma once

#include <cmath>

namespace utec::spatial {

using distance_t = double;

template<typename DataType, std::size_t DIM>
class Point {
 public:
  Point() {
    std::fill_n(_values, DIM, DataType(0));
  }

  Point(const std::array<DataType, DIM> &init_array) : _values(init_array) {}

  bool operator==(const Point<DataType, DIM> &p) const;
  distance_t distance(const Point<DataType, DIM> &p) const;

  DataType get(std::size_t pos) const {
    return _values.at(pos);
  }

  std::size_t size() {
    return DIM;
  }

  enum Direction { NW, NE, SW, SE };
  template<typename Rectangle>
  bool covers(Rectangle region, Direction direction) {
    const int x = 0, y = 1;
    switch (direction) {
      case NW:return region.min().get(x) <= get(x) and region.max().get(y) >= get(y);
      case NE:return region.max().get(x) >= get(x) and region.max().get(y) >= get(y);
      case SW:return region.min().get(x) <= get(x) and region.min().get(y) <= get(y);
      case SE:return region.max().get(x) >= get(x) and region.min().get(y) <= get(y);
    }
  }

 private:
  std::array<DataType, DIM> _values;
};

template<typename DataType, std::size_t DIM>
inline bool Point<DataType, DIM>::operator==(const Point<DataType, DIM> &p) const {
  for (std::size_t I = 0; I < DIM; I++) {
    if (this->_values.at(I) != p._values.at(I))
      return false;
  }
  return true;
}

template<typename DataType, std::size_t DIM>
inline distance_t Point<DataType, DIM>::distance(const Point<DataType, DIM> &p) const {
  double acum = 0.0;

  for (std::size_t I = 0; I < DIM; I++) {
    acum += (this->_values.at(I) - p._values.at(I)) * (this->_values.at(I) - p._values.at(I));
  }
  return sqrt(acum);
}

} //utec