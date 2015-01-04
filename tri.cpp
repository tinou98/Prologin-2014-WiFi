#include "tri.h"

#include <math.h>
#include <algorithm>
#include "val.h"
#include <droiteutils.h>

#include "coord.h"

tri::tri(const coord _a, const coord _b, const coord _c) {
	a = _a;
	b = _b;
	c = _c;
}

bool tri::operator ==(const tri a) {
	if(this->a == a.a) {
		if(this->b == a.b) {
			if(this->c == a.c) {
				return true;
			}
		} else if(this->b == a.c) {
			if(this->c == a.b) {
				return true;
			}
		}
	} else if(this->a == a.b) {
		if(this->b == a.a) {
			if(this->c == a.c) {
				return true;
			}
		} else if(this->b == a.c) {
			if(this->c == a.a) {
				return true;
			}
		}
	} else if(this->a == a.c) {
		if(this->b == a.a) {
			if(this->c == a.b) {
				return true;
			}
		} else if(this->b == a.b) {
			if(this->c == a.a) {
				return true;
			}
		}
	}

	return false;
}

coord tri::getCentreCercleCirconscrit() {
	// Si on a pas déjà calculé
	if(!centreCercleCirconscrit.isCalc()) {
		// Equation de la droite (AB)
		droiteUtils ab(this->a, this->b);

		// centre est le centre du segment [AB]
		coord centre;
		centre.x = (a.x + b.x) / 2;
		centre.y = (a.y + b.y) / 2;

		// Equation de la droite perpendiculaire a (AB) qui passe par son millieu
		droiteUtils medAB(ab.getVecteurNormale(), centre);


//TODO : Error Med BC for : (0, -1) et (4, 0)

		// Equation de la droite (BC)
		droiteUtils bc(this->b, this->c);

		// centre est le centre du segment [BC]
		centre.x = (b.x + c.x) / 2;
		centre.y = (b.y + c.y) / 2;

		// Equation de la droite perpendiculaire a (BC) qui passe par son millieu
		droiteUtils medBC(bc.getVecteurNormale(), centre);


		// On définie la valeur
		centreCercleCirconscrit.setVal(
										medAB.solve(medBC)
									  );

		//std::cerr << "Tmp : " << medAB << "\t" << medBC << std::endl;
		//std::cerr << "Vect dir : " << medAB.getVecteurDirecteur() << "\t" << medBC.getVecteurDirecteur() << std::endl;

		//std::cerr << "Calcule de la valeur du centre : " << medAB.solve(medBC) << std::endl;
	}

	return centreCercleCirconscrit.getVal();
}

double tri::getRayonCercleCirconscrit() {
	// Si on a pas déjà calculé
	if(!rayonCercleCirconscrit.isCalc()) {
		coord d = this->getCentreCercleCirconscrit();

		double r = sqrt(pow(d.x - this->a.x, 2) + pow(d.y - this->a.y, 2));

		// On définie la valeur
		rayonCercleCirconscrit.setVal(r);
		//std::cerr << "Calcule de la valeur du rayon : " << r << std::endl;
	}

	return rayonCercleCirconscrit.getVal();
}

double tri::ab() {
	// Si on a pas déjà calculé
	if(!abVal.isCalc()) {

		// On définie la valeur
		abVal.setVal(a.dist(b));
	}

	return abVal.getVal();
}

double tri::bc() {
	// Si on a pas déjà calculé
	if(!bcVal.isCalc()) {

		// On définie la valeur
		bcVal.setVal(b.dist(c));
	}

	return bcVal.getVal();
}

double tri::ac() {
	// Si on a pas déjà calculé
	if(!acVal.isCalc()) {

		// On définie la valeur
		acVal.setVal(a.dist(c));
	}

	return acVal.getVal();
}

double tri::getPlusGrandCote() {
	// Si on a pas déjà calculé
	if(!plusGrandCote.isCalc()) {
		// On définie la valeur
		plusGrandCote.setVal(std::max(std::max(ab(), bc()), ac()));
	}

	return plusGrandCote.getVal();
}

bool operator<(tri a, tri b) {
	return a.getRayonCercleCirconscrit() < b.getRayonCercleCirconscrit();
}

