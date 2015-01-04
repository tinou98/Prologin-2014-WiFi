#ifndef DROITEUTILS_H
#define DROITEUTILS_H


#include "coord.h"
#include "vecteur.h"

/**
 * @brief La classe `droiteUtils` regroupe les outils sur les droites
 */
class droiteUtils {
public:
	/**
	 * @brief Construit une droite de la forme ax + by + c = 0
	 * On peut auusi la creer en connaissant la forme y = mx + p = mx + -1y + p = ax + by + c = 0.
	 * Donc a = m; b = -1; c = p
	 */
	droiteUtils(const double &a, const double &b, const double &c);

	/**
	 * @brief Crée un droite passant par `a` et `b`
	 * @warning `a` et `b` ne doivent pas etre confondu
	 * @throw std::invalid_argument Les point `a` et `b` sont confondus
	 * @param a Premier point de passage
	 * @param b Deuxième point de passage
	 */
	droiteUtils(const coord &a, const coord &b);

	/**
	 * @brief Crée un droite a aprtir de son vecteur directeur et un point
	 * @param v Le vecteur directeur
	 * @param point Le point par lequelle passe la droite.
	 */
	droiteUtils(const vecteur &v, const coord &point);

	/**
	 * @brief Calcule un vecteur directeur
	 * @return Le vecteur directeur de la droite
	 */
	const vecteur getVecteurDirecteur();

	/**
	 * @brief Calcule un vecteur normale
	 * @return Le vecteur normale de la droite
	 */
	const vecteur getVecteurNormale();

	/**
	 * @brief Trouve le point d'intersection des deux droites
	 * @param drt2 La deuxième droite
	 * @return Les coordonné du point d'intersection, (0, 0) si les droites sont confondus, (nan, nan) si il n'y a pas de point d'intersection.
	 */
	coord solve(droiteUtils &drt2);

	/**
	 * @brief Calcule l'ordonné de X
	 * @param L'absisse du point
	 * @return L'ordonné du point (double)
	 */
	double calcForX(double x);
// TODO : calcFoxY() [Bonus]

	/**
	 * @brief Permet d'afficher la formule de la droite.
	 * Forme : ax + by + c = 0
	 * @param c Objet de type droiteUtils a afficher
	 */
	friend std::ostream& operator<<(std::ostream& os, const droiteUtils& d);

	/**
	 * @brief Opérateur d'égalité
	 * @param lhs Left-hand side
	 * @param rhs Right-hand side
	 * @return `true` si les deux paramètre sont égaux
	 */
	friend bool operator==(const droiteUtils& lhs, const droiteUtils& rhs);
private:
	double a;
	double b;
	double c;
};

#endif // DROITEUTILS_H
