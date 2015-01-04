#include "droiteutils.h"

#include <stdexcept>
#include <limits>

droiteUtils::droiteUtils(const double &a, const double &b, const double &c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

droiteUtils::droiteUtils(const coord &a, const coord &b) {
	if(a == b) {
		throw std::invalid_argument("Pour créer une droite, les deux points doivent être difféerent");
	}

	if(a.x == b.x) { // Vertical
		// x = (const)
		// 1x + 0y = -c
		// x = -c

		this->a = 1;
		this->b = 0;
		this->c = -a.x;
	} else if(a.y == b.y) { // Horizontale
		// y = (const)
		// 0x + 1y = -c

		this->a = 0;
		this->b = 1;
		this->c = -a.y;
	} else {
		// y = mx + p
		// mx + -1y + p = 0
		// ax + by + p
		this->a = (a.y-b.y) / (a.x-b.x);
		this->b = -1;
		this->c = -this->a * a.x + a.y;
	}
}

droiteUtils::droiteUtils(const vecteur &v, const coord &point) {
	if(v.x == 0) { // Vertical
		// x = (const)
		// 1x + 0y = -c
		// x = -c

		this->a = 1;
		this->b = 0;
		this->c = -point.x;
	} else if(v.y == 0) { // Horizontale
		// y = (const)
		// 0x + 1y = -c

		this->a = 0;
		this->b = 1;
		this->c = -point.y;
	} else {
		// y = mx + p
		// mx + -1y + p = 0
		// ax + by + p
		this->a = v.x / v.y;
		this->b = -1;
		this->c = -this->a * point.x + point.y;
	}
}


const vecteur droiteUtils::getVecteurDirecteur() {
	return vecteur(-this->b, this->a);
}
const vecteur droiteUtils::getVecteurNormale() {
	return vecteur(this->a, this->b);
}

coord droiteUtils::solve(droiteUtils &drt2) {
	if(this->getVecteurDirecteur() == drt2.getVecteurDirecteur()) { // Les droites sont parrallèles
		if(true) // TODO : Les droites sont confondus [Bonus]
			return coord(0, 0);
		else // Elle ne se coupent jamais
			return coord(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
	}

	if(this->a == 0) { // La première est Horizontale
		double y = -this->c / this->b;
		double x = (drt2.b * y + drt2.c) / -drt2.a;

		return coord(x, y);
	} else if(this->b == 0) { // La première est Vertical
		double x = -this->c / this->a;
		double y = (drt2.a * x + drt2.c) / -drt2.b;

		return coord(x, y);
	} else if(drt2.a == 0) { // La Deuxième est Horizontale
		double y = -drt2.c / drt2.b;
		double x = (this->b * y + this->c) / -this->a;

		return coord(x, y);
	} else if(drt2.b == 0) { // La Deuxième est Vertical
		double x = -drt2.c / drt2.a;
		double y = (this->a * x + this->c) / -this->b;

		return coord(x, y);
	} else {
		double x = ((drt2.c/drt2.b) - (this->c/this->b))	/	((this->a/this->b) - (drt2.a/drt2.b));

		return coord(x, this->calcForX(x));
	}
}

double droiteUtils::calcForX(double x) {
	// ax + by + c = 0
	// y = -(ax + c) / b

	return -(this->a*x + this->c) / this->b;
}

bool operator==(const droiteUtils& lhs, const droiteUtils& rhs) {
	return (lhs.a == rhs.a) && (lhs.b == rhs.b) && (lhs.c == rhs.c);
}

std::ostream& operator<<(std::ostream& os, const droiteUtils& d) {
	os << d.a << "x + " << d.b << "y + " << d.c << " = 0";
	return os;
}
