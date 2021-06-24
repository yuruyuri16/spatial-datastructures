#include "QuadTree.h"
#include <memory>
#include <iostream>
#include <vector>

namespace utec::spatial {

template<typename Node, typename Rectangle, typename Point>
QuadTree<Node, Rectangle, Point>::QuadTree() {
  this->root = nullptr;
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::insert(Point new_point) {
  std::shared_ptr<Node> &target = search(new_point, this->root);
  if (target == nullptr) {
    target = std::make_shared<Node>(new_point);
  }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node> &QuadTree<Node, Rectangle, Point>::search(Point target, std::shared_ptr<Node> &node) {
  if (node == nullptr or node->get_point() == target) return node;

  auto cur_point = node->get_point();

  const int x = 0, y = 1;

  if (target.get(x) < cur_point.get(x)) {
    if (target.get(y) > cur_point.get(y))
      return search(target, node->NW());
    else
      return search(target, node->SW());
  } else {
    if (target.get(y) > cur_point.get(y))
      return search(target, node->NE());
    else
      return search(target, node->SE());
  }
}

template<typename Node, typename Rectangle, typename Point>
std::shared_ptr<Node> QuadTree<Node, Rectangle, Point>::search(Point target) {
  return search(target, this->root);
}

template<typename Node, typename Rectangle, typename Point>
void QuadTree<Node, Rectangle, Point>::range(Rectangle region,
                                             std::shared_ptr<Node> &node,
                                             std::vector<Point> &points) {
  if (node == nullptr) return;
  auto cur_point = node->get_point();
  if (region.contains(cur_point)) points.push_back(cur_point);

  range(region, node->NW(), points);
  range(region, node->NE(), points);
  range(region, node->SW(), points);
  range(region, node->SE(), points);
}

template<typename Node, typename Rectangle, typename Point>
std::vector<Point> QuadTree<Node, Rectangle, Point>::range(Rectangle region) {
  std::vector<Point> points;
  range(region, this->root, points);
  return points;
}

template<typename Node, typename Rectangle, typename Point>
Point QuadTree<Node, Rectangle, Point>::nearest_neighbor(Point reference) {
  return Point({0});
}

} //utec
