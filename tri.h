#ifndef TRI_H
#define TRI_H

#include "val.h"
#include "coord.h"

/**
 * @brief Cette classe regroupe des fonction sur les triangles.
 */
class tri {
public:
	/**
	 * @brief Crée un nouveau triangle.
	 * @warning L'ordre des paramètre n'a pas d'importance
	 *
	 * @param _a Le premier point de type coord
	 * @param _b Le deuxième point de type coord
	 * @param _c Le troisième point de type coord
	 */
	tri(const coord _a, const coord _b, const coord _c);

	/**
	 * @brief Compare les deux triangles
	 * @param a Triangle a comparer
	 * @return Renvoi `true` si `this` et a ont les trois mêmes points
	 */
	bool operator ==(const tri a);

	/**
	 * @brief Calcule le centre du cercle Circonscrit (si besoin)
	 * @return Un coord contenant les coordonné du cercle Circonscrit
	 */
	coord getCentreCercleCirconscrit();

	/**
	 * @brief Calcule le rayon du cercle Circonscrit a partir de son centre (si besoin)
	 * @see getCentreCercleCirconscrit
	 * @return Un double contenant le rayon du cercle Circonscrit
	 */
	double getRayonCercleCirconscrit();

	/**
	 * @brief Calcule la valeur de [AB]
	 * @return La distance entre a et b
	 * @see coord::dist
	 */
	double ab();

	/**
	 * @brief Calcule la valeur de [BC]
	 * @return La distance entre b et c
	 * @see coord::dist
	 */
	double bc();

	/**
	 * @brief Calcule la valeur de [AC]
	 * @return La distance entre a et c
	 * @see coord::dist
	 */
	double ac();

	/**
	 * @brief Calcule le plus grand coté du triangle (si besoin)
	 * @see ab, bc, ac
	 * @return Un `double` contenant la longueur du plus grand coté
	 */
	double getPlusGrandCote();

	coord a; /**< Les coordonné du premier point (privée) */
	coord b; /**< Les coordonné du deuxième point (privée) */
	coord c; /**< Les coordonné du troisième point (privée) */
private:
	val<coord> centreCercleCirconscrit; /**< Stockage dynamique du centre du Cerlce Circonscrit */
	val<double> rayonCercleCirconscrit; /**< Stockage dynamique du rayon du Cercle Circonscrit */
	val<double> abVal; /**< Stockage dynamique de la longeur [AB] */
	val<double> bcVal; /**< Stockage dynamique de la longeur [BC] */
	val<double> acVal; /**< Stockage dynamique de la longeur [AC] */
	val<double> plusGrandCote; /**< Stockage dynamique du plus grand coté du triangle */
};

bool operator<(tri a, tri b);

#endif // TRI_H
