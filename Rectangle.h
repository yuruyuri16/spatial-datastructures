#pragma once

namespace utec {
namespace spatial {

template<typename Point>
class Rectangle {
 public:
  Rectangle(Point min, Point max) : _min(min), _max(max) {}

  bool contains(Point point) {
    const int x = 0, y = 1;
    return point.get(x) >= _min.get(x) and
        point.get(x) <= _max.get(x) and
        point.get(y) >= _min.get(y) and
        point.get(y) <= _max.get(y);
  }

 private:
  Point _min;
  Point _max;
};

} //spatial
} //utec