#include "vecteur.h"

#include <math.h>

vecteur::vecteur() {

}

vecteur::vecteur(const vecteur &old) {
	this->x = old.x;
	this->y = old.y;
}

vecteur::vecteur(const int &x, const int &y) : x(x), y(y) {}

double vecteur::norme() {
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

void vecteur::normalize() {

}

vecteur& vecteur::operator+=(vecteur const& a) {
	this->x += a.x;
	this->y += a.y;

	return *this;
}

vecteur operator+(vecteur const& a, vecteur const& b) {
	vecteur copie(a);   //On utilise le constructeur de copie
	copie += b;       //On appelle la méthode d'addition qui modifie l'objet `copie`
	return copie;     //Et on renvoie le résultat. Ni a ni b n'ont changé.
}

bool operator==(const vecteur& lhs, const vecteur& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::ostream& operator<<(std::ostream& os, const vecteur& c) {
	os << "(" << c.x << ";" << c.y << ")";
	return os;
}
