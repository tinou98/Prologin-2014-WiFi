#include "coord.h"

#include <math.h>

coord::coord() {}

coord::coord(const coord &old) {
	this->x = old.x;
	this->y = old.y;
}

coord::coord(const double &x, const double &y) : x(x), y(y) {

}

double coord::dist(const coord &b) {
	return sqrt(pow(this->x - b.x, 2) + pow(this->y - b.y, 2));
}

bool operator==(const coord& lhs, const coord& rhs){
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::ostream& operator<<(std::ostream& os, const coord& c) {
	os << "(" << c.x << ";" << c.y << ")";
	return os;
}
