#pragma once

#include "SpatialTreeBase.h"

namespace utec {
namespace spatial {

/**
 * Point QuadTree implementation
 */
template<typename Node, typename Rectangle, typename Point>
class QuadTree : public SpatialTreeBase<Node, Rectangle, Point> {
 private:
  /**
   * Función recursiva de búsqueda.
   *
   * @param target Punto a buscar
   * @param node Nodo actual
   *
   * @return Retorna referencia al Nodo que contiene o podría contener el punto buscado
   */
  std::shared_ptr<Node> &search(Point target, std::shared_ptr<Node> &node);
  void range(Rectangle region, std::shared_ptr<Node> &node, std::vector<Point> &points);

 public:
  QuadTree();
  void insert(Point new_point) override;
  std::shared_ptr<Node> search(Point target) override;
  std::vector<Point> range(Rectangle region) override;
  Point nearest_neighbor(Point reference_point) override;
};

} //spatial
} //utec

#include "QuadTree.inl"