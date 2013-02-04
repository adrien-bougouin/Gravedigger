#include "CPosition.hpp"

CPosition::CPosition(GameObject* parent, int _x, int _y) : CComponent(parent) {
  setX(_x);
  setY(_y);
}

int CPosition::getX() {
  return x;
}

int CPosition::getY() {
  return y;
}

void CPosition::setX(int _x) {
  x = _x;
}

void CPosition::setY(int _y) {
  y = _y;
}
