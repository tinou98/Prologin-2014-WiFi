#ifndef COORD_H
#define COORD_H

#include <iostream>

/**
 * @brief Stocke en 2d les coordonné d'un point
 */
class coord {
public:
	double x; /**< Coordonné sur l'axe X (accéssible en lecture + écriture) */
	double y; /**< Coordonné sur l'axe Y (accéssible en lecture + écriture) */

	/**
	 * @brief Constructeur par défaut
	 */
	coord();

	/**
	 * @brief Constructeur prenant deux paramètres
	 * @param x La coordonné X du point
	 * @param y La coordonné Y du point
	 */
	coord(const double &x, const double &y);

	/**
	 * @brief Constructeur de copie
	 * @param old Objet a copier
	 */
	coord(const coord &old);

	/**
	 * @brief Calcule la distance entre 2 points
	 * La distance entre \f$a = (a_x,a_y)\f$ et \f$b = (b_x,b_y)\f$ est \f$\sqrt{(a_x-b_x)^2+(a_y-b_y)^2}\f$.
	 * @param b \f$b = (x_2,y_2)\f$
	 * @return La distance entre `this` et `b`
	 */
	double dist(const coord &b);

	/**
	 * @brief Permet d'afficher un point.
	 * Forme : (x;y)
	 * @param c Objet de type coord a afficher
	 */
	friend std::ostream& operator<<(std::ostream& os, const coord& c);
};

/**
 * @brief Opérateur d'égalité
 * @param lhs Left-hand side
 * @param rhs Right-hand side
 * @return `true` si les deux paramètre sont égaux
 */
bool operator==(const coord& lhs, const coord& rhs);

#endif // COORD_H
